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
  
  // on demarre la conexion wifi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  delay(100);
}

void loop() 
{
  long myRssi = 0;
  String mySSID = "";
  int myIndex = -1;
  
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
      int val = WiFi.SSID(network).indexOf("ZONE_MAGIQUE_1");
      
      // on a trouve un reseau ZONE_MAGIQUE
      if (val == 0)
      {
        // on collecte quelques renseignements
        myIndex = network;
        myRssi = WiFi.RSSI(network);
        mySSID = WiFi.SSID(network);
      }
    }
  }

  if (myIndex >= 0)
  {
    // zone magique detectee
    if (myRssi>=-55)
    {
      // 1er SEUIL
      // zone magique tres proche
      // rouge pur
      pixels.setPixelColor(0,255,0,0);
    }
    else
    {
      if (myRssi>=-65)
      {
        // 2eme SEUIL
        // zone magique moyennement proche
        // orange
        pixels.setPixelColor(0,255,40,0);
      }
      else
      {
        // 3eme SEUIL
        // zone magique a portee, mais eloignee
        // jaune
        pixels.setPixelColor(0,255,100,0);
      }
    }
  }
  else
  {
    // zone magique hors de portée
    // on affiche un violet pale
    pixels.setPixelColor(0,5,0,5);
  }

  // mise a jour de la couleur de la LED
  pixels.show();

  
  // on attend 2s
  delay(2000);
}


