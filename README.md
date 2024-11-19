# hello_world-thing #

a simple example demonstrating the development of custom "modular things" 

This work demonstrates the development, installation and use of a custom "thing" for the "[Modular-Things](https://github.com/modular-things/modular-things)" project.

> Nota bene: in contrast to the "things" provided by the "Modular-Things" project itself, this one has been developed for a [Pimoroni Tiny2040](https://shop.pimoroni.com/products/tiny-2040) board (simply because I just had one on my desk). Since it uses the built-in RGB LEDs of that board, you may have to adjust the LED output commands in the Arduino "Firmware" shown below in order to make a thing for a different board.

## Installation and Usage ##

Below are instructions for installation and use of the "hello_world" thing - skip whatever does not seem applicable:

#### Firmware Preparation ####

1. Install Arduino IDE (see https://www.arduino.cc/en/software)
2. Install the board "**Raspberry Pi Pico/RP2040/RP2350** by Earle F. Philhower, III" using the Arduino "Boards Manager"
3. Install "**osap** by Jake Robert Read" using the Arduino "Library Manager"

#### Firmware Installation ####

1. Create a new sketch and rename it to `hello_world`
2. Copy the firmware shown below into the sketch editor using the clipboard
3. Connect the RP2040 board via USB and select it from the board dropdown in the Arduino IDE
4. Compile and upload the sketch

#### Software Preparation ####

1. Install Node.js (see https://nodejs.org/en/)
2. Download "modular-things" as a [ZIP archive](https://github.com/modular-things/modular-things/archive/refs/heads/main.zip), unpack it, and move it to a location of your choice
3. Open a terminal window and navigate to the extracted directory
4. run `npm install`

#### Software Installation ####

1. Open the terminal window and navigate to the extracted directory
2. copy the "hello_world" directory and its contents into the `things` folder. In the end, `./things/hello_world` should have the following structure:
```
./things/hello_world/
  circuit/
    images/
      layout.png
      schematic.png
      preview.png
  firmware/
    hello_world/
      hello_world.ino
  software/
    hello_world.ts
```
3. Insert the following text into file `./things/_things.json` after the first line (i.e., the opening bracket):
```json
  {
    "author":  "Andreas Rozek",
    "name":    "hello_world",
    "software":"software/hello_world.ts",
    "firmware":"firmware/hello_world/hello_world.ino",
    "images": [
      { 
        "name": "layout", 
        "src": "circuit/images/layout.png"
      },
      { 
        "name": "schematic", 
        "src": "circuit/images/schematic.png"
      },
      { 
        "name": "preview", 
        "src": "circuit/images/preview.png"
      }
    ]
  },
```
12. Insert the following lines into the file `./index.ts`
  * `import hello_world from "./hello_world/software/hello_world";`<br>
    e.g., as the last import statement
  * `hello_world,`<br>
    e.g., as the last line in the `export default {` block
13. (Re)start the server
    `npm run dev`




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
