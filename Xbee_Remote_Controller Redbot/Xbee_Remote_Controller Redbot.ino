/*****************************************************************
XBee_Remote_Controller.ino

*****************************************************************/
// SoftwareSerial is used to communicate with the XBee
#include <SoftwareSerial.h>

// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

//values read from joy stick i.e. (0-1023)
int xval = 0;
int yval = 0;
int swval = 0;
int xval2 = 0;
int yval2 = 0;
int swval2 = 0;
float temp;


const int xpin = A1;
const int ypin = A2;
const int swpin = A0;   // this is the

const int xpin2 = A4;
const int ypin2 = A5;
const int swpin2 = A3;




void setup()
{
	// Initialize XBee Software Serial port. Make sure the baud
	// rate matches your XBee setting (9600 is default).
	XBee.begin(9600);
	Serial.begin(9600);
	
	// enable pull up on analog pins that are connected to the SEL output
	// of the joystick
	//digitalWrite(A0, HIGH);
	//digitalWrite(A3, HIGH);
}

void loop()
{
	xval = analogRead(xpin);
	temp = (float)xval / (float)1023;
	xval = 255 * temp;

	swval = analogRead(swpin);			// only concered if swval is 0
	if (swval != 0) swval = 255;

	yval2 = analogRead(ypin2);
	temp = (float)yval2 / (float)1023;
	yval2 = 255 * temp;

	swval2 = analogRead(swpin2);


	if (swval2 != 0) swval2 = 255;


	XBee.write(xval);  // This first code will be interpreted for steering
	XBee.write(yval2);  // motor drive
	XBee.write(swval);

	Serial.print("swval = ");
	Serial.println(swval);
	delay(50);
	if (swval == 0) delay(600);  // horn was pressed, give user time to release'

}