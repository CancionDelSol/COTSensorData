#include "mac_ca821x.h"

#include "ca821x_spi.h"
#include "ca821x_bsp.h"

#include "log.h"

static uint8_t _msdu_handle;

void fastBlinkLEDTwo(int times);

extern sfr sbit MAC_CA821X_RST;

/*
 * Public functions
 ******************************************************************************/

/*
 ******************************************************************************/
uint8_t mac_init()
{
    _msdu_handle = 0;

    ca821x_bsp_cs_high();
    ca821x_bsp_reset_low();

    ca821x_spi_init(SPI2_Read);
    ca821x_irq_init();

    return mac_reset();
}


/*
 ******************************************************************************/
uint8_t mac_reset()
{
    bool is_timeout;
    MAC_Message_t mac_message;
    uint8_t status;
    uint8_t chipid[2];
    uint8_t attlen;

    ca821x_bsp_reset_low();
    Delay_ms(10);
    ca821x_bsp_reset_high();

    is_timeout = ca821x_irq_wait(TIMEOUT_MS(10));
    if (is_timeout)
    {
        LOG_ERROR("CA-821X connection timed out, check hardware.");
        return 1;
    }

    status = ca821x_spi_receive((uint8_t*)&mac_message);

    if (mac_message.CommandId != SPI_HWME_WAKEUP_INDICATION)
    {
        LOG_ERROR("Instead of wakeup indication, check status.");
        return 1;
    }

    if (mac_message.PData.HWMEWakeupInd.WakeUpCondition != HWME_WAKEUP_POWERUP)
    {
        LOG_ERROR("CA-821X wakeup condition not power-up, check status");
        return 1;
    }

    // Delay_ms(10);
    if(TDME_ChipInit(NULL))
    {
        LOG_ERROR("CA-821X initialisation failed");
        return 1;
    }

    if(HWME_GET_request_sync(HWME_CHIPID, &attlen, chipid,NULL))
    {
        LOG_ERROR("ID Failed");
    }
    else
    {
        status = 0;
        // MAC_Workarounds for V1.1
        if((chipid[0] == 1) && (chipid[1] == 1))
            MAC_Workarounds = 1;
        else
            MAC_Workarounds = 0;
        // MAC_MPW for V0.x
        if(chipid[0] == 0)
            MAC_MPW = 1;
        else
            MAC_MPW = 0;
    }
    
    return status;
}


/*
 ******************************************************************************/
uint8_t mac_send(
    uint8_t *lladdr_dst,
    uint8_t *msdu,
    uint16_t msdu_length
)
{
    MacAddr_t dst_addr;
    uint8_t status;

    memcpy(&dst_addr.IEEEAddress[0], lladdr_dst, 8);

    status = MCPS_DATA_request(
        MAC_MODE_LONG_ADDR, // SrcAddrMode
        MAC_MODE_LONG_ADDR, // DstAddrMode
        0xffff,             // DstPANId
        &dst_addr,          // DstAddr
        msdu_length,        // msduLength
        msdu,               // msdu
        _msdu_handle++,     // msduHandle
        0x00,               // TxOptions
        NULL,               // pSecurity
        NULL
    );

    return status;
}

/*
 ******************************************************************************/
uint8_t mac_process()
{
    MAC_Message_t mac_message;

    if (ca821x_irq_is_pending())
    {
        int rec = ca821x_spi_receive((uint8_t*)&mac_message);
        
        fastBlinkLEDTwo(rec);
        
        ca821x_downstream_dispatch(
            (uint8_t*)&mac_message, 
            mac_message.Length + 2
        );
        
        // Do not call mac_reset
        //  This is a kludgy work-around
        //  but seems to solve the issue
        //  related to only being able to
        //  receive one message
        // mac_reset();
    }
    
    return 0;
}


/*
 ******************************************************************************/
uint8_t mac_set_addr(uint8_t *addr)
{
    uint8_t status;

    status = MLME_SET_request_sync(
        nsIEEEAddress,
        0,
        8,
        (void*)addr,
        NULL
    );

    return status;
}


/*
 ******************************************************************************/
uint8_t mac_get_addr(uint8_t *addr)
{
    uint8_t status;
    uint8_t pib_length;
    uint8_t pib_value[16];

    status = MLME_GET_request_sync(
        nsIEEEAddress,
        0,
        &pib_length,
        (uint8_t*)pib_value,
        NULL
    );

    memcpy(addr, pib_value, pib_length);

    return status;
}
