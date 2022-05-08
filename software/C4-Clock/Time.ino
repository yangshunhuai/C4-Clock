void getDateStr(char* datestr) {
	RtcDateTime now = rtc.GetDateTime();
	sprintf(datestr, "%04u/%02u/%02u",
		now.Year(), now.Month(), now.Day());
}

void getTimeStr(char* timestr) {
	RtcDateTime now = rtc.GetDateTime();
	sprintf(timestr, "%02u:%02u",
		now.Hour(), now.Minute());
}

void getDayStr(char* daystr) {
	RtcDateTime now = rtc.GetDateTime();
	int day = now.DayOfWeek();
	char* names[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	strcpy(daystr, names[day]);
}