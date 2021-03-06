/*
  LiquidCrystal Library - Autoscroll
  https://www.arduino.cc/en/Tutorial/LiquidCrystalAutoscroll

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch demonstrates the use of the autoscroll()
 and noAutoscroll() functions to make new text scroll or not.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalAutoscroll

 */

String banner = "Welcome To HackerspaceTech               ";

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
		// set the cursor to (0,0):
	lcd.setCursor(0, 0);
	Serial.begin(9600);
}

void loop()
{
	int limit = banner.length();
	//lcd.autoscroll();
	Serial.print("String Length = ");
	Serial.println(limit);
	for (int thisChar = 0; thisChar < limit; thisChar++)
	{
		lcd.print(banner[thisChar]);
		if(thisChar == 16) lcd.autoscroll();
		Serial.print("Displaying character: ");
		Serial.println(banner[thisChar]);
		delay(300);
	}

	
	// turn off automatic scrolling
	// lcd.noAutoscroll();

	// clear screen for the next loop:
	//lcd.clear();
	 //lcd.setCursor(0, 0);
}
