/*Upload the code to make the
  piezo buzzer on the Kit-on-a-Shield
  play some different notes.

  Open the serial monitor to display the
  tones being played.
*/

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);

}

void loop()
{
	Serial.println  ("Playing 250hz Tone...");
	tone (A3, 250);
	delay(100);

	Serial.println  ("Playing 440hz Tone...");
	tone (A3, 440);
	delay(100);

	Serial.println  ("Playing 660hz Tone...");
	tone (A3, 660);
	delay(100);

	Serial.println  ("Playing 880hz Tone...");
	tone (A3, 880);
	delay(100);

	noTone (A1);
}
