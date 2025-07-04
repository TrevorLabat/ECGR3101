#include <msp430.h> //the linker only links the used parts of the library

 
int main(){
    WDTCTL = 0x5A80;

    P1DIR = ~BIT3;
    P1REN = BIT3;
    P1OUT = BIT3;
    while(1){
        if((P1IN & BIT3) == 0x00){ //If switch grounds the pin 
            P1OUT |= BIT0;
        }
        else{
            P1OUT &= ~BIT0;
        }
    }
}
