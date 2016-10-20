/*  Ultrasonic Sensor HC-SR04
 *  With warning LED
 */

#include <LiquidCrystal.h>
#include <MsTimer2.h>

#define trigPin 9
#define echoPin 10

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
int checkLed = 10;			// controls how often we see if led needst to blink
const int blinkPin = 7;		// warning led connected to this led
int blinkRate = 1000;    	// start with led on and off for 1 sec
long time;					// used to store current time and compare with lasttime
long lasttime;				// stores the last time that warning led was toggled


void setup()
{
	Serial.begin(9600);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(blinkPin, OUTPUT);

	MsTimer2::set(checkLed, blink);
	MsTimer2::start();
	lasttime = millis();
	time = lasttime;
	lcd.begin(16, 2);	// start LCD display
}

void loop()
{
	float duration, distance;

	digitalWrite(trigPin, LOW);		// Clears the trigPin
	delayMicroseconds(2);


	digitalWrite(trigPin, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
	delayMicroseconds(10);

	digitalWrite(trigPin, LOW); 		// Now pulse LOW and use pulseIn to measure pulse
	duration = pulseIn(echoPin, HIGH);  // width on echo pin
	distance = (duration / 2) * 0.0344;

	lcd.clear();  // prepare to write new message


	lcd.print(distance, 0);
	lcd.print(" cm");
	distance = distance / 2.54;
	lcd.setCursor(0, 1); // bottom left
	lcd.print(distance, 0);
	lcd.print(" in");
	blinkRate =  7 * distance;  // as distance decreases decrease the time led is on/off, thus increasing it's rate


	delay(500);
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
