#include <IRremote.h>
#include <LiquidCrystal.h>

#define PIN_DETECT 2
#define PIN_ANALOG 1
#define PIN_STATUS 13

IRsend irsend;
// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
int visitors = 0;

void setup()
{
	pinMode(PIN_DETECT, INPUT);
	pinMode(PIN_STATUS, OUTPUT);
	irsend.enableIROut(38);
	irsend.mark(0);
	Serial.begin(9600);
	// set up the LCD's number of columns and rows:
	//lcd.begin(16, 2);
	// Print a message to the LCD.
	//lcd.print("McMath Library");
	//delay(2000); // this delay prevents false start up counts ??
}

void loop()
{
	int pinstatus = digitalRead(PIN_DETECT);
	//int pinstatus = analogRead(A0);
	digitalWrite(PIN_STATUS, !pinstatus);
	Serial.print("pinstatus = ");
	Serial.println(pinstatus);
	if(!pinstatus) visitors++;
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	//lcd.setCursor(0, 1);
	//lcd.print("Visitors: ");
	//lcd.print(visitors);
	delay(500);
}
