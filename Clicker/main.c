#include "utils.h"

#define ORIG_CODE 1

#include "log.h"
#include <stdio.h>

void main() 
{
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

    while (1)
    {

#if defined(APP_TRANSMITTER)
        if(Button(&PORTE, 7, 100, 0))
        {
            int res = mac_send(rec_add, buffer, strlen(buffer) + 1);
            switch(res) {
                case MAC_SUCCESS:
                    LOG_INFO("Message Sent");
                    break;
                case MAC_ERROR:
                    LOG_INFO("Message Send failure");
                    break;
                case MAC_CANCELLED:
                    LOG_INFO("Message cancelled");
                    break;
                default:
                    LOG_INFO("Mac status other");
                    break;
            }
        }
#else
        // Read input from ESP32 module
        unsigned char buffer[8];
        
        if (UART3_Data_Ready()) {
            UART3_Read_Text(buffer, "/r/n", 1);
        }
        
        uint8_t rec_add[8] = { TRANSMITTER_MAC_ADDR };
        mac_send(rec_add, buffer, strlen(buffer) + 1);
#endif

       mac_process();
    }
}

/*
 ******************************************************************************/
void RF_ISR() iv IVT_EXTERNAL_1 ilevel 7 ics ICS_SRS
{
    INT1IF_bit = 0;
    
    //blink(1);

    ca821x_irq_signal();
}
