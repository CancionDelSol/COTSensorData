/*
 * File to assist with organizing some portions of the code
 */
#ifndef UTILS_H
#define UTILS_H

#include "mac_ca821x.h"
#include "mac_messages.h"
#include "ca821x_api.h"
#include "enc_supp.h"
#include "led.h"
#include "__time.h"
#include "stdio.h"

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

// Sending a message back to the ESP32 module
//  with proper formatting
void SendMessageOverUART(char* buffer, int len);

// Time utilities

/*
 * Append the current "unix" time to the end of the buffer
 */
int AppendCurrentTime(char* buffer, int bufferMaxLength) {
    int curStrLen = strlen(buffer);
    if (curStrLen >= bufferMaxLength)
    {
        return 1;
    }
    
    TimeStruct curTime;
    Time_dateToEpoch(&curTime);
    
    long fullTime = curTime.ss + (curTime.mn * 60) + (curTime.hh * 60 * 60) * 1000;
    
    sprintf(buffer+curStrLen, " %d", fullTime);
}

// MAC addresses
#define RECEIVER_MAC_ADDR 0xC0, 0xB0, 0xA0, 0xFF, 0xFE, 0x00, 0x00, 0x01
#define TRANSMITTER_MAC_ADDR 0xC0, 0xB0, 0xA0, 0xFF, 0xFE, 0xA0, 0xB0, 0xC0

/*
 * CA821 SPI and interrupts
 */
sbit CA821X_RF_RST at LATE2_bit;
sbit CA821X_RF_CS at LATE3_bit;
sbit CA821X_RF_IRQ at RD1_bit;

sbit T1 at RE7_bit;

sbit CA821X_RF_RST_DIR at TRISE2_bit;
sbit CA821X_RF_CS_DIR at TRISE3_bit;
sbit CA821X_RF_IRQ_DIR at TRISD1_bit;

sbit T1_DIR at TRISE7_bit;

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

/*
 * Set the PIB attribute for
 *  for message receive enabled
 */
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

/*
 * Set the PIB attribute for pan id
 */
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

/*
 * Use these addresses for the transmitter
 *  and receiver
 */
uint8_t mac_trans[] = { TRANSMITTER_MAC_ADDR };
uint8_t mac_rec[] = { RECEIVER_MAC_ADDR };

/*
 * Callback to handle message outgoing
 *  confirmation
 */
int handle_mcps_data_confirm(struct MCPS_DATA_confirm_pset *params)
{   
    return 0;
}

/*
 * Callback for data incoming event
 *  Transmitter - Encrypt the from-memory message and send back
 *                 to the receiver
 *  Receiver - Decrypt the incoming message and send to the ESP32 module
 *              over UART
 */
int handle_mcps_data_indication(struct MCPS_DATA_indication_pset *params)
{
    #ifdef APP_RECIEVER
    
    #else
    fastBlinkLEDTwo(5);
    #endif
    // Handle incoming message
    unsigned char output[ENC_MSG_BUFFER_SIZE] = { 0 };
    unsigned char oa_msg[OA_BUFFER_SIZE] = { 0 };
    
    // Copy the incoming message to
    //  the outgoing buffer
    sprintf(oa_msg, "%s", params->Msdu);
    
#if defined(APP_TRANSMITTER)
    
    // Encrypt the general message
    Encrypt(gen_msg, output);
    
    // Append the timestamp and send out
    mac_send(mac_rec, output, strlen(oa_msg) + 1);
    
#elif defined(APP_RECIEVER)
    // Decrypt incoming message
    Decrypt(oa_msg, output);
    
    //AppendCurrentTime(oa_msg, OA_BUFFER_SIZE);
    SendMessageOverUART(params->Msdu, strlen(params->Msdu));
    
#endif
    return 0;
}

int handle_mcps_error_indication(struct TDME_ERROR_indication_pset *params) {
    return -1;
}

int handle_mlme_comm_status_indication(struct MLME_COMM_STATUS_indication_pset *params) {
    return 0;
} 

/*
 * General system initialization
 */
int system_init( void )
{
    struct ca821x_api_callbacks api_cb;
    uint8_t status;

    // Initialize GPIO
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

    // Mac status initialization
    status = mac_init();
    if (status)
    {
        LOG_INFO("MAC initialization failed.");
        while (1) {
            fastBlinkLEDOne(1);
        }
        return status;
    }

    // Initialize interrupts
    irq_init();

    // Set the data incoming callback
    api_cb.MCPS_DATA_indication = handle_mcps_data_indication;

    // Set the data confirmed callback
    api_cb.MCPS_DATA_confirm = handle_mcps_data_confirm;
    
    // Set the error handling callback
    api_cb.TDME_ERROR_indication = handle_mcps_error_indication;
    
    // Set the mlme comm status indication callback
    api_cb.MLME_COMM_STATUS_indication = handle_mlme_comm_status_indication;

    // Register callbacks with Cascoda api
    ca821x_register_callbacks(&api_cb);
    
    return 0;
}
#endif
