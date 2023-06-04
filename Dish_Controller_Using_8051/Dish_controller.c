#include <reg52.h>   // include the header file for 89S52

sbit IRsensor = P3^2;  // define the IR sensor input pin
sbit LED = P1^0;      // define the LED output pin
sbit MOTOR_PIN1 = P1^1; // define the GPIO pin connected to L293D pin 2
sbit MOTOR_PIN2 = P1^2; // define the GPIO pin connected to L293D pin 7

void Delay_ms(unsigned int ms_count)
{
	unsigned int i,j;
	for(i=0; i<ms_count; i++)
	{
		for(j=0; j<100; j++);
	}
}
void main()
{

  while(1)  // continuously read sensor data
  {
    LED = 1 ;
		MOTOR_PIN1 = 0;
		MOTOR_PIN2 = 0;

    if(IRsensor == 0 )  // if sensor output is low
    {
      LED = 0;  // turn on LED
			MOTOR_PIN1 = 1;  // Set L293D pin 2 high
			MOTOR_PIN2 = 1;  // Set L293D pin 7 low
			Delay_ms(125);
    }
		
  }
}
