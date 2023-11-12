void ICACHE_RAM_ATTR int_encoder() {
  gv_int_enc = true;
}

void init_button() {
  // Wire.setClock(40000L);
  Wire.begin(/*SDA*/ D2, /*SCL*/ D1);  //(D1mini)

  pinMode(IntPin, INPUT);

  Encoder.reset();
  Encoder.begin(i2cEncoderMiniLib::WRAP_ENABLE
                | i2cEncoderMiniLib::DIRE_RIGHT | i2cEncoderMiniLib::IPUP_ENABLE
                | i2cEncoderMiniLib::RMOD_X1);

  Encoder.writeCounter((int32_t)0);  /* Reset the counter value */
  Encoder.writeMax((int32_t)10);     /* Set the maximum threshold*/
  Encoder.writeMin((int32_t)-10);    /* Set the minimum threshold */
  Encoder.writeStep((int32_t)1);     /* Set the step to 1*/
  Encoder.writeDoublePushPeriod(50); /*Set a period for the double push of 500ms */

  // Definition of the events
  Encoder.onIncrement = encoder_increment;
  Encoder.onDecrement = encoder_decrement;
  Encoder.onMax = encoder_max;
  Encoder.onMin = encoder_min;
  Encoder.onButtonPush = encoder_push;
  Encoder.onButtonRelease = encoder_released;
  Encoder.onButtonDoublePush = encoder_double_push;
  Encoder.onButtonLongPush = encoder_long_push;

  /* Enable the I2C Encoder V2 interrupts according to the previus attached callback */
  Encoder.autoconfigInterrupt();
  delay(100);

  //Encoder.updateStatus();

  gv_int_enc = false;
  gv_enc_push = false;
  gv_enc_rel = false;
  attachInterrupt(digitalPinToInterrupt(IntPin), int_encoder, FALLING);
}

void check_button() {
  //if (digitalRead(IntPin) == LOW) {
  if (gv_int_enc) {
    /* Check the status of the encoder and call the callback */
    Encoder.updateStatus();
    gv_int_enc = false;
  }

  if (gv_enc_inc) {
    if (gv_show_menu) {
      gv_inc_menu = true;
    }
    gv_enc_inc = false;
  }

  if (gv_enc_lpush) {
    //switch gv_menu
    gv_show_menu = true;
    gv_enc_lpush = false;
    gv_enc_ldone = true;
  } else {

    if (gv_enc_rel) {
      if (gv_enc_ldone) {
        gv_enc_ldone = false;
      } else {
        if (gv_show_menu) {
          gv_show_menu = false;
        } else {
          if (gv_enc_push) {
            //switch gv_menu
            gv_do_tare = true;
          }
        }
      }
      gv_enc_push = false;
      gv_enc_rel = false;
    }
  }
}