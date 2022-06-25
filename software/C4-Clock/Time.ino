void getTimeCfg(struct timeConfig* configStruct) {
	RtcDateTime now = rtc.GetDateTime();
	configStruct->year = now.Year();
	configStruct->month = now.Month();
	configStruct->day = now.Day();
	configStruct->hour = now.Hour();
	configStruct->minute = now.Minute();
}

void getDateStr(char* datestr) {
	struct timeConfig config;
	getTimeCfg(&config);
	sprintf(datestr, "%04u/%02u/%02u",
		config.year, config.month, config.day);
}

void getTimeStr(char* timestr) {
	struct timeConfig config;
	getTimeCfg(&config);
	sprintf(timestr, "%02u:%02u",
		config.hour, config.minute);
}

void getDayStr(char* daystr) {
	RtcDateTime now = rtc.GetDateTime();
	int day = now.DayOfWeek();
	char* names[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	strcpy(daystr, names[day]);
}

void saveTimeCfg(struct timeConfig* configStruct) {
	RtcDateTime dt = RtcDateTime(configStruct->year, configStruct->month, configStruct->day, configStruct->hour, configStruct->minute, 0);
	rtc.SetDateTime(dt);
}

void saveAlarmCfg(struct alarmConfig* configStruct) {
	EEPROM.write(ALARM_HOUR_ADDR, configStruct->hour);
	EEPROM.write(ALARM_MINUTE_ADDR, configStruct->minute);
	EEPROM.write(ALARM_REPEAT_ADDR, configStruct->repeat);
}