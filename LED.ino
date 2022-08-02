#include <FastLED.h>
#include <OneButton.h>

// Pin numbers.
const int ledPins[6] = {13, 12, 11, 10, 9, 8};
const int buttonPin = 7;
OneButton btn = OneButton(buttonPin, true, true);

// Button states.
int buttonPressed = 0;

// Animation durations in miliseconds.
const int sparkInterval = 50;
const int energyFlowPeriod = 5;

// LED strip arrays.
const int NUM_LEDS = 27;
CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
CRGB leds_3[NUM_LEDS];
CRGB leds_4[NUM_LEDS];
CRGB leds_5[NUM_LEDS];
CRGB leds_6[NUM_LEDS];

// LED strip brightness.
const int brightness = 50;


// ------------------- Gradient Palettes START --------------------- //  
DEFINE_GRADIENT_PALETTE(yellow_gp) {       // Update required, red dots present.
  0, 255, 255, 0,
  100, 255, 255, 0,
  127, 255, 255, 170,
  154, 255, 255, 0,
  255, 255, 255, 0
};

DEFINE_GRADIENT_PALETTE(blue_gp) {         // Less green, overall good looking.
  0, 0, 121, 255,
  127, 0, 255, 213,
  255, 0, 121, 255
};

DEFINE_GRADIENT_PALETTE(red_gp) {          // Update required, yellow dots present.
  0, 255, 0, 0,
  100, 255, 0, 0,
  127, 255, 0, 20,
  154, 255, 0, 0,
  255, 255, 0, 0
};

DEFINE_GRADIENT_PALETTE(green_gp) {        // Less yellow, overall good looking.
  0, 0, 255, 0,
  127, 255, 251, 0,
  255, 0, 255, 0
};

DEFINE_GRADIENT_PALETTE(pink_gp) {         // Update required, random colours present.
  0, 247, 15, 172,
  100, 247, 15, 172,
  127, 251, 210, 122,
  154, 247, 15, 172,
  255, 247, 15, 172
};

DEFINE_GRADIENT_PALETTE(purple_gp) {       // Good looking.
  0, 105, 0, 254,
  100, 105, 0, 254,
  127, 245, 0, 240,
  154, 105, 0, 254,
  255, 105, 0, 254
};

CRGBPalette16 yellow = yellow_gp;
CRGBPalette16 blue = blue_gp;
CRGBPalette16 red = red_gp;
CRGBPalette16 green = green_gp;
CRGBPalette16 pink = pink_gp;
CRGBPalette16 purple = purple_gp;
// ------------------- Gradient Palettes END --------------------- //


// LED color indices.
uint8_t colorIndex_1[NUM_LEDS];
uint8_t colorIndex_2[NUM_LEDS];
uint8_t colorIndex_3[NUM_LEDS];
uint8_t colorIndex_4[NUM_LEDS];
uint8_t colorIndex_5[NUM_LEDS];
uint8_t colorIndex_6[NUM_LEDS];


void setup() {
  // Setup Dout pins for LED strips.
  FastLED.addLeds<WS2812B, 13, GRB>(leds_1, NUM_LEDS); // Ledpins integers can be found here.
  FastLED.addLeds<WS2812B, 12, GRB>(leds_2, NUM_LEDS);
  FastLED.addLeds<WS2812B, 11, GRB>(leds_3, NUM_LEDS);
  FastLED.addLeds<WS2812B, 10, GRB>(leds_4, NUM_LEDS);
  FastLED.addLeds<WS2812B, 9, GRB>(leds_5, NUM_LEDS);
  FastLED.addLeds<WS2812B, 8, GRB>(leds_6, NUM_LEDS);
  FastLED.setBrightness(brightness);

  // Setup Din pin for button.
  pinMode(buttonPin, INPUT_PULLUP);
  btn.attachClick(stateChange);

  // Fill the colorIndex with random numbers
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex_1[i] = random8();
    colorIndex_2[i] = random8();
    colorIndex_3[i] = random8();
    colorIndex_4[i] = random8();
    colorIndex_5[i] = random8();
    colorIndex_6[i] = random8();
  }
}


void loop() {
  if (buttonPressed == 13) {
    stopAnimations();
    return 0;
  }
  if (buttonPressed >= 12) {         // Done.
    runPurpleEnergy();
  }

  if (buttonPressed == 11) {         // 6th stone inserted.
    runPurpleSpark();
  }

  if (buttonPressed >= 10) {         // Watiing for 6th stone.
    runPinkEnergy();
  }
  
  if (buttonPressed == 9) {         // 5th stone inserted.
    runPinkSpark();
  }

  if (buttonPressed >= 8) {         // Watiing for 5th stone.
    runGreenEnergy();
  }

  if (buttonPressed == 7) {         // 4th stone inserted.
    runGreenSpark();
  }

  if (buttonPressed >= 6) {         // Watiing for 4th stone.
    runRedEnergy();
  }

  if (buttonPressed == 5) {         // 3rd stone inserted.
    runRedSpark();
  }

  if (buttonPressed >= 4) {         // Waiting for 3rd stone.
    runBlueEnergy();
  }

  if (buttonPressed == 3) {         // 2nd stone inserted.
    runBlueSpark();
  }

  if (buttonPressed >= 2) {         // Waiting for 2nd stone.
    runYellowEnergy();
  }

  if (buttonPressed == 1) {         // 1st stone inserted.
    runYellowSpark();
  }

  FastLED.show();
  btn.tick();
}


// -------------------- Key Animation Functions START -------------------- //
void stopAnimations() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_1[i] = CRGB::Black;
    leds_2[i] = CRGB::Black;
    leds_3[i] = CRGB::Black;
    leds_4[i] = CRGB::Black;
    leds_5[i] = CRGB::Black;
    leds_6[i] = CRGB::Black;
  }
}
// -------------------- Key Functions END -------------------- //


// -------------------- Spark Animation Functions START -------------------- //
void runYellowSpark() {
  EVERY_N_MILLISECONDS(sparkInterval) {
    leds_1[random8(0, NUM_LEDS - 1)] = ColorFromPalette(yellow, random8(), 255, LINEARBLEND);
  }
  fadeToBlackBy(leds_1, NUM_LEDS, 1);
}

void runBlueSpark() {
  EVERY_N_MILLISECONDS(sparkInterval) {
    leds_2[random8(0, NUM_LEDS - 1)] = ColorFromPalette(blue, random8(), 255, LINEARBLEND);
  }
  fadeToBlackBy(leds_2, NUM_LEDS, 1);
}

void runRedSpark() {
  EVERY_N_MILLISECONDS(sparkInterval) {
    leds_3[random8(0, NUM_LEDS - 1)] = ColorFromPalette(red, random8(), 255, LINEARBLEND);
  }
  fadeToBlackBy(leds_3, NUM_LEDS, 1);
}

void runGreenSpark() {
  EVERY_N_MILLISECONDS(sparkInterval) {
    leds_4[random8(0, NUM_LEDS - 1)] = ColorFromPalette(green, random8(), 255, LINEARBLEND);
  }
  fadeToBlackBy(leds_4, NUM_LEDS, 1);
}

void runPinkSpark() {
  EVERY_N_MILLISECONDS(sparkInterval) {
    leds_5[random8(0, NUM_LEDS - 1)] = ColorFromPalette(pink, random8(), 255, LINEARBLEND);
  }
  fadeToBlackBy(leds_5, NUM_LEDS, 1);
}

void runPurpleSpark() {
  EVERY_N_MILLISECONDS(sparkInterval) {
    leds_6[random8(0, NUM_LEDS - 1)] = ColorFromPalette(purple, random8(), 255, LINEARBLEND);
  }
  fadeToBlackBy(leds_6, NUM_LEDS, 1);
}
// -------------------- Spark Animation Functions END -------------------- //


// -------------------- Energy Flow Animation Functions START -------------------- //
void runYellowEnergy() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_1[i] = ColorFromPalette(yellow, colorIndex_1[i]);
  }

  EVERY_N_MILLISECONDS(energyFlowPeriod){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex_1[i]++;
    }
  }
}

void runBlueEnergy() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_2[i] = ColorFromPalette(blue, colorIndex_2[i]);
  }

  EVERY_N_MILLISECONDS(energyFlowPeriod){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex_2[i]++;
    }
  }
}

void runRedEnergy() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_3[i] = ColorFromPalette(red, colorIndex_3[i]);
  }

  EVERY_N_MILLISECONDS(energyFlowPeriod){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex_3[i]++;
    }
  }
}

void runGreenEnergy() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_4[i] = ColorFromPalette(green, colorIndex_4[i]);
  }

  EVERY_N_MILLISECONDS(energyFlowPeriod){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex_4[i]++;
    }
  }
}

void runPinkEnergy() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_5[i] = ColorFromPalette(pink, colorIndex_5[i]);
  }

  EVERY_N_MILLISECONDS(energyFlowPeriod){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex_5[i]++;
    }
  }
}

void runPurpleEnergy() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_6[i] = ColorFromPalette(purple, colorIndex_6[i]);
  }

  EVERY_N_MILLISECONDS(energyFlowPeriod){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex_6[i]++;
    }
  }
}
// -------------------- Energy Flow Animation Functions END -------------------- //

void stateChange() {
  buttonPressed ++;
}
