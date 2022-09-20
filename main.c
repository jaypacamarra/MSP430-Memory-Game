#include <msp430.h>
#include <stdint.h>
#include <driverlib.h>
#include "myGpio.h"
#include "myClocks.h"
#include "myLcd.h"
#include "game.h"

#define ENABLE_PINS     0xFFFE // Required to use inputs and outputs
#define ACLK            0x0100 // Timer_A ACLK source
#define UP              0x0010 // Timer_A UP mode

GameStatus_t g_memorygame;        // To keep track of game progress

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 = ENABLE_PINS;      // To use IO pins

	TA0CTL = ACLK | UP;         // setup timer0 in up mode that use ACLK
	TA0CCR0 = 0xFFFF;           // Setup reload value of timer0 to count to maximum 65535
	TA0CCTL0 = CCIE;            // Enable timer0 interrupt
	_BIS_SR(GIE);               // Activate interrupts

	P1DIR |= BIT0;              // Setup red led
	P1OUT &= ~BIT0;             // ensure led off initially

	P9DIR |= BIT7;              // Setup green led
	P9OUT &= ~BIT7;             // ensure led off initially
	
	P1REN |= BIT1;              // Enable pull up
	P1OUT |= BIT1;              // Red LED switch pulled up

	P1REN |= BIT2;              // Enable pull up
	P1OUT |= BIT2;              // Green LED switch pulled up

	initGPIO();                 // for LCD
	initClocks();               // for LCD
	myLCD_init();               // for LCD


	GAME_START();               // Must be called to start memory game
	DISPLAY_ROUND();

	while( !g_memorygame.game_over )
	{
	    GAME_GET_SEQUENCE();
	    DISPLAY_ROUND();
	    DISPLAY_SEQUENCE();
	    g_memorygame.game_over = CHECK_SEQUENCE();

	    if(g_memorygame.game_over)
	    {
	        DISPLAY_GAME_OVER();
	        DISPLAY_SCORE();
	        GAME_START();           // Restart game
	    }
	    else
	    {
	        g_memorygame.round++;
	    }
	}

	for(;;);

	return 0;
}

/*
 *
 * Timer0 ISR
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_ISR (void)
{

}
