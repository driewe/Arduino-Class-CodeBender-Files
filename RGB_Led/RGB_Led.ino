/*
 * example 1.2 - fun with PWM and RGB LED -  Created 07/04/2010 ---  
 * CC by-sa v3.0 Share the love!
 * By John Boxall --- http://tronixstuff.com
 *
 * Grab the book here -> http://goo.gl/3tgibp
 *
 * Get your own squid here -> http://goo.gl/y5Z8dU
 */

int red = 11; // the pins for the LED
int green = 9;
int blue = 10;
int i = 0; // for loops
int j = 0;
void setup()
{
  pinMode(red, OUTPUT); // tell Arduino LED is an output
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}
void loop()
{
  // first, cycle up each primary colour twice
  for (j = 1; j < 6; j++)
  {  // loop 5 times
    for (i = 0; i < 255; i++)
    { // loop from 0 to 254 (fade in)
      analogWrite(red, i);      // set the LED brightness
      delay(20); // Wait 10ms because analogWrite isn't instant
    }
    analogWrite(red,0);
    delay (20);
    for (i = 0; i < 255; i++)
    { // loop from 0 to 254 (fade in)
      analogWrite(green, i);      // set the LED brightness
      delay(20); // Wait 10ms because analogWrite isn't instant
    }
    delay (20);
    analogWrite(green,0);
    for (i = 0; i < 255; i++)
    { // loop from 0 to 254 (fade in)
      analogWrite(blue, i);      // set the LED brightness
      delay(20); // Wait 10ms because analogWrite isn't instant
    }
    delay (20);
    analogWrite(blue,0);
  }
  // psychadelic time
  for (j = 1; j < 10000; j++)
  {
    analogWrite(red,random(255)); // set red at random brightness between 0 and 254
    delay (random(10,31));           // wait for a random duration between 10 and 30 milliseconds
    analogWrite(green,random(255));
    delay (random(10,31));
    analogWrite(blue,random(255));
    delay (random(10,31));
  }
}