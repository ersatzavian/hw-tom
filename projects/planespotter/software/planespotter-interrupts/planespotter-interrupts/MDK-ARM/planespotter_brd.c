#include "planespotter_brd.h"

void setLed(uint16_t _led, uint16_t _state) {
	uint16_t state = GPIO_PIN_RESET;
	uint16_t led = GPIO_PIN_5;
	if (_state == 0) { state = GPIO_PIN_SET; }
	if (_led == 2) { led = GPIO_PIN_6; }
	if (_led == 3) { led = GPIO_PIN_7; }
	HAL_GPIO_WritePin(GPIOB, led, state);
}

void toggleLed(uint16_t _led) {
	uint16_t led = GPIO_PIN_5;
	if (_led == 2) { led = GPIO_PIN_6; }
	if (_led == 3) { led = GPIO_PIN_7; }
	HAL_GPIO_TogglePin(GPIOB, led);
}

uint16_t readDecoder(void) {
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET) {
		return 1;
	} else {
		return 0;
	}
}

uint16_t readBtn(uint16_t _btn) {
	uint16_t btn = GPIO_PIN_6;
	if (_btn == 2) { btn = GPIO_PIN_7; }
	if (_btn == 3) { btn = GPIO_PIN_8; }
	if (HAL_GPIO_ReadPin(GPIOA, btn) == GPIO_PIN_SET) { 
		return 1;
	} else { 
		return 0;
	}
}