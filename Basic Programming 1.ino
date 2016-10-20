/*
Connect leds to pins 3,5,6,9,10 and 11 (UNO PWM Pins)
Write a program that varies the brightness on these leds
Store the brightness levels in an array
*/
int ledPins[] = {3, 5, 6, 9, 10, 11};
int ledBrightnessLevels[] = {25, 50, 75, 100, 125, 150, 125, 100, 75, 50};
int ledDelay = 500;

void setup()
{
	// set pins to output
	for (int i = 0; i < sizeof(ledPins); i++)
	{
		pinMode(ledPins[i], OUTPUT);
	}
}

void loop()
{
	for(int a = 0; a < sizeof(ledBrightnessLevels); a++)
	{
		// Apply brightness level to all leds
		for(int x = 0; x < sizeof(ledPins); x++)
		{
			analogWrite(ledPins[x], ledBrightnessLevels[a]);
		}
		// lets brightness level be perceived
		delay(ledDelay);
	}

}
