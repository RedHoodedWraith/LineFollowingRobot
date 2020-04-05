#include "colours_LED.hpp"

using namespace colour;

/** Colour **/

/**
 * Defualt RGB Colour Constructor sets colour to white
 */
colourRGB::colourRGB(){
    red = 0;
    green = 0;
    blue = 0;
}

/**
 * RGB Colour Constructor
 */
colourRGB::colourRGB(unsigned int r, unsigned int g, unsigned int b){
    red = r;
    green = g;
    blue = b;
}

/** LED **/

/**
 * LED Set Object Constructor:
 * Creates the object and saves the mBlock LED object that handles the LED on the mBot.
 * It also saves some default RGB colours.
 * 
 * @param obj  The MeRGBLed object of the lights mBot lights to configure
 */
LEDset::LEDset(MeRGBLed obj){
    _ledObj = obj;

    red = colourRGB(255,0,0);
    green = colourRGB(0,255,0);
    blue = colourRGB(0,0,255);
}

/**
 * Sets the current LED Colour of the selected LEDs
 * @param led   The LED to Select (Either Left, Right or Both)
 * @param r The red component of the colour (value between 0 and 255)
 * @param g The green component of the colour (value between 0 and 255)
 * @param b The blue component of the colour (value between 0 and 255)
*/
void LEDset::lightConfig(led_select led, unsigned int r, unsigned int g, unsigned int b){
    _ledObj.setColor((unsigned int) led, r, g, b);
}

/**
 * Sets the current LED Colour of the selected LEDs
 * @param led   The LED to Select (Either Left, Right or Both)
 * @param col   The RGB Colour Object configured to the desired colour
*/
void LEDset::lightConfig(led_select led, colourRGB col){
    LEDset::lightConfig(led, col.red, col.green, col.blue);
}

/**
 * Turns off all the LEDs on the robot off
 */
void LEDset::allOff(){
    _ledObj.setColor(0, 0, 0, 0);
    _ledObj.show();
}