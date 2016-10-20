/*
  LiquidCrystal Using Sparkfun LCD Button shield
  https://www.sparkfun.com/products/13293

NOTE:   This uses different hook up than what the examples in
		the arduino library use.  see 



  The circuit:
 * LCD RS pin to digital pin 12  (8 for shield)
 * LCD Enable pin to digital pin 11 (9 for shield)
 * LCD D4 pin to digital pin 5   (D4)
 * LCD D5 pin to digital pin 4   (D5 for shield)
 * LCD D6 pin to digital pin 3   (D6 for shield)
 * LCD D7 pin to digital pin 2   (D7 for shield)
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
// for the sparkfun shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	Serial.begin(9600);  //for debugging

}

char* buttons[] = {"Left", "Up", "Down", "Right", "Select", "Undefined"};

#define LEFT_BUTTON 	0
#define UP_BUTTON 		1
#define DN_BUTTON 		2
#define RIGHT_BUTTON 	3
#define SEL_BUTTON	 	4
#define UNDEFINED 		5

int buttonindex;

void loop()
{
	int buttonValue = 1023;
	lcd.clear();
	lcd.print("Press Any Button");
	
	while (buttonValue > 1015) 
	{
		buttonValue = analogRead(A0);
	    Serial.println(buttonValue);
	}
	
 	if (buttonValue > 845 && buttonValue < 865)  // left button
	{
		buttonindex = LEFT_BUTTON;
	}
	else if (buttonValue > 915 && buttonValue < 949)  // UP button
	{
		buttonindex = UP_BUTTON;
	}
	else if (buttonValue > 895 && buttonValue < 910) // down button
	{
		buttonindex = DN_BUTTON;
	}
	else if (buttonValue > 810 && buttonValue < 820) // right button
	{
		buttonindex = RIGHT_BUTTON;
	}
	else if (buttonValue > 605 && buttonValue < 620) // select button
	{
		buttonindex = SEL_BUTTON;
	}
	else buttonindex = UNDEFINED;
	lcd.clear();
	lcd.print(buttons[buttonindex]);
	lcd.print("  pressed");
	// wait for key to be releasted

	while (buttonValue < 1000) 
	{
		buttonValue = analogRead(A0);
	};  // sit in this loop till key unpressed
	
}

