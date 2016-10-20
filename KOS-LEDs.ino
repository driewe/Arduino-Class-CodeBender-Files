/*Upload the code to watch the LEDs
  light up back and forth.
*/

const int LED0 =  6;
const int LED1 =  7;
const int LED2 =  8;
const int LED3 =  9;
const int LED4 = 10;
const int LED5 = 11;
const int LED6 = 12;
const int LED7 = 13;

void setup()
{

	pinMode (LED0, OUTPUT);
	pinMode (LED1, OUTPUT);
	pinMode (LED2, OUTPUT);
	pinMode (LED3, OUTPUT);
	pinMode (LED4, OUTPUT);
	pinMode (LED5, OUTPUT);
	pinMode (LED6, OUTPUT);
	pinMode (LED7, OUTPUT);


}

void loop()
{

	// ALL LEDS ON
	for (int i = LED0; i < LED7 + 1; i++)
	{
		digitalWrite (i, HIGH);
	}
	delay(250);

	// ALL LEDS OFF
	for (int i = LED0; i < LED7 + 1; i++)
	{
		digitalWrite (i, LOW);
	}
	delay(250);

	// SCAN UP
	for (int i = LED0; i < LED7; i++)
	{
		digitalWrite(i, HIGH);
		if (i == LED0) digitalWrite(i + 1, LOW);
		if (i > LED0) digitalWrite(i - 1, LOW);
		delay(40);
	}

	// SCAN DOWN
	for (int i = LED7; i > LED0; i--)
	{
		digitalWrite(i, HIGH);
		if (i == LED7) digitalWrite(i - 1, LOW);
		if (i < LED7) digitalWrite(i + 1, LOW);
		delay(40);
	}

}
