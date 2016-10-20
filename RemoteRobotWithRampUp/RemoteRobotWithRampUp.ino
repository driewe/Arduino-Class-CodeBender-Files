/*
 * Remote control Robot
 *
 * In order for this to compile the library IRremote has to be set to use TIMER2
 * which will prevent the tone function from being available as it tries to use 
 * that same timer.
 */

#include <IRremote.h>
#include <Servo.h> 

const int moveforward = 1;
const int movebackward = 2;
const int spinleft = 3;
const int spinright = 4;
const int pause = 5;

int RECV_PIN = 2;

const long func = 0x6106C03F;
const long uparrow = 0x6106D827;
const long zone = 0x6106D02F;
const long reverse = 0x61066897;
const long play = 0x610610EF;
const long forward = 0x6106E817;
const long down = 0x6106B847;

IRrecv irrecv(RECV_PIN);
decode_results results;
Servo servoLeft;        // Declare Left Servo
Servo servoRight;       // Declare Right Servo
int lastcommand;


void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  servoLeft.attach(13);
  servoRight.attach(12);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  lastcommand = pause;
  // tone(4, 3000, 1000);              
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == func) 
    {
        // Do nothing on func
    } 
    else if (results.value == uparrow)  // Move Forward, ramp 
    {
      if (lastcommand != moveforward)
      {
        lastcommand = moveforward;
        for(int speed = 0; speed <= 100; speed+=2)
        {
          servoLeft.writeMicroseconds(1500+speed);
          servoRight.writeMicroseconds(1500-speed);
          delay(20);
        }
      }
      else // Already at full speed, keep it going
      {
        servoLeft.writeMicroseconds(1600);
        servoRight.writeMicroseconds(1400);
      }
    }
    else if (results.value == zone)
    {
    // Do nothing on zone
    }
    else if (results.value == reverse)  // Spin Left
    {
      if(lastcommand != spinleft)
      {
        lastcommand = spinleft;
        for(int speed = 0; speed <= 100; speed +=2)
        {
          servoLeft.writeMicroseconds(1500-speed);
          servoRight.writeMicroseconds(1500-speed);
          delay(20);
        }
      }
      else
      {
        servoLeft.writeMicroseconds(1400);
        servoRight.writeMicroseconds(1400);
      }
    }
    else if (results.value == play)   // do nothing
    {
      // should pause???
    }
    else if (results.value == forward)   // Sping right
    {
      if(lastcommand != spinright)
      {
        lastcommand = spinright;
        for(int speed = 0; speed <= 100; speed +=2)
        {
          servoLeft.writeMicroseconds(1500+speed);
          servoRight.writeMicroseconds(1500+speed);
          delay(20);
        }
      }
      else
      {
        servoLeft.writeMicroseconds(1600);
        servoRight.writeMicroseconds(1600);
      }
    }
    else if (results.value == down)   // move backwards
    {
      if(lastcommand != movebackward)
      {
        lastcommand = movebackward;
        for(int speed = 0; speed <= 100; speed += 2)
        {
          servoLeft.writeMicroseconds(1500 - speed);
          servoRight.writeMicroseconds(1500 + speed);
          delay(20);
        }
      }
      else
      {
        servoLeft.writeMicroseconds(1400);
        servoRight.writeMicroseconds(1600);
      }
    }
  } 
  else 
  {
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
  }
  
  irrecv.resume();
  delay(200);
}
