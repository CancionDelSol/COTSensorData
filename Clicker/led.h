#ifndef LED_H
#define LED_H

#define ENABLE_LEDS true

void setLEDOneHigh() {
        RB1_bit = 1;
}
void setLEDTwoHigh() {
        RB2_bit = 1;
}
void setLEDOneLow() {
        RB1_bit = 0;
}
void setLEDTwoLow() {
        RB2_bit = 0;
}

void blinkLEDOne(int count) {
    if (!ENABLE_LEDS) return;
    for (int i = 0; i < count; i++) {
        setLEDOneHigh();
        Delay_ms(250);
        setLEDOneLow();
        Delay_ms(250);
    }
}

void fastBlinkLEDOne(int count) {
    if (!ENABLE_LEDS) return;
    for (int i = 0; i < count; i++) {
        setLEDOneHigh();
        Delay_ms(100);
        setLEDOneLow();
        Delay_ms(100);
    }
}

void blinkLEDTwo(int count) {
    if (!ENABLE_LEDS) return;
    for (int i = 0; i < count; i++) {
        setLEDTwoHigh();
        Delay_ms(250);
        setLEDTwoLow();
        Delay_ms(250);
    }
}

void fastBlinkLEDTwo(int count) {
    if (!ENABLE_LEDS) return;
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
