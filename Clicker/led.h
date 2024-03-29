#ifndef LED_H
#define LED_H

#define ENABLE_LEDS true

void setLEDOneHigh() {
    if (!ENABLE_LEDS) return;
        RB1_bit = 1;
}
void setLEDTwoHigh() {
    if (!ENABLE_LEDS) return;
        RB2_bit = 1;
}
void setLEDOneLow() {
    if (!ENABLE_LEDS) return;
        RB1_bit = 0;
}
void setLEDTwoLow() {
    if (!ENABLE_LEDS) return;
        RB2_bit = 0;
}

void blinkLEDOne(int count) {
    for (int i = 0; i < count; i++) {
        setLEDOneHigh();
        Delay_ms(250);
        setLEDOneLow();
        Delay_ms(250);
    }
}

void fastBlinkLEDOne(int count) {
    for (int i = 0; i < count; i++) {
        setLEDOneHigh();
        Delay_ms(100);
        setLEDOneLow();
        Delay_ms(100);
    }
}

void blinkLEDTwo(int count) {
    for (int i = 0; i < count; i++) {
        setLEDTwoHigh();
        Delay_ms(250);
        setLEDTwoLow();
        Delay_ms(250);
    }
}

void fastBlinkLEDTwo(int count) {
    for (int i = 0; i < count; i++) {
        setLEDTwoHigh();
        Delay_ms(100);
        setLEDTwoLow();
        Delay_ms(100);
    }
}

void InitLEDs() {
    if (ENABLE_LEDS) {
        LATB = 0;
    
        TRISB = 0;
    }
}

#endif
