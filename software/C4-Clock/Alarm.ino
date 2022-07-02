void checkAlarm() {
	Serial.println("Entering checkAlarm");
	struct timeConfig timecfg;
	struct alarmConfig alarmcfg;
	getTimeCfg(&timecfg);
	getAlarmCfg(&alarmcfg);

	int dayofweek = rtc.GetDateTime().DayOfWeek();
	bool isTimeCorrect = (alarmcfg.hour == timecfg.hour) && (alarmcfg.minute == timecfg.minute);
	// Check if today is Monday~Friday
	bool isDayOfWeek1To5 = ((dayofweek == 1) || (dayofweek == 2) || (dayofweek == 3)
		|| (dayofweek == 4) || (dayofweek == 5));
	// Check if today is Saturday~Sunday
	bool isDayOfWeek6To7 = ((dayofweek == 6) || (dayofweek == 0));
	bool isDayCorrect = ((alarmcfg.repeat == 3)           // Is repeated every day
		|| ((alarmcfg.repeat == 1) && isDayOfWeek1To5)    // Is repeated Monday~Friday
		|| ((alarmcfg.repeat == 2) && isDayOfWeek6To7));  // Is repeated Saturday~Sunday
	Serial.print("AlarmIsOff is ");
	Serial.println(alarmIsOff);
	if (isTimeCorrect && isDayCorrect && !alarmIsOff) {
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Any key to");
		lcd.setCursor(0, 1);
		lcd.print("deactivate");
		unsigned long curmillis = millis();
		unsigned long timePassed;
		int remainingSeconds;
		while (true) {
			beep();
			delay(300);
			keypad.tick();
			timePassed = millis() - curmillis;
			remainingSeconds = (CONFIRM_TIMEOUT - timePassed) / 1000;
			if (remainingSeconds < 10) {
				lcd.setCursor(15, 0);
				lcd.print(" ");
			}
			lcd.setCursor(14, 0);
			lcd.print(remainingSeconds);
			if (keypad.available()) {
				keypadEvent e = keypad.read();
				if (e.bit.EVENT == KEY_JUST_PRESSED) {
					askMathQuestion();
					Serial.println("Alarm is turned off");
					alarmIsOff = true;
					lcd.clear();
					break;
				}
			}
			if ((timePassed >= CONFIRM_TIMEOUT) && (EEPROM.read(C_EXP_ADDR) == 1)) {
				if (EEPROM.read(C_EXP_ADDR) == 1) {
					explode();
					resetFunc();
				}
				else {
					break;
				}
			}
		}
	}
	if (!isTimeCorrect) {
		Serial.println("Setting alarmIsOff to false");
		alarmIsOff = false;
	}
}
