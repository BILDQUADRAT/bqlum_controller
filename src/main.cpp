#include <Arduino.h>
#include <Wire.h>

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

#define statusPin 6

// A, B, Click
Encoder encoder[3] = {
  Encoder(15, 16),
  Encoder(2,  3),
  Encoder(9,  10)
};

void setup() {
  // Status LED
  pinMode(statusPin, OUTPUT);
  digitalWrite(statusPin, HIGH);

  digitalWrite(statusPin, LOW);
  delay(2000);
  digitalWrite(statusPin, HIGH);
  delay(2000);

  Wire.begin(); // join i2c bus (address optional for master)
}

void loop() {
  for(uint8_t i = 0; i < sizeof(encoder); i++) {
    long value = encoder[i].read();
    if(value != 0) {
      encoder[i].write(0);
      Wire.beginTransmission(8);
      Wire.write(i);
      Wire.write(value);
      Wire.endTransmission();
    }
  }
}
