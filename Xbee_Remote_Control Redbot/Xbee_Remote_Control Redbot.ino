/*****************************************************************
XBee_Remote_Control.ino

*****************************************************************/
#include <RedBot.h>  // This line "includes" the RedBot library into your sketch.
// Provides special objects, methods, and functions for the RedBot.
RedBotMotors motors; // Instantiate the motor control object. This only needs

#include "notes.h"  // Individual "notes" have been #defined in the notes.h tab to make
// playing sounds easier. noteC4, for example, is defined as 262, the
// frequency for middle C. See the tab above?

RedBotSoftwareSerial XBee;  // version of SoftwareSerial that will work with Redbot

const int buzzerPin = 9;

int xval;
int yval;
int swval=1023;
int leftmotorspeed;
int rightmotorspeed;

float temp;

void setup()
{
	// Initialize XBee Software Serial port. Make sure the baud
	// rate matches your XBee setting (9600 is default).
	XBee.begin(9600);
	Serial.begin(9600);
	pinMode(buzzerPin, OUTPUT);
}

void loop()
{

//	if (XBee.available())
	if (XBee.available())
	{
		xval = XBee.read();
		yval = XBee.read();
		swval = XBee.read();
		//xval = Serial.read();
		//yval = Serial.read();
		//swval = Serial.read();

		//normalize the values to a 1 byte value

		temp = (float)xval / (float)255;
		xval = temp * 1023;

		temp = (float)yval / (float)255;
		yval = temp * 1023;

		temp = (float)swval / (float)255;
		swval = temp * 1023;

		xval = map(xval, 0, 1023, -255, 255);
		yval = map(yval, 0, 1023, -255, 255);

	}

	if(swval == 0) 
	{
		XBee.end();
	//	playSmallWorld();
		blowhorn();
		XBee.begin(9600);
	}
	
	if (xval > -40 && xval < 40)  			// If we are not turning
	{										
		if ((yval < -40) || (yval > 40))    // set motor speed
		{
			rightmotorspeed = yval;
			leftmotorspeed = -yval; 
		}
		else
		{
			rightmotorspeed = 0;
			leftmotorspeed = 0;		
		}
     
	}
	else if (xval>40)  // Turning Left, are we moving while turning left or 
	{					// spinning
		if ((yval < -40) || (yval > 40)) // User is moving forward or backwards
		{
			rightmotorspeed = yval; 	// drive right motor 100% forward
			leftmotorspeed = -yval/2;	// runt left by slowing left wheel
		}
		else    						// spin
		{
			rightmotorspeed = 200;
			leftmotorspeed = 200;
		}
	}
	else			// We are not going straight or turning left, must be right
	{
		if ((yval < -40) || (yval > 40))    // user is moving forward or backwards
		{
			leftmotorspeed = -yval;
			rightmotorspeed = yval/2;
		}
		else
		{
			rightmotorspeed = -200;
			leftmotorspeed = -200;
		}
	}

	motors.rightMotor(rightmotorspeed);
	motors.leftMotor(leftmotorspeed);
	delay(50);
}

void blowhorn()
{
	tone(buzzerPin, 1000);   // Play a 1kHz tone on the pin number held in
	//  the variable "buzzerPin".
	delay(125);   // Wait for 125ms.
	noTone(buzzerPin);   // Stop playing the tone.

	tone(buzzerPin, 2000);  // Play a 2kHz tone on the buzzer pin

	delay(500);   // delay for 1000 ms (1 second)

	noTone(buzzerPin);       // Stop playing the tone.

}

void playSmallWorld()
{
	// we use a custom function below called playNote([note],[duration])
	// to play a note and delay a certain # of milliseconds.
	//
	// Both notes and durations are #defined in notes.h -- WN = whole note,
	// HN = half note, QN = quarter note, EN = eighth note, SN = sixteenth note.
	//
	playNote(noteG5, HN + QN);
	playNote(noteG5, QN);
	playNote(noteB5, HN);
	playNote(noteG5, HN);
	playNote(noteA5, HN + QN);
	playNote(noteA5, QN);
	playNote(noteA5, HN + QN);
	playNote(Rest, QN);
	playNote(noteA5, HN + QN);
	playNote(noteA5, QN);
	playNote(noteC6, HN);
	playNote(noteA5, HN);
	playNote(noteB5, HN + QN);
	playNote(noteB5, QN);
	playNote(noteB5, HN + QN);
	playNote(Rest, QN);
	playNote(noteB5, HN + QN);
	playNote(noteB5, QN);
	playNote(noteD6, HN);
	playNote(noteB5, HN);
	playNote(noteC6, HN + QN);
	playNote(noteC6, QN);
	playNote(noteC6, HN);
	playNote(noteB5, QN);
	playNote(noteA5, QN);
	playNote(noteD5, WN);
	playNote(noteFs5, WN);
	playNote(noteG5, WN);
}

void playNote(int note, int duration)
// This custom function takes two parameters, note and duration to make playing songs easier.
// Each of the notes have been #defined in the notes.h file. The notes are broken down by
// octave and sharp (s) / flat (b).
{
	tone(buzzerPin, note, duration);
	delay(duration);
}