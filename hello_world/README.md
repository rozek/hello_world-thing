This is just a simple example (and a "proof-of-concept") for a custom modular "thing".

It controls the built-in RGB LED of a Pimoroni Tiny2040 - for different boards, you may have to modify the LED driver logic in the Arduino code (i.e., the "firmware").

A simple program to test a paired "hello_world" thing (renamed to `LEDView`) may be:

```javascript

  let Value = 0
  loop(async () => {
    Value = (Value === 0 ? 0.1 : 0)
    LEDView.setRGB(0,0,Value)
  }, 800)
 
```