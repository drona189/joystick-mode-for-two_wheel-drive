void delay_Nms(int n )
{
   	while(n>0)
  	 {
		TMR1H=0xEC;	// EC77H=60535d
		TMR1L=0x77;
	
		T1CKPS1=0;
		T1CKPS0=0;
	
		TMR1CS=0;
		TMR1IF=0;
		TMR1ON=1;
		while(!TMR1IF)  { }
		TMR1IF=0;
		n--;
	}
}
