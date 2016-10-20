//initializes/defines the output pin of the LM34 temperature sensor
int outputpin = A4;
//this sets the ground pin to LOW and the input voltage pin to high
void setup()
{
	Serial.begin(9600);
}

//main loop
void loop()
{
	int rawvoltage = analogRead(outputpin);
	float millivolts = (rawvoltage / 1024.0) * 5000;
	float fahrenheit = millivolts / 10;
	Serial.print(fahrenheit);
	Serial.println(" degrees Fahrenheit, ");

	float celsius = (fahrenheit - 32) * (5.0 / 9.0);

	Serial.print (celsius);
	Serial.println(" degrees Celsius");
	delay(1000);

}
