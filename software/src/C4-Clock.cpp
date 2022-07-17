/*
 Name:		C4_Clock.ino
 Created:	2022/5/4 21:56:00
 Author:	Michael
*/

#include <Arduino.h>

#include <Wire.h>
#include <WiFi.h>
#include <ESP32Time.h>
#include <EEPROM.h>
#include <Adafruit_Keypad_Ringbuffer.h>
#include <Adafruit_Keypad.h>
#include <LiquidCrystal_PCF8574.h>

// Pin definitions
// Relay pin
#define RELAY 16
// Buzzer & LED pin
#define BUZZER 4
// LCD1602 device address
#define LCD1602_ADDR 0x27
// GMT offset in seconds (GMT? * 3600)
#define GMT_OFFSET 2880
// The NTP time server
const char ntpServer[] = "ntp1.aliyun.com";
// Serial baud. On ESP32 it should better be 115200
#define SER_BAUD 115200

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
char 

LiquidCrystal_PCF8574 lcd(LCD1602_ADDR);
ESP32Time rtc(GMT_OFFSET);

// Variable declaration
unsigned long lastmillis;
struct alarmConfig {
	int hour;
	int minute;
	int repeat;
};

struct timeConfig {
	int year;
	int month;
	int day;
	int hour;
	int minute;
};

bool alarmIsOff = false;

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
	
	lcd.begin(16, 2);
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
	/*keypad.tick();
	if (keypad.available()) {
		keypadEvent e = keypad.read();
		if ((e.bit.KEY == 'A') && (e.bit.EVENT == KEY_JUST_PRESSED)) {
			beep();
			settings();
			beep();
			lcd.clear();
		}
	}*/

	unsigned long curmillis = millis();
	if ((curmillis - lastmillis) >= 1000) {
		updateTime();
		checkAlarm();
		lastmillis = curmillis;
	}
}
