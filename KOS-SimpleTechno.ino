/*This program generates "Techno-ish"
 * music based on ambient light levels
 * sensed by the Light Dependant Resistor (LDR).
 *
 * During the first 5 seconds of the sketch,
 * wave your hands over the LDR.
 * This sets the min and max light levels for the
 * the program.
 *
 * Warning: Your brain will melt if this sketch runs too
 * long...
 */

int       sensorValue = 0;
int       sensorLow   = 1023;
int       sensorHigh  = 0;
float     pitch       = 0;
const int ledPin      = 13;

void setup()
{

	pinMode     (ledPin, OUTPUT);
	digitalWrite(ledPin, HIGH);

	while (millis() < 5000)
	{
		sensorValue = analogRead(A2);
		if (sensorValue > sensorHigh) sensorHigh = sensorValue;
		if (sensorValue < sensorLow)  sensorLow  = sensorValue;
	}

	digitalWrite(ledPin, LOW);

}

void loop()
{

	sensorValue = analogRead(A2);
	pitch2Note ();

	tone  (A3, pitch, 109);
	delay (110);

	tone  (A3, 55, 24);
	delay (25);

	tone  (A3, 880, 24);
	delay (25);
}

void pitch2Note ()
{

	pitch = map(sensorValue, sensorLow, sensorHigh, 55, 900);

	if (pitch <   60.205)                    pitch = 55;     // A
	if (pitch >=  60.205 && pitch < 69.415)  pitch = 65.41;  // C
	if (pitch >=  69.415 && pitch < 77.915)  pitch = 73.42;  // D
	if (pitch >=  77.915 && pitch < 90.205)  pitch = 82.41;  // E
	if (pitch >=  90.205 && pitch < 104)     pitch = 98;     // G
	if (pitch >= 104.000 && pitch < 120.405) pitch = 110;    // A
	if (pitch >= 120.405 && pitch < 138.82)  pitch = 130.81; // C
	if (pitch >= 138.820 && pitch < 155.82)  pitch = 146.83; // D
	if (pitch >= 155.820 && pitch < 180.405) pitch = 164.81; // E
	if (pitch >= 180.405 && pitch < 208)     pitch = 196;    // G
	if (pitch >= 208.000 && pitch < 240.815) pitch = 220;    // A
	if (pitch >= 240.815 && pitch < 277.645) pitch = 261.63; // C
	if (pitch >= 277.645 && pitch < 311.645) pitch = 293.66; // D
	if (pitch >= 311.645 && pitch < 360.815) pitch = 329.63; // E
	if (pitch >= 360.815 && pitch < 416)     pitch = 392;    // G
	if (pitch >= 416.000 && pitch < 481.625) pitch = 440;    // A
	if (pitch >= 481.625 && pitch < 555.29)  pitch = 523.25; // C
	if (pitch >= 555.290 && pitch < 623.29)  pitch = 587.33; // D
	if (pitch >= 623.290 && pitch < 721.62)  pitch = 659.25; // E
	if (pitch >= 721.620 && pitch < 831.995) pitch = 783.99; // G
	if (pitch >= 831.995 && pitch <= 880)    pitch = 880;    // A
	if (pitch >  880)                        pitch = 0;
}
