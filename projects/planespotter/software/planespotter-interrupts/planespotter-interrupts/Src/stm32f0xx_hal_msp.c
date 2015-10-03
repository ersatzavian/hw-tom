/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "planespotter_brd.h"

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void) {
  __SYSCFG_CLK_ENABLE();

  /* System interrupt init*/
/* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @}
  */

/**
  * @}
  */