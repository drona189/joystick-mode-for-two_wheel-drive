#include "htc.h"
#include "pwm&timer@20Mhz.c"
#include"adc.c"
#include "uart.c"

//#define button RD0
#define _XTAL_FREQ 20000000
#define enable RA4

__CONFIG(HS & BORDIS & PWRTEN & WDTDIS & LVPDIS);


int x,y,x_temp,y_temp;
int  WML=125,WMR=125,CLIP_HIGH=240,CLIP_LOW=10;
	
void main()
{  
	TRISA0=1;
	TRISA1=1;
	TRISA2=1;
	TRISA3=1;
	TRISA4=0;
	TRISA5=1;
	TRISE0=1;
	TRISE1=1;
	TRISE2=0;
	TRISC1=0;
	TRISC2=0;
	TRISD=0xff;
	TRISB=0x00;
	PORTB=0x00;
   	enable=0;

 
    adc_Initj();
   
	pwm_Init();


	
	while(1)
	{
         x=adc(5);
         y=adc(6);
	     if(x<132 && x>122 && y<132 && y>122)       //specify the dead band for smooth navigation...
           {
	          WML=HALT_PWM;
	          WMR=HALT_PWM;
		    
           }
        

    
         else if(y>=132/*&&!button*/)    //forward motion only.. upto 255..
	       {

		      y_temp=y-127;    
			  x_temp=x-127;
		    
			   
              WML=HALT_PWM+y_temp-(x_temp/2) ;	//check for i makin smooth..	
		      WMR=HALT_PWM+y_temp+(x_temp/2) ;
			     
		      
        	}
			
	

       	else if(y<=122/*&&button*/)/// backward motion..
	      
           {
		
		      y_temp=y-127;
              x_temp=x-127;    
			  	
              WML=HALT_PWM+y_temp + (x_temp/2);
			  WMR=HALT_PWM+y_temp - (x_temp/2);
				      
		   }
        

       else{WML=WMR=HALT_PWM;}

       if(WMR>=CLIP_HIGH)WMR=CLIP_HIGH;
       if(WML>=CLIP_HIGH)WML=CLIP_HIGH;
       if(WMR<=CLIP_HIGH)WMR=CLIP_LOW;
       if(WML<=CLIP_HIGH)WML=CLIP_LOW;
       
    
       PWMR=WMR;	
       PWML=WML;

   
   }
}	


