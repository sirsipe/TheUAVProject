// NEED Libraries:
// - Adafruit PWM Servo Driver Library
// - EnableInterrupt

#include <EnableInterrupt.h>
#include "Adafruit_PWMServoDriver.h"

#define CHANNELS 6
#define DIGITAL_PINS 3, 5, 6, 9, 10, 11

const byte _InputPins[CHANNELS] = { DIGITAL_PINS };

// Cache
volatile uint16_t _PWMValues[CHANNELS] = { 0 };

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();
#define PWM_FREQ 50

void GetPWMData(uint16_t channels[CHANNELS])
{
  for(uint16_t ch = 0; ch < CHANNELS; ch++)
    channels[ch] = _PWMValues[ch]; 
}


// Some syntactic sugar to ease up handler declarations. CH_HANDLER_NAME(X) 
// pre-compiles into chX_handler which can be used as function name.
#define CH_HANDLER_NAME(x) ch##x##_handler

#define CHANNEL_HANDLER(x) \
  void CH_HANDLER_NAME(x) () { \
    const uint8_t chIndex = x - 1; \
    const byte UNKNOWN_STATUS = 99; \
    static byte lastStatus = UNKNOWN_STATUS; \
    static uint32_t start = 0; \
    switch (lastStatus) { \
      case UNKNOWN_STATUS: \
      { \
        lastStatus = digitalRead(_InputPins[chIndex]) == HIGH ? LOW : HIGH; \
        break; \
      } \
      case HIGH: \
      { \
        lastStatus = LOW; \
        start = micros(); \
        break; \
      } \
      case LOW: \
      { \
        lastStatus = HIGH; \
        uint16_t value = micros() - start; \
        _PWMValues[chIndex] = value; \
        break; \
      } \
    }\
  }

// Cherry on the top: Setup the handler
#define SETUP_CH_HANDLER(x) \
  pinMode(_InputPins[x-1], INPUT); \
  enableInterrupt(_InputPins[x-1], CH_HANDLER_NAME(x), CHANGE);


void setup() {
  SETUP_CH_HANDLER(1);
  SETUP_CH_HANDLER(2);
  SETUP_CH_HANDLER(3);
  SETUP_CH_HANDLER(4);
  SETUP_CH_HANDLER(5);
  SETUP_CH_HANDLER(6);
  
  pwmDriver.begin();
  pwmDriver.setPWMFreq(PWM_FREQ);
  
}
void loop() {
  uint16_t values[CHANNELS];
  GetPWMData(values);

  for (int i = 0; i < CHANNELS; i++)
  {
    if (values[i])
      setServoPulse(i, values[i]);
  }  
}


CHANNEL_HANDLER(1)
CHANNEL_HANDLER(2)
CHANNEL_HANDLER(3)
CHANNEL_HANDLER(4)
CHANNEL_HANDLER(5)
CHANNEL_HANDLER(6)


void setServoPulse(uint8_t n, double pulse) {

  double pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= PWM_FREQ;   
  pulselength /= 4096;  // 12 bits of resolution
  pulse /= pulselength;
  pwmDriver.setPWM(n, 0, pulse);
    
}
