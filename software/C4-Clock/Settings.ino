/*
About configuration persistence:
  Item                    Address       Data type  Length
- Alarm hour              1             int        1 byte
- Alarm minute            2             int        1 byte
- Alarm repeat mode       3             int        1 byte
- C3 Explosion            4             bool       1 bit
*/

#define ALARM_HOUR_ADDR 1
#define ALARM_MINUTE_ADDR 2
#define ALARM_REPEAT_ADDR 3
#define C_EXP_ADDR 4

void settings() {
	beep();
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("1.S-Alm 2.S-time");
	lcd.setCursor(0, 1);
	lcd.print("3.S-Eff 4.About");
	char key = waitForKeypad();
	Serial.println(key);
	switch (key)
	{
	default:
		break;
	case '1':
		setAlarm();
		break;
	case '2':
		setTime();
		break;
	case '3':
		setEffect();
		break;
	case '4':
		about();
		break;
	case '9':
		resetConfig();
		break;
	case 'D':
		break;
	}
}

void setAlarm() {
	beep();
	Serial.println("Entering setAlarm");

	struct alarmConfig alarmcfg{};

	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print("Set Hour");
	lcd.setCursor(6, 1);
	lcd.print(">  <");
	alarmcfg.hour = getIntFromKeypad(2, 1, 7);

	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print("Set Minute");
	lcd.setCursor(6, 1);
	lcd.print(">  <");
	alarmcfg.minute = getIntFromKeypad(2, 1, 7);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("1.Mo-Fr  2.Sa-Su");
	lcd.setCursor(0, 1);
	lcd.print("3.All  > <");
	alarmcfg.repeat = getIntFromKeypad(1, 1, 8);
}

void setTime() {
	Serial.println("Entering setTime");
	beep();

	struct timeConfig timecfg{};

	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print("Set Year");
	lcd.setCursor(5, 1);
	lcd.print(">    <");
	timecfg.year = getIntFromKeypad(4, 1, 6);

	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print("Set Month");
	lcd.setCursor(6, 1);
	lcd.print(">  <");
	timecfg.month = getIntFromKeypad(2, 1, 7);

	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print("Set Day");
	lcd.setCursor(6, 1);
	lcd.print(">  <");
	timecfg.day = getIntFromKeypad(2, 1, 7);

	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print("Set Hour");
	lcd.setCursor(6, 1);
	lcd.print(">  <");
	timecfg.hour = getIntFromKeypad(2, 1, 7);

	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print("Set Minute");
	lcd.setCursor(6, 1);
	lcd.print(">  <");
	timecfg.minute = getIntFromKeypad(2, 1, 7);

	saveTimeCfg(&timecfg);
	lcd.clear();
	lcd.setCursor(3, 0);
	lcd.print("DateTime Set");
	delay(1000);
}

void setEffect() {
	// TODO: ������ý����߼�
	;;
}

void about() {
	// TODO����ӹ��ڽ����߼�
	;;
}

void resetConfig() {
	Serial.println("Entering resetConfig");
	beep();
	lcd.clear();
	lcd.setCursor(1, 0);
	lcd.print("Clear EEPROM?");
	lcd.setCursor(0, 1);
	lcd.print("1. Yes     2. No");
	while (true) {
		keypad.tick();
		if (keypad.available()) {
			keypadEvent e = keypad.read();
			if (char(e.bit.KEY) == '1') {
				for (int i = 0; i < EEPROM.length(); i++) {
					EEPROM.write(i, 0);
				}
				lcd.clear();
				lcd.setCursor(1, 0);
				lcd.print("EEPROM cleared");
				delay(1000);
				break;
			}
			if (char(e.bit.KEY) == '2') break;
		}
	}
	settings();
}

void getAlarmCfg(struct alarmConfig *configStruct) {
	configStruct->hour = EEPROM.read(ALARM_HOUR_ADDR);
	configStruct->minute = EEPROM.read(ALARM_MINUTE_ADDR);
	configStruct->repeat = EEPROM.read(ALARM_REPEAT_ADDR);
}

void saveAlarmCfg(struct alarmConfig *configStruct) {
	EEPROM.write(ALARM_HOUR_ADDR, configStruct->hour);
	EEPROM.write(ALARM_MINUTE_ADDR, configStruct->minute);
	EEPROM.write(ALARM_REPEAT_ADDR, configStruct->repeat);
}