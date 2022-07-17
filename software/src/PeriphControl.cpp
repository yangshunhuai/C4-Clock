#include <Arduino.h>
#include "C4-Clock.h"

void beep() {
	digitalWrite(BUZZER, HIGH);
	delay(100);
	digitalWrite(BUZZER, LOW);
}

char waitForKeypad() {
	Key currentkey;
	while (1) {
		if (keypad.getKeys()) {
			for (int i = 0; i < LIST_MAX; i++) {
				currentkey = keypad.key[i];
				if (currentkey.stateChanged && currentkey.kstate == PRESSED) {
					break;
				}
			}
		}
	}
	beep();
	char serbuf[7];
	sprintf(serbuf, "%c down", currentkey.kchar);
	Serial.println(serbuf);
	return currentkey.kchar;
}

int getIntFromKeypad(int bits, int echoRow, int echoCol) {
	String number;
	for (int i = 0; i <= (bits - 1); i++) {
		char key = '\0';
		do
		{
			key = waitForKeypad();
		} while (key == 'A' || key == 'B' || key == 'C' || key == 'D' || key == '*' || key == '#');
		lcd.setCursor(echoCol + i, echoRow);
		lcd.print(key);
		number += key;
	}
	char serbuf[30];
	sprintf(serbuf, "Got %i from keypad", number.toInt());
	Serial.println(serbuf);
	return number.toInt();
}