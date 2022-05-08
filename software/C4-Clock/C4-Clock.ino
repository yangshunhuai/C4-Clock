/*
 Name:		C4_Clock.ino
 Created:	2022/5/4 21:56:00
 Author:	Michael
*/

#include <Adafruit_Keypad_Ringbuffer.h>
#include <Adafruit_Keypad.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
#define LED A0
#define RELAY A1
#define BUZZER 10
#define LCD1602_ADDR 0x27
#define DS1302_CLK A2
#define DS1302_IO A3
#define DS1302_CE 11

// Device object initialization
#define ROWS 4
#define COLS 4
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = { 2, 3, 4, 5 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 6, 7, 8, 9 }; //connect to the column pinouts of the keypad
Adafruit_Keypad keypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

ThreeWire myWire(DS1302_IO, DS1302_CLK, DS1302_CE); // IO, SCLK, CE
RtcDS1302<ThreeWire> rtc(myWire);

LiquidCrystal_I2C lcd(LCD1602_ADDR, 16, 2);

// the setup function runs once when you press reset or power the board
void setup() {
	// Pin initialization
	pinMode(LED, OUTPUT);
	pinMode(RELAY, OUTPUT);
	pinMode(BUZZER, OUTPUT);
	digitalWrite(RELAY, LOW);
	// Device initialization
	Serial.begin(9600);
	keypad.begin();
	lcd.init();
	lcd.backlight();
	lcd.setCursor(4, 0);
	lcd.print("C4 Clock");
	lcd.setCursor(0, 1);
	lcd.print("by yangshunhuai");
	// RTC initialization. Time is automatically synchronized to
	// the time this program is built.
	rtc.Begin();
	RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
	if (!rtc.IsDateTimeValid())
	{
		// Common Causes:
		//    1) first time you ran and the device wasn't running yet
		//    2) the battery on the device is low or even missing

		Serial.println("RTC lost confidence in the DateTime!");
		rtc.SetDateTime(compiled);
	}

	if (rtc.GetIsWriteProtected())
	{
		Serial.println("RTC was write protected, enabling writing now");
		rtc.SetIsWriteProtected(false);
	}

	if (!rtc.GetIsRunning())
	{
		Serial.println("RTC was not actively running, starting now");
		rtc.SetIsRunning(true);
	}

	RtcDateTime now = rtc.GetDateTime();
	if (now < compiled)
	{
		Serial.println("RTC is older than compile time!  (Updating DateTime)");
		rtc.SetDateTime(compiled);
	}
	else if (now > compiled)
	{
		Serial.println("RTC is newer than compile time. (this is expected)");
	}
	else if (now == compiled)
	{
		Serial.println("RTC is the same as compile time! (not expected but all is fine)");
	}
	delay(1000);
	lcd.clear();
}

// the loop function runs over and over again until power down or reset
void loop() {
	mainMenu();
}
