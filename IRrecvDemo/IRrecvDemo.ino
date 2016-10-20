/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 6;

IRrecv irrecv(RECV_PIN);

decode_results IRcodereceived;

void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
	if (irrecv.decode(&IRcodereceived))
	{
		Serial.println(IRcodereceived.value, HEX);
		irrecv.resume(); // Receive the next value
	}
	delay(200);
}
