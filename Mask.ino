
/* 
 *  8x8 LED matrix control by Arduino (Facemask)
 *  Created by William Dumberry
 *  04/08/2020
 *  
 *  using : 
 *     Arduino 256 RGB LEDs Matrix Animation Frame 
 *     Using WS2812 LED Strips
 *     Created by Yvan / https://Brainy-Bits.com
 *
 *     FastLED library : https://github.com/FastLED
 */

// Libraries
#include <avr/pgmspace.h>  // Needed to store stuff in Flash using PROGMEM
#include "FastLED.h"       // Fastled library to control the LEDs

// Numbers of led connected to the 8x8 matrix
// To be changed if needed
#define NUM_LEDS 64


// Define the Data Pin
#define DATA_PIN 3  // Connected to the data pin of the first LED strip

// Define the array of leds
CRGB leds[NUM_LEDS];

// Create the arrays of retro arcade characters and store it in Flash memory
// All arrays (vectors 1X NUM_LEDS) represents RGB color of a particuliar LED
// Note : The data sent to the led follows their wirering order. 
const long Neutral[] PROGMEM = 
{
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000, 0x000000,
0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};

const long SmallOpen[] PROGMEM = 
{
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000, 0x000000,
0x000000, 0x000000, 0xffffff, 0x000000, 0x000000, 0xffffff, 0x000000, 0x000000,
0xffffff, 0xffffff, 0x000000, 0x000000, 0x000000, 0x000000, 0xffffff, 0xffffff,
0x000000, 0x000000, 0xffffff, 0x000000, 0x000000, 0xffffff, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0xffffff, 0xffffff, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};

const long BigOpen[] PROGMEM = 
{
0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000, 0x000000,
0x000000, 0xffffff, 0xffffff, 0x000000, 0x000000, 0xffffff, 0xffffff, 0x000000,
0x000000, 0xffffff, 0x000000, 0x000000, 0x000000, 0x000000, 0xffffff, 0x000000,
0xffffff, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xffffff,
0x000000, 0xffffff, 0x000000, 0x000000, 0x000000, 0x000000, 0xffffff, 0x000000,
0x000000, 0xffffff, 0xffffff, 0x000000, 0x000000, 0xffffff, 0xffffff, 0x000000,
0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0xffffff, 0xffffff, 0x000000, 0x000000, 0x000000
};

const long SmallSmile[] PROGMEM = 
{
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0xffffff, 0x000000, 0x000000, 0xffffff, 0xffffff, 0x000000, 0x000000, 0xffffff,
0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000,
0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};

const long BigSmile[] PROGMEM = 
{
0xfffffff, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xffffff,
0xffffff, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xffffff,
0xffffff, 0xffffff, 0x000000, 0x000000, 0x000000, 0x000000, 0xffffff, 0xffffff,
0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000,
0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};

const long SmallTongue[] PROGMEM = 
{
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000, 0x000000,
0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
0x000000, 0xffffff, 0xff0000, 0xffA0A0, 0xffA0A0, 0xff0000, 0xffffff, 0x000000,
0x000000, 0x000000, 0xff0000, 0xffA0A0, 0xffA0A0, 0xff0000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};
         
const long BigTongue[] PROGMEM = 
{
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000, 0x000000,
0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
0x000000, 0xffffff, 0xff0000, 0xffA0A0, 0xffA0A0, 0xff0000, 0xffffff, 0x000000,
0x000000, 0x000000, 0xff0000, 0xffA0A0, 0xffA0A0, 0xff0000, 0x000000, 0x000000,
0x000000, 0x000000, 0xff0000, 0xff7070, 0xff7070, 0xff0000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};


// Initialization of the variables
const int microInputPin = 0;
const long int lowerSoundBound = 100;
const long int higherSoundBound = 800;
int mouthState;
bool switchState = false;
unsigned long int currentTime = 0;
unsigned long int previousTime = 0;
unsigned const int periodMS = 60;
long int microBuffer = 0; 
int microInputValue = 0;
bool tongueButtonPushed = false;
const int tongueButtonPin = 1;
int tongueInput = 0;
long int tongueBuffer = 0;
bool smileButtonPushed = false;
const int smileButtonPin = 2;
int smileInput = 0;
bool sadButtonPushed = false;
const int sadButtonPin = 3;
int sadInput = 0;


// Initialize the FastLED object
void setup() { 
FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // Init of the Fastled library
FastLED.setBrightness(20);
Serial.begin(9600); // Used for debugging
}

// Main program
void loop() { 
currentTime = millis();                        // Update the current time of the system
microInputValue = analogRead(microInputPin);   // Reed the value from the sound sensor
/* smileInput = analogRead(smileButtonPin);
 if (smileInput < 700){
  smileButtonPushed = true;
  } else {
    smileButtonPushed = false;
    }
sadInput = analogRead(sadButtonPin);
 if (sadInput < 700){
  sadButtonPushed = true;
  } else {
    sadButtonPushed = false;
    }
*/
// Accumulate the analogic value of the sound sensor in the buffer microbuffer for the current period periodMS
if((currentTime - previousTime) < periodMS){   
  microBuffer += long(1023-microInputValue);
  //tongueInput = analogRead(tongueButtonPin);
  //tongueBuffer += long(tongueInput);
  //Serial.println(tongueBuffer);

// Check if tongue button is pushed
// if (tongueInput < 700 && tongueInput > 500){
//   tongueButtonPushed = false;
//  } else {
//    tongueButtonPushed = false;
//    }
// if (tongueInput < 700 && tongueInput > 500){
//tongueButtonPushed = true;
   } else { 
    tongueBuffer = 0;
    switchState = true;
    previousTime = currentTime;}

if(switchState) {
  switchState = false;  
  Serial.println(microBuffer);
switch (mouthState) {
  case 0:
    if (microBuffer > lowerSoundBound) {
      mouthState = 1; //Small open
      }
    if (tongueButtonPushed) {
//      tongueInput = analogRead(tongueButtonPin);
//      if(tongueInput < 700 && tongueInput > 500){
//        mouthState = 3;
//        } else {
//          tongueButtonPushed = false;
//          }
      }
    if (smileButtonPushed) {
      mouthState = 5;
      }
    if (sadButtonPushed) {
      mouthState = 3;
      }
    break;
  case 1:
      if(microBuffer > lowerSoundBound){
        if (microBuffer > higherSoundBound) {
          mouthState = 2; //Big open
        }
      } else {
        mouthState = 0; //Neutral
        }
    break;
   case 2:
       if (microBuffer < higherSoundBound) {
        mouthState = 1; //Small open
       } 
    break;
    case 3:
      if(tongueButtonPushed) {
        mouthState = 4;
        tongueButtonPushed = false;
        } else {
          mouthState = 0;
          tongueButtonPushed = false;
          }
    break;
    case 4:
       mouthState = 3;
    break;
    case 5:
      if(smileButtonPushed) {
        mouthState = 6;
        smileButtonPushed = false;
        } else {
          mouthState = 0;
          }
    break;
    case 6:
        mouthState = 5;
    break;
    case 7:
      if(sadButtonPushed) {
        mouthState = 8;
        sadButtonPushed = false;
        } else {
          mouthState = 0;
          }
    break;
    case 8:
        mouthState = 7;
    break;
  default:
    mouthState = 0; //Neutral
    break;
  } 
   microBuffer = 0;
  }
  
//Print LEDs
switch (mouthState) {
  case 0:
    FastLED.clear();
      for(int i = 0; i < NUM_LEDS; i++) {
       leds[i] = pgm_read_dword(&(Neutral[i]));  // Read array from Flash
       }
    FastLED.show();
    break;
  case 1:
    FastLED.clear();
      for(int i = 0; i < NUM_LEDS; i++) {
       leds[i] = pgm_read_dword(&(SmallOpen[i]));  // Read array from Flash
       }
    FastLED.show();
    break;
  case 2:
    FastLED.clear();
      for(int i = 0; i < NUM_LEDS; i++) {
       leds[i] = pgm_read_dword(&(BigOpen[i]));  // Read array from Flash
       }
    FastLED.show();
    break;
  case 3:
    FastLED.clear();
      for(int i = 0; i < NUM_LEDS; i++) {
       leds[i] = pgm_read_dword(&(SmallTongue[i]));  // Read array from Flash
       }
    FastLED.show();
    break;
  case 4: 
    FastLED.clear();
      for(int i = 0; i < NUM_LEDS; i++) {
       leds[i] = pgm_read_dword(&(BigTongue[i]));  // Read array from Flash
       }
    FastLED.show();
    break;
  case 5:
    FastLED.clear();
      for(int i = 0; i < NUM_LEDS; i++) {
       leds[i] = pgm_read_dword(&(SmallSmile[i]));  // Read array from Flash
       }
    FastLED.show();
    break;
  case 6:
    FastLED.clear();
      for(int i = 0; i < NUM_LEDS; i++) {
       leds[i] = pgm_read_dword(&(BigSmile[i]));  // Read array from Flash
       }
    FastLED.show();
    break;
  default:
    FastLED.clear();
    break;
  } 
}
