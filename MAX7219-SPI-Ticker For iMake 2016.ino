#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

class Flasher
{
	// Class Member Variables
	// These are initialized at startup
	int ledPin;      // the number of the LED pin
	long OnTime;     // milliseconds of on-time
	long OffTime;    // milliseconds of off-time

	// These maintain the current state
	int ledState;             		// ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated

	// Constructor - creates a Flasher
	// and initializes the member variables and state
public:
	Flasher(int pin, long on, long off)
	{
		ledPin = pin;
		pinMode(ledPin, OUTPUT);

		OnTime = on;
		OffTime = off;

		ledState = LOW;
		previousMillis = 0;
	}

	void Update(unsigned long currentMillis)
	{
		if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
		{
			ledState = LOW;  // Turn it off
			previousMillis = currentMillis;  // Remember the time
			digitalWrite(ledPin, ledState);  // Update the actual LED
		}
		else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
		{
			ledState = HIGH;  // turn it on
			previousMillis = currentMillis;   // Remember the time
			digitalWrite(ledPin, ledState);	  // Update the actual LED
		}
	}
	void ChangeRate(long on, long off)
	{
		OnTime = on;
		OffTime = off;
		ledState = LOW;
		previousMillis = millis();
		digitalWrite(ledPin, LOW);
	
	}
	void pause()
	{
		previousMillis = previousMillis+1;
	}
};

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 2;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "Welcome To TheLab.MS Be a Maker, Not A Faker!!";
int wait = 40; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels

// These variables are constructors for the leds

Flasher led1(7, 100, 900);
Flasher led2(6, 300, 700);
Flasher led3(5, 500, 500);
Flasher led4(4, 700, 300);

#define MAXPATTERNS 7

void ChangePattern();
int CurrentPattern = 1;
boolean TogglePattern = false;

void setup()
{
	Serial.begin(9600);
	matrix.setIntensity(7); // Use a value between 0 and 15 for brightness


	// Timer0 is already used for millis() - we'll just interrupt somewhere
	// in the middle and call the "Compare A" function below
	OCR0A = 0xAF;
	TIMSK0 |= _BV(OCIE0A);
	pinMode(2, INPUT);

}
// Interrupt is called once a millisecond
SIGNAL(TIMER0_COMPA_vect)
{
	unsigned long currentMillis = millis();

	if (digitalRead(2) == LOW)
	{
		led1.Update(currentMillis);
		led2.Update(currentMillis);
		led3.Update(currentMillis);
		led4.Update(currentMillis);
	}
	else
	{
		led1.pause();
		led2.pause();
		led3.pause();
		led4.pause();
	}
	if(TogglePattern == true && digitalRead(3) == LOW)
	{
		TogglePattern = false;
		ChangePattern();
	}
	if (digitalRead(3) == HIGH)
	{
		TogglePattern = true;
	}
}

void ChangePattern()
{
	if(CurrentPattern < MAXPATTERNS)
	{
		CurrentPattern += 1;
	}
	else
	{
		CurrentPattern = 1;
	}
	switch (CurrentPattern)
	{
		case 1:
			ApplyPattern(100,900,300,700,500,500,700,300);
			break;
		case 2:
			ApplyPattern(950,50,300,700,800,200,100,900);
			break;
		case 3:
			ApplyPattern(25,100,50,300,100,100,200,200);
			break;
		case 4:
			ApplyPattern(900,100,100,500,150,150,500,500);
			break;
		case 5:
			ApplyPattern(700,300,500,500,300,700,100,900);
			break;
		case 6:
			ApplyPattern(100,100,200,200,400,400,800,800);
			break;
		case 7:
			ApplyPattern(500,1000,2000,500,500,2500,500,4000);
			break;
	}

}

void ApplyPattern(int led1on, int led1off, int led2on, int led2off, int led3on, int led3off, int led4on, int led4off)
{
	led1.ChangeRate(led1on, led1off);
	led2.ChangeRate(led2on, led2off);
	led3.ChangeRate(led3on, led3off);
	led4.ChangeRate(led4on, led4off);
}

void loop()
{
	Serial.print("Current pattern is: ");
	Serial.println(CurrentPattern);

	for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ )
	{

		matrix.fillScreen(LOW);

		int letter = i / width;
		int x = (matrix.width() - 1) - i % width;
		int y = (matrix.height() - 8) / 2; // center the text vertically

		while ( x + width - spacer >= 0 && letter >= 0 )
		{
			if ( letter < tape.length() )
			{
				matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
			}

			letter--;
			x -= width;
		}

		matrix.write(); // Send bitmap to display

		delay(wait);
	}

}
