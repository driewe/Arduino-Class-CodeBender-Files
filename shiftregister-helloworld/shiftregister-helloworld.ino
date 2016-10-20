//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

int latchPin = 5;   // to pin 12
int clockPin = 6;	// to pin 11
int dataPin = 4;	// to pin 14

void setup() 
{
  	//set pins to output so you can control the shift register
	pinMode(latchPin, OUTPUT);
  	pinMode(clockPin, OUTPUT);
  	pinMode(dataPin, OUTPUT);
}

void loop() 
{
  	// count from 0 to 255 and display the number 
  	// on the LEDs
  	for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) 
  	{
    	// take the latchPin low so 
    	// the LEDs don't change while you're sending in bits:
    	digitalWrite(latchPin, LOW);
    	// shift out the bits:
    	shiftOut(dataPin, clockPin, LSBFIRST, numberToDisplay);  

    	//take the latch pin high so the LEDs will light up:
    	digitalWrite(latchPin, HIGH);
    	// pause before next value:
    	delay(500);
  	}
}