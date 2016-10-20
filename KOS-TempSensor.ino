/*Upload this code, open the serial monitor window
   and the ambient temperature will be displayed.

   Put your finger on the Kit-on-a-Shields LM34 temp
   sensor, to see if it changes the temperature reading.
   (If it doesn't change, you may be a vampire.)
*/

void setup()
{

	Serial.begin(9600);

}

void loop()
{

	float tempValue = analogRead(A4);
	Serial.print ("Temp Raw: ");
	Serial.println (tempValue);
	Serial.print ("Temp In Fahrenheit: ");
	Serial.println ((tempValue * .0048) / .010);

	Serial.println ();
	delay(500);

}
