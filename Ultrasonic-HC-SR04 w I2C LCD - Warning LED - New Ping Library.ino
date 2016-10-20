// work in progress, trying to combine infrared

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <MsTimer2.h>
#include <NewPing.h>

#define trigPin 10
#define echoPin 8

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define TRIGGER_PIN  10
#define ECHO_PIN     8
#define MAX_DISTANCE 400

int checkLed = 10;		// How many ms to load into Timer2
const int blinkPin = 7;		// warning led connected to this led
int blinkRate = 1000;    // start with led on and off for 1 sec
long time;
long lasttime;
long lastping;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float duration, distance;

void setup()
{
	Serial.begin(9600);

	pinMode(trigPin, OUTPUT); 	// Setup digital pins
	pinMode(echoPin, INPUT);
	pinMode(blinkPin, OUTPUT);

	lcd.begin(16, 2);
	lcd.setCursor(0, 0);
	MsTimer2::set(checkLed, blink);
	MsTimer2::start();
	lasttime = millis();
	time = lasttime;
	lastping = lasttime;

}

void loop()
{
	char incomingByte;
	update_sonar();
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

}
void update_sonar()
{

	time = millis();
	if ((time - lastping) > 400)    // only check ping and update display if 400 ms passed
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
