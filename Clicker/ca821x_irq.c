#include "ca821x_irq.h"

#include "ca821x_bsp.h"

static bool _irq_pending;


/*
 * Public functions
 ******************************************************************************/

/*
 ******************************************************************************/
void ca821x_irq_init()
{
    _irq_pending = false;
}

/*
 ******************************************************************************/
bool ca821x_irq_is_pending()
{
    if (_irq_pending)
    {
        _irq_pending = false;
        return true;
    }

    return false;
}

/*
 ******************************************************************************/
void ca821x_irq_signal()
{
    _irq_pending = true;
}

/*
 ******************************************************************************/
uint8_t ca821x_irq_wait(uint16_t timeout_ms)
{
    uint32_t cnt;
    cnt = timeout_ms * 10;

    while (cnt--)
    {
        if (!ca821x_bsp_irq_sense())
        {
            return false;
        }

        Delay_us(100);
    }

    return true;
}

/*
 ******************************************************************************/
void ca821x_irq_enable()
{
    INT1IF_bit = 0;
    INT1IE_bit = 1;
}

/*
 ******************************************************************************/
void ca821x_irq_disable()
{
    INT1IE_bit = 0;
}

/*
 *************************************************************************EOF**/
