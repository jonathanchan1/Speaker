/* 
 * File:   main.c
 * Author: Chan
 *
 * Created on November 14, 2017, 10:51 AM
 */


/*________________________________SPEAKER_______________________________*/

/*The code for this module was adapted from an online source.
 http://hades.mech.northwestern.edu/index.php/Driving_a_piezo_speaker_with_a_PIC
 */


#include <p18f452.h>
#include <delays.h>
#include <pwm.h>
#include <timers.h>


#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000

//The note for a medical alarm is C4
#define C4 0xED         //This value was determined using a prescalar of 16 and 4MHz clock.

//Global Vars
char song[3]={C4, C4, C4}; //alarm pattern
int i;

void spkr_setup(void){
    TRISCbits.TRISC2 = 0;
    SetDCPWM1(50);
    OpenTimer2(TIMER_INT_OFF & T2_PS_1_16 & T2_POST_1_1);
}

void sound_spkr(void){
    for (i=0; i<3; i++) {       //play x notes inside song array
      
        OpenPWM1(song[i]); 
                                //set PWM frequency according to entries in song array
        Delay10KTCYx(40);       //note is played for 400ms

        OpenPWM1(1);            //the PWM frequency set beyond audible range
                                //in order to create a short silence between notes
        Delay10KTCYx(40);       //play nothing for 400 ms                  
        }
    Delay10KTCYx(40);
}


void main(void)
{
    spkr_setup();
    while(1)
    {
        sound_spkr();
    }
    Sleep(); 
}
