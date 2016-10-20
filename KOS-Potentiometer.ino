/*Upload this code, open the serial monitor window
  and adjust the 2 side mounted potentiometers.

  You will see the changing values displayed on the
  serial monitor window.
*/

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);

}

void loop()
{
	// put your main code here, to run repeatedly:
	Serial.print ("10K POT01: ");
	Serial.print (analogRead(A0));

	Serial.print ("   10K POT02: ");
	Serial.print (analogRead(A1));
	Serial.println ();

}
