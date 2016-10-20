/*
  Shift Register Example
 for 74HC595 shift register

 This sketch turns reads serial input and uses it to set the pins
 of a 74HC595 shift register.

 Hardware:
 * 74HC595 shift register attached to pins 4, 5 and 6 of the Arduino,
 as detailed below.
 * LEDs attached to each of the outputs of the shift register

 Created 22 May 2009
 Created 23 Mar 2010
 by Tom Igoe

 */

int latchPin = 5;   // to pin 12
int clockPin = 6;	// to pin 11
int dataPin = 4;	// to pin 14

void setup() 
{
	//set pins to output because they are addressed in the main loop
  	pinMode(latchPin, OUTPUT);
  	pinMode(dataPin, OUTPUT);  
  	pinMode(clockPin, OUTPUT);
  	Serial.begin(9600);
  	Serial.println("reset");
}

void loop() 
{
  	if (Serial.available() > 0) 
  	{
    	// ASCII '0' through '9' characters are
    	// represented by the values 48 through 57.
    	// so if the user types a number from 0 through 9 in ASCII, 
    	// you can subtract 48 to get the actual value:
    	int bitToSet = Serial.read() - 48;
		if(bitToSet < 8)
		{
  			// write to the shift register with the correct bit set high:
    		registerWrite(bitToSet, HIGH);
		}
  	}
}

// This method sends bits to the shift register:

void registerWrite(int whichPin, int whichState) 
{
	// the bits you want to send
  	byte bitsToSend = 0;

  	// turn off the output so the pins don't light up
  	// while you're shifting bits:
  	digitalWrite(latchPin, LOW);

  	// turn on the next highest bit in bitsToSend:
  	bitWrite(bitsToSend, whichPin, whichState);

  	// shift the bits out:
  	shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  	digitalWrite(latchPin, HIGH);

}