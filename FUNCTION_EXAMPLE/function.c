// Name:            Trevor Labat
// Date:            6/12/2025
// Assignment:      Lab 2
// Youtube:         https://youtu.be/y-bsRtsbg3k
// 
// Program info:
// This program controls a red and green LED to blink in a specific pattern.

#include <msp430.h>
#include <stdbool.h>

static inline void setGreenLed(bool enable){
    P1OUT = enable ? P1OUT | BIT0 : P1OUT & ~BIT0;
}
static inline void setRedLed(bool enable){
    P1OUT = enable ? P1OUT | BIT6 : P1OUT & ~BIT6;
}
static inline void setBothLed(bool enable){
    P1OUT = enable ? P1OUT | 0x41 : P1OUT & 0xBE;
}
static inline bool isButtonPressed(){
    return (P1IN & BIT3) == 0x00;
}
void init(){
    WDTCTL = 0x5A80;
    P1DIR = ~BIT3;
    P1REN = BIT3;
    P1OUT = BIT3;
}
int main(){
    init();
    int countVal = 0;

    while(1){
        if(isButtonPressed()){
            __delay_cycles(500000); //debounce
            countVal++;
            switch(countVal){
                case 1:
                    setGreenLed(false);
                    setRedLed(true);
                    break;
                case 2:
                    setGreenLed(true);
                    setRedLed(false);
                    break;
                case 3:
                    setBothLed(true);
                    countVal = 0;
                    break; 
            }
        }
    }
}
