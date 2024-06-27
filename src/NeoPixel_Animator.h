#ifndef Animator_h
#define Animator_h
class Adafruit_NeoPixel;

// Class that handles animating a collection of frames using am Adafruit_NeoPixel object
class Animation {
  private:
    Adafruit_NeoPixel* pixels; // The NeoPixel object we will use to write to the lights
    uint32_t** frames; // An array of pointers to the frames in the animation 
    int* pixelMap;
    int startingPixel; // The pixel in the NeoPixel to start drawing at (ex: 4 will skip the first 4 pixels)
    int lastFrame; // The last frame we animated for this animation 
    int frameSize;
    int numFrames;
  public:

    /*
      Constructs an animation
      PARAM p: An Adafruit_NeoPixel object to use to write to a light strip
      PARAM f: An array in program memory of pointers to frames stored in program memory 
      PARAM starting pixel: The pixel to start drawing at 
    */
    Animation(Adafruit_NeoPixel& p, const uint32_t* const f[], int numFrames, int frameSize, int startingPixel);
    void writeNextFrame();
    void setPixelMap(int map[]);
    ~Animation();
};
#endif