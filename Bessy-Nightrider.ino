// place pins of leds in an array for easy indexing
int ledPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

// how long to hold pattern for visibility
#define BLINKDELAY 140
int blinkDelay = BLINKDELAY;
// amount to decrrease delay on while progressing through pattern giving
// the effect of momentum picking up
int blinkIncrement = 20; 
// number of leds
int leds = 8;

void setup()
{
	// Set pins used for leds to output mode.
	for(int i = 0; i < sizeof(ledPins); i++)
	{
		pinMode(ledPins[i], OUTPUT);
	}
}

void loop()
{
	//turn each led on and off in order starting from ledPins[0]
	// and finishing on ledPins[7]
	blinkDelay = BLINKDELAY;
	for (int i = 0; i < leds; i++)
	{
		digitalWrite(ledPins[i], HIGH);
		if (i!=0)
		{
			digitalWrite(ledPins[i-1], LOW);
		}
		delay(blinkDelay);
		blinkDelay = blinkDelay - blinkIncrement;
	}
	blinkDelay = BLINKDELAY;
	//turn each of the pins on and off in order starting from ledPins[7]
	// and finishing on ledPins[0]
	for (int i = leds-1; i > -1; i--)
	{
		digitalWrite(ledPins[i], HIGH);
		if (i!=leds-1)
		{
			digitalWrite(ledPins[i+1], LOW);
		}
		delay(blinkDelay);
		blinkDelay = blinkDelay - blinkIncrement;
	}
}
