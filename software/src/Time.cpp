void getTimeCfg(struct timeConfig* configStruct) {
	configStruct->year = rtc.getYear();
	configStruct->month = rtc.getMonth();
	configStruct->day = rtc.getDay();
	configStruct->hour = rtc.getHour();
	configStruct->minute = rtc.getMinute();
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
	int day = rtc.getDayofWeek();
	char* names[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	strcpy(daystr, names[day]);
}
