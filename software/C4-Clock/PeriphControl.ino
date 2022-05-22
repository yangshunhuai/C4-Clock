void beep() {
	digitalWrite(LED, HIGH);
	digitalWrite(BUZZER, HIGH);
	delay(100);
	digitalWrite(LED, LOW);
	digitalWrite(BUZZER, LOW);
}

char getKeypad() {
	keypadEvent e;
	while (1) {
		keypad.tick();
		if (keypad.available()) {
			e = keypad.read();
			break;
		}
	}
	return e.bit.KEY;
}