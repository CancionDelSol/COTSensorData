// Setup flags
#define ENC_NONE 1
//#define ENC_AES 1
//#define ENC_DES 1
//#define ENC_ECC 1

#include "utils.h"

//#define ORIG_CODE 1

#define IS_DEBUG false

#include "log.h"
#include <stdio.h>
#include "led.h"

// Method to read from UART3 into a buffer
int ReadUARTIntoBuffer(char* buffer, int max) {
    int len = 0;
    bool msgEnd = false;
    
    while (!msgEnd) {
        if (UART3_Data_Ready()) {
            buffer[len++] = UART3_Read();
        }
        
        if (len >= max)
            break;
        
        if (buffer[len-1] == ' ') 
            break;
        
    }
    
    return len;
}

// Send a message back over UART
// Wraps the message in "<" and ">"
void SendMessageOverUART(char* buffer, int len) {
    UART3_Write('<');
    for (int i = 0; i < len; i++) {
        UART3_Write(buffer[i]);
    }
    UART3_Write('>');
}


void main() 
{
    // Initialize LEDs
    InitLEDs();
    
    // Initialize MAC_821 system
    if (system_init() > 0) {
        fastBlinkLEDTwo(10);
    }
    
    fastBlinkLEDOne(3);
    
    // Set mac address
    mac_set_addr(ieee_address);
    
    #ifdef APP_TRANSMITTER
    mac_set_pan_id();
    #endif
    
    // Receiver address
    uint8_t rec_add[8] = { RECEIVER_MAC_ADDR };
    
    // Transmitter address
    uint8_t trans_add[8] = { TRANSMITTER_MAC_ADDR };
    unsigned char buffer[] = "HELLO";

#if defined(APP_RECIEVER)
    mac_rx_on();
    LOG_INFO("Waiting message...");
#endif
    
    while (1)
    {
        // Seperate debug-only logic
        if (IS_DEBUG) {
            // Grab any input from UART
            unsigned char buffer[64] = { 0 };
            unsigned char output[64] = { 0 };
            unsigned char final[64] = { 0 };
            
            int len = ReadUARTIntoBuffer(buffer, 64);
            
            Encrypt(buffer, output);
            
            Decrypt(output, final);
            
            if (len > 0) {
                SendMessageOverUART(final, len);
            }
            
            // Don't do the normal loop'
            continue;
        }
#if defined(APP_TRANSMITTER)
        if(Button(&PORTE, 7, 100, 0))
        {
            int resp = mac_send(rec_add, buffer, strlen(buffer) + 1);
        }
#else
        // Read input from ESP32 module
//         if (UART3_Data_Ready()) {
//             UART3_Read_Text(buffer, "/r/n", 1);
//             
//             mac_send(rec_add, buffer, strlen(buffer) + 1);
//         }
        
#endif

        //mac_process();

    }
}

/*
 ******************************************************************************/
bool ca821x_bsp_irq_sense();
void RF_ISR() iv IVT_EXTERNAL_1 ilevel 7 ics ICS_SRS
{
    INT1IF_bit = 0;
    
    ca821x_irq_signal();
    
    blinkLEDOne(1);
    
    mac_process();
}
