/*
 * Read light value, contantly calibrating lowest and highest reading
 * map it to the 8 leds
 */

int ledPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
int lightPin = A2;
int minLightLevel = 1023;
int maxLightLevel = 0;
int buzzerPin = A3;
int toneFrequency;


void setup()
{
	for (int i = 0; i < 8; i++)
	{
		pinMode(ledPins[i], OUTPUT);
	}
	Serial.begin(9600);
	pinMode(buzzerPin, OUTPUT);
}

void loop()
{
	int lightLevel;

	int ledMark = 0;   // highest led to display based on reading

	lightLevel = analogRead(lightPin);


	if (lightLevel > maxLightLevel)
	{
		maxLightLevel = lightLevel;
	}
	if (lightLevel < minLightLevel)
	{
		minLightLevel = lightLevel;
	}


	ledMark = map(lightLevel, minLightLevel, maxLightLevel, 0, 8);
	toneFrequency = map(1023-lightLevel, minLightLevel, maxLightLevel, 100, 1000);
	tone(buzzerPin, toneFrequency);
/*	Serial.print("Light Level ");
	Serial.print(lightLevel);
	Serial.print("    Max Light Level  ");
	Serial.print(maxLightLevel);
	Serial.print("   Min Light Level ");
	Serial.println(minLightLevel); */
	Serial.print("Tone Frequency ");
	Serial.println(toneFrequency);

	for(int i = 0; i < 8; i++)
	{
		if (i < ledMark)
		{
			digitalWrite(ledPins[i], HIGH);
		}
		else
		{
			digitalWrite(ledPins[i], LOW);

		}
	}

	delay(300);
}

