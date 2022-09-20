/*
 * game.c
 *
 *  Created on: Sep. 17, 2022
 *      Author: jpaca
 */

#include "game.h"

extern GameStatus_t g_memorygame;        // To keep track of game progress

void GAME_START( void )
{
    g_memorygame.game_over      = false;
    g_memorygame.round          = 1;
    g_memorygame.sequence       = 0;
    g_memorygame.sequence_speed = 100000;
}

void DISPLAY_GAME_OVER( void )
{
    uint32_t i;
    myLCD_showChar(' ', 1);
    myLCD_showChar(' ', 2);
    myLCD_showChar(' ', 3);
    myLCD_showChar(' ', 4);
    myLCD_showChar(' ', 5);
    myLCD_showChar(' ', 6);
    DisplayWord("GAME");
    for(i=0 ; i<=500000; i++);
    DisplayWord("OVER");
    for(i=0 ; i<=500000; i++);
}

void GAME_GET_SEQUENCE( void )
{
    uint32_t i;
    DisplayWord("PRESS");
    for(i=0 ; i<=400000; i++);
    DisplayWord("BUTTON");

    while(!RED_BUTTON_PRESSED() && !GREEN_BUTTON_PRESSED());    // wait for either button to be pressed
    g_memorygame.sequence = TA0R;
    for(i=0 ; i<=500000; i++);
}

void DISPLAY_SEQUENCE( void )
{
    uint32_t i,led_color,delay;
    for(i=0; i<g_memorygame.round; i++)
    {
        led_color = (g_memorygame.sequence >> i) & BIT0;
        if(led_color==1) // turn on red led
        {
            RED_LED_STATE(LED_ON);
            GREEN_LED_STATE(LED_OFF);
        }
        else // turn on green led
        {
            RED_LED_STATE(LED_OFF);
            GREEN_LED_STATE(LED_ON);
        }
        for(delay=0; delay<=500000; delay++); // led on delay
        RED_LED_STATE(LED_OFF);
        GREEN_LED_STATE(LED_OFF);
        for(delay=0; delay<=500000; delay++); // led off delay
    }
}

void DISPLAY_SCORE( void )
{
    uint32_t i;

    myLCD_showChar('S', 1);
    myLCD_showChar('C', 2);
    myLCD_showChar('O', 3);
    myLCD_showChar('R', 4);
    myLCD_showChar('E', 5);
    myLCD_showChar(' ', 6);

    for(i=0; i<=500000; i++);   // delay time

    myLCD_showChar('I', 1);
    myLCD_showChar('S', 2);
    myLCD_showChar(' ', 3);
    myLCD_showChar(' ', 4);
    myLCD_showChar(' ', 5);
    myLCD_showChar(' ', 6);

    for(i=0; i<=500000; i++);   // delay time

    myLCD_displayNumber( g_memorygame.round - 1);

    for(i=0; i<=1500000; i++);   // delay time
}

void DISPLAY_ROUND( void )
{
    uint32_t i;

    myLCD_showChar('R', 1);
    myLCD_showChar('O', 2);
    myLCD_showChar('U', 3);
    myLCD_showChar('N', 4);
    myLCD_showChar('D', 5);
    myLCD_showChar(' ', 6);

    for(i=0; i<=500000; i++);   // delay time

    myLCD_displayNumber(g_memorygame.round);
    for(i=0; i<=1000000; i++);   // delay time
    myLCD_showChar(' ', 1);
    myLCD_showChar(' ', 2);
    myLCD_showChar(' ', 3);
    myLCD_showChar(' ', 4);
    myLCD_showChar(' ', 5);
    myLCD_showChar(' ', 6);
}

bool CHECK_SEQUENCE( void )
{
    uint8_t  numUserInputs     = 0;
    uint16_t userInputSequence = 0;

    while( numUserInputs != g_memorygame.round )
    {
        if(RED_BUTTON_PRESSED())
        {
            RED_LED_STATE(LED_ON);
            GREEN_LED_STATE(LED_OFF);
            while( RED_BUTTON_PRESSED() ); // wait for user to let go of red led button
            userInputSequence = userInputSequence | (1 << numUserInputs);
            numUserInputs++;
        }
        else if(GREEN_BUTTON_PRESSED())
        {
            RED_LED_STATE(LED_OFF);
            GREEN_LED_STATE(LED_ON);
            while( GREEN_BUTTON_PRESSED() ); // wait for user to let go of green led button
            userInputSequence = userInputSequence & ~(1 << numUserInputs);
            numUserInputs++;
        }
        RED_LED_STATE(LED_OFF);
        GREEN_LED_STATE(LED_OFF);
//        while( RED_BUTTON_PRESSED() || GREEN_BUTTON_PRESSED() ); // wait until both buttons not pressed anymore
    }

    uint16_t i;
    bool sequenceIncorrect = false;
    for(i = 0; i<g_memorygame.round; i++)
    {
        if( (g_memorygame.sequence & 0x1) == (userInputSequence & 0x1) )
        {
            g_memorygame.sequence >>= 1;
            userInputSequence >>= 1;
        }
        else
            sequenceIncorrect = true;
    }
    return sequenceIncorrect;
}

bool RED_BUTTON_PRESSED( void )
{
    if((P1IN & BIT1)==0)
    {
        int i;
        for(i=0; i<=20000; i++); //debounce time
        return (P1IN & BIT1)==0;
    }
    else
        return false;
}

bool GREEN_BUTTON_PRESSED( void )
{
    if((P1IN & BIT2)==0)
    {
        int i;
        for(i=0; i<=20000; i++); //debounce time
        return (P1IN & BIT2)==0;
    }
    else
        return false;
}

void DisplayWord(char word[6])
{
    #define true 1
    #define false 0

    char length; // word length
    unsigned int i; // Used to "step" through word, 1 character at a time
    char next_char; // The character in word presently displaying

    length = strlen(word);

    if (length <= 6) // If 6 or less characters
    {
        for (i = 0; i < length; i = i + 1) // Loop through each of characters
        {
            next_char = word[i]; // Get character for the ith slot
            if (next_char) // If character exists (not null)
            {
                myLCD_showChar(next_char, i + 1); // Show character on LCD
            }
        }
    }
    else // Else, word has more than 6 characters, display error message
    {
        myLCD_showChar('E', 1);
        myLCD_showChar('R', 2);
        myLCD_showChar('R', 3);
        myLCD_showChar('O', 4);
        myLCD_showChar('R', 5);
        myLCD_showChar(' ', 6);
    }
}

void RED_LED_STATE( uint8_t red_led_state)
{
    if(LED_ON == red_led_state)
        P1OUT |= BIT0;
    else
        P1OUT &= ~BIT0;
}

void GREEN_LED_STATE( uint8_t green_led_state)
{
    if(LED_ON == green_led_state)
        P9OUT |= BIT7;
    else
        P9OUT &= ~BIT7;
}

