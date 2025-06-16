#include <ESP32Encoder.h>

const int M1A = 18;
const int M1B = 5;
const int VR = 32;
const int ENC1A = 17;
const int ENC1B = 16;

const int MARGIN = 50;

ESP32Encoder ENC1;

void setup() {
  analogWrite(M1A, 0);
  analogWrite(M1B, 0);
  analogWriteResolution(M1A, 8);
  analogWriteResolution(M1B, 8);
  analogWriteFrequency(M1A, 500);
  analogWriteFrequency(M1B, 500);

  pinMode(ENC1A, INPUT);
  pinMode(ENC1B, INPUT);
  ENC1.attachSingleEdge(ENC1A, ENC1B);
  ENC1.clearCount();

  analogReadResolution(10);

  Serial.begin(115200);
}

void loop() {
  int sensor = analogRead(VR) - 512;

  if (sensor > MARGIN) {
    analogWrite(M1A, map(sensor, 0, 512, 0, 255));
    analogWrite(M1B, 0);
  }
  else if (sensor < -MARGIN) {
    analogWrite(M1A, 0);
    analogWrite(M1B, map(-sensor, 0, 512, 0, 255));
  }
  else {
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
  }
  Serial.println(ENC1.getCount());

  delay(100);
}
