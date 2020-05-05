/***************************************************************************
  This is a library for the Adafruit AS7262 6-Channel Visible Light Sensor

  This sketch reads the sensor

  Designed specifically to work with the Adafruit AS7262 breakout
  ----> http://www.adafruit.com/products/3779
  
  These sensors use I2C to communicate. The device's I2C address is 0x49
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  
  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include "Adafruit_AS726x.h"

//create the object
Adafruit_AS726x ams;
int red, blue, green, yellow, orange, violet;

inline void readCalibratedColors(int high_constrain){
  red = ams.readRed();
  green = ams.readGreen();
  yellow = ams.readYellow();
  blue = ams.readBlue();
  orange = ams.readOrange();
  violet = ams.readViolet();

  red = constrain(red, 0, high_constrain);
  green = constrain(green,0, high_constrain);
  blue = constrain(blue, 0, high_constrain);
  yellow = constrain(yellow, 0, high_constrain);
  orange = constrain(orange, 0, high_constrain);
  violet = constrain(violet, 0, high_constrain);
  
}

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //begin and make sure we can talk to the sensor
  if(!ams.begin()){
    Serial.println("could not connect to sensor! Please check your wiring.");
    while(1);
  }
  ams.setIntegrationTime(254);
  ams.setGain(GAIN_64X);
  //ams.drvOn();
}

void loop() {

  //read the device temperature
  uint8_t temp = ams.readTemperature();

  ams.startMeasurement(); //begin a measurement
  
  //wait till data is available
  bool rdy = false;
  while(!rdy){
    delay(5);
    rdy = ams.dataReady();
  }

  readCalibratedColors(10000);
  
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" Violet: "); Serial.print(violet);
  Serial.print(" Blue: "); Serial.print(blue);
  Serial.print(" Green: "); Serial.print(green);
  Serial.print(" Yellow: "); Serial.print(yellow);
  Serial.print(" Orange: "); Serial.print(orange);
  Serial.print(" Red: "); Serial.print(red);
  Serial.println();
  Serial.println();
}
