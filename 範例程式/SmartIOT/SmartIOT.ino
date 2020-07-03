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
}

void loop() {
  fire_sensor = !digitalRead(fire);
  rain_sensor = digitalRead(rain);
  temp_sensor = dht.readTemperature();
  humid_sensor = dht.readHumidity();
  light_sensor = myLux.getLux();
  if (fire_sensor == 1 || rain_sensor == 1) {
    for (int i=0;i<3;i++) {
      tone(buzzer, 1000, 100);
      delay(200);
    }
  }
  if (light_sensor < 50) {
    rgbled(100, 100, 100);
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
  delay(1000);
}
