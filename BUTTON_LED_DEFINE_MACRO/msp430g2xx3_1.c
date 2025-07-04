//preprocessor macros
#define WDTCL *((unsigned int*) 0x120)
#define P1IN *((unsigned char*) 0x20)       // I want to treat the number 0x20 as the memory address where an unsigned char lives and assign what is at that address to P1IN.
#define P1OUT *((unsigned char*) 0x21)  
#define P1DIR *((unsigned char*) 0x22)

int main(){
    
    P1DIR = 0x01;
    WDTCL = 0x5A80;
    while(1){
        if((P1IN & 0x08) == 0x00){ //If switch grounds the pin 
            P1OUT = 0x01;
        }
        else{
            P1OUT = 0x00;
        }
    }
}
