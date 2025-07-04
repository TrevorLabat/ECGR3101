#include <msp430.h>
int main()
    {
     volatile unsigned int* wdtctl = (unsigned int*) 0x0120;
    *wdtctl = 0x5A80;


    volatile unsigned int* P1DIR = (unsigned int*) 0x02A;
    volatile unsigned int* P1OUT = (unsigned int*) 0x029;

    *P1DIR = 0x2A;
    volatile long i;
    while(1){
        *P1OUT = 0x2A;
        for(i = 100000; i != 0; i--);
        *P1OUT = 0x00;
        for(i = 100000; i != 0; i--);
    }
}
