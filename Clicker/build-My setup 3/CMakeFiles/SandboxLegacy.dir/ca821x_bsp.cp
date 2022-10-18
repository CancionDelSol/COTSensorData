#line 1 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_bsp.c"
#line 1 "ca821x_bsp.h"
#line 4 "ca821x_bsp.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdbool.h"



typedef char _Bool;
#line 5 "ca821x_bsp.h"
#line 12 "ca821x_bsp.h"
void ca821x_bsp_reset_low();
#line 21 "ca821x_bsp.h"
void ca821x_bsp_reset_high();
#line 30 "ca821x_bsp.h"
void ca821x_bsp_cs_low();
#line 39 "ca821x_bsp.h"
void ca821x_bsp_cs_high();
#line 48 "ca821x_bsp.h"
_Bool  ca821x_bsp_irq_sense();
#line 2 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_bsp.c"

extern sfr sbit CA821X_RF_IRQ;
extern sfr sbit CA821X_RF_CS;
extern sfr sbit CA821X_RF_RST;
#line 10 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_bsp.c"
void ca821x_bsp_reset_low()
{
    CA821X_RF_RST = 0;
}
#line 18 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_bsp.c"
void ca821x_bsp_reset_high()
{
    CA821X_RF_RST = 1;
}
#line 26 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_bsp.c"
void ca821x_bsp_cs_low()
{
    CA821X_RF_CS = 0;
}
#line 34 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_bsp.c"
void ca821x_bsp_cs_high()
{
    CA821X_RF_CS = 1;
}
#line 42 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_bsp.c"
_Bool  ca821x_bsp_irq_sense()
{
    if (CA821X_RF_IRQ == 1)
    {
        return  1 ;
    }

    return  0 ;
}
