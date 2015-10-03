#include "stm32f0xx_hal.h"

static void setLed(uint16_t, uint16_t);
static void toggleLed(uint16_t);
uint16_t readDecoder(void);
uint16_t readBtn(uint16_t);