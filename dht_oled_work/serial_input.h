#define manual_input_temp(Serial, input_ser)  \
  ({                                          \
    if (Serial.available() > 0) {             \
      String input_tmp = Serial.readString(); \
      input_tmp.trim();                       \
      if (input_tmp == "off") {               \
        Serial.println("off change action");  \
        input_ser = 0;                        \
      } else {                                \
        Serial.println("change temp");        \
        input_ser = 1;                        \
        temp = input_tmp.toFloat();           \
        Serial.print("temp has change to ");  \
        Serial.println(temp);                 \
      }                                       \
    }                                         \
  })