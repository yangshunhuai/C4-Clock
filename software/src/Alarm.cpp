#include <Arduino.h>
#include "C4-Clock.h"
#include "Time1.h"
#include "Alarm.h"
#include "Settings.h"
#include "PeriphControl.h"

void checkAlarm()
{
	struct timeConfig timecfg;
	struct alarmConfig alarmcfg;
	getTimeCfg(&timecfg);
	getAlarmCfg(&alarmcfg);

	int dayofweek = rtc.getDayofWeek();
	bool isTimeCorrect = (alarmcfg.hour == timecfg.hour) && (alarmcfg.minute == timecfg.minute);
	// Check if today is Monday~Friday
	bool isDayOfWeek1To5 = ((dayofweek == 1) || (dayofweek == 2) || (dayofweek == 3) || (dayofweek == 4) || (dayofweek == 5));
	// Check if today is Saturday~Sunday
	bool isDayOfWeek6To7 = ((dayofweek == 6) || (dayofweek == 0));
	bool isDayCorrect = ((alarmcfg.repeat == 3)							  // Is repeated every day
						 || ((alarmcfg.repeat == 1) && isDayOfWeek1To5)	  // Is repeated Monday~Friday
						 || ((alarmcfg.repeat == 2) && isDayOfWeek6To7)); // Is repeated Saturday~Sunday
	Serial.print("AlarmIsOff is ");
	Serial.println(alarmIsOff);
	if (isTimeCorrect && isDayCorrect && !alarmIsOff)
	{
		lcd.clear();
		lcd.print("Alarm is present");
		while (true)
		{
			beep();
			delay(300);
			Key currentkey;
			while (1)
			{
				if (keypad.getKeys())
				{
					for (int i = 0; i < LIST_MAX; i++)
					{
						currentkey = keypad.key[i];
						if (currentkey.stateChanged && currentkey.kstate == PRESSED)
						{
							Serial.println("Alarm is turned off");
							alarmIsOff = true;
							lcd.clear();
						}
					}
				}
			}
		}
	}
	if (!isTimeCorrect)
	{
		Serial.println("Setting alarmIsOff to false");
		alarmIsOff = false;
	}
}