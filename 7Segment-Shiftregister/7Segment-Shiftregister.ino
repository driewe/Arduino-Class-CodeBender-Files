   /*
Using the 74HC595 to a 7 segment display


*/

int latchPin = 5;   // to pin 12
int clockPin = 6;	// to pin 11
int dataPin = 4;	// to pin 14

// first 16 spots have value to light 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, b, C, D, E and F.  
// the 17th spot is 0 for blanking display - used for numbers that do not require all 
// four digts.  The 18th spot has the value of 2 which will produce the dash, used for 
// out of range..
int digits[] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 156, 122, 158, 142, 0, 2};


void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
 Serial.begin(9600);
 //displayNumber(3456);
}

void loop() 
{

	int i;
	for(i = 0; i < 13000; i++)
	{
		displayNumber(i);
		// delay(10);
	}
}

void displayNumber(int n)
{
	int digit3=0, digit2=0, digit1=0, digit0=0;

	//Serial.println("Displaying Something");

	if(n > 9999)   // check to see if number requires more than 4 digits
	{
		// index 17 of the digits arraw will contain bits to turn on 
		// dashes.
		digit3 = 17;
		digit2 = 17;
		digit1 = 17;
		digit0 = 17;
	}

	else
	{
		digit3 = n / 1000;
		n = n % 1000;
		if (digit3 == 0) digit3 = 16;  // no leading zero's'.  Setting
		digit2 = n / 100;				// to 16 will blank 7 seg.
		if ((digit3 == 16) && (digit2 == 0)) digit2 = 16;
		n = n % 100;
		digit1 = n / 10;
		if ((digit3 == 16) && (digit2 == 16) && (digit1==0)) digit1 = 16;
		digit0 = n % 10;
	}
	
	//Shift the number out to the displays
	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, LSBFIRST, digits[digit3]); 
	shiftOut(dataPin, clockPin, LSBFIRST, digits[digit2]);
	shiftOut(dataPin, clockPin, LSBFIRST, digits[digit1]);
	shiftOut(dataPin, clockPin, LSBFIRST, digits[digit0]);
	digitalWrite(latchPin, HIGH);
}

