/*
 *  A program to test the
 *  Rheingold Heavy / Programming Electronics Academy
 *  "Kit on a Shield for Arduino"
 *
 *
 *  Five tests are available through a serial interface menu...
 *  1.  Test the LEDs
 *  2.  Test the LDR
 *  3.  Test the Piezo
 *  4.  Test the Temperature Sensor
 *  5.  Test the Potentiometers
 *  6.  Test the standard button
 *
 *  Additionally, Button 02 is attached as an interrupt and can be triggered at any time.
 *
 *  https://programmingelectronics.com
 *  http://www.rheingoldheavy.com
 *
 */

const int pot01         = A0;
const int pot02         = A1;
const int LDRPin        = A2;
const int piezoPin      = A3;
const int tempSensor    = A4;
const int button1       = 2;
const int button2       = 5;
const int LEDS[]        = {6, 7, 8, 9, 10, 11, 12, 13};

int showSerial          = 1;
int testMode            = 0;         // Holds the value indicating which test to run.

volatile int ISRCounts  = 0;
volatile int ISRFired   = 0;

void setup()
{

	attachInterrupt(digitalPinToInterrupt(button1), button1ISR, RISING);
	interrupts();

	Serial.begin(9600);

	for (int i = 0; i < 8; i++)
	{
		pinMode (LEDS[i], OUTPUT);
	}

	pinMode (button1, INPUT);
	pinMode (button2, INPUT);

}

void loop()
{

	testMode = 0;

	ShowSerialInterface();

	switch (testMode)
	{
		case 0:
			break;
		case 1:
			testMode = 0;
			LEDTest();
			Serial.println();
			Serial.println();
			break;
		case 2:
			testMode = 0;
			LDRTest();
			Serial.println();
			Serial.println();
			break;
		case 3:
			testMode = 0;
			playTones();
			Serial.println();
			Serial.println();
			break;
		case 4:
			testMode = 0;
			temperatureTest();
			Serial.println();
			Serial.println();
			break;
		case 5:
			testMode = 0;
			potTest();
			Serial.println();
			Serial.println();
			break;
		case 6:
			testMode = 0;
			buttonTest();
			Serial.println();
			Serial.println();
			break;
		default:
			testMode = 0;
			Serial.print ("An invalid selection was made: ");
			Serial.println (testMode);
			Serial.println();
			Serial.println();
			break;
	}

}

void ShowSerialInterface()
{
	Serial.println("===================================================");
	Serial.println("Select which test to perform...");
	Serial.println();
	Serial.println("Enter 1 to test the LEDs.");
	Serial.println("Enter 2 to test the LDR.");
	Serial.println("Enter 3 to test the Piezo.");
	Serial.println("Enter 4 to test the Temperature Sensor.");
	Serial.println("Enter 5 to test the Potentiometers.");
	Serial.println("Enter 6 to test the Digital Button (B01).");
	Serial.println();
	Serial.println("The Interrupt Button (B00) may be pressed at any time to trigger the ISR.");
	Serial.println();
	Serial.println("===================================================");
	Serial.println();

	while (Serial.available() == 0) ;  // Wait here until input buffer has a character
	{
		testMode = Serial.parseInt();
	}
}

void button1ISR()
{

	ISRCounts++;
	Serial.print ("ISR Triggered. Count = " );
	Serial.println (ISRCounts);
	Serial.println ();
}

void temperatureTest()
{

	float tempValue = 0;

	tempValue = analogRead(tempSensor);
	Serial.println  ("Ambient Temperature...");
	Serial.print    ("Temp Raw: ");
	Serial.println  (tempValue);
	Serial.print    ("Temp In Fahrenheit: ");
	Serial.println  ((tempValue * .0048) / .010);
	Serial.println  ();

	Serial.println  ("Place finger on temperature sensor for 3 seconds...");
	delay(5000);

	tempValue = analogRead(tempSensor);
	Serial.print    ("Temp Raw: ");
	Serial.println  (tempValue);
	Serial.print    ("Temp In Fahrenheit: ");
	Serial.println  ((tempValue * .0048) / .010);
	Serial.println  ();

}

void potTest()
{

	Serial.println ("Starting test in 5 seconds...");
	delay(5000);

	long startMillis = millis();
	while (millis() - startMillis < 2500)
	{
		Serial.print   ("10K POT01: ");
		Serial.print   (analogRead(pot01));
		Serial.print   ("   10K POT02: ");
		Serial.print   (analogRead(pot02));
		Serial.println ();
	}
}

void LDRTest()
{

	Serial.println ("Starting test in 3 seconds...");
	delay(3000);

	long startMillis = millis();
	while (millis() - startMillis < 2500)
	{
		Serial.print   ("LDR Level: ");
		Serial.print   (analogRead(LDRPin));
		Serial.println ();
	}

}

void LEDTest()
{


	Serial.println ("All LEDs On.");
	for (int i = 0; i < 8; i++)
	{
		digitalWrite (LEDS[i], HIGH);
	}
	delay(1000);

	Serial.println ("All LEDs Off.");
	for (int i = 0; i < 8; i++)
	{
		digitalWrite (LEDS[i], LOW);
	}
	delay(1000);

	Serial.println ("LEDs Scanning...");
	for (int i = 0; i < 8; i++)
	{
		for (int n = 1; n < 10; n++)
		{
			digitalWrite(LEDS[i], HIGH);
			delay(25);
			digitalWrite(LEDS[i], LOW);
			delay(25);
		}
		if (i > 0)  digitalWrite(LEDS[i - 1], LOW);
		delay(40);
	}


}

void buttonTest()
{

	int exitTest = 0;

	Serial.println ("Press the Digital Button (B01) to exit the test...");
	Serial.println ();

	while (exitTest == 0)
	{

		int  button2Press = 1;

		while (digitalRead(button2) == HIGH)
		{
			if (button2Press  == 1)
			{
				button2Press     = 0;
				Serial.println ("Digital Button (B01) Pressed...");
				playTones ();
				exitTest = 1;
			}
		}
	}
}

void playTones()
{

	Serial.println  ("Playing 250hz Tone...");
	tone (piezoPin, 250);
	delay(100);

	Serial.println  ("Playing 440hz Tone...");
	tone (piezoPin, 440);
	delay(100);

	Serial.println  ("Playing 660hz Tone...");
	tone (piezoPin, 660);
	delay(100);

	Serial.println  ("Playing 880hz Tone...");
	tone (piezoPin, 880);
	delay(100);

	noTone (piezoPin);

}
