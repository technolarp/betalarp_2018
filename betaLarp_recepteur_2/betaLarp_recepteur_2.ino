// code source basé sur 
// https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/examples/WiFiScan

#include "ESP8266WiFi.h"
#include <Adafruit_NeoPixel.h>

// connexion de la LED RGB sur la pin D2
#define PIN D2

// 1 seule led
#define NUMPIXELS 1

// on initialise la LED RGB
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() 
{
  // on demarre la LED RGB
  pixels.begin();
  // on affiche un violet tres pale
  // pixels.setPixelColor(NUM_LED, ROUGE, VERT, BLEU);
  pixels.setPixelColor(0,5,0,5);
  pixels.show();

  // nécessaire pour les cartes Wemos D1 mini
  WiFi.persistent(false);
  
  // on demarre l AP wifi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  delay(100);
}

void loop() 
{
  
  // WiFi.scanNetworks renvoie le nb de reseau wifi detectes
  byte available_networks = WiFi.scanNetworks();

  if (available_networks == 0)
  {
    //Serial.println("no networks found");
    // rien
  }
  else
  {
    for (int network = 0; network < available_networks; network++) 
    {
      int val = WiFi.SSID(network).indexOf("ZONE_MAGIQUE");
      
      // on a trouve un reseau ZONE_MAGIQUE
      if (val == 0)
      {
        int zone_1 = WiFi.SSID(network).indexOf("ZONE_MAGIQUE_1");
        if (zone_1==0)
        {
          // ZONE MAGIQUE 1 detectee
          // rouge pur
          pixels.setPixelColor(0,255,50,0);
          
          // mise a jour de la couleur de la LED
          pixels.show();

          // on attend 3s
          delay(3000);
        }
        
        int zone_2 = WiFi.SSID(network).indexOf("ZONE_MAGIQUE_2");
        if (zone_2==0)
        {
          // ZONE MAGIQUE 2 detectee
          // vert pur
          pixels.setPixelColor(0,0,255,50);
          
          // mise a jour de la couleur de la LED
          pixels.show();

          // on attend 3s
          delay(3000);
        }

        int zone_3 = WiFi.SSID(network).indexOf("ZONE_MAGIQUE_3");
        if (zone_3==0)
        {
          // ZONE MAGIQUE 3 detectee
          // bleu pur
          pixels.setPixelColor(0,50,0,255);
          
          // mise a jour de la couleur de la LED
          pixels.show();

          // on attend 3s
          delay(3000);
        }
      }
    }
  }

  // on affiche un violet pale
  pixels.setPixelColor(0,5,0,5); 
  // mise a jour de la couleur de la LED
  pixels.show();

  // on attend 2s
  delay(2000);
}


