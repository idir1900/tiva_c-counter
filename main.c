#include "TM4C123GH6PM.h"
#include "delay.h"
#include <stdio.h>
#include "tm4c_cmsis.h"
#define RED_LED (0x01 <<1)
#define BLUE_LED (0x01 <<2)
#define GREEN_LED (0x01 <<3)

#define switch1_pin (0x1 <<4)
int my_count(void);

int main()
{
  *((int *)0x400FE604)=0x1;//clock gating port B 
*((int *)0x400FE608)=0x02; // Timer 0 clock gating
GPIOB->DIR&=~(1<<6); //pin 6 as input
GPIOB->DEN|=(1<<6); // enable pin 6
GPIOB->AFSEL|=(1<<6); // pin 6 alternate function
GPIOB->PCTL|=~0x0F000000;
GPIOB->PCTL |= 0x07000000;// PB6 as input
TIMER0->CTL=0x0; //rising edge counter 

TIMER0->CFG|=(1<<2); //configuration of the counter 
TIMER0->TAMR=0x13; // configuration of the counter 
TIMER0->TAMATCHR=0xA;// making the counter count to 10
TIMER0->TAPMR=0x0;// 0 to the prescaler register 
*((int *)0x40030050)&=0x0;// reset the counter


TIMER0->CTL |= (1<<0);


while(1){
   printf("%d  ",my_count());// display current counter value 
   
   if (TIMER0->RIS==0x2){ // test if match value is reached 
     TIMER0->ICR|=0x2; // clearing the timer 
     
   *((int *)0x40030050)&=0x0;
   }  // making count value equal to zero
}
}

int my_count(void)
{
    return TIMER0->TAR;// current value of the counter
}






