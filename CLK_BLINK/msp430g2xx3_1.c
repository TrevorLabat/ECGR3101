#include <msp430.h>
#include <stdbool.h>

static inline void setGreenLed(bool enable){
    P1OUT = enable ? P1OUT | BIT0 : P1OUT & ~BIT0;
}

void initClocks(){
    BCSCTL3 = LFXT1S_2;         // Configure VLO clock as LFXT1CLK
    IFG1 &= ~OFIFG;             // Clear fault flag
    BCSCTL2 = SELM_2 | DIVM_0;  // Select VLO clock as MCLK, set /1 MCLK divider... "MSP430G2xx3: LFXT1 does not support HF mode,XT2 is not present, ROSC is not supported."
}

void init(){
    WDTCTL = 0x5A80; // Stop the watchdog timer

    initClocks();

    P1DIR = ~BIT3;
    P1REN = BIT3;
    P1OUT = BIT3;
}

int main(){
    init();

    while(1){
        setGreenLed(true);
        __delay_cycles(12000);
        setGreenLed(false);
        __delay_cycles(12000);
    }
}
