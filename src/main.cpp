/*************************************************************************************
  Aquaponics-ENGR195D Spring 2020 class

  Due to COVID-19 the team were not able to fully test the code at the Tech Museum
  ,and thus resorted to documenting the details of our plan for the next team.
 **************************************************************************************/

#include <Wire.h>
#include "Adafruit_AS726x.h"

//create the color module object and global int values
Adafruit_AS726x ams;
int red, blue, green, yellow, orange, violet;

/*
Purpose: normalize and calibrate the color values to avoid extreme changes
parameter: high_constrain (used to specify the maximum constrain value)

return: void

*/
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

/*
  Purpose: Measure the cuvette and return the estimated High range PH value
  Parameters: void/None

  Simply compare the color values and return the appropriate values. Unfortunately due to
  covid-19 were not able to test it under the right conditions.

  return : float PH value (6.0 - 7.6) reference the color card
*/
inline float highRangePH(){

  float ph_value = 0;

  //if(yellow > green && yellow > blue && yellow > 450) ph_value = 6
  //else if(yellow > green && yellow > blue & yellow < 450) ph_value = 6.4

  return ph_value;
}

/*
  Purpose: Read nitrite value from a sample water test
  Parameters: void/None

  Use the 6 channel color value to determine the nitrite value in the sample
  Needs more tweaking once tested on the aquaponics system

  return : float nitrite value (0 ppm - 5.0 ppm) reference the color card
*/

inline float read_nitrite(){
  float nitrite_value = 0;

  if(blue > yellow && blue > violet) nitrite_value = 0;
  else if(violet > green && violet > blue && red < blue) nitrite_value = 0.25;
  else if(violet > blue && red > green) nitrite_value = 0.50;
  // more test to be conducted below

  return nitrite_value;
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
