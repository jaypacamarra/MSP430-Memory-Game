/*
 * game.h
 *
 *  Created on: Sep. 17, 2022
 *      Author: jpaca
 */

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <msp430.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <driverlib.h>
#include "myGpio.h"
#include "myClocks.h"
#include "myLcd.h"

#define RED_LED                 (BIT0)
#define GREEN_LED               (BIT7)
#define LED_ON                  (1U)
#define LED_OFF                 (0U)
#define NUM_PULSE_IN_ROUND_1    (3U)
#define NUM_PULSE_IN_ROUND_2    (5U)
#define NUM_PULSE_IN_ROUND_3    (7U)
#define MAX_PULSE_IN_A_PATTERN  NUM_PULSE_IN_ROUND_3

typedef struct
{
    uint8_t     round;
    bool        game_over;
    uint16_t    sequence;
    uint16_t    sequence_speed; // used for blocking delay duration
}GameStatus_t;



void    GAME_START              ( void );
void    GAME_GET_SEQUENCE       ( void );
void    DISPLAY_GAME_OVER       ( void );
void    DISPLAY_SEQUENCE        ( void );
void    DISPLAY_SCORE           ( void );
void    DISPLAY_ROUND           ( void );
void    RED_LED_STATE           ( uint8_t );
void    GREEN_LED_STATE         ( uint8_t );
bool    CHECK_SEQUENCE          ( void );
bool    RED_BUTTON_PRESSED      ( void );
bool    GREEN_BUTTON_PRESSED    ( void );

void DisplayWord(char word[6]);

#endif /* GAME_GAME_H */



