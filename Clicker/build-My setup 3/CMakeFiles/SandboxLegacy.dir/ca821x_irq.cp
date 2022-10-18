#line 1 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_irq.c"
#line 1 "ca821x_irq.h"
#line 6 "ca821x_irq.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdbool.h"



typedef char _Bool;
#line 7 "ca821x_irq.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;


typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 8 "ca821x_irq.h"
#line 15 "ca821x_irq.h"
void ca821x_irq_init();
#line 23 "ca821x_irq.h"
_Bool  ca821x_irq_is_pending();
#line 31 "ca821x_irq.h"
void ca821x_irq_signal();
#line 39 "ca821x_irq.h"
uint8_t ca821x_irq_wait(uint16_t timeout_ms);
#line 47 "ca821x_irq.h"
void ca821x_irq_enable();
#line 55 "ca821x_irq.h"
void ca821x_irq_disable();
#line 2 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_irq.c"
#line 3 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_irq.c"
#line 1 "ca821x_bsp.h"
#line 4 "ca821x_bsp.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdbool.h"
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
#line 4 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_irq.c"

static  _Bool  _irq_pending;
#line 14 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_irq.c"
void ca821x_irq_init()
{
    _irq_pending =  0 ;
}
#line 21 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_irq.c"
_Bool  ca821x_irq_is_pending()
{
    if (_irq_pending)
    {
        _irq_pending =  0 ;
        return  1 ;
    }

    return  0 ;
}
#line 34 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_irq.c"
void ca821x_irq_signal()
{
    _irq_pending =  1 ;
}
#line 41 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_irq.c"
uint8_t ca821x_irq_wait(uint16_t timeout_ms)
{
    uint32_t cnt;
    cnt = timeout_ms * 10;

    while (cnt--)
    {
        if (!ca821x_bsp_irq_sense())
        {
            return  0 ;
        }

        Delay_us(100);
    }

    return  1 ;
}
#line 61 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_irq.c"
void ca821x_irq_enable()
{
    INT1IF_bit = 0;
    INT1IE_bit = 1;
}
#line 69 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_irq.c"
void ca821x_irq_disable()
{
    INT1IE_bit = 0;
}
