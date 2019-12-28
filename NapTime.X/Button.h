/* 
 * File:   Button.h
 * Author: phia_
 *
 * Created on March 26, 2019, 4:04 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include <stdbool.h>

    char Current_Addr[4];
    char End_Addr[4];
    
    char start [5][4]=
        {{0,0,0,0},
        {0,0,0x07,0xd0},
        {0,0,0x0f,0xa0},
        {0,0,0x17,0x70},
        {0,0,0x1f,0x40}};

    char end [5][4]=
        {{0,0,0x07,0x53},
        {0,0,0x0f,0x23},
        {0,0,0x16,0xf3},
        {0,0,0x1e,0xc2},
        {0,0,0x26,0x93}};

void Button_ChangeSong(void);
bool Button_CheckPress(void);


#endif	/* BUTTON_H */

