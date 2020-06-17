#include "DHT.h"
#include "BH1750FVI.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#define fire 14
#define rain 15
#define Dht 16
#define buzzer 2
#define red 3
#define green 4
#define blue 5

int fire_sensor = 0;
int rain_sensor = 0;
int temp_sensor = 0;
int humid_sensor = 0;
float light_sensor = .0;

DHT dht(Dht, DHT11);
BH1750FVI myLux(0x23);
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void rgbled(int r, int g, int b) {
  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
}

#include <LWiFi.h>
#include "MCS.h"
int color_red = 100;
int color_green = 100;
int color_blue = 100;
char _lwifi_ssid[] = "MakerLab_2.4G";
char _lwifi_pass[] = "53574722";
MCSDevice mcs("D2OdLkjh", "bL6L0ie7nrDuBLiE");

MCSDisplayInteger Data1("Data1");
MCSDisplayInteger Data2("Data2");
MCSDisplayInteger Data3("Data3");
MCSDisplayFloat Data4("Data4");
MCSDisplayInteger Data5("Data5");
MCSControllerInteger Slider1("Slider1");
MCSControllerInteger Slider2("Slider2");
MCSControllerInteger Slider3("Slider3");


void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(fire, INPUT);
  pinMode(rain, INPUT);
  dht.begin();
  Wire.begin();
  myLux.powerOn();
  myLux.setContHighRes();
  u8g2.begin();
  mcs.addChannel(Data1);
  mcs.addChannel(Data2);
  mcs.addChannel(Data3);
  mcs.addChannel(Data4);
  mcs.addChannel(Data5);
  mcs.addChannel(Slider1);
  mcs.addChannel(Slider2);
  mcs.addChannel(Slider3);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  if (!mcs.connected()) {
    mcs.connect();
  }
}

void loop() {
  fire_sensor = !digitalRead(fire);
  rain_sensor = digitalRead(rain);
  temp_sensor = dht.readHumidity();
  humid_sensor = dht.readTemperature();
  light_sensor = myLux.getLux();
  if (fire_sensor == 1 || rain_sensor == 1) {
    for (int i=0;i<3;i++) {
      tone(buzzer, 1000, 100);
      delay(200);
    }
  }
  if (light_sensor < 50) {
    rgbled(color_red, color_green, color_blue);
  }
  else {
    rgbled(0, 0, 0);
  }
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "Smart IOT");
  u8g2.drawStr(0, 20, ("Temp: "+ String(temp_sensor)).c_str());
  u8g2.drawStr(0, 30, ("Humid: "+ String(humid_sensor)).c_str());
  u8g2.drawStr(0, 40, ("Fire: "+ String(fire_sensor)).c_str());
  u8g2.drawStr(0, 50, ("Light: "+ String(light_sensor)).c_str());
  u8g2.drawStr(0, 60, ("Rain: "+ String(rain_sensor)).c_str());
  u8g2.sendBuffer();
  if (!mcs.connected()) {
    mcs.connect();
  }
  mcs.process(100);
  Data1.set(temp_sensor);
  Data2.set(humid_sensor);
  Data3.set(fire_sensor);
  Data4.set(light_sensor);
  Data5.set(rain_sensor);
  if (Slider1.updated()) {
    color_red = Slider1.value();
  }
  if (Slider2.updated()) {
    color_green = Slider2.value();
  }
  if (Slider3.updated()) {
    color_blue = Slider3.value();
  }
}
