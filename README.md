# hello_world-thing #

a simple example demonstrating the development of custom "modular things" 

This work demonstrates the development, installation and use of a custom "thing" for the "[Modular-Things](https://github.com/modular-things/modular-things)" project.

> Nota bene: in contrast to the "things" provided by the "Modular-Things" project itself, this one has been developed for a [Pimoroni Tiny2040](https://shop.pimoroni.com/products/tiny-2040) board (simply because I just had one on my desk). Since it uses the built-in RGB LEDs of that board, you may have to adjust the LED output commands in the Arduino "Firmware" shown below in order to make a thing for a different board.

## Installation Usage ##

Below are instructions for installation and use of the "hello_world" thing - skip what you have already done

## Firmware ##

In the "Modular-Things" terminology, the "firmware" of a thing is an Arduino sketch which implements a thing's functionality on the hardware side. Here is the one for the "hello_world" thing:

```c++
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
```

## Software ##

In the "Modular-Things" terminology, the "software" of a thing is its JavaScript interface (which may still include some additional functionality on the software side). Here is the one for the "hello_world" thing:

```typescript
import Thing from "../../../src/lib/thing"

export default class hello_world extends Thing {
  async setRGB (R:number, G:number, B:number):Promise<void> {
    const Datagram = new Uint8Array([
      255 * Math.max(0,Math.min(R,1)),
      255 * Math.max(0,Math.min(G,1)),
      255 * Math.max(0,Math.min(B,1)),
    ])
    await this.send('setRGB',Datagram)
  }

/**** API Documentation ****/

  public api = [{
    name: 'setRGB',
    args: [
      'R: 0 to 1',
      'G: 0 to 1',
      'B: 0 to 1'
    ]
  }]
}
```

## Application Example ##

An "application" may be some JavaScript code entered into and run by the "Modular Things" web editor.

> **Important**: as soon as you plan to use custom things, you can no longer use the original web environment found at [https://modular-things.com/](https://modular-things.com/) but must navigate your browser to [http://localhost:3000](http://localhost:3000) (assuming that you use the default port).

Here is an example for an application using the "hello_world" thing:

```javascript
const BlinkDelay = 800 // LED toggle every BlinkDelay millisecond

let Value = 0
loop(async () => {
    Value = (Value === 0 ? 0.1 : 0)
    await LEDView.setRGB(0,0,Value)
}, BlinkDelay)
```

## License ##

[MIT License](LICENSE.md)
