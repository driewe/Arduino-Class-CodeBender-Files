
// based on an orginal sketch by Arduino forum member "danigom"
// http://forum.arduino.cc/index.php?action=profile;u=188950
// I am using this to drive 8x8 LED Matrixes with the MAX7219 controller
//http://www.davidriewe.com/2015/11/expanding-on-my-experiment-with-max7219.html
//
// I am also using Timer2 to generate an interrupt every "period" seconds
// and use that to update a 7 segment display via the I2C interface.
 
#include <avr/pgmspace.h>
#include <LedControl.h>
#include <MsTimer2.h>
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

const int numDevices = 2;      // number of MAX7219s used
const long scrollDelay = 20;   // adjust scrolling speed
const int krdelay = 30;
const int brdelay = 20;
const int pulsePin = 13;

int period = 1000; // 100 milli seconds
int mycounter = 0;
boolean output = HIGH;
 
unsigned long bufferLong [14] = {0}; 
 
 // output pin 12 = dataPin
 // output pin 11 = clkPin, 
 // output pin 10 = csPin, 
 // numDevices = number of MAX7219s used
 
LedControl lc=LedControl(12,11,10,numDevices);  // create instance of LedControl

Adafruit_7segment matrix = Adafruit_7segment();

prog_uchar scrollText[] PROGMEM ={
    "Welcome to the world of Arduino!!!   \0"};
    
void setup(){
    for (int x=0; x<numDevices; x++)
    {
        lc.shutdown(x,false);       //The MAX72XX is in power-saving mode on startup
        lc.setIntensity(x,8);       // Set the brightness to default value
        lc.clearDisplay(x);         // and clear the display
    }
    pinMode(pulsePin, OUTPUT);
    MsTimer2::set(period, flash);
    MsTimer2::start();
    matrix.begin(0x70);
}
 
void loop()
{ 
	scrollMessage(scrollText);
  // scrollFont();
 
	for(int col=0; col<16; col++)
	{
		for(int row=0; row<8; row++)
		{
			if (col < 8)
			{
			lc.setLed(0,col,row, true);
			}
			else
			{
				lc.setLed(1,col-8,row, true);
			}
			delay(brdelay);
			matrix.writeDisplay();
		}
		
	}
	for(int col=0; col<16; col++)
	{
		for(int row=0; row<8; row++)
		{
			if (col < 8)
			{
				lc.setLed(0,col,row,false);
			}
			else
			{
				lc.setLed(1,col-8,row,false);
			}
			
			delay(brdelay);
			matrix.writeDisplay();
		}
	}
	
	
	

  	for (int row=0; row<8; row++)
  	{
    	for (int col=0; col<16; col++)
    	{
    		if (col < 8)
    		{
    			lc.setLed(0,col,row,true);
    		}
    		else
    		{
    			lc.setLed(1,col-8,row,true);
    		}
      		delay(brdelay);
      		matrix.writeDisplay();
    	}
  	}
 
  	for (int row=0; row<8; row++)
  	{
    	for (int col=0; col<16; col++)
    	{
    		if (col < 8)
    		{
    			lc.setLed(0,col,row,false);
    		}
    		else
    		{
    			lc.setLed(1,col-8,row,false);
    		}
      		delay(brdelay);
      		matrix.writeDisplay();
    	}
  	} 
 	
  	// knight rider efffect
  	for (int row=0; row<8; row++)
  	{
  		for(int col=0; col<16; col++)
  		{
  			if (col < 8)
  			{
  				lc.setLed(0,col,row,true);
   				delay(krdelay);
   				matrix.writeDisplay();
   				lc.setLed(0,col,row,false);
  			}
  			else
  			{
  				lc.setLed(1,col-8,row,true);
  	  			delay(krdelay);
  	  			matrix.writeDisplay();
  	  			lc.setLed(1,col-8,row,false);
  			}

  		}
  	}
  	for (int row=7; row>-1;row--)
  	{
  		for(int col=15; col>-1; col--)
  		{
  			if (col > 7)
  			{
  				lc.setLed(1,col-8,row, true);
  				delay(krdelay);
  				matrix.writeDisplay();
  				lc.setLed(1,col-8,row, false);
  			}
  			else
  			{
  				lc.setLed(0,col,row,true);
  				delay(krdelay);
  				matrix.writeDisplay();
  				lc.setLed(0,col,row, false);
  			}
  		}
  	}
  	for (int col=0; col<16; col++)
  	{
  		for(int row=0; row<8; row++)
  		{
  			if (col < 8)
  			{
  				lc.setLed(0,col,row,true);
  				delay(krdelay);
  				matrix.writeDisplay();
  				lc.setLed(0,col,row,false);
  			}
  			else
  			{
  				lc.setLed(1,col-8,row,true);
  				delay(krdelay);
  				matrix.writeDisplay();
  				lc.setLed(1,col-8,row,false);
  			}
  		}
  	}
  	for(int col=15; col>=-1; col--)
  	{
  		for(int row=7; row>-1; row--)
  		{
  			if(col > 7)
  			{
  				lc.setLed(1,col-8,row,true);
  				delay(krdelay);
  				matrix.writeDisplay();
  				lc.setLed(1,col-8,row,false);
  			}
  			else
  			{
  				lc.setLed(0,col,row,true);
  				delay(krdelay);
  				matrix.writeDisplay();
  				lc.setLed(0,col,row,false);
  			}
  		}
  	}
}


 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
prog_uchar font5x7 [] PROGMEM = {      //Numeric Font Matrix (Arranged as 7x font data + 1x kerning data)
    B00000000,	//Space (Char 0x20)
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    6,
 
    B10000000,	//!
    B10000000,
    B10000000,
    B10000000,
    B00000000,
    B00000000,
    B10000000,
    2,
 
    B10100000,	//"
    B10100000,
    B10100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    4,
 
    B01010000,	//#
    B01010000,
    B11111000,
    B01010000,
    B11111000,
    B01010000,
    B01010000,
    6,
 
    B00100000,	//$
    B01111000,
    B10100000,
    B01110000,
    B00101000,
    B11110000,
    B00100000,
    6,
 
    B11000000,	//%
    B11001000,
    B00010000,
    B00100000,
    B01000000,
    B10011000,
    B00011000,
    6,
 
    B01100000,	//&
    B10010000,
    B10100000,
    B01000000,
    B10101000,
    B10010000,
    B01101000,
    6,
 
    B11000000,	//'
    B01000000,
    B10000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    3,
 
    B00100000,	//(
    B01000000,
    B10000000,
    B10000000,
    B10000000,
    B01000000,
    B00100000,
    4,
 
    B10000000,	//)
    B01000000,
    B00100000,
    B00100000,
    B00100000,
    B01000000,
    B10000000,
    4,
 
    B00000000,	//*
    B00100000,
    B10101000,
    B01110000,
    B10101000,
    B00100000,
    B00000000,
    6,
 
    B00000000,	//+
    B00100000,
    B00100000,
    B11111000,
    B00100000,
    B00100000,
    B00000000,
    6,
 
    B00000000,	//,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B01000000,
    B10000000,
    3,
 
    B00000000,	//-
    B00000000,
    B11111000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    6,
 
    B00000000,	//.
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B11000000,
    3,
 
    B00000000,	///
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    B00000000,
    6,
 
    B01110000,	//0
    B10001000,
    B10011000,
    B10101000,
    B11001000,
    B10001000,
    B01110000,
    6,
 
    B01000000,	//1
    B11000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,
 
    B01110000,	//2
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B11111000,
    6,
 
    B11111000,	//3
    B00010000,
    B00100000,
    B00010000,
    B00001000,
    B10001000,
    B01110000,
    6,
 
    B00010000,	//4
    B00110000,
    B01010000,
    B10010000,
    B11111000,
    B00010000,
    B00010000,
    6,
 
    B11111000,	//5
    B10000000,
    B11110000,
    B00001000,
    B00001000,
    B10001000,
    B01110000,
    6,
 
    B00110000,	//6
    B01000000,
    B10000000,
    B11110000,
    B10001000,
    B10001000,
    B01110000,
    6,
 
    B11111000,	//7
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B00100000,
    B00100000,
    6,
 
    B01110000,	//8
    B10001000,
    B10001000,
    B01110000,
    B10001000,
    B10001000,
    B01110000,
    6,
 
    B01110000,	//9
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B00010000,
    B01100000,
    6,
 
    B00000000,	//:
    B11000000,
    B11000000,
    B00000000,
    B11000000,
    B11000000,
    B00000000,
    3,
 
    B00000000,	//;
    B11000000,
    B11000000,
    B00000000,
    B11000000,
    B01000000,
    B10000000,
    3,
 
    B00010000,	//<
    B00100000,
    B01000000,
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    5,
 
    B00000000,	//=
    B00000000,
    B11111000,
    B00000000,
    B11111000,
    B00000000,
    B00000000,
    6,
 
    B10000000,	//>
    B01000000,
    B00100000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    5,
 
    B01110000,	//?
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B00000000,
    B00100000,
    6,
 
    B01110000,	//@
    B10001000,
    B00001000,
    B01101000,
    B10101000,
    B10101000,
    B01110000,
    6,
 
    B01110000,	//A
    B10001000,
    B10001000,
    B10001000,
    B11111000,
    B10001000,
    B10001000,
    6,
 
    B11110000,	//B
    B10001000,
    B10001000,
    B11110000,
    B10001000,
    B10001000,
    B11110000,
    6,
 
    B01110000,	//C
    B10001000,
    B10000000,
    B10000000,
    B10000000,
    B10001000,
    B01110000,
    6,
 
    B11100000,	//D
    B10010000,
    B10001000,
    B10001000,
    B10001000,
    B10010000,
    B11100000,
    6,
 
    B11111000,	//E
    B10000000,
    B10000000,
    B11110000,
    B10000000,
    B10000000,
    B11111000,
    6,
 
    B11111000,	//F
    B10000000,
    B10000000,
    B11110000,
    B10000000,
    B10000000,
    B10000000,
    6,
 
    B01110000,	//G
    B10001000,
    B10000000,
    B10111000,
    B10001000,
    B10001000,
    B01111000,
    6,
 
    B10001000,	//H
    B10001000,
    B10001000,
    B11111000,
    B10001000,
    B10001000,
    B10001000,
    6,
 
    B11100000,	//I
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,
 
    B00111000,	//J
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B10010000,
    B01100000,
    6,
 
    B10001000,	//K
    B10010000,
    B10100000,
    B11000000,
    B10100000,
    B10010000,
    B10001000,
    6,
 
    B10000000,	//L
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B11111000,
    6,
 
    B10001000,	//M
    B11011000,
    B10101000,
    B10101000,
    B10001000,
    B10001000,
    B10001000,
    6,
 
    B10001000,	//N
    B10001000,
    B11001000,
    B10101000,
    B10011000,
    B10001000,
    B10001000,
    6,
 
    B01110000,	//O
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B01110000,
    6,
 
    B11110000,	//P
    B10001000,
    B10001000,
    B11110000,
    B10000000,
    B10000000,
    B10000000,
    6,
 
    B01110000,	//Q
    B10001000,
    B10001000,
    B10001000,
    B10101000,
    B10010000,
    B01101000,
    6,
 
    B11110000,	//R
    B10001000,
    B10001000,
    B11110000,
    B10100000,
    B10010000,
    B10001000,
    6,
 
    B01111000,	//S
    B10000000,
    B10000000,
    B01110000,
    B00001000,
    B00001000,
    B11110000,
    6,
 
    B11111000,	//T
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    6,
 
    B10001000,	//U
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B01110000,
    6,
 
    B10001000,	//V
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    6,
 
    B10001000,	//W
    B10001000,
    B10001000,
    B10101000,
    B10101000,
    B10101000,
    B01010000,
    6,
 
    B10001000,	//X
    B10001000,
    B01010000,
    B00100000,
    B01010000,
    B10001000,
    B10001000,
    6,
 
    B10001000,	//Y
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    B00100000,
    B00100000,
    6,
 
    B11111000,	//Z
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    B11111000,
    6,
 
    B11100000,	//[
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B11100000,
    4,
 
    B00000000,	//(Backward Slash)
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    B00001000,
    B00000000,
    6,
 
    B11100000,	//]
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B11100000,
    4,
 
    B00100000,	//^
    B01010000,
    B10001000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    6,
 
    B00000000,	//_
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111000,
    6,
 
    B10000000,	//`
    B01000000,
    B00100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    4,
 
    B00000000,	//a
    B00000000,
    B01110000,
    B00001000,
    B01111000,
    B10001000,
    B01111000,
    6,
 
    B10000000,	//b
    B10000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B11110000,
    6,
 
    B00000000,	//c
    B00000000,
    B01110000,
    B10001000,
    B10000000,
    B10001000,
    B01110000,
    6,
 
    B00001000,	//d
    B00001000,
    B01101000,
    B10011000,
    B10001000,
    B10001000,
    B01111000,
    6,
 
    B00000000,	//e
    B00000000,
    B01110000,
    B10001000,
    B11111000,
    B10000000,
    B01110000,
    6,
 
    B00110000,	//f
    B01001000,
    B01000000,
    B11100000,
    B01000000,
    B01000000,
    B01000000,
    6,
 
    B00000000,	//g
    B01111000,
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B01110000,
    6,
 
    B10000000,	//h
    B10000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B10001000,
    6,
 
    B01000000,	//i
    B00000000,
    B11000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,
 
    B00010000,	//j
    B00000000,
    B00110000,
    B00010000,
    B00010000,
    B10010000,
    B01100000,
    5,
 
    B10000000,	//k
    B10000000,
    B10010000,
    B10100000,
    B11000000,
    B10100000,
    B10010000,
    5,
 
    B11000000,	//l
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,
 
    B00000000,	//m
    B00000000,
    B11010000,
    B10101000,
    B10101000,
    B10001000,
    B10001000,
    6,
 
    B00000000,	//n
    B00000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B10001000,
    6,
 
    B00000000,	//o
    B00000000,
    B01110000,
    B10001000,
    B10001000,
    B10001000,
    B01110000,
    6,
 
    B00000000,	//p
    B00000000,
    B11110000,
    B10001000,
    B11110000,
    B10000000,
    B10000000,
    6,
 
    B00000000,	//q
    B00000000,
    B01101000,
    B10011000,
    B01111000,
    B00001000,
    B00001000,
    6,
 
    B00000000,	//r
    B00000000,
    B10110000,
    B11001000,
    B10000000,
    B10000000,
    B10000000,
    6,
 
    B00000000,	//s
    B00000000,
    B01110000,
    B10000000,
    B01110000,
    B00001000,
    B11110000,
    6,
 
    B01000000,	//t
    B01000000,
    B11100000,
    B01000000,
    B01000000,
    B01001000,
    B00110000,
    6,
 
    B00000000,	//u
    B00000000,
    B10001000,
    B10001000,
    B10001000,
    B10011000,
    B01101000,
    6,
 
    B00000000,	//v
    B00000000,
    B10001000,
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    6,
 
    B00000000,	//w
    B00000000,
    B10001000,
    B10101000,
    B10101000,
    B10101000,
    B01010000,
    6,
 
    B00000000,	//x
    B00000000,
    B10001000,
    B01010000,
    B00100000,
    B01010000,
    B10001000,
    6,
 
    B00000000,	//y
    B00000000,
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B01110000,
    6,
 
    B00000000,	//z
    B00000000,
    B11111000,
    B00010000,
    B00100000,
    B01000000,
    B11111000,
    6,
 
    B00100000,	//{
    B01000000,
    B01000000,
    B10000000,
    B01000000,
    B01000000,
    B00100000,
    4,
 
    B10000000,	//|
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    2,
 
    B10000000,	//}
    B01000000,
    B01000000,
    B00100000,
    B01000000,
    B01000000,
    B10000000,
    4,
 
    B00000000,	//~
    B00000000,
    B00000000,
    B01101000,
    B10010000,
    B00000000,
    B00000000,
    6,
 
    B01100000,	// (Char 0x7F)
    B10010000,
    B10010000,
    B01100000,
    B00000000,
    B00000000,
    B00000000,
    5
};
 
void flash()
{
	digitalWrite(pulsePin, output);
	output = !output;
	mycounter = mycounter++;
	matrix.print(mycounter);
	if (mycounter>=9999) mycounter=0;
}
 
// Scroll Message
void scrollMessage(prog_uchar * messageString) 
{
    int counter = 0;
    int myChar=0;
    do 
    {
        // read back a char 
        myChar =  pgm_read_byte_near(messageString + counter); 
        if (myChar != 0)
        {
            loadBufferLong(myChar);
        }
        counter++;
    } 
    while (myChar != 0);
}
// Load character into scroll buffer
void loadBufferLong(int ascii)
{
    if (ascii >= 0x20 && ascii <=0x7f)
    {
        for (int a=0;a<7;a++)
        {                      // Loop 7 times for a 5x7 font
            unsigned long c = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + a);     // Index into character table to get row data
            unsigned long x = bufferLong [a*2];     // Load current scroll buffer
            x = x | c;                              // OR the new character onto end of current
            bufferLong [a*2] = x;                   // Store in buffer
        }
        byte count = pgm_read_byte_near(font5x7 +((ascii - 0x20) * 8) + 7);     // Index into character table for kerning data
        for (byte x=0; x<count;x++)
        {
            rotateBufferLong();
            printBufferLong();
            delay(scrollDelay);
        }
    }
}
// Rotate the buffer
void rotateBufferLong()
{
    for (int a=0;a<7;a++)
    {                      						// Loop 7 times for a 5x7 font
        unsigned long x = bufferLong [a*2];     // Get low buffer entry
        byte b = bitRead(x,31);                 // Copy high order bit that gets lost in rotation
        x = x<<1;                               // Rotate left one bit
        bufferLong [a*2] = x;                   // Store new low buffer
        x = bufferLong [a*2+1];                 // Get high buffer entry
        x = x<<1;                               // Rotate left one bit
        bitWrite(x,0,b);                        // Store saved bit
        bufferLong [a*2+1] = x;                 // Store new high buffer
    }
}  

// Display Buffer on LED matrix
/*
void printBufferLong()
{
	for (int a=0;a<7;a++)
	{                    						// Loop 7 times for a 5x7 font
    	unsigned long x = bufferLong [a*2+1];   // Get high buffer entry
    	byte y = x;                             // Mask off first character
    	lc.setRow(3,a,y);                       // Send row to relevent MAX7219 chip
    	x = bufferLong [a*2];                   // Get low buffer entry
    	y = (x>>24);                            // Mask off second character
    	lc.setRow(2,a,y);                       // Send row to relevent MAX7219 chip
    	y = (x>>16);                            // Mask off third character
    	lc.setRow(1,a,y);                       // Send row to relevent MAX7219 chip
    	y = (x>>8);                             // Mask off forth character
    	lc.setRow(0,a,y);                       // Send row to relevent MAX7219 chip
  	}
}
*/
void printBufferLong()
{
	for (int a=0;a<7;a++)
	{                    						// Loop 7 times for a 5x7 font
    	unsigned long x = bufferLong [a*2+1];   // Get high buffer entry
    	byte y = x;                             // Mask off first character
    	y = Bit_Reverse(y);
    	lc.setColumn(3,a, y);                       // Send row to relevent MAX7219 chip
    	x = bufferLong [a*2];                   // Get low buffer entry
    	y = (x>>24);                            // Mask off second character
    	y = Bit_Reverse(y);
    	lc.setColumn(2,a,y);                       // Send row to relevent MAX7219 chip
    	y = (x>>16);                            // Mask off third character
    	y = Bit_Reverse(y);    	
    	lc.setColumn(1,a,y);                       // Send row to relevent MAX7219 chip
    	y = (x>>8);                             // Mask off forth character
    	y = Bit_Reverse(y);    	
    	lc.setColumn(0,a,y);                       // Send row to relevent MAX7219 chip
    	matrix.writeDisplay();
  	}
} 

// Reverse the order of bits in a byte. 
// I.e. MSB is swapped with LSB, etc. 
byte Bit_Reverse( byte x ) 
{ 
    //          01010101  |         10101010
    x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
    //          00110011  |         11001100 
    x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
    //          00001111  |         11110000 
    x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0); 
    return x;    
}