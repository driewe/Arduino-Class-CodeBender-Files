//Push your buttons and see what happens...

const int  button1 =  2;
const int  button2 =  5;
const int  ledPin = 6;

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);

	pinMode (button1, INPUT);
	pinMode (button2, INPUT);
	pinMode (ledPin, OUTPUT);

}

void loop()
{

	int  button1Press = 1;
	int  button2Press = 1;

	while (digitalRead(button1) == HIGH)
	{
		if (button1Press  == 1)
		{
			Serial.println ("button1 Press");
			button1Press     = 0;
			playTones ();

		}
	}

	while (digitalRead(button2) == HIGH)
	{
		if (button2Press  == 1)
		{
			Serial.println ("button2 Press");
			button2Press     = 0;
			playTones ();
			digitalWrite(ledPin, HIGH);
			delay(100);
			digitalWrite(ledPin, LOW);
		}
	}
}

void playTones()
{

	Serial.println  ("Playing 250hz Tone...");
	tone (A3, 250);
	delay(100);

	Serial.println  ("Playing 440hz Tone...");
	tone (A3, 440);
	delay(100);

	Serial.println  ("Playing 660hz Tone...");
	tone (A3, 660);
	delay(100);

	Serial.println  ("Playing 880hz Tone...");
	tone (A3, 880);
	delay(100);

	noTone (A3);

}
