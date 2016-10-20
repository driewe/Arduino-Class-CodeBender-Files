/*
Using the 74HC595 to control 8 leds (outputs) without giving up 8 ports on the arduino uno. 
Three outputs from the arduino are used to shift the data out in serial to the 74HC595 were it 
is then parceled out to each of its individual pins. 

*/

int latchPin = 5;   // to pin 12
int clockPin = 6;	// to pin 11
int dataPin = 4;	// to pin 14

long int leds = 1;

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
	
  	for (int i = 0; i < 47; i++)
  	{
  		if( i < 24 )
  			leds = leds << 1;
  		else
  			leds = leds >> 1;
    	updateShiftRegister();
    	delay(300);
  	}
}

void myshiftOut(int myDataPin, int myClockPin, long int myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  long int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=23; i>=0; i--)  
  //for(i=0; i<25;i++)
  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
   
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}


void updateShiftRegister()
{
   	digitalWrite(latchPin, LOW);
   	myshiftOut(dataPin, clockPin, leds);
   	digitalWrite(latchPin, HIGH);
}

