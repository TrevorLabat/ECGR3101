int main(){

    volatile unsigned int* wdtctl = (unsigned int*) 0x0120;
    *wdtctl = 0x5A80; // Stop the watchdog timer

    volatile unsigned char* P1IN = (unsigned char*) 0x20;       // I want to treat the number 0x20 as the memory address where an unsigned char lives.
    volatile unsigned char* P1OUT = (unsigned char*) 0x021;
    volatile unsigned char* P1DIR = (unsigned char*) 0x022;
    
    *P1DIR = 0x01;


    while(1){
        if((*P1IN & 0x08) == 0x00){ //If switch grounds the pin 
            *P1OUT = 0x01;
        }
        else{
            *P1OUT = 0x00;
        }
    }
}
