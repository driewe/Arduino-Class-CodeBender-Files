/*
Using the 74HC595 to control 8 leds (outputs) without giving up 8 ports on the arduino uno. 
Three outputs from the arduino are used to shift the data out in serial to the 74HC595 were it 
is then parceled out to each of its individual pins. 

When running without delay the clock pin runs at 59.8Khz

*/

int latchPin = 5;   // to pin 12
int clockPin = 6;	// to pin 11
int dataPin = 4;	// to pin 14
int d = 50;			// delay

byte leds = 0;
int patternright[] = {1, 2, 4, 8, 16, 32, 64, 128};  
int patternleft[] = {128, 64, 32, 16, 8, 4, 2, 1};	

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() 
{
  	for (int i = 0; i < 8; i++)		// move led to the right through the first shift register
  	{
  		leds = 0;
		blankShiftRegister();		// send to blank bytes to clear out any leds on the other two shift registers
		blankShiftRegister();
    	leds = patternright[i];		// apply the pattern and output it
    	updateShiftRegister();		// hold for delay
    	delay(d);
  	}
	leds = 0;
	blankShiftRegister();		
  	for (int i = 0; i < 8; i++)		// start on the second shift register
  	{								// shift pattern in but do not display it until it
  		leds = patternright[i];		// has been shifted into through the first shift register to 
  		blankShiftRegister();		// the second one.
  		leds = 0;					// blank byte will push the pattern on through, where it will then
  		updateShiftRegister();		// be displayed
  		delay(d);
  	}
  	for (int i = 0; i < 8; i++)		// Third shift register
  	{
  		leds = patternright[i];
  		blankShiftRegister();		// shift pattern into the first shift registr but do not update yet
  		leds = 0;					// shift into second by pushing a zero byte into first
  		blankShiftRegister();		
  		updateShiftRegister();		// move patter to the third shift register and update
  		delay(d);
  	}
  	
  	//  Led has been moved through all three shift registers and is now at the far right, time to bring
  	//  it back to the left end.
  	
  	for (int i = 1; i < 8; i++)
  	{
  		leds = patternleft[i];
  		blankShiftRegister();
  		leds=0;
  		blankShiftRegister();
  		updateShiftRegister();
  		delay(d);
  	}
  	for (int i = 0; i < 8; i++)
  	{
  		leds = patternleft[i];
  		blankShiftRegister();
  		leds = 0;
  		updateShiftRegister();
  		delay(d);
  	}
  	for (int i = 0; i < 7; i++)
  	{
  		leds = 0;
		blankShiftRegister();
		blankShiftRegister();
  		leds = patternleft[i];
  		updateShiftRegister();
  		delay(d);
  	}
}

void updateShiftRegister()
{
   	digitalWrite(latchPin, LOW);
   	shiftOut(dataPin, clockPin, MSBFIRST, leds);
   	digitalWrite(latchPin, HIGH);
}
void blankShiftRegister()
{
	shiftOut(dataPin, clockPin, MSBFIRST, leds);
}