#include <stdbool.h>
#include "Button.h"


    //Setting the intial button state to 0
//  int lastButtonState = 0;
//    
//
//
//  
//char SongNumber=0;
    
    //if button is pressed, go to the next song by changing the start_addr and the nxt_addr of the SD card
    void Button_ChangeSong(void)
{
        static char SongNumber = 0;
        
        SongNumber++;
        if (SongNumber>4) SongNumber = 0;
        
        for(int i = 0; i < 4; i++)
        {
            End_Addr[i] = end[SongNumber][i];
            Current_Addr[i] = start[SongNumber][i];
            
        
        }
       // SongNumber++;
        
        return;
}
   
                
//
//bool Button_CheckPress(void){
//    //Is button currently pressed,
//    //AND was button previously not pressed
//    //return true if the button is currently pressed, otherwise return false
//    if(PORTBbits.RB2!= lastButtonState)
//        {
//            if(PORTBbits.RB2 == 1)
//            {
//                lastButtonState = PORTBbits.RB2;
//                return true;
//            }
//        }
//    return false;
//}
