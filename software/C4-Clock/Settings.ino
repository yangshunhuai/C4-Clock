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
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("1.S-Alm 2.S-time");
	lcd.setCursor(0, 1);
	lcd.print("3.S-Eff 4.About");
	while (true) {
		keypad.tick();
		if (keypad.available()) {
			keypadEvent e = keypad.read();
			if (char(e.bit.KEY) == '1') setAlarm();
			if (char(e.bit.KEY) == '2') setTime();
			if (char(e.bit.KEY) == '3') setEffect();
			if (char(e.bit.KEY) == '4') about();
			if (char(e.bit.KEY) == '9') resetConfig();
			if (char(e.bit.KEY) == 'D') return;
		}
	}
}

void setAlarm() {
	beep();
	lcd.clear();
	lcd.setCursor(3, 0);
	lcd.print("Alarm Time");
	struct alarmConfig config;
	getAlarmCfg(&config);
	char timestr[6];
	sprintf(timestr, "%02u:%02u", config.hour, config.minute);
	lcd.setCursor(5, 1);
	lcd.print(timestr);
	
	
}

void setTime() {
	beep();
}

void setEffect() {
	beep();
}

void about() {
	beep();
}

void resetConfig() {
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

void saveAlarmCfg(int hour, int minute, int repeat) {
	EEPROM.write(ALARM_HOUR_ADDR, hour);
	EEPROM.write(ALARM_MINUTE_ADDR, minute);
	EEPROM.write(ALARM_REPEAT_ADDR, repeat);
}