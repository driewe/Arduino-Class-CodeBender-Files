#include "LedControl.h" //  need the library
LedControl lc=LedControl(12,11,10,1); // 
 
// pin 12 is connected to the MAX7219 pin 1 - Data In
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219
 
int krdelay = 50;

void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,1);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}
void loop()
{
	for(int row=0; row<8; row++)
	{
		lc.setLed(0,0,row, true);
		delay(1000);
		
	}
	lc.clearDisplay(0);

  	for (int row=0; row<8; row++)
  	{
    	for (int col=0; col<8; col++)
    	{
      		lc.setLed(0,col,row,true); // turns on LED at col, row
      		delay(25);
    	}
    	delay(25);
  	}
 
  	for (int row=0; row<8; row++)
  	{
    	for (int col=0; col<8; col++)
    	{
      		lc.setLed(0,col,row,false); // turns off LED at col, row
      		delay(25);
    	}
  	} 
  	
  	// knight rider efffect
  	for (int row=0; row<8; row++)
  	{
  		for(int col=0; col<8; col++)
  		{
  			lc.setLed(0,col,row,true);
  			delay(krdelay);
  			lc.setLed(0,col,row,false);
  		}
  	}
  	for (int row=7; row>-1;row--)
  	{
  		for(int col=7; col>-1; col--)
  		{
  			lc.setLed(0,col,row,true);
  			delay(krdelay);
  			lc.setLed(0,col,row,false);
  		}
  	}
  	for (int col=0; col<8; col++)
  	{
  		for(int row=0; row<8; row++)
  		{
  			lc.setLed(0,col,row,true);
  			delay(krdelay);
  			lc.setLed(0,col,row,false);
  		}
  	}
  	for(int col=7; col>=-1; col--)
  	{
  		for(int row=7; row>-1; row--)
  		{
  			lc.setLed(0,col,row,true);
  			delay(krdelay);
  			lc.setLed(0,col,row,false);
  		}
  	}
}