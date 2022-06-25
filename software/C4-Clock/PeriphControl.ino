void beep() {
	digitalWrite(LED, HIGH);
	digitalWrite(BUZZER, HIGH);
	delay(100);
	digitalWrite(LED, LOW);
	digitalWrite(BUZZER, LOW);
}

char waitForKeypad() {
	keypadEvent e;
	while (1) {
		keypad.tick();
		if (keypad.available()) {
			e = keypad.read();
			if (e.bit.EVENT == KEY_JUST_PRESSED) break;
		}
	}
	beep();
	char serbuf[7];
	sprintf(serbuf, "%c down", e.bit.KEY);
	Serial.println(serbuf);
	return e.bit.KEY;
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
		delay(1000);
	}
	char serbuf[30];
	sprintf(serbuf, "Got %i from keypad", number.toInt());
	Serial.println(serbuf);
	return number.toInt();
}