// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
//#include <utility/Adafruit_MCP23017.h>
#include <MsTimer2.h>
#include <Ultrasonic.h>  // uses grove library

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

#define trigPin 10
#define echoPin 13

Ultrasonic ultrasonic(trigPin,echoPin); // (Trig PIN,Echo PIN)

int checkLed = 10;			// controls how often we see if led needst to blink
const int blinkPin = 7;		// distance led connected to this led / green, always blinks
const int warningPin = 8;
int blinkRate = 1000;    	// start with led on and off for 1 sec
long time;					// used to store current time and compare with lasttime
long lasttime;				// stores the last time that warning led was toggled


void setup()
{
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(blinkPin, OUTPUT);
	
	MsTimer2::set(checkLed, blink);
	MsTimer2::start();
	lasttime = millis();
	time = lasttime;
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	lcd.setBacklight(WHITE);

}

void loop()
{
	long duration, distance;

	// Clears the trigPin
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(echoPin, HIGH);

	// Calculating the distance
	distance = (duration / 2) * 0.0344; 
	//distance = ultrasonic.Ranging(CM);

	if (distance >= 400 || distance <= 5)
	{
		lcd.print("Out of range");
		delay(500);
	}
	else
	{
		lcd.print(distance);
		lcd.print(" cm");
		delay(500);
	}
	blinkRate =  6 * distance;  // as distance decreases decrease the time led is on/off, thus increasing it's rate
	if (distance < 20)
	{
		digitalWrite(warningPin, HIGH);
	}
	else {
		digitalWrite(warningPin, LOW);
	}
	delay(500);
	lcd.clear();
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