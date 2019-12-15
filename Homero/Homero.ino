/*********************************************************************

 *  *  OLED pinout:
     - GND goes to ground
     - Vin goes to 3.3V
     - Data to I2C SDA (GPIO 0 ==>D3)
     - Clk to I2C SCL  (GPIO 2 ==>D4)


 *********************************************************************/
#define SW_VERSION "NH_temphum_meter_wifi_v0.1"

/* NodeMCU ESP12-E */
#include <ESP8266WiFi.h>
WiFiClient client;
const char* MY_SSID = "_SSID_";
const char* MY_PWD = "_PWD_";

/* Thinkspeak */
const char* TS_SERVER = "api.thingspeak.com";
String TS_API_KEY = "_TS_APY_KEY";
int sent = 0;

/* OLED */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

/* DHT22*/
#include "SimpleDHT.h"

int pinDHT22 = D3;
int button = D4;
SimpleDHT22 dht22(pinDHT22);
float temperature = 0;
float humidity = 0;
uint32_t time1 = millis();
uint32_t time2 = millis();
uint32_t readDelay = 60000; //300000; //6000


void setup()
{
  Serial.begin(115200);
  pinMode(button, INPUT);

  
  connectWifi();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear the buffer.
  display.clearDisplay();
  display.display();
  //display.dim(true);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("NH Temp monitor v0.1");
  display.display();
  
    

}



void loop()
{
  time2 = millis();
  if (time1 + readDelay < time2)
  {
    getDhtDataSilent();
    time1 = millis();
  }

  if (digitalRead(button) == LOW)
  {
    Serial.println("Button: LOW");
    getDhtData();
    display.clearDisplay();
    display.display();

  }
  else
  {
    Serial.println("Button: HIGH");
    display.clearDisplay();
    display.println("HIGH");
    display.display();

  }

}

/* Get DHT DATA SILENT */
void getDhtDataSilent(void)
{
  // start working...
  Serial.println("=================================");
  // Clear display
  display.clearDisplay();
  display.display();

  // read without samples.
  //  float temperature = 0;
  //  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err); delay(2000);
    return;
  }

  Serial.print("Hőmérséklet: "); Serial.print((float)temperature); Serial.print(" °C, ");
  Serial.print("Páratartalom: "); Serial.print((float)humidity); Serial.println(" rH%");
  delay(1500);
  //delay(300000); /*5000 */

  //THINGSPEAK DATA
  if (client.connect(TS_SERVER, 80))
    Serial.println("Sending...");
  {
    String postStr = TS_API_KEY;
    postStr += "&field1=";
    postStr += String(temperature);
    postStr += "&field2=";
    postStr += String(humidity);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + TS_API_KEY + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    delay(1000);
  }
  sent++;
  client.stop();

  Serial.println("Data is sent. I'm going to sleep for 30s");
    ESP.deepSleep(300e6); 
}


/* Get DHT data */
void getDhtData(void)
{
  // start working...
  Serial.println("=================================");


  // read without samples.
  //  float temperature = 0;
  //  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err); delay(2000);
    return;
  }

  Serial.print("Hőmérséklet: "); Serial.print((float)temperature); Serial.print(" °C, ");
  Serial.print("Páratartalom: "); Serial.print((float)humidity); Serial.println(" rH%");

  display.clearDisplay();

  display.dim(true);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.print("Hum: "); display.print(humidity); display.print(" rH%");
  display.display();


  //5 percenként küldés 5x60
  //delay(300000); /*5000 5 másodpercig megy a kijelző */
  delay(5000);

}



/***************************************************
   Connecting WiFi
 **************************************************/
void connectWifi()
{
  delay(1000);

  WiFi.begin(MY_SSID, MY_PWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("");
}
