#include "Arduino.h"
#include <NeoPixel_Animator.h>
#include <Adafruit_NeoPixel.h>    // library of functions to control the LED strip
#include <avr/pgmspace.h>         // Library for accessing program memory


Animation::Animation(Adafruit_NeoPixel& p, const uint32_t* const f[], int numFrames, int frameSize, int startingPixel) {
  this->pixels = &p;
  this->numFrames = numFrames;
  frames = new uint32_t*[numFrames];
  for (int i = 0; i < numFrames; i++) {
    frames[i] = pgm_read_ptr(&f[i]); // Read the pointers to the frames from program memory, and store them in this object 
  }
  this->startingPixel = startingPixel;
  this->lastFrame=0;
  this->frameSize = frameSize;
}

void Animation::writeNextFrame() {
      this->lastFrame++; // Increment the frame to display 
      if (this->lastFrame == this->numFrames) {
        this->lastFrame = 0;
      }
      const uint32_t* img = frames[this->lastFrame]; // Get the pointer to the frame to display 
      for (int i = 0; i < this->frameSize; i++) { // Loop through the pixels in the frame
        uint32_t value = pgm_read_dword_near(&img[i]); // Read the 32bit value in program memory representing a pixel
        int red = (value & 0xff0000) >> 16; // Parse the red value in the pixel using a bit mask and bit shifting
        int green = (value & 0x00ff00) >> 8; // Parse green
        int blue = (value & 0x0000ff); // Parse blue
        // Serial.println(i);
        // Serial.println(red);
        // Serial.println(green);
        // Serial.println(blue);
        this->pixels->setPixelColor(this->startingPixel+i, green, red, blue); // Set the pixel colour to the parsed colours (GRB)
      }
      
}

Animation::~Animation() {
  delete this->frames;
}