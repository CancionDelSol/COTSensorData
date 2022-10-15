#include "mac_ca821x.h"
#include "mac_messages.h"
#include "ca821x_api.h"

#include "log.h"
#include <stdio.h>

#define PIN_DIR_IN (1)
#define PIN_DIR_OUT (0)

void blink(int i);
void fastBlink(int i);

sbit CA821X_RF_RST at LATE2_bit;
sbit CA821X_RF_CS at LATE3_bit;
sbit CA821X_RF_IRQ at RD1_bit;

sbit T1 at RE7_bit;

sbit CA821X_RF_RST_DIR at TRISE2_bit;
sbit CA821X_RF_CS_DIR at TRISE3_bit;
sbit CA821X_RF_IRQ_DIR at TRISD1_bit;

sbit T1_DIR at TRISE7_bit;

//#define APP_TRANSMITTER true

#ifndef APP_TRANSMITTER
#define APP_RECIEVER 1
#endif

#if defined(APP_TRANSMITTER)
static char message[] = "Hello 6LoWPAN clicker!";
static uint8_t msg_cnt;
#define START_MSG "Transmitter is on."
#endif

#define RECEIVER_MAC_ADDR 0xC0, 0xB0, 0xA0, 0xFF, 0xFE, 0x00, 0x00, 0x01

#if defined(APP_TRANSMITTER)
#define TRANSMITTER_MAC_ADDR 0xC0, 0xB0, 0xA0, 0xFF, 0xFE, 0xA0, 0xB0, 0xC0
#endif

#if defined(APP_TRANSMITTER)
static uint8_t ieee_address[8] = {
    TRANSMITTER_MAC_ADDR
};

static uint8_t dst_address[8] = {
    RECEIVER_MAC_ADDR
};
#endif

#if defined(APP_RECIEVER)
static uint8_t ieee_address[8] = {
    RECEIVER_MAC_ADDR
};
#endif

/*
 ******************************************************************************/
#if defined(APP_RECIEVER)
int handle_mcps_data_indication(struct MCPS_DATA_indication_pset *params)
{
    // MAX_DATA_SIZE size maximum
    char* message = (char*)params->Msdu;
    int messageLength = params->MsduLength;
    
    LOG_RULE();

    LOG_INFO("Message received.");
    LOG_INFO(params->Msdu);

    LOG_RULE();
    blink(1);
    
    return 0;
}
#endif

/*
 ******************************************************************************/
#if defined(APP_TRANSMITTER)
int handle_mcps_data_confirm(struct MCPS_DATA_confirm_pset *params)
{   
    LOG_INFO("Message sent.");
}
#endif

/*
 ******************************************************************************/
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
 ******************************************************************************/
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
 ******************************************************************************/
void system_init( void )
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
        blink(5);
        return;
    }

    irq_init();

#if APP_RECIEVER
    api_cb.MCPS_DATA_indication = handle_mcps_data_indication;
#endif

#if APP_TRANSMITTER
    api_cb.MCPS_DATA_confirm = handle_mcps_data_confirm;
    msg_cnt = 1;
#endif

    ca821x_register_callbacks(&api_cb);

    LOG_INFO("System initialized.");
}

/*
 ******************************************************************************/
#if APP_TRANSMITTER
static uint8_t send_message( void )
{
    uint8_t status;
    char str_buffer[16 + sizeof(message)];
    char msg_cnt_buffer[8];

    strcpy(str_buffer, message);
    strcat(str_buffer, " (MSG No: ");
    IntToStr(msg_cnt++, msg_cnt_buffer);
    strcat(str_buffer, Ltrim(msg_cnt_buffer));
    strcat(str_buffer, ").");


    status = mac_send(dst_address, str_buffer, strlen(str_buffer) + 1);

    return status;
}
#endif

/*
 ******************************************************************************/
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
 ******************************************************************************/
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
 ******************************************************************************/
void LEDOneHigh() {
    LATB |= 0x3F;       // Turn ON LEDs on PORTB
    LATC = 0xFF;       // Turn ON LEDs on PORTC
    LATD = 0xFF;       // Turn ON LEDs on PORTD
    
}
void LEDOneLow() {
    LATB &= 0xC0;      // Turn OFF LEDs on PORTB
    LATC = 0x00;       // Turn OFF LEDs on PORTC
    LATD = 0x00;       // Turn OFF LEDs on PORTD
    
}

void LEDTwoHigh() {
    LATE = 0xFF;       // Turn ON LEDs on PORTE
    LATF = 0xFF;       // Turn ON LEDs on PORTF
    LATG = 0xFF;       // Turn ON LEDs on PORTG
}

void LEDTwoLow() {
    LATE = 0x00;       // Turn OFF LEDs on PORTE
    LATF = 0x00;       // Turn OFF LEDs on PORTF
    LATG = 0x00;       // Turn OFF LEDs on PORTG
}

void blink(int count) {
    for (int i = 0; i < count; i++) {
        LEDOneHigh();
        LEDTwoHigh();
        Delay_ms(250);
        
        LEDOneLow();
        LEDTwoLow();
        Delay_ms(250);
    }
}
void fastBlink(int count) {
    
    for (int i = 0; i < count; i++) {
        LEDOneHigh();
        LEDTwoHigh();
        Delay_ms(50);
        
        LEDOneLow();
        LEDTwoLow();
        Delay_ms(50);
    }
}
void main() 
{
    TRISB &= 0xC0;       // set direction to be output
    TRISC = 0;           // set direction to be output
    TRISD = 0;           // set direction to be output
    TRISE = 0;           // set direction to be output
    TRISF = 0;           // set direction to be output
    TRISG = 0;           // set direction to be output
    
    LEDOneLow();
    LEDTwoLow();
  
    system_init();

    mac_set_addr(ieee_address);
    mac_set_pan_id();

#if defined(APP_RECIEVER)
    mac_rx_on();
    LOG_INFO("Waiting message...");
#endif

#if defined(APP_TRANSMITTER)
    //mac_send(dst_address, START_MSG, sizeof(START_MSG) + 1);
#endif

    //fastBlink(5);
    
    while (1)
    {

#if defined(APP_TRANSMITTER)
        if(Button(&PORTE, 7, 100, 0))
        {
            if(send_message()) {
                blink(2);
            }
            else {
                blink(1);
            }
        }
#endif

       mac_process();
    }
}

/*
 ******************************************************************************/
void RF_ISR() iv IVT_EXTERNAL_1 ilevel 7 ics ICS_SRS
{
    INT1IF_bit = 0;
    INT1IE_bit = 1;//asdf
    
    //blink(1);

    ca821x_irq_signal();
}
