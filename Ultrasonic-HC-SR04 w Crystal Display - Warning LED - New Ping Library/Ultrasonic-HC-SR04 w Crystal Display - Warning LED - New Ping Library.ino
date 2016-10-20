// work in progress, trying to combine infrared

#include <LiquidCrystal.h>
#include <IRremote.h>
#include <MsTimer2.h>
#include <NewPing.h>

#define trigPin 10
#define echoPin 8

#define RECV_PIN 6	// 

#define TRIGGER_PIN  10
#define ECHO_PIN     8
#define MAX_DISTANCE 400

/* Crystal Display hookup
 * The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K potentiometer:
 * ends to +5V and ground
 * wiper to LCD VO pin
 */

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int checkLed = 10;		// How many ms to load into Timer2
const int blinkPin = 7;		// warning led connected to this led
int blinkRate = 1000;    // start with led on and off for 1 sec
long time;
long lasttime;
long lastping;
IRsend irsend;
IRrecv irrecv(RECV_PIN);
decode_results IRcodereceived;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float duration, distance;

void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn(); // Start the receiver
	
	lcd.begin(16, 2);	// start LCD display

	pinMode(trigPin, OUTPUT); 	// Setup digital pins
	pinMode(echoPin, INPUT);
	pinMode(blinkPin, OUTPUT);
	pinMode(RECV_PIN, INPUT);

	MsTimer2::set(checkLed, blink);
	MsTimer2::start();
	lasttime = millis();
	time = lasttime;
	lastping = lasttime;

	// testing IR send led
	// irsend.enableIROut(38);
//irsend.mark(0);
}

void loop()
{
	char incomingByte;
	update_sonar();
/*	if (irrecv.decode(&IRcodereceived))
	{
		irrecv.resume(); // Receive the next value
		delay(200);
	}
*/
	if (Serial.available() > 0)
	{
		// read the incoming byte:
		incomingByte = Serial.read();
		switch (incomingByte)
		{
			case 'a':
				for (int i = 0; i < 3; i++)
				{
					Serial.println("Sending IR Code");
					irsend.sendRaw(0x6106C03F, 32, 38); // Sony TV power code
				
					delay(100);
				}
		}
		// say what you got:
		Serial.print("I received: ");
		Serial.println(incomingByte);
	}
	
}
void update_lcd()
{
	lcd.clear();  // prepare to write new message
	if (distance >= MAX_DISTANCE || distance <= 2)
	{
		lcd.println("Out of range");
		blinkRate = 1000;     // reset the blink rate of the led
	}
	else
	{
		lcd.print(distance);
		lcd.print(" cm");
		blinkRate =  7 * distance;  // as distance decreases decrease the time led is on/off, thus increasing it's rate
	}
/*	lcd.setCursor(0, 1); // bottom left

	lcd.print("IR Code = ");
	lcd.print(IRcodereceived.value, HEX);*/
}
void update_sonar()
{

	time = millis();
	if ((time - lastping) > 400)
	{
		lastping = time;
		int uS = sonar.ping();
		distance = (uS / 2) * 0.0344;

		// convert distance to inches
		// distance = distance / 2.54;
		update_lcd();
	}
}

/* Interrupt service routing called by Timer2, toggle LED
 * Rate increases as object draws closer
 */

void blink()
{
	static boolean blinkLed;

	time = millis();

	if ((time - lasttime) > blinkRate)  // is it time to toggle LED?
	{
		blinkLed = !blinkLed;
		digitalWrite(blinkPin, blinkLed);
		lasttime = time;
	}
}
