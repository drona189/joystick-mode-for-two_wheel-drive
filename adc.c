#define _XTAL_FREQ 20000000

void adc_Init(void)
	{
		ADCS2 = 0;
		ADCS1 = 1;
		ADCS0 = 0 ;
		
		PCFG3 = 1;
 		PCFG2 = 0;
 		PCFG1 = 1;
 		PCFG0 = 0;
 		
 		ADFM = 0; 
 	}
void adc_Initj(void)
{
        ADCS2 = 0;
		ADCS1 = 1;
		ADCS0 = 0 ;
	
    	PCFG3 = 0;
 		PCFG2 = 0;
 		PCFG1 = 0;
 		PCFG0 = 0;
 		
 		ADFM = 0;  
}


int adc(char an)
{	
//	int adc_val;
	an = an << 3;
	ADCON0 = (ADCON0 & 0b11000000) | an;	
	ADON = 1;
	__delay_ms(1);
	ADGO = 1;
	while(ADGO);
	ADON = 0;
	return ADRESH;
//	adc_val = ADRESH;
	
//	return((adc_val << 8) | ADRESL);	
}