#include <osap.h>

#define PIN_LED_R 18
#define PIN_LED_G 19
#define PIN_LED_B 20

  OSAP_Runtime osap;
  OSAP_Gateway_USBSerial serLink(&Serial);
  OSAP_Port_DeviceNames namePort("hello_world");

/**** RGB Control (RGB LED on Tiny2040 is "active low"!) ****/

  void _setRGB (uint8_t* Data, size_t Length) {
    analogWrite(PIN_LED_R, 255-Data[0]);
    analogWrite(PIN_LED_G, 255-Data[1]);
    analogWrite(PIN_LED_B, 255-Data[2]);
  }
  OSAP_Port_Named setRGB("setRGB",_setRGB);

/**** Startup ****/

  void setup() {
    osap.begin();

    analogWriteResolution(8);
    pinMode(PIN_LED_R, OUTPUT);
    pinMode(PIN_LED_G, OUTPUT);
    pinMode(PIN_LED_B, OUTPUT);

    analogWrite(PIN_LED_R,255);
    analogWrite(PIN_LED_G,255);
    analogWrite(PIN_LED_B,255);
  }

/**** Operation ****/

  void loop() {
    osap.loop();
  }
