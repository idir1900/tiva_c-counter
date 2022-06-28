#include "delay.h"
#include <stdio.h>
#include "tm4c_cmsis.h"
#include "TM4C123GH6PM.h"
#include <stdbool.h>
#include <stdint.h>

void timer_delay(int time){
 
 int i ;
  
SYSCTL_RCGCTIMER_R|=SYSCTL_RCGCTIMER_R0;
SYSCTL_SCGCTIMER_R |=SYSCTL_SCGC1_TIMER0;
TIMER0_CFG_R=TIMER_CFG_32_BIT_TIMER  ;
TIMER0->CTL=0x0;
 TIMER0->TAMR=0x02|(0b1<<7)|(0b1<<5)|(0b1<<4);
TIMER0_TAILR_R=0xF42400;
TIMER0_CTL_R=0x01U;
for (i=0;i<time;i++){while ((TIMER0_RIS_R & 0x1) == 0) ;      }
        TIMER0_ICR_R= 0x1; 
}


void my_time(int second){
  int i;
SYSCTL_RCGCTIMER_R|=SYSCTL_RCGCTIMER_R0;
SYSCTL_SCGCTIMER_R |=SYSCTL_SCGC1_TIMER0;
TIMER0_CFG_R=TIMER_CFG_32_BIT_TIMER ;
 TIMER0->CTL=0x0;
 TIMER0->TAMR=0x02|(0b1<<7)|(0b1<<5)|(0b1<<4);
TIMER0->TAILR|=0xF42400;
TIMER0_CTL_R=0x01U;

for ( i=0;i<second;i++){while((TIMER0->RIS & 0x1)==0); }
   TIMER0->ICR|=0x1;

 }

  
int counter_up(int limit,int prescaler_up ){
 

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
TIMER0->TAMATCHR=limit;// making the counter count to 10
TIMER0->TAPMR=prescaler_up;// 0 to the prescaler register 
*((int *)0x40030050)&=0x0;// reset the counter


TIMER0->CTL |= (1<<0);


while(1){
  if(GPIOB->DATA & (1<<6)){
    
    printf("%d ", my_count());}
   
   if (TIMER0->RIS==0x2){ // test if match value is reached 
   
     TIMER0->ICR|=0x2;

   }  // making count value equal to zero
}
}


int counter_down(int start,int prescaler_down){
*((int *)0x400FE604)=0x1;//clock gating port B 
*((int *)0x400FE608)=0x02; // Timer 0 clock gating
GPIOB->DIR&=~(1<<6); //pin 6 as input
GPIOB->DEN|=(1<<6); // enable pin 6
GPIOB->AFSEL|=(1<<6); // pin 6 alternate function
GPIOB->PCTL|=~0x0F000000;
GPIOB->PCTL |= 0x07000000;// PB6 as input
TIMER0->CTL=0x0; //rising edge counter 

TIMER0->CFG|=0x0; //configuration of the counter 
TIMER0->TAMR=0x3; // configuration of the counter 
TIMER0->TAILR=start;
TIMER0->TAMATCHR=0x0;// making the counter count to 10
TIMER0->TAPMR=0x0;
TIMER0->TAPR=prescaler_down;// 0 to the prescaler register 


TIMER0->CTL |= (1<<0);


while(1){
  if(GPIOB->DATA & (1<<6)){
    
    printf("%d\n ", my_count());
    //printf("%d\n ", TIMER0->TAPR);
  
  }
   
   
   if (TIMER0->RIS==0x2){ // test if match value is reached 
     
     // clearing the timer 
     
     TIMER0->ICR=0x2;
     TIMER0->CTL=0x0; //rising edge counter 

TIMER0->CFG|=0x0; //configuration of the counter 
TIMER0->TAMR=0x3; // configuration of the counter 
TIMER0->TAILR=start;
TIMER0->TAMATCHR=0x0;// making the counter count to 10
TIMER0->TAPMR=0x0;
TIMER0->TAPR=prescaler_down;// 0 to the prescaler register 
     TIMER0->CTL |= (1<<0);
   } 
  
   // making count value equal to zero
}
}

void wide_counter_down(unsigned long long int wlimit){
  
*((int *)0x400FE65C)=0x1;//clock gating port B 
*((int *)0x400FE608)=0x02; // Timer 0 clock gating



GPIOB->DIR&=~(1<<6); //pin 6 as input
GPIOB->DEN|=(1<<6); // enable pin 6
GPIOB->AFSEL|=(1<<6); // pin 6 alternate function
GPIOB->PCTL|=~0x0F000000;
GPIOB->PCTL |= 0x07000000;// PB6 as input

TIMER0->CTL=0x0; //rising edge counter 

TIMER0->CFG=0x0; //configuration of the counter 
TIMER0->TAMR=0x3; // configuration of the counter 
TIMER0->TAILR=wlimit;
TIMER0->TAMATCHR=0x0;// making the counter count to 10
TIMER0->TAPMR=0x0;
TIMER0->TAPR=0x0;// 0 to the prescaler register 

  TIMER0->CTL |= (1<<0);



while(1){
  if(GPIOB->DATA & (1<<6)){
    
    printf("%lld\n ",  my_count_wide());
    //printf("%d\n ", TIMER0->TAPR);
  
  }
   
   
   if (TIMER0->RIS==0x2){ // test if match value is reached 
     
     // clearing the timer 
     
     TIMER0->ICR=0x2;
     TIMER0->CTL=0x0; //rising edge counter 

TIMER0->CFG|=0x0; //configuration of the counter 
TIMER0->TAMR=0x3; // configuration of the counter 
TIMER0->TAILR=wlimit;
TIMER0->TAMATCHR=0x0;// making the counter count to 10
TIMER0->TAPMR=0x0;
TIMER0->TAPR=0x0;// 0 to the prescaler register 
     TIMER0->CTL |= (1<<0);
   } 
  
   // making count value equal to zero
}
}










int my_count(void)
{
    return TIMER0->TAR;// current value of the counter
}

unsigned long long int    my_count_wide(void){
    return TIMER0->TAR;// current value of the counter
}

