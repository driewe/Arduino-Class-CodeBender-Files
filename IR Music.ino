/*
 * IRMusic: 
 * Uses Ken Shirriff's library to receive commands from a clarion IR remote then
 * play notes based on the command pressed.  
 * In order to compile upload modified version of Ken Shirrifs IRremote library
 * where IRremoteint.h is modified to use TIMER1 instead of TIMER2
 * This will leave TIMER2 free for the tone function that is used by this sketch.
 *
 * Note that TIMER1 uses pin9.  The library likes to use this for transmit.
 * Even though this sketch is not using any of the transmit functions I
 * do not attempt to use pin 9.
 * 
 */

#include <IRremote.h>

int RECV_PIN = 2;
int currentled = 0;

// Led Pin Numbers.  Used for visual effects
int leds[]={3, 4, 5, 6, 7, 10, 11, 12};

// notes to play
const int midc = 262;
const int midd = 294;
const int mide = 330;
const int midf = 349;
const int midg = 392;
const int mida = 440;
const int midb = 494;

// the following definitions are for my specific clarion controller
// 
const long func = 0x6106C03F;
const long uparrow = 0x6106D827;
const long zone = 0x6106D02F;
const long reverse = 0x61066897;
const long play = 0x610610EF;
const long forward = 0x6106E817;
const long down = 0x6106B847;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  // set led pins to output
  for(int i=0;i<7;i++) pinMode(leds[i], OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

// Note about checking for currentled below.
// Only when the note changes do we want to turn off the current led then
// turn on the led matching the new note.  To prevent flicker of leds
// I solved by keeping a variable "currentled" that I would check each time
// if the currentled didn't go with the results.value then I would turn off
// the currentled then set currentled to the new value and turn that on and play the tone.
// 
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == func) 
    {
      if (currentled != 0) 
      {
        digitalWrite(leds[currentled], LOW);
        currentled = 0;
      }
      digitalWrite(leds[currentled], HIGH);
      tone(8, midc);
    } 
    else if (results.value == uparrow)
    {
      if (currentled != 1) 
      {
        digitalWrite(leds[currentled], LOW);
        currentled = 1;
      }     
      digitalWrite(leds[currentled], HIGH);      
      tone(8, midd);
    }
    else if (results.value == zone)
    {
      if (currentled != 2) 
      {
        digitalWrite(leds[currentled], LOW);
        currentled = 2;
      }      
      digitalWrite(leds[currentled], HIGH);      
      tone(8, mide);
    }
    else if (results.value == reverse)
    {
      if (currentled != 3) 
      {
        digitalWrite(leds[currentled], LOW);
        currentled = 3;
      }      
      digitalWrite(leds[currentled], HIGH);      
      tone(8, midf);
    }
    else if (results.value == play)
    {
      if (currentled != 4) 
      {
        digitalWrite(leds[currentled], LOW);
        currentled = 4;
      }      
      digitalWrite(leds[currentled], HIGH);      
      tone(8, midg);
    }
    else if (results.value == forward)
    {
      if (currentled != 5) 
      {
        digitalWrite(leds[currentled], LOW);
        currentled = 5;
      }      
      digitalWrite(leds[currentled], HIGH);      
      tone(8, mida);
    }
    else if (results.value == down)
    {
      if (currentled != 6) 
      {
        digitalWrite(leds[currentled], LOW);
        currentled = 6;
      }      
      digitalWrite(leds[currentled], HIGH);      
      tone(8, midb);
    }
  } 
  else 
  {
    noTone(8);
    digitalWrite(leds[currentled], LOW);
  }
  irrecv.resume();
  delay(200);
}