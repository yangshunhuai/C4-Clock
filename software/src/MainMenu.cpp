#include <Arduino.h>
#include "C4-Clock.h"
#include "Time1.h"

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

	char serbuf[30];
	sprintf(serbuf, "Current time %s %s", datestr, timestr);
	Serial.println(serbuf);
}