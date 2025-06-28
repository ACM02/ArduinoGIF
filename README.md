# ArduinoGIF

This is an [Arduino](https://www.arduino.cc/) library which adds on to the [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) library by creating a method to display animations on a NeoPixel light strip. 

## How to use

### 1. Finding an image

Find an image you want to display on your light strip (**must** match the resolution of your strip)

### 2. Converting to a C array
Run the image you found through a file -> C array converter (like [this](https://notisrac.github.io/FileToCArray/) or [this](https://github.com/bitbank2/image_to_c)), making sure you use a 24bit RGB mode (3bytes/pixel).
This should give you something that looks like this:
```c
const uint32_t arr PROGMEM = {
  0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x22b14c
};
```

### 3. Paste this into your code

Paste the array you generated into your code, like in any of the [examples](examples/).

### 4. Set the frame order

As in the [examples](examples/), you need to tell the library which order to display the frames in. This is done by making an array of the frames you made, like this:

```c
const uint32_t *const frames[] PROGMEM = {frame0, frame1, frame2, frame3};
```

where `frame0`, `frame1`, .... are the arrays you made.

*This uses pointers, if you're not familiar with how pointers work, don't worry about it and just follow the examples*

### 5. Initialize the library

We now need to make an instance of the `Animation`, to do this we need:
 - An Adafruit_NeoPixel strip to write to
 - Our frames
 - The number of frames in the animation 
 - The size of the frames in the animation in number of pixels (ie. 16x16 frames will be 256 pixels)
 - The pixel number to start drawing at, for if you want to start drawing the animation at the nth pixel.

It'll look something like this:
```c
Animation animation = Animation(strip, frames, NUM_FRAMES, FRAME_SIZE, 4);
```

### 6. Re-mapping pixels (optional) 
If your light strip is in a grid, it's likely every other row is indexed in reverse, to account for this, the library has an optional mapping that you can give it.

Make a mapping, like this one, which flips every 2nd row in a 16x16 grid:
```c
const int pixelMap[] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
    31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,
    32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
    63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,
    64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
    95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,
    96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,
    127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,
    128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
    159,158,157,156,155,154,153,152,151,150,149,148,147,146,145,144,
    160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
    191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176,
    192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
    223,222,221,220,219,218,217,216,215,214,213,212,211,210,209,208,
    224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
    255,254,253,252,251,250,249,248,247,246,245,244,243,242,241,240
};
```

And tell the library you want to use it:
```c
Animation animation = Animation(strip, frames, NUM_FRAMES, FRAME_SIZE, 4);

void setup() {
  // .....
  animation.setPixelMap(pixelMap); // Set the pixel map
}
```

### 7. Display Frames

This is probably the easiest step, all you need to do now is tell the animation library to update the light strip with the next frame, something like this:

```c
void loop() {
  // Write the next frame to using the animator
  animation.writeNextFrame();
  // Show the frame on the strip
  strip.show();
  // 500ms delay = 2fps (frames per second)
  delay(500);
}
```