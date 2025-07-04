// Name: Trevor Labat
// Date: 6/29/2025
// Assignment: Lab 3
// Youtube: https://youtube.com/shorts/vP3icSsa7gY
//
// Program info:
// This program includes a software state machine that is used to recreate the cyclone arcade game. 

#include <stdint.h>
#include <stdbool.h>
#include <msp430.h>

#define CYAN_LED_PIN            BIT1
#define CYAN_LED_DIR_REG        P2DIR
#define CYAN_LED_OUT_REG        P2OUT

#define ORANGE_1_LED_PIN        BIT0
#define ORANGE_2_LED_PIN        BIT1
#define ORANGE_3_LED_PIN        BIT2
#define ORANGE_4_LED_PIN        BIT4
#define ORANGE_5_LED_PIN        BIT5
#define ORANGE_6_LED_PIN        BIT0
#define ORANGE_1_5_LED_DIR_REG  P1DIR
#define ORANGE_1_5_LED_OUT_REG  P1OUT
#define ORANGE_6_LED_DIR_REG    P2DIR
#define ORANGE_6_LED_OUT_REG    P2OUT

#define BUTTON_DIR_REG          P1DIR
#define BUTTON_PIN              BIT3
#define BUTTON_IN_REG           P1IN

#define BUTTON_IE_REG           P1IE
#define BUTTON_PIES_REG         P1IES
#define BUTTON_PIFG_REG         P1IFG

typedef enum {WAITING = 1, ACTIVE, FAILED, CELEBRATION, MAX_STATE} state_t;

void init();
static inline void setLed(uint8_t ledNum);
state_t waitingState();
state_t activeState();
state_t failedState();
state_t celebrationState();

volatile bool buttonInterrupt = false;

int main(){
    init();
    state_t currentState = WAITING;
    state_t nextState = WAITING;    

    while(1){
        switch(currentState){
            case WAITING:
                nextState = waitingState();
                break;
            case ACTIVE:
                nextState = activeState();
                break;
            case FAILED:
                nextState = failedState();
                break;
            case CELEBRATION:
                nextState = celebrationState();
                break;
        }
        currentState = nextState;
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port1(void){
    buttonInterrupt = true;
    BUTTON_PIFG_REG &= ~BUTTON_PIN;
    __delay_cycles(1000);
}

void init(){
    WDTCTL = WDTPW | WDTHOLD;
    
    CYAN_LED_DIR_REG |= CYAN_LED_PIN;

    ORANGE_1_5_LED_DIR_REG |= ORANGE_1_LED_PIN;
    ORANGE_1_5_LED_DIR_REG |= ORANGE_2_LED_PIN;
    ORANGE_1_5_LED_DIR_REG |= ORANGE_3_LED_PIN;
    ORANGE_1_5_LED_DIR_REG |= ORANGE_4_LED_PIN;
    ORANGE_1_5_LED_DIR_REG |= ORANGE_5_LED_PIN;
    ORANGE_6_LED_DIR_REG |= ORANGE_6_LED_PIN;
    
    BUTTON_DIR_REG &= ~BUTTON_PIN;

    BUTTON_IE_REG |= BUTTON_PIN;
    BUTTON_PIES_REG |= BUTTON_PIN;
    BUTTON_PIFG_REG &= ~BUTTON_PIN;

    __enable_interrupt();
}

static inline void setLed(uint8_t ledNum){ //should inline be used here?
    switch(ledNum){
        case 1:
            ORANGE_1_5_LED_OUT_REG |= ORANGE_1_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_2_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_3_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_4_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_5_LED_PIN;
            ORANGE_6_LED_OUT_REG &= ~ORANGE_6_LED_PIN;

            CYAN_LED_OUT_REG &= ~CYAN_LED_PIN;
            break;
        case 2:
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_1_LED_PIN;
            ORANGE_1_5_LED_OUT_REG |= ORANGE_2_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_3_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_4_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_5_LED_PIN;
            ORANGE_6_LED_OUT_REG &= ~ORANGE_6_LED_PIN;

            CYAN_LED_OUT_REG &= ~CYAN_LED_PIN;
            break;
        case 3:
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_1_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_2_LED_PIN;
            ORANGE_1_5_LED_OUT_REG |= ORANGE_3_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_4_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_5_LED_PIN;
            ORANGE_6_LED_OUT_REG &= ~ORANGE_6_LED_PIN;

            CYAN_LED_OUT_REG &= ~CYAN_LED_PIN;
            break;
        case 4: //cyan
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_1_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_2_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_3_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_4_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_5_LED_PIN;
            ORANGE_6_LED_OUT_REG &= ~ORANGE_6_LED_PIN;

            CYAN_LED_OUT_REG |= CYAN_LED_PIN;
            break;
        case 5:
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_1_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_2_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_3_LED_PIN;
            ORANGE_1_5_LED_OUT_REG |= ORANGE_4_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_5_LED_PIN;
            ORANGE_6_LED_OUT_REG &= ~ORANGE_6_LED_PIN;

            CYAN_LED_OUT_REG &= ~CYAN_LED_PIN;
            break;
        case 6:
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_1_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_2_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_3_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_4_LED_PIN;
            ORANGE_1_5_LED_OUT_REG |= ORANGE_5_LED_PIN;
            ORANGE_6_LED_OUT_REG &= ~ORANGE_6_LED_PIN;

            CYAN_LED_OUT_REG &= ~CYAN_LED_PIN;
            break;
        case 7:
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_1_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_2_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_3_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_4_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_5_LED_PIN;
            ORANGE_6_LED_OUT_REG |= ORANGE_6_LED_PIN;

            CYAN_LED_OUT_REG &= ~CYAN_LED_PIN;
            break;
        default:
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_1_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_2_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_3_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_4_LED_PIN;
            ORANGE_1_5_LED_OUT_REG &= ~ORANGE_5_LED_PIN;
            ORANGE_6_LED_OUT_REG &= ~ORANGE_6_LED_PIN;

            CYAN_LED_OUT_REG &= ~CYAN_LED_PIN;
            break;
    }
}

state_t waitingState(){
    if(buttonInterrupt){
        buttonInterrupt = false;
        return ACTIVE;
    }
    else{
        setLed(0);
        return WAITING;
    }
}

state_t activeState(){
    uint8_t i;
    while(1){
        for(i = 1; i < 8; i++){ //left to right
            setLed(i);
            __delay_cycles(100000);
            if(buttonInterrupt && ((CYAN_LED_OUT_REG & CYAN_LED_PIN) == CYAN_LED_PIN)){
                
                return CELEBRATION;
            }
            else if(buttonInterrupt && ((CYAN_LED_OUT_REG & CYAN_LED_PIN) != CYAN_LED_PIN)){
                 buttonInterrupt = false;
                __delay_cycles(10000);
                return FAILED;
            }
        }
        for(i = 7; i > 0; i--){ //right to left
            setLed(i);
            __delay_cycles(100000);
             if(buttonInterrupt && ((CYAN_LED_OUT_REG & CYAN_LED_PIN) == CYAN_LED_PIN)){
                return CELEBRATION;
            }
            else if(buttonInterrupt && ((CYAN_LED_OUT_REG & CYAN_LED_PIN) != CYAN_LED_PIN)){
                 buttonInterrupt = false;
                __delay_cycles(10000);
                return FAILED;
            }
        }
    }
}

state_t failedState(){
    while(!buttonInterrupt){
        __delay_cycles(1000);
    }
    buttonInterrupt = false;
    return WAITING;
}

state_t celebrationState(){
    buttonInterrupt = false;
    ORANGE_1_5_LED_OUT_REG |= ORANGE_1_LED_PIN;
    ORANGE_1_5_LED_OUT_REG |= ORANGE_2_LED_PIN;
    ORANGE_1_5_LED_OUT_REG |= ORANGE_3_LED_PIN;
    ORANGE_1_5_LED_OUT_REG |= ORANGE_4_LED_PIN;
    ORANGE_1_5_LED_OUT_REG |= ORANGE_5_LED_PIN;
    ORANGE_6_LED_OUT_REG |= ORANGE_6_LED_PIN;

    CYAN_LED_OUT_REG &= ~CYAN_LED_PIN;

    while(1){
        ORANGE_1_5_LED_OUT_REG ^= ORANGE_1_LED_PIN;
        ORANGE_1_5_LED_OUT_REG ^= ORANGE_2_LED_PIN;
        ORANGE_1_5_LED_OUT_REG ^= ORANGE_3_LED_PIN;
        ORANGE_1_5_LED_OUT_REG ^= ORANGE_4_LED_PIN;
        ORANGE_1_5_LED_OUT_REG ^= ORANGE_5_LED_PIN;
        ORANGE_6_LED_OUT_REG ^= ORANGE_6_LED_PIN;

        CYAN_LED_OUT_REG ^= CYAN_LED_PIN;
        __delay_cycles(500000);
        if(buttonInterrupt){
            buttonInterrupt = false;
            return WAITING;
        }
    }
}
