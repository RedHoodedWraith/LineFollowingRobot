/**
 * 
 */
#ifndef COLOURS_LED
#define COLOURS_LED

#include "MeRGBLed.h"

namespace colour{

    enum led_select {
        ALL = 0,
        RIGHT = 1,
        LEFT = 2
    };

    class colourRGB{
        public:
            unsigned int red;
            unsigned int green;
            unsigned int blue;

            colourRGB();
            colourRGB(unsigned int r, unsigned int g, unsigned int b);
    };

    class LEDset{
        private:
            MeRGBLed _ledObj;
        
        public:
            LEDset(MeRGBLed obj);
            void lightConfig(led_select led, unsigned int r, unsigned int g, unsigned int b);
            void lightConfig(led_select led, colourRGB col);
            void allOff();

            colourRGB red;
            colourRGB green;
            colourRGB blue;
    };

};

using namespace colour;

#endif