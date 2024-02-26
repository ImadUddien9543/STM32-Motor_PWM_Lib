/*
 * PWM_Motor.h
 *
 *  Created on: Feb 26, 2024
 *      Author: Imaduddien
 */

#ifndef INC_PWM_MOTOR_H_
#define INC_PWM_MOTOR_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include "stdlib.h"
#include "stdint.h"

typedef struct _PWM_MOTOR_t{
	TIM_HandleTypeDef *htim_A, *htim_B;
	TIM_TypeDef *in_A, *in_B;
	uint32_t ch_A, ch_B;
	void (*Set_CCR_A)(TIM_TypeDef*, int_fast32_t);
	void (*Set_CCR_B)(TIM_TypeDef*, int_fast32_t);
	void (*Move_MOTOR)(struct _PWM_MOTOR_t*, int_fast32_t);
}PWM_MOTOR;

extern PWM_MOTOR *Init_Motor(TIM_HandleTypeDef *htim_A, TIM_HandleTypeDef *htim_B, uint32_t ch_A, uint32_t ch_B);

#endif /* INC_PWM_MOTOR_H_ */
