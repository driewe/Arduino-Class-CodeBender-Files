
// include the library code: for Adafruit RGB LCD
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
//#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

#define MAX_MENU_ITEMS 8

char* Menu[] = {"1 After Another", "1 at a time", "Ping Pong",
                "Random LED", "Marquee", "Binary Count", "Increase Delay",
                "Decrease Delay"
               };

// Pin definitions:
// The 74HC595 uses a type of serial connection called SPI
// (Serial Peripheral Interface) that requires three pins:

int datapin = 2;
int clockpin = 3;
int latchpin = 4;



// We'll also declare a global variable for the data we're
// sending to the shift register:
byte data = 0;
int index = 0;								// current bit that is being acted on
int menuIndex = 0;   						// actively displayed menu item
int activePattern = 0;
int delayTime = 100;   							// delay in milliseconds
boolean PatternChanged = false;
boolean direction = true;
boolean TimeToTurnOn = true;				// used by
boolean SkipDelay = false;
unsigned long  PreviousMillis, CurrentMillis;  // will store last time LED was updated


void setup()
{
	Serial.begin(9600);
	// Set the three SPI pins to be outputs:

	pinMode(datapin, OUTPUT);
	pinMode(clockpin, OUTPUT);
	pinMode(latchpin, OUTPUT);
	pinMode(13, OUTPUT);
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	lcd.setCursor(0, 0);
	lcd.print("Use up/dn buttons");

	// Timer0 is already used for millis() - we'll just interrupt somewhere
	// in the middle and call the "Compare A" function below
	OCR0A = 0xAF;
	TIMSK0 |= _BV(OCIE0A);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Use up/dn buttons");
	lcd.setCursor(0, 1);
	lcd.print(Menu[menuIndex]);


}


// Interrupt is called once a millisecond
SIGNAL(TIMER0_COMPA_vect)
{
	CurrentMillis = millis();

	if (PatternChanged == true)
	{
		PatternChanged = false;
		data = 0;
		direction = true;
		index = 0;
		TimeToTurnOn = true;
	}
	else if (CurrentMillis - PreviousMillis > delayTime || SkipDelay == true)		// is it time to update?
	{
		PreviousMillis = CurrentMillis;
		digitalWrite(13, HIGH);		// for scope trigger
		digitalWrite(13, LOW);

		switch (activePattern)
		{
			case 0:								// One after another
				if(direction == true && index < 7)
				{
					shiftWrite(index, HIGH);
					index += 1;
				}
				else if(direction == true && index == 7)
				{
					direction = false;
					shiftWrite(index, HIGH);
				}
				else if(direction == false && index > 0)
				{

					shiftWrite(index, LOW);
					index -= 1;
				}
				else if (direction == false && index == 0)
				{
					direction = true;
					shiftWrite(index, LOW);
				}
				break;

			case 1:							//  One at a time
				if(TimeToTurnOn == true)
				{
					shiftWrite(index, HIGH);
					TimeToTurnOn = false;
				}
				else						// time to turn off and update index
				{
					shiftWrite(index, LOW);
					TimeToTurnOn = true;

					if (index < 7)
					{
						index += 1;
					}
					else
					{
						index = 0;
					}

				}
				break;
			case 2:						// ping pong
				if(TimeToTurnOn == true)
				{
					shiftWrite(index, HIGH);
					TimeToTurnOn = false;
					SkipDelay = true;
				}
				else						// time to turn off and update index
				{
					shiftWrite(index, LOW);
					TimeToTurnOn = true;
					SkipDelay = false;
					if (direction == true)
					{
						if (index < 7)
						{
							index += 1;
						}
						else
						{
							direction = false;
							index -= 1;
						}
					}
					else				// direction must be false
					{
						if (index > 0)
						{
							index -= 1;
						}
						else
						{
							direction = true;
							index += 1;
						}
					}
				}
				break;

			case 3:						//random
				if(TimeToTurnOn == true)
				{
					index = random(8);
					shiftWrite(index, HIGH);
					TimeToTurnOn = false;
					SkipDelay = true;
				}
				else
				{
					shiftWrite(index, LOW);
					TimeToTurnOn = true;
					SkipDelay = false;
				}
				break;

			case 4:    // Marquee
				if(TimeToTurnOn == true)
				{
					shiftWrite(index, HIGH);
					shiftWrite(index + 4, HIGH);
					TimeToTurnOn = false;
					SkipDelay = false;
				}
				else						// time to turn off and update index
				{
					shiftWrite(index, LOW);
					shiftWrite(index + 4, LOW);
					TimeToTurnOn = true;
					SkipDelay = true;

				
					if (direction == true)
					{
						if (index < 3)
						{
							index += 1;
						}
						else
						{
							direction = false;
							index -= 1;
						}
					}
					else				// direction must be false
					{
						if (index > 0)
						{
							index -= 1;
						}
						else
						{
							direction = true;
							index += 1;
						}
					}
				}


				break;
				
			case 5:				// binary count
				digitalWrite(latchpin, HIGH);

				shiftOut(datapin, clockpin, MSBFIRST, data);

				digitalWrite(latchpin, LOW);
				data++;
		}

	}
}



void loop()
{

	uint8_t buttons = lcd.readButtons();

	if (buttons)
	{
		if (buttons & BUTTON_UP)
		{
			if(menuIndex > 0)
			{
				menuIndex -= 1;

			}
			else
			{
				//menuIndex = 0;
				menuIndex = MAX_MENU_ITEMS - 1;
			}
		}
		if (buttons & BUTTON_DOWN)
		{
			if(menuIndex < MAX_MENU_ITEMS - 1)
			{
				menuIndex += 1;
			}
			else
			{
				//menuIndex = MAX_MENU_ITEMS - 1;
				menuIndex = 0;
			}
		}

		if (buttons & BUTTON_SELECT)		//if select then assign the selected
		{
			//menu item
			if (menuIndex == 6)
			{
				delayTime += 25;
			}
			else if (menuIndex == 7)
			{
				delayTime -= 25;
			}
			else
			{
				activePattern = menuIndex;
				PatternChanged = true;			// flag the change for the ISR
			}

		}
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Use up/dn buttons");
		lcd.setCursor(0, 1);
		lcd.print(Menu[menuIndex]);

	}

}

//
void shiftWrite(int desiredPin, boolean desiredState)
// This function lets you make the shift register outputs
// HIGH or LOW in exactly the same way that you use digitalWrite().
{
	bitWrite(data, desiredPin, desiredState);

	shiftOut(datapin, clockpin, MSBFIRST, data);
	digitalWrite(latchpin, HIGH);
	digitalWrite(latchpin, LOW);
}

