/*
Binary Quiz game using 74HC595 shift registers 

*/

int latchPin = 5;   // to pin 12
int clockPin = 6;	// to pin 11
int dataPin = 4;	// to pin 14

int number = 0;
int answer = 0;


void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
  displayNumber(0);
}

void displayNumber(byte a)
{
	// sends byte to be displayed on the LEDs
	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, LSBFIRST, a);
	digitalWrite(latchPin, HIGH);
}

void getAnswer()
{
	// receive the answer from the player
	int z = 0;
	Serial.flush();
	while(Serial.available() == 0)
	{
		//do nothing until something comes into the serial buffer
	}
	// one character of serial data is available, begin calculating
	while(Serial.available() > 0)
	{
		// move any previous digit to the next column on the left; in
		// other words, 1 becomes 10 while there is data in the buffer
		answer = answer * 10;
		// read the next number in the buffer and subtract the character '0'
		// from it to convert it to the actual integer number
		z = Serial.read() - '0';
		// add this digit into the accumulating value
		answer = answer + z;
		// allow a short delay for any more numbers to come into Serial.available
		delay(5);
	}
	Serial.print("You entered: ");
	Serial.println(answer);
}

void checkAnswer()
{
	//check the answer from the player and show the results
	if (answer == number)  // Correct!
	{
		Serial.print("Correct! ");
		Serial.print(answer, BIN);
		Serial.print(" equals ");
		Serial.println(number);
		Serial.println();
	}
	else  // Incorrect
	{
		Serial.print("Incorrect, ");
		Serial.print(number, BIN);
		Serial.print(" equals ");
		Serial.println(number);
		Serial.println();
	}
	answer = 0;
	delay(10000);
}
void loop() 
{
	number = random(256);
	displayNumber(number);
	Serial.println("What is the binary number in base-10? ");
	getAnswer();
	checkAnswer();
}
