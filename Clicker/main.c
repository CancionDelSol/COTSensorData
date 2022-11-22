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
    
    // Set mac address
#ifdef APP_TRANSMITTER
    mac_set_addr(mac_trans);
#else
    mac_set_addr(mac_rec);
#endif
    
//#ifdef APP_TRANSMITTER
    mac_set_pan_id();
//#endif
    
//#if defined(APP_RECIEVER)
    mac_rx_on();
//#endif
    
    // Notify ready
    fastBlinkLEDOne(3);
    
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
        
        // If the button is pressed,
        //  send a message to the other board
        // This is only for testing
        if(Button(&PORTE, 7, 100, 0))
        {
#if defined(APP_TRANSMITTER)
            int resp = mac_send(mac_rec, gen_msg, strlen(gen_msg) + 1);
#else
            int resp = mac_send(mac_trans, gen_msg, strlen(gen_msg) + 1);
#endif
        }
        
        // Read input from ESP32 module
        if (UART3_Data_Ready()) {
            char buffer[OA_BUFFER_SIZE];
            UART3_Read_Text(buffer, "/r/n", 1);
            
            mac_send(mac_trans, buffer, strlen(buffer) + 1);
        }
    }
}

/*******************************************************************************/
void RF_ISR() iv IVT_EXTERNAL_1 ilevel 7 ics ICS_SRS
{
    // Reset the interrupt bit
    INT1IF_bit = 0;
    
    // Set is interrupted flag
    ca821x_irq_signal();
    
    // Notify interrupt fired
    blinkLEDOne(1);
    
    // Process MAC
    mac_process();
}
