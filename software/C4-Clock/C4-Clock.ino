/*
 Name:		C4_Clock.ino
 Created:	2022/5/4 21:56:00
 Author:	Michael
*/

// the setup function runs once when you press reset or power the board

#include <LiquidCrystal_I2C.h>
void setup() {
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.println("demo");
	delay(1000);
}
