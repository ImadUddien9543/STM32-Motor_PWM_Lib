/*
 * PWM_Motor.c
 *
 *  Created on: Feb 26, 2024
 *      Author: Imaduddien
 */

#include "PWM_Motor.h"

static inline void TIM_CH1(TIM_TypeDef *TIMx, uint32_t PWM);
static inline void TIM_CH2(TIM_TypeDef *TIMx, uint32_t PWM);
static inline void TIM_CH3(TIM_TypeDef *TIMx, uint32_t PWM);
static inline void TIM_CH4(TIM_TypeDef *TIMx, uint32_t PWM);

static void Rotate_MOTOR(PWM_MOTOR *self, int_fast32_t PWM);
static void EnableDriver(PWM_MOTOR *self);
static void DisableDriver(PWM_MOTOR *self);

PWM_MOTOR *Init_Motor(TIM_HandleTypeDef *htim_A, TIM_HandleTypeDef *htim_B, uint32_t ch_A, uint32_t ch_B){
	PWM_MOTOR *self;
	self = (PWM_MOTOR*)malloc(sizeof(PWM_MOTOR));
	self->in_A = htim_A->Instance;
	self->in_B = htim_B->Instance;
	self->Move_MOTOR = Rotate_MOTOR;

	self->Enable_MOTOR = EnableDriver;
	self->Disable_MOTOR = DisableDriver;
	self->Enable_MOTOR(self);

	(ch_A == TIM_CHANNEL_1) ? (self->Set_CCR_A = TIM_CH1) :
	(ch_A == TIM_CHANNEL_2) ? (self->Set_CCR_A = TIM_CH2) :
	(ch_A == TIM_CHANNEL_3) ? (self->Set_CCR_A = TIM_CH3) :
	(ch_A == TIM_CHANNEL_4) ? (self->Set_CCR_A = TIM_CH4) : ((void)0U);

	(ch_B == TIM_CHANNEL_1) ? (self->Set_CCR_B = TIM_CH1) :
	(ch_B == TIM_CHANNEL_2) ? (self->Set_CCR_B = TIM_CH2) :
	(ch_B == TIM_CHANNEL_3) ? (self->Set_CCR_B = TIM_CH3) :
	(ch_B == TIM_CHANNEL_4) ? (self->Set_CCR_B = TIM_CH4) : ((void)0U);

	return self;
}

static void Rotate_MOTOR(PWM_MOTOR *self, int_fast32_t PWM){
	if(PWM > 0){
		self->Set_CCR_A(self->in_A, (uint32_t)PWM);
		self->Set_CCR_B(self->in_B, 0);
	}
	else if(PWM < 0){
		self->Set_CCR_A(self->in_A, 0);
		self->Set_CCR_B(self->in_B, (uint32_t)abs(PWM));
	}
	else{
		self->Set_CCR_A(self->in_A, 0);
		self->Set_CCR_B(self->in_B, 0);
	}
}

static inline void TIM_CH1(TIM_TypeDef *TIMx, uint32_t PWM){
	TIMx->CCR1 = PWM;
}
static inline void TIM_CH2(TIM_TypeDef *TIMx, uint32_t PWM){
	TIMx->CCR2 = PWM;
}
static inline void TIM_CH3(TIM_TypeDef *TIMx, uint32_t PWM){
	TIMx->CCR3 = PWM;
}
static inline void TIM_CH4(TIM_TypeDef *TIMx, uint32_t PWM){
	TIMx->CCR4 = PWM;
}

static void EnableDriver(PWM_MOTOR *self){
	HAL_GPIO_WritePin(self->en_port, self->en_pin, GPIO_PIN_SET);
}
static void DisableDriver(PWM_MOTOR *self){
	HAL_GPIO_WritePin(self->en_port, self->en_pin, GPIO_PIN_RESET);
}
