#include <Arduino.h>
#include <WiFi.h>
// 0: Network setup is successful
// 1: Network setup failed
int setupNetwork() {
	WiFi.mode(WIFI_AP_STA);
	WiFi.begin();

	int tm = 0;
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
		tm++;
		if (tm >= 30) {
			Serial.println("Failed to connect WiFi");
			return 1;
		}
	}
	Serial.println("WiFi Connected");
	return 0;
}