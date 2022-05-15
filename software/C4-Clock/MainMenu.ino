void updateTime() {
	char timestr[7], datestr[11], daystr[3];
	getTimeStr(timestr);
	getDateStr(datestr);
	getDayStr(daystr);

	lcd.setCursor(5, 0);
	lcd.print(timestr);
	lcd.setCursor(2, 1);
	lcd.print(datestr);
	lcd.setCursor(13, 1);
	lcd.print(daystr);

}