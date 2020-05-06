/***************************************************************************
  Aquaponics-ENGR195D class

  Due to the COVID-19 the team were not able to full test the code, and thus
  resorted to documenting the details of our plan for the next team.
 ***************************************************************************/

#include <Wire.h>
#include "Adafruit_AS726x.h"

//create the object
Adafruit_AS726x ams;
int red, blue, green, yellow, orange, violet;

// normalize and calibrate the color values to avoid extreme changes
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
  

  ams.drvOn(); // turns on LED if the enviroment is not well lit
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

 // Debug code to check the values - Testing purpose 
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
