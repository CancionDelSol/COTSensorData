/*
 * File to assist with organizing some portions of the code
 */
#ifndef UTILS_H
#define UTILS_H

#include "mac_ca821x.h"
#include "mac_messages.h"
#include "ca821x_api.h"
#include "led.h"

/************** Transmitter and Receiver Flags ****************************************/
//#define APP_TRANSMITTER 1
#ifndef APP_TRANSMITTER // This represents the server module (Power monitered)
#define APP_RECIEVER 1  // This represents the client module (Connected to ESP)
#endif
/**************************************************************************************/

#define PIN_DIR_IN (1)
#define PIN_DIR_OUT (0)

// Encryption algorithm used
// Uncomment to switch, only
// one should be used at a time
#include "enc_supp.h"
#include "log.h"

/*
 * CA821 API
 */
sbit CA821X_RF_RST at LATE2_bit;
sbit CA821X_RF_CS at LATE3_bit;
sbit CA821X_RF_IRQ at RD1_bit;

sbit T1 at RE7_bit;

sbit CA821X_RF_RST_DIR at TRISE2_bit;
sbit CA821X_RF_CS_DIR at TRISE3_bit;
sbit CA821X_RF_IRQ_DIR at TRISD1_bit;

sbit T1_DIR at TRISE7_bit;


// Sending a message back to the ESP32 module
//  with proper formatting
void SendMessageOverUART(char* buffer, int len);

/*
 * Initialize interrupts
 */
static void irq_init( void )
{
    INT1IP0_bit = 1;
    INT1IP1_bit = 1;
    INT1IP2_bit = 1;
    INT1EP_bit = 0;
    INT1IF_bit = 0;
    INT1IE_bit = 1;

    EnableInterrupts();
}

/*
 * Initialize general gpio
 *  this includes peripheral pin
 *  mapping the UART, Radio interrupt,
 *  and Radio Serial peripheral Interface
 */
static void gpio_init( void )
{
    // Selects all pins as digital.
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    ANSELF = 0;
    ANSELG = 0;

    // UART pin mapping for LOG.
    PPS_Mapping(_RPF5, _INPUT, _U3RX);
    PPS_Mapping(_RPF4, _OUTPUT, _U3TX);

    // RF-SPI pin mapping.
    PPS_Mapping( _RPG7, _INPUT, _SDI2);
    PPS_Mapping( _RPG8, _OUTPUT, _SDO2);
    
    // RF-IRQ pin mapping. 
    PPS_Mapping( _RPD1, _INPUT, _INT1);

    CA821X_RF_RST_DIR = PIN_DIR_OUT;
    CA821X_RF_CS_DIR = PIN_DIR_OUT;

    CA821X_RF_IRQ_DIR = PIN_DIR_IN;

    T1_DIR = PIN_DIR_IN;
}

static void mac_rx_on( void )
{
    uint8_t value;
    value = 0x01;
    
    MLME_SET_request_sync(
        macRxOnWhenIdle,        // PIBAttribute
        0,                      // PIBAttributeIndex
        1,                      // PIBAttributeLength,
        (const void*)&value,    // pPIBAttributeValue,
        NULL                    // pDeviceRef
    );
}
static void mac_set_pan_id( void )
{
    uint8_t pan_id[2];
    
    pan_id[0] = 0xFF;
    pan_id[1] = 0xFF;

    MLME_SET_request_sync(
        macPANId,               // PIBAttribute
        0,                      // PIBAttributeIndex
        2,                      // PIBAttributeLength,
        (const void*)pan_id,    // pPIBAttributeValue,
        NULL                    // pDeviceRef
    );
}

/* Messaging */
static char message[] = "DEADBEEF";

// MAC addresses
#define RECEIVER_MAC_ADDR 0xC0, 0xB0, 0xA0, 0xFF, 0xFE, 0x00, 0x00, 0x01
#define TRANSMITTER_MAC_ADDR 0xC0, 0xB0, 0xA0, 0xFF, 0xFE, 0xA0, 0xB0, 0xC0

int handle_mcps_data_confirm(struct MCPS_DATA_confirm_pset *params)
{   
    char msg[] = "Message sent.";
    SendMessageOverUART(msg, strlen(msg));
    
    fastBlinkLEDTwo(3);
    
    return 0;
}

#if defined(APP_TRANSMITTER)
#define START_MSG "Transmitter is on."

static uint8_t ieee_address[8] = {
    TRANSMITTER_MAC_ADDR
};

static uint8_t dst_address[8] = {
    RECEIVER_MAC_ADDR
};

static uint8_t send_message( void )
{
    uint8_t status;
    char str_buffer[16 + sizeof(message)];

    strcpy(str_buffer, message);
    strcat(str_buffer, " Hello");
    strcat(str_buffer, ")");


    status = mac_send(dst_address, str_buffer, strlen(str_buffer) + 1);

    return status;
}
#endif

#if defined(APP_RECIEVER)
static uint8_t ieee_address[8] = {
    RECEIVER_MAC_ADDR
};


#endif
int handle_mcps_data_indication(struct MCPS_DATA_indication_pset *params)
{
    
#if defined(ORIG_CODE)
    // MAX_DATA_SIZE size maximum
    int messageLength = params->MsduLength;
    
    LOG_RULE();
    LOG_INFO("Message received.");
    LOG_INFO(params->Msdu);

    LOG_RULE();
    
    return 0;
#else
    
    // Handle incoming message
    unsigned char output[OA_BUFFER_SIZE];
    
#if defined(APP_TRANSMITTER)
    // Encrypt message and transmit to the Receiver board
    Encrypt(params->Msdu, output);
    mac_send(dst_address, output, strlen(output) + 1);
    
#elif defined(APP_RECIEVER)
    // Send incoming message back via UART to the ESP32 Module
    fastBlinkLEDOne(5);
    //Decrypt(params->Msdu, output);
    //SendMessageOverUART(output, strlen(output));
    
#endif

#endif
    //Delay_ms(250);
    return 0;
}

int system_init( void )
{
    struct ca821x_api_callbacks api_cb;
    uint8_t status;

    gpio_init();

    LOG_INIT(38400);
    
    SPI2_Init_Advanced(
        _SPI_MASTER,
        _SPI_8_BIT,
        32,
        _SPI_SS_DISABLE,
        _SPI_DATA_SAMPLE_END,
        _SPI_CLK_IDLE_HIGH,
        _SPI_IDLE_2_ACTIVE
    );

    status = mac_init();
    if (status)
    {
        LOG_INFO("MAC initialization failed.");
        while (1) {
            fastBlinkLEDOne(1);
        }
        return status;
    }

    irq_init();

#if APP_RECIEVER
    api_cb.MCPS_DATA_indication = handle_mcps_data_indication;
#endif

//#if APP_TRANSMITTER
    api_cb.MCPS_DATA_confirm = handle_mcps_data_confirm;
//#endif

    ca821x_register_callbacks(&api_cb);
    
    return 0;
}

/* UART Communication with ESP32 */
void SendMsgToESP(unsigned char* msg) {
    LOG_SERIAL_RESPONSE(msg);
}

#endif
