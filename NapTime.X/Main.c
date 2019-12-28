/*
 * File:   Main.c
 * Author: phia_
 *
 * Created on March 26, 2019, 4:05 PM
 */

#include "Button.h"
// In order to use device register names like PORTB you must include <xc.h> 
#include <xc.h>
#include <pic.h>
#include "Configuration.h"
#include "SPI.h"
#include "SD.h"




// This instruction sets the watchdog timer to user-controlled, 
// so the device will not automatically reset itself.
//#pragma config WDTE = SWDTEN 
int i=0;
int lastButtonState = 0;


void main(void)
{
   
     OSCCON = 0xF4;
    while(OSCSTATbits.HFIOFR == 0);

    //Initialize all required peripherals.
    
    //SPI_Init //Provided in lab 3
    SPI_Init();
     //SD_Init //Provided in lab 3
    SD_Init();
    
    //Initialize the Digital to Analog Converter
    DAC1CON0=0xA0;
    TRISA=0xFB;
    
        
    //Initialize Timer2 at 16kHz
    //Timer_Init //Provided in lab 2
    ConfigureTimer(63);
    
    
    //Button_Init
    TRISBbits.TRISB2 = 1; //RC6=input (button))
    ANSELBbits.ANSB2 = 0; // reads digital input (button))
    
    //Comparator_Init
    TRISBbits.TRISB3 = 1;   //C3=input to pic (output of comparator)
    ANSELBbits.ANSB3 = 0;    //reads analog input
    
      
//    int count=0;
//   
//    if(PORTBbits.RB3==1)
//        count++;
//    if (count==10)
//    {
//         PlayingEnabled=1;
//         count=0;
//    }
//    
    
    // bool PlayingEnabled=PORTBbits.RB3;
   
   char one=0;
    char two=0;
    char three=0;
    char four=0;
    
    
  bool PlayingEnabled=1;
 
    //Address Counter
    int counter=0;
    
    while(1)
    {

        if(PlayingEnabled == 0)
        {

            if(PORTBbits.RB2!= lastButtonState || PORTBbits.RB2==lastButtonState)
            {
                if(PORTBbits.RB2 == 1)
                {
                    Button_ChangeSong();
                }
                lastButtonState = PORTBbits.RB2;
            }
        //  PlayingEnabled = 1;  
        }
        
        if(PlayingEnabled == 1)
        {
            //Lab 3 code

            char rM = 0xFF;
            if (counter==0)
                {
                    //Send block read command
                     SD_SendCommand(17, Current_Addr[0], Current_Addr[1], Current_Addr[2], Current_Addr[3]);

                     //Wait for a response from the SD card that all bits have been read
                     SD_Read8bitResponse();
                     if(SD_Check8bitResponse(0x00)==false)exit(1);
                     do{rM = SPI_Read();}
                     while(rM == 0xFF);
                }

            //Write the bits from the SD card to the the DAQ
            char temp = SPI_Read();
            WriteDAQ(temp);

            //increase counter
            counter++;

            //when the program has read a set of 512 bits
            if (counter==512)
            {       
                //Read 3 bytes from SD card
                SPI_Read();
                SPI_Read();
                SPI_Read();

                //reset counter
                counter=0;

                //Check the button
                
              
                if(PORTBbits.RB2!= lastButtonState && PORTBbits.RB2 == 1)
                {
                    Button_ChangeSong();
                   
                }
                 lastButtonState = PORTBbits.RB2;


         
               // Increase bits to read from the next set of 512 bits
                Current_Addr[3]++;
                if(Current_Addr[3]==0)
                {
                    Current_Addr[2]++;
                    if(Current_Addr[2]==0)
                    {
                        Current_Addr[1]++;
                        if(Current_Addr[1]==0)
                        {
                            Current_Addr[0]++;
                        }
                    }
                }

               // Check for the end of the file
                if (Current_Addr[0] == End_Addr[0] &&
                    Current_Addr[1] == End_Addr[1] &&
                    Current_Addr[2] == End_Addr[2] &&
                    Current_Addr[3] == End_Addr[3])
                {
                    PlayingEnabled = 0;
                }
                

            } //End of if(counter == 512)

        } //End of if(PlayingEnabled == 1)

        while(!PIR1bits.TMR2IF);

        PIR1bits.TMR2IF = 0;

    } //End of while(1)
    
    return;
} //End of main
   



