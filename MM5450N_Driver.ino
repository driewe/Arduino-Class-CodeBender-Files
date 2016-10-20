// Program..: stairway_v.1_code.pde
// Author...: l.e. hughes
// Date.....: 27 May 2011
// Notes....: Basic, simple example of using shift registers to control the MM5450/5451
//            LED driver. This program was specifically written for the 5450, but should
//            also work with the 5451 and be easily modified for others. The 5450/5451
//            is latching and requires 36 signal databits to send all of the information
//            to control the LEDs (34 for the 5450; 35 for the 5451). There are minor
//            differences in the chip between the manufacturers, please read the appropriate
//            datasheet(s) before connecting power.
//
#define BITSB 8                        // number of bits per byte, used for code clarity
#define DATABITS 36                    // what we must send to the chip in order to control the lights
#define STARTBIT 1                     // value of the starting bit;  

const int clockPin  = 3;               // connect Arduino pin 3 to clock pin (21) on the 5450
const int dataPin   = 6;               // connect Arduino pin 6 to data pin (22) on the 5450
const int delayTime = 200;             // delay between lights

// The following line just computes the number of bytes we will need in the ledArray to hold all of
// bits of data for the signal; it could be declared statically.
//
const int arrayLen  = (int)((DATABITS - 1) / BITSB) + 1;

// This is the actual array that will hold the signal bits. This program, for the 5450/5451, will
// need 5 bytes for a total of 40 bits.
//
byte ledArray[arrayLen];               // for this chip, length is 5 and that could hold 40 values

typedef enum                           // this exists primarily for code clarity
{
    OFF, ON
} ledState;

// Start program -------------------------------------------------------------------------------------
//
void setup()
{
	pinMode(clockPin, OUTPUT);           // we don't need a latch pin since the 5450/5451 latched after
	pinMode(dataPin,  OUTPUT);           // receiving the 36 databits
	allOff();                            // start with all lights off
}

void loop()
{
	allOn();                             // turn all lights on
	sendDatabits();
	delay(delayTime);

	allOff();                            // turn all lights off
	sendDatabits();
	delay(delayTime);

	for(int i = 1; i < DATABITS; i++)    // turn all lights on, in numerical order, starting with light 1
	{
		setLight(i, ON);
		sendDatabits();
		delay(delayTime);
	}

	for(int i = (DATABITS - 1); i > 0; i--)
	{
		setLight(i, OFF);                  // turn all lights off, in reverse numerical order, starting
		sendDatabits();                    // with the last light
		delay(delayTime);
	}

	for(int i = (DATABITS - 1); i > 0; i--)
	{
		setLight(i, ON);                   // turn all lights on, in reverse numerical order, starting
		sendDatabits();                    // with the last light
		delay(delayTime);
	}

	for(int i = 1; i < DATABITS; i++)    // turn all lights off, in numerical order, starting with light 1
	{
		setLight(i, OFF);
		sendDatabits();
		delay(delayTime);
	}

	for(int i = 0; i < 3; i++)            // flash the lights 3 times
	{
		allOn();
		sendDatabits();
		allOff();
		sendDatabits();
		delay(100);
	}
	delay(5000);                          // wait 5 seconds before starting loop over

// Other examples:
//
// setLight(1,ON);                    // This would turn light 1 on
// sendDatabits();
// toggleLight(1);                    // This would turn it off
// sendDatabits();
// setLight(2,ON);                    // Turn on lights 2 and 4
// setLight(4,ON);
// sendDatabits();
}

// Subroutine that sends all of the DATABITS to the chip. It begins by first sending the startbit, then it
// uses the Arduino shiftOut function to send the bits in each byte of the ledArray. I could have put the
// STARTBIT into the ledArray but decided that I liked it better outside of the array. Any time you want
// to turn lights on or off, this routine must be called after setting the appropriate bits in the ledArray.
//
void sendDatabits()
{
	digitalWrite(clockPin, LOW);
	delay(2);
	digitalWrite(dataPin, STARTBIT);
	delay(2);
	digitalWrite(clockPin, HIGH);
	delay(5);
	digitalWrite(clockPin, LOW);
	delay(2);
	for(int i = 0; i < arrayLen; i++)
	{
		shiftOut(dataPin, clockPin, LSBFIRST, ledArray[i]);
	}

}

// Subroutine that takes a light (output pin) as a sole argument and sets the bit value for that pin
// to the opposite of its current setting (toggle).
//
void toggleLight(int pin)
{
	byte arrayElem = int((pin - 1) / BITSB);                 // which element of the ledArray is pin in
	byte byteElem  = (pin - (arrayElem * BITSB)) - 1;        // and which bit in that byte is the pin
	ledArray[arrayElem] ^= (1 << byteElem);                  // toggle byteElem
}

// Subroutine that takes a light (output pin) and an additional argument and sets the bit value
// for that pin appropriately
//
void setLight(int pin, byte val)
{
	byte arrayElem = int((pin - 1) / BITSB);                 // which element of the ledArray is pin in
	byte byteElem  = (pin - (arrayElem * BITSB)) - 1;        // and which bit in that byte is the pin
	ledArray[arrayElem] |= (val << byteElem);                // zero vals require a two-step process,
	if(val == 0)                                             // first we set them to a one and then
	{
		ledArray[arrayElem] ^= (1 << byteElem);                // toggle them
	}
}

// Subroutine that turns all lights on. Because the STARTBIT is 1 or ON, we don't want to set any
// bits above 35 to ON, lest it be interpreted as the start of another set of databits. Better error
// checking would be to make sure that no bit > 35 was ever set to 1.
//
void allOn()
{
	for(int i = 1; i < DATABITS; i++)
	{
		setLight(i, ON);
	}
}

// Subroutine that turns all lights off
//
void allOff()
{
	for(int i = 0; i < arrayLen; i++)
	{
		ledArray[i] = 0;
	}
}
