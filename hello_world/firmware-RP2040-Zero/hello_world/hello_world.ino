#include <osap.h>
#include <Adafruit_NeoPixel.h>

#define builtin_LED_Pin 16

  OSAP_Runtime osap;
  OSAP_Gateway_USBSerial serLink(&Serial);
  OSAP_Port_DeviceNames namePort("hello_world");

/**** RGB Control  ****/

  Adafruit_NeoPixel builtin_LED(1, builtin_LED_Pin, NEO_GRB + NEO_KHZ800);

  void _setRGB (uint8_t* Data, size_t Length) {
    int R = (Length < 1 ? 0 : Data[0]);
    int G = (Length < 2 ? 0 : Data[1]);
    int B = (Length < 3 ? 0 : Data[2]);

    builtin_LED.setPixelColor(0,builtin_LED.Color(R,G,B));
    builtin_LED.show();
  }
  OSAP_Port_Named setRGB("setRGB",_setRGB);

/**** Startup ****/

  void setup() {
    osap.begin();

    builtin_LED.begin();
    builtin_LED.clear();
    builtin_LED.setBrightness(50);
    builtin_LED.show();
  }

/**** Operation ****/

  void loop() {
    osap.loop();
  }
