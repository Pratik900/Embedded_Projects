#include <reg52.h> 

sbit Button = P3^2; 
sbit LED1 = P1^0; 
sbit LED2 = P1^1;
sbit LED3 = P1^2; 

void Delay_ms(unsigned int ms_count)
{
	unsigned int i,j;
	for(i=0; i<ms_count; i++)
	{
		for(j=0; j<100; j++);
	}
}
void on()
{
	 if(Button == 1 )  
    {
		LED1 = 0 ;
		LED2 = 0;
		LED3 = 1;
		Delay_ms(7000);
		LED1 = 0;
		LED2 = 1;
		LED3 = 0;
		Delay_ms(3000);
    }
}
void main()
{
	Button = 0;
  while(1)
  {
		LED1 = 0;
		LED2 = 0;
		LED3 = 1;
		Delay_ms(3000);
		LED1 = 0;
		LED2 = 1;
		LED3 = 0;
		Delay_ms(3000);
		on();
		LED1 = 1;
		LED2 = 0;
		LED3 = 0;
		Delay_ms(3000);
		on();
	}		
}

