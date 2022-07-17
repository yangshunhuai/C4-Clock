#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <ESP32Time.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Device configuration and global variables should be placed here.

// Relay pin
#define RELAY 16
// Buzzer & LED pin
#define BUZZER 4
// LCD1602 device address
#define LCD1602_ADDR 0x27
// GMT offset in seconds (GMT? * 3600)
#define GMT_OFFSET 2880
// The NTP time server
extern char ntpServer[];
// Serial baud. On ESP32 it should better be 115200
#define SER_BAUD 115200

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
extern bool alarmIsOff;

#define ROWS 4
#define COLS 4
extern Keypad keypad;

extern LiquidCrystal_I2C lcd;
extern ESP32Time rtc;