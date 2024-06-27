# ArduinoGIF

This is an [Arduino](https://www.arduino.cc/) library which adds on to the [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) library by creating a method to display animations on a NeoPixel light strip. 

All you need to do, is take your desired images, and run them through a file to C array converter ([Like this one](https://notisrac.github.io/FileToCArray/)), put your frames into your code, and pass them to an instance of the Animation class, along with your NeoPixel object, and some information about the frames. You can then just call the `writeNextFrame()` function and the Animation will write the next frame in the sequence to your strip!

This libarary also supports the ability to give custom mappings to your pixels if say for example, your grid of LEDs is wired in a way that every second row is reversed, or you want to display you images mirrored without taking up more of your limited program memory