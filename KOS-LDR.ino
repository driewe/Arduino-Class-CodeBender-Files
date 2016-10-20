/*Upload the code, open the serial monitor window
  and wave your hand over the LDR on the Kit-on-a-Shield
  You can also shine some light on the LDR and test
  the change.
*/

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);

}

void loop()
{
	// put your main code here, to run repeatedly:
	Serial.print ("LDR Level: ");
	Serial.println (analogRead(A2));

	delay(500);

}
