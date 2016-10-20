/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 12 Trig to Arduino pin 13
Red POS to Arduino pin 11
Green POS to Arduino pin 10
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define trigPin 10
#define echoPin 13

void setup()
{
	Serial.begin (9600);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}


void loop()
{
	float duration, distance;
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	duration = pulseIn(echoPin, HIGH);
	distance = (duration / 2) * 0.0344;

	if (distance >= 400 || distance <= 2)
	{
		Serial.print("Distance = ");
		Serial.println("Out of range");
	}
	else
	{
		Serial.print("Distance = ");
		Serial.print(distance);
		Serial.println(" cm");
		delay(500);
	}
	delay(500);
}

