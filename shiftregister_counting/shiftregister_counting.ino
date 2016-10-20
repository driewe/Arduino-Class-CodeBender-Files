/*
Adapted from Adafruit lesson
*/

int latchPin = 5;   // to pin 12
int clockPin = 6;	// to pin 11
int dataPin = 4;	// to pin 14

byte leds = 0;

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() 
{
  //	leds = 0;
  //	updateShiftRegister();
  	for (int i = 0; i < 256; i++)
  	{
    	//bitSet(leds, i);
    	leds = leds+1;
    	updateShiftRegister();
    	delay(300);
  	}
}

void updateShiftRegister()
{
   	digitalWrite(latchPin, LOW);
   	shiftOut(dataPin, clockPin, MSBFIRST, leds);
   	digitalWrite(latchPin, HIGH);
}