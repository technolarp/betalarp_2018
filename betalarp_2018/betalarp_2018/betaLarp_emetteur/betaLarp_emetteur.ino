// code source basé sur 
// https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 

/* indiquer ici le nom du reseau wifi a creer */
const char *ssid = "ZONE_MAGIQUE_1";

/* facultatif, indiquer le mot de passe du reseau wifi a creer */
const char *password = "tototiti";

void setup() 
{
	delay(1000);
	Serial.begin(115200);
	Serial.println();

	// créer l Access Point wifi
	WiFi.softAP(ssid, password);

	// debug, afficher l'adresse ip sur la sortie serie
	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	Serial.println("AP demarree");
}

void loop() 
{
  // on ne fait rien à part attendre
  delay(10);
}


