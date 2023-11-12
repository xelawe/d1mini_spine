#include <Wire.h>
#include <i2cEncoderMiniLib.h>

//Class initialization with the I2C addresses
i2cEncoderMiniLib Encoder(0x20); /* 0c20 A0 is soldered */

boolean gv_enc_push;
boolean gv_enc_lpush;
boolean gv_enc_rel;
bool gv_enc_inc = false;
bool gv_enc_ldone = false;

//Callback when the CVAL is incremented
void encoder_increment(i2cEncoderMiniLib* obj) {
  Serial.print("Increment: ");
  Serial.println(Encoder.readCounterByte());
  gv_enc_inc = true;
}

//Callback when the CVAL is decremented
void encoder_decrement(i2cEncoderMiniLib* obj) {
  Serial.print("Decrement: ");
  Serial.println(Encoder.readCounterByte());
}

//Callback when CVAL reach MAX
void encoder_max(i2cEncoderMiniLib* obj) {
  Serial.print("Maximum threshold: ");
  Serial.println(Encoder.readCounterByte());
}

//Callback when CVAL reach MIN
void encoder_min(i2cEncoderMiniLib* obj) {
  Serial.print("Minimum threshold: ");
  Serial.println(Encoder.readCounterByte());
}

//Callback when the encoder is pushed
void encoder_push(i2cEncoderMiniLib* obj) {
  Serial.println("Encoder is pushed!");
  gv_enc_push = true;
}

//Callback when the encoder is released
void encoder_released(i2cEncoderMiniLib* obj) {
  Serial.println("Encoder is released");
  gv_enc_rel = true;
}

//Callback when the encoder is double pushed
void encoder_double_push(i2cEncoderMiniLib* obj) {
  Serial.println("Encoder is double pushed!");
}

//Callback when the encoder is long pushed
void encoder_long_push(i2cEncoderMiniLib* obj) {
  Serial.println("Encoder is long pushed!");
  gv_enc_lpush = true;
}
