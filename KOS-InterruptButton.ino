//Upload this code, open the Serial monitor window
//and press the Interrupt Button on the Kit-on-a-Shield

const int button1       = 2;
volatile int ISRCounts  = 0;
volatile int ISRFired   = 0;

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);

	pinMode (button1, INPUT);
	attachInterrupt(digitalPinToInterrupt(button1), button1ISR, RISING);
	interrupts();

}

void loop()
{
	// put your main code here, to run repeatedly:

	if (ISRFired == 1)
	{
		Serial.print ("ISR Triggered. Count = " );
		Serial.println (ISRCounts);
		ISRFired = 0;
	}

}

void button1ISR()
{

	ISRFired = 1;
	ISRCounts++;

}
