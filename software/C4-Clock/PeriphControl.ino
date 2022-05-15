void beep() {
	digitalWrite(LED, HIGH);
	digitalWrite(BUZZER, HIGH);
	delay(100);
	digitalWrite(LED, LOW);
	digitalWrite(BUZZER, LOW);
}