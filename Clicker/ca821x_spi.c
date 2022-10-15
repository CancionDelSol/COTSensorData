#include "ca821x_spi.h"

#include <stdint.h>

#include "ca821x_api.h"
#include "ca821x_irq.h"
#include "ca821x_bsp.h"



spi_transfer_t _spi_transfer;



/*
 * Function declaration
 ******************************************************************************/
static int _downstream(
    const uint8_t *out_buffer,
    size_t length,
    uint8_t *in_buffer,
    void *device_ref
);

static uint8_t _send(uint8_t *bufffer, size_t length);

static uint8_t _downstream_sync(
    uint8_t *tx_buffer,
    size_t length,
    uint8_t *rx_buffer
);

static uint8_t _downstream_async(
    uint8_t *tx_buffer,
    size_t length
);

/*
 * Public functions
 ******************************************************************************/

/*
 ******************************************************************************/
void ca821x_spi_init(spi_transfer_t spi_transfer)
{
    _spi_transfer = spi_transfer;
    ca821x_api_downstream = _downstream;
}

/*
 ******************************************************************************/
uint8_t ca821x_spi_receive(uint8_t *buffer)
{
    uint8_t i;
    MAC_Message_t *mac_message;
    mac_message = (MAC_Message_t*)buffer;

    ca821x_bsp_cs_low();
    mac_message->CommandId = _spi_transfer( SPI_IDLE );

    if (mac_message->CommandId == SPI_IDLE)
    {
        ca821x_bsp_cs_high();
        return CA821X_SPI_NO_MSG;
    }

    mac_message->Length = _spi_transfer( SPI_IDLE );

    // Check if packet is valid.
    if((mac_message->CommandId & 0x80) || !(mac_message->CommandId & SPI_S2M) ||
         (mac_message->Length == 0x00))
    {
        ca821x_bsp_cs_high();
        return CA821X_SPI_INVALID_PACKET;
    }

    for (i = 0; i < mac_message->Length; i++)
    {
        mac_message->PData.Payload[i] = _spi_transfer( SPI_IDLE );
    }

    ca821x_bsp_cs_high();
    return CA821X_SPI_OK;
}


/*
 * Private functions
 ******************************************************************************/

/*
 ******************************************************************************/
static uint8_t _downstream_sync(
    uint8_t *tx_buffer,
    size_t length,
    uint8_t *rx_buffer
)
{
    uint8_t status;
    bool timeout;

    ca821x_irq_disable();

    status = _send(tx_buffer, length);
    if (status != CA821X_SPI_OK)
    {
        ca821x_irq_enable();
        return status;
    }

    timeout = ca821x_irq_wait(TIMEOUT_MS(5));
    if (timeout)
    {
        ca821x_irq_enable();
        return CA821X_SPI_ERROR;
    }

    status = ca821x_spi_receive(rx_buffer);
    if (status != CA821X_SPI_OK)
    {
        ca821x_irq_enable();
        return status;
    }

    ca821x_irq_enable();
    return CA821X_SPI_OK;
}

/*
 ******************************************************************************/
static uint8_t _downstream_async(
    uint8_t *tx_buffer,
    size_t length
)
{
    uint8_t status;

    ca821x_irq_disable();
    status = _send(tx_buffer, length);
    ca821x_irq_enable();

    return status;
}

/*
 ******************************************************************************/
static int _downstream(
    uint8_t *tx_buffer,
    size_t length,
    uint8_t *rx_buffer,
    void *device_ref
)
{
    uint8_t status;
    MAC_Message_t *mac_message;
    mac_message = (MAC_Message_t*)tx_buffer;

    if ((mac_message->CommandId & SPI_SYN) && rx_buffer)
    {
        status = _downstream_sync(tx_buffer, length, rx_buffer);
    }
    else
    {
        status = _downstream_async(tx_buffer, length);
    }


    ca821x_irq_enable();
    return status;
}

/*
 ******************************************************************************/
static uint8_t _send(uint8_t *buffer, size_t length)
{
    uint8_t rx_byte;
    uint8_t status;
    uint8_t i;
    uint8_t timeout_cnt;

    timeout_cnt = 200;
    rx_byte = SPI_NACK;

    while ((rx_byte == SPI_NACK) && timeout_cnt)
    {
        ca821x_bsp_cs_low();
        for (i = 0; i < length; i++)
        {
            rx_byte = _spi_transfer( buffer[i] );

            if (rx_byte == SPI_NACK)
            {
                i = length;
            }
        }
        ca821x_bsp_cs_high();

        timeout_cnt--;
        Delay_us(10);
    }

    return CA821X_SPI_OK;
}
