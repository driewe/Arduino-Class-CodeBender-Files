#include <Servo.h>

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
};

class Sweeper
{
	Servo servo;              // the servo
	int pos;              // current servo position
	int increment;        // increment to move for each interval
	int  updateInterval;      // interval between updates
	unsigned long lastUpdate; // last update of position

public:
	Sweeper(int interval)
	{
		updateInterval = interval;
		increment = 1;
	}

	void Attach(int pin)
	{
		servo.attach(pin);
	}

	void Detach()
	{
		servo.detach();
	}

	void Update(unsigned long currentMillis)
	{
		if((currentMillis - lastUpdate) > updateInterval)  // time to update
		{
			lastUpdate = millis();
			pos += increment;
			servo.write(pos);
			if ((pos >= 180) || (pos <= 0)) // end of sweep
			{
				// reverse direction
				increment = -increment;
			}
		}
	}
};


Flasher led1(11, 100, 900);
Flasher led2(12, 450, 450);
Flasher led3(13, 500, 100);

Sweeper sweeper1(20);
Sweeper sweeper2(55);

void setup()
{
	sweeper1.Attach(9);
	sweeper2.Attach(10);

	// Timer0 is already used for millis() - we'll just interrupt somewhere
	// in the middle and call the "Compare A" function below
	OCR0A = 0xAF;
	TIMSK0 |= _BV(OCIE0A);  
}

// Interrupt is called once a millisecond
SIGNAL(TIMER0_COMPA_vect)
{
	unsigned long currentMillis = millis();
	sweeper1.Update(currentMillis);

	if(digitalRead(2) == HIGH)
	{
		sweeper2.Update(currentMillis);
		led1.Update(currentMillis);
	}

	led2.Update(currentMillis);
	led3.Update(currentMillis);
}

void loop()
{
} 