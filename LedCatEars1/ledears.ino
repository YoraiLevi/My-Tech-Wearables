#include <FastLED.h>

#define LED_PIN     2
#define NUM_LEDS    32
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 60

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.



CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
extern const TProgmemPalette16 PurpleAndGreenPalette_p PROGMEM;
extern const TProgmemPalette16 SetupBlackAndWhiteStriped_p PROGMEM;


void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
}

#define CHANGE_MODE_PERIOD (1000*20)
#define N_MODES 8
void loop()
{
  //static bool animationDirection = 0;
  //    if((millis()) % CHANGE_MODE_PERIOD==0){

  //      animationDirection = random()%2;
  //    }
  static uint8_t startIndex = 0;
  switch (millis() / (CHANGE_MODE_PERIOD / 3) % 2) {
    case 0:
    
      startIndex = startIndex + 1;
      break;
    case 1:
      startIndex = startIndex - 1;
      break;
  }
  switch (millis() / CHANGE_MODE_PERIOD % N_MODES) {
    case 0:
    case 1:
    case 5:
    case 6:
    {

        ChangePalettePeriodically();
        FillLEDsFromPaletteColors( startIndex);
        break;
    } case 3:
    case 4:
    case 7:
      // a colored dot sweeping back and forth, with fading trails
      { fadeToBlackBy( leds, NUM_LEDS, 20);
        int pos = beatsin16( 13, 0, NUM_LEDS - 1 );
        leds[pos] += CHSV( startIndex, 255, 192);
        break;
      }
    case 2: {
        // eight colored dots, weaving in and out of sync with each other
        fadeToBlackBy( leds, NUM_LEDS, 20);
        byte dothue = 0;
        for ( int i = 0; i < 8; i++) {
          leds[beatsin16( i + 7, 0, NUM_LEDS - 1 )] |= CHSV(dothue, 200, 255);
          dothue += 32;
        }
      } break;
  }
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;

  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

// 1 = 5 sec per palette
// 2 = 10 sec per palette
// etc
#define HOLD_PALETTES_X_TIMES_AS_LONG 3


void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000 / HOLD_PALETTES_X_TIMES_AS_LONG) % 30;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { SetupTotallyRandomPalette();         currentBlending = LINEARBLEND; }
        if( secondHand == 5)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 10)  { currentPalette = PurpleAndGreenPalette_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 15)  { currentPalette = ForestColors_p;       currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { currentPalette = SetupBlackAndWhiteStriped_p;       currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { currentPalette = LavaColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { currentPalette = myRedWhiteBluePalette_p;           currentBlending = NOBLEND; }
        }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
  for ( int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV( random8(), 255, random8());
  }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.

const TProgmemPalette16 SetupBlackAndWhiteStriped_p PROGMEM =
{
  CRGB::White,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::White,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::White,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::White,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black

};

const TProgmemPalette16 PurpleAndGreenPalette_p PROGMEM =
{
  CRGB::Purple,
  CRGB::Purple,
  CRGB::Black,
  CRGB::Black,
  CRGB::Green,
  CRGB::Green,
  CRGB::Black,
  CRGB::Black,
  CRGB::Purple,
  CRGB::Purple,
  CRGB::Black,
  CRGB::Black,
  CRGB::Green,
  CRGB::Green,
  CRGB::Black,
  CRGB::Black
};
// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};



// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
