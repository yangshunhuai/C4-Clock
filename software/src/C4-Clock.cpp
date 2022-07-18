/*
 Name:		C4_Clock.ino
 Created:	2022/5/4 21:56:00
 Author:	Michael
*/

#include "C4-Clock.h"
#include "Alarm.h"
#include "Time1.h"
#include "Network.h"
#include "MainMenu.h"
#include "Settings.h"
#include "PeriphControl.h"

unsigned long lastmillis;
char ntpServer[] = "ntp1.aliyun.com";
bool alarmIsOff = false;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = { 14, 27, 26, 25 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 33, 32, 2, 17 }; //connect to the column pinouts of the keypad
Adafruit_Keypad keypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(LCD1602_ADDR, 16, 2);
ESP32Time rtc(GMT_OFFSET);

// the setup function runs once when you press reset or power the board
void setup() {
	// Device initialization
	Serial.begin(SER_BAUD);
	Serial.println("Serial communication begun");
	// Pin initialization
	pinMode(RELAY, OUTPUT);
	pinMode(BUZZER, OUTPUT);
	digitalWrite(RELAY, LOW);
	Serial.println("GPIO init completed");
	//keypad.begin();
	Serial.println("Keypad init completed");
	
	lcd.init();
	lcd.backlight();
	Serial.println("LCD init completed");
	lcd.setCursor(4, 0);
	lcd.print("C4 Clock");
	lcd.setCursor(0, 1);
	lcd.print("by yangshunhuai");
	digitalWrite(BUZZER, HIGH);
	delay(100);
	digitalWrite(BUZZER, LOW);
	delay(1000);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Configuring net");
	lcd.setCursor(0, 1);
	lcd.print("work");
	setupNetwork();
	Serial.println("Network init completed");

	lastmillis = millis();
}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.println("Testing keypad");
	keypad.tick();
	if (keypad.available()) {
		keypadEvent e = keypad.read();
		if (e.bit.KEY == 'A' && e.bit.EVENT == KEY_JUST_RELEASED) {
			beep();
			settings();
		}
	}

	unsigned long curmillis = millis();
	if ((curmillis - lastmillis) >= 1000) {
		updateTime();
		checkAlarm();
		lastmillis = curmillis;
	}
}
