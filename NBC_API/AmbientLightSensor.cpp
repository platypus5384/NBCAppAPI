#include "AmbientLightSensor.h"


AmbientLightSensor::AmbientLightSensor() {
  Wire.beginTransmission( OPT3001_ADRS);
  Wire.write( OPT3001_CONFIG);
  Wire.write(0xC6);
  Wire.write(0x10);
  Wire.endTransmission();
}


uint16_t AmbientLightSensor::read() {
  
  Wire.beginTransmission( OPT3001_ADRS);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(1);
  
  
  Wire.requestFrom( OPT3001_ADRS, 2);
  uint8_t d1 = Wire.read();
  uint8_t d2 = Wire.read();
  Serial.print(d1);
  Serial.print(", ");
  Serial.println(d2);
  return (d1 << 8) | d2;
}
