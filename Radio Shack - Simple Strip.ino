#include <PololuLedStrip.h>
#include <avr/pgmspace.h>  // for using PROGMEM, storing data in Flash memory


// Create an ledStrip object on pin 12.  Will need one of these created
// for each of the strips
PololuLedStrip<12> ledStrip;

// Create a buffer for holding 30 colors.  Takes 90 bytes.
#define LED_COUNT 10
rgb_color colors[LED_COUNT];
rgb_color refColors[10];
int d = 100;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	//load the colors
	refColors[1] = (rgb_color)	{255, 0, 0};
	refColors[2] = (rgb_color)	{255, 0, 127};
	refColors[3] = (rgb_color)	{255, 0, 255};
	refColors[4] = (rgb_color)	{0, 0, 255};
	refColors[5] = (rgb_color)	{0, 127, 255};
	refColors[6] = (rgb_color)	{0, 255, 0};
	refColors[7] = (rgb_color)	{0, 255, 160};
	refColors[8] = (rgb_color)	{127, 255, 0};
	refColors[9] = (rgb_color)	{255, 255, 0};
	refColors[0] = (rgb_color)	{0, 0, 0};


	//loop ten times to create chasing effect
	
	for (int i = 0; i < 100; i++)
	{
		//Serial.println("Using Colors:");
		// This 4 loop loads the colors[] array with a new pattern that will
		// be the previous pattern shifted down by the amount 0-9, depending
		// on where we are in the loop.  NOTE the use of module operator %. 
		// that ensures 
		for (int k = 0; k < 10; k++)
		{
			colors[k] = refColors[ (k + i) % 10 ];
		}
		// This writes the values in the colors array to the LED strip
		ledStrip.write(colors, LED_COUNT);
		delay(d);
	} 
	
	for (int i = 99; i > -1; i--)
	{
		//Serial.println("Using Colors:");
		for (int k = 0; k < 10; k++)
		{
			colors[k] = refColors[ (k + i) % 10 ];
		}
		ledStrip.write(colors, LED_COUNT);
		delay(d);
	} 
}