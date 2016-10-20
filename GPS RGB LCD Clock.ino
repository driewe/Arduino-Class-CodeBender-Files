// Adapted from Tony DiCola's program for a GPS 7 Seg Clock.
// I wanted to do more with the GPS Shield so I built mine with 
// an RGB LCD Shield.
//
// original tutorial here: https://learn.adafruit.com/arduino-clock
//
// Must have the Adafruit GPS library installed too!  See:
//   https://github.com/adafruit/Adafruit-GPS-Library
//
// Designed specifically to work with the Adafruit LED 7-Segment backpacks
// and ultimate GPS breakout/shield:
// ----> http://www.adafruit.com/products/881
// ----> http://www.adafruit.com/products/880
// ----> http://www.adafruit.com/products/879
// ----> http://www.adafruit.com/products/878
// ----> http://www.adafruit.com/products/746
//
// Adafruit invests time and resources providing this open source code,
// please support Adafruit and open-source hardware by purchasing
// products from Adafruit!
//
// Written by Tony DiCola for Adafruit Industries.
// Released under MIT a license: https://opensource.org/licenses/MIT

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>   // replaces LED Backpack, using 
// #include <utility/Adafruit_MCP23017.h>
#include <SoftwareSerial.h>
// #include "Adafruit_GFX.h"
#include <Adafruit_GPS.h>
#include <SPI.h>              //for GPS logging
#include <SD.h>

// Set to false to display time in 12 hour format, or true to use 24 hour:
#define TIME_24_HOUR      false

#define HOUR_OFFSET       -6

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

#define DISPLAY_TIME 0
#define DISPLAY_LOCATION 1
#define DISPLAY_SPEEDANGLE 2
#define DISPLAY_ALTITUDESATELLITES 3

SoftwareSerial gpsSerial(8, 7);  // GPS breakout/shield will use a
// software serial connection with
// TX = pin 8 and RX = pin 7.

Adafruit_GPS gps(&gpsSerial);

// update the LCD screen
boolean UpdateGPSLocation = true;    // True when GPS has been parsed
unsigned int LastScreenUpdate = 0;  	// Millis reading of last time screen was updated

boolean morning;   // used when 12 hour format
int hours;
int minutes;
int oldminutes;
int seconds;
int activescreen = DISPLAY_TIME;

void setup()
{
	// Setup function runs once at startup to initialize the display and GPS.
	// Setup Serial port to print debug output.
	Serial.begin(115200);
	Serial.println("Clock starting!");

	// Setup the GPS using a 9600 baud connection (the default for most
	// GPS modules).
	gps.begin(9600);
	// Configure GPS to onlu output minimum data (location, time, fix).
	gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
	// Use a 1 hz, once a second, update rate.
	gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
	// Enable the interrupt to parse GPS data.
	enableGPSInterrupt();
	// Start up LCD
	lcd.begin(16, 2);
	lcd.setBacklight(TEAL);
}

void loop()
{
	CheckGPS();		// check to see if GPS has new data and parse in if so
	
	uint8_t buttons = lcd.readButtons();

	if (buttons)
	{
		lcd.clear();
		lcd.setCursor(0, 0);
		if (buttons & BUTTON_UP)
		{
			activescreen = DISPLAY_LOCATION;
		}
		if (buttons & BUTTON_DOWN)
		{
			activescreen = DISPLAY_TIME;
		}
		if (buttons & BUTTON_LEFT)
		{
			activescreen = DISPLAY_SPEEDANGLE;
		}
		if (buttons & BUTTON_RIGHT)
		{
			activescreen = DISPLAY_ALTITUDESATELLITES;
		}
		if (buttons & BUTTON_SELECT)
		{
			NotABomb();
			delay(1000);
			activescreen = DISPLAY_TIME;
		}
		UpdateGPSLocation = true;    // force redraw
		oldminutes = 0;
	}

	if (activescreen == DISPLAY_TIME)
	{
		DisplayTimeAndDate();
	}
	else if (activescreen == DISPLAY_LOCATION)
	{
		DisplayLocation();
	}
	else if (activescreen == DISPLAY_SPEEDANGLE)
	{
		DisplaySpeedAngle();
	}
	else if (activescreen == DISPLAY_ALTITUDESATELLITES)
	{
		DisplayAltitudeSatellites();
	}
	else
	{
		NotABomb();
		delay(1000);
		activescreen = DISPLAY_TIME;
	}
}

void CheckGPS()
{
	// Check if GPS has new data and parse it.
	if (gps.newNMEAreceived())
	{
		gps.parse(gps.lastNMEA());
		UpdateGPSLocation = true;
	}
	else
	{
		UpdateGPSLocation = false;
	}

	// Grab the current hours, minutes, seconds from the GPS.
	// This will only be set once the GPS has a fix!  Make sure to add
	// a coin cell battery so the GPS will save the time between power-up/down.
	hours = gps.hour + HOUR_OFFSET;  // Add hour offset to convert from UTC


	// to local time.
	// Handle when UTC + offset wraps around to a negative or > 23 value.
	if (hours < 0)
	{
		hours = 24 + hours;
	}
	if (hours > 23)
	{
		hours = 24 - hours;
	}
	minutes = gps.minute;
	seconds = gps.seconds;

	// Do 24 hour to 12 hour format conversion when required.
	// set morning flag accordingly
	if (!TIME_24_HOUR)
	{
		// Handle when hours are past 12 by subtracting 12 hours (1200 value).
		if (hours > 12)
		{
			hours -= 12;
			morning = false;
		}
		// Handle hour 0 (midnight) being shown as 12.
		else if (hours == 0)
		{
			hours += 12;
			morning = true;
		}
		else  if (hours == 12)// hour format ok, if it is 12 set morning flag false
		{
			morning = false;
		}
		else
		{
			morning = true;
		}
	}
}

void DisplayTimeAndDate()
{
	lcd.setBacklight(TEAL);
	
	if (minutes != oldminutes)    	// only updates time when it has changed.
	{
		oldminutes = minutes;
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Time: ");
		lcd.print(hours);
		lcd.print(":");
		if (minutes < 10) lcd.print("0");  //pad 0-9 with a 0
		lcd.print(minutes);
		if (!TIME_24_HOUR)
		{
			if (morning)
			{
				lcd.print(" AM");
			}
			else
			{
				lcd.print(" PM");
			}
		}
		lcd.setCursor(0, 1);
		lcd.print("Date: ");
		lcd.print(gps.month);
		lcd.print("/");
		lcd.print(gps.day);
		lcd.print("/");
		lcd.print(gps.year);
	}

}

void NotABomb()
{
	lcd.setBacklight(RED);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("It's A Clock");
	lcd.setCursor(0, 1);
	lcd.print("NOT a Bomb!!");
}
void DisplayLocation()
{
	lcd.setBacklight(GREEN);
	lcd.setCursor(0, 0);
	if (gps.fix)
	{
		if (UpdateGPSLocation)
		{
			lcd.clear();
			UpdateGPSLocation = false;
			lcd.print("Lat: ");
			lcd.print(gps.latitudeDegrees, 4);
			lcd.setCursor(0, 1);
			lcd.print("Long: ");
			lcd.print(gps.longitudeDegrees, 4);


	/*		Serial.print("Location: ");
			Serial.print(gps.latitude, 4);
			Serial.print(gps.lat);
			Serial.print(", ");
			Serial.print(gps.longitude, 4);
			Serial.println(gps.lon);
			Serial.print("Location (in degrees, works with Google Maps): ");
			Serial.print(gps.latitudeDegrees, 4);
			Serial.print(", ");
			Serial.println(gps.longitudeDegrees, 4);

			Serial.print("Speed (knots): ");
			Serial.println(gps.speed);
			Serial.print("Angle: ");
			Serial.println(gps.angle);
			Serial.print("Altitude: ");
			Serial.println(gps.altitude);
			Serial.print("Satellites: ");
			Serial.println((int)gps.satellites);*/
		}
	}
	
	else
	{
		NoGPSFix();		// Make sure display
	}


}

void DisplaySpeedAngle()
{
	lcd.setBacklight(GREEN);
	lcd.setCursor(0, 0);
	
	if (gps.fix)
	{
		if (UpdateGPSLocation)
		{
			lcd.print("Speed: ");
			lcd.print(gps.speed);
			lcd.setCursor(0,1);
			lcd.print("Angle: ");
			lcd.print(gps.angle);
		}
	}
	else
	{
		NoGPSFix();
	}
}

void DisplayAltitudeSatellites()
{
	lcd.setBacklight(GREEN);
	lcd.setCursor(0, 0);
	
	if (gps.fix)
	{
		if (UpdateGPSLocation)
		{
			lcd.print("Altitude: ");
			lcd.print(gps.altitude);
			lcd.setCursor(0,1);
			lcd.print("Satellites: ");
			lcd.print(gps.satellites);
		}
	}
	else
	{
		NoGPSFix();
	}
}

void NoGPSFix()
{
	if (UpdateGPSLocation)
	{
		lcd.setBacklight(GREEN);
		// oldminutes = minutes;
		lcd.clear();
		lcd.print("No GPS Fix!");
	}
}

SIGNAL(TIMER0_COMPA_vect)
{
	// Use a timer interrupt once a millisecond to check for new GPS data.
	// This piggybacks on Arduino's internal clock timer for the millis()
	// function.
	gps.read();
}

void enableGPSInterrupt()
{
	// Function to enable the timer interrupt that will parse GPS data.
	// Timer0 is already used for millis() - we'll just interrupt somewhere
	// in the middle and call the "Compare A" function above
	OCR0A = 0xAF;
	TIMSK0 |= _BV(OCIE0A);
}
