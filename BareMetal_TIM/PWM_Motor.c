/*
 * PWM_Motor.c
 *
 *  Created on: Feb 26, 2024
 *      Author: Imaduddien
 */

#include "PWM_Motor.h"

static inline void TIM_CH1(TIM_TypeDef *TIMx, int_fast32_t PWM);
static inline void TIM_CH2(TIM_TypeDef *TIMx, int_fast32_t PWM);
static inline void TIM_CH3(TIM_TypeDef *TIMx, int_fast32_t PWM);
static inline void TIM_CH4(TIM_TypeDef *TIMx, int_fast32_t PWM);

static void Rotate_MOTOR(PWM_MOTOR *self, int_fast32_t PWM);

PWM_MOTOR *Init_Motor(TIM_HandleTypeDef *htim_A, TIM_HandleTypeDef *htim_B, uint32_t ch_A, uint32_t ch_B){
	PWM_MOTOR *self;
	self = (PWM_MOTOR*)malloc(sizeof(PWM_MOTOR));
	self->in_A = htim_A->Instance;
	self->in_B = htim_B->Instance;
	self->Move_MOTOR = Rotate_MOTOR;

	(ch_A == TIM_CHANNEL_1) ? (self->Set_CCR_A = TIM_CH1) :
	(ch_A == TIM_CHANNEL_2) ? (self->Set_CCR_A = TIM_CH2) :
	(ch_A == TIM_CHANNEL_3) ? (self->Set_CCR_A = TIM_CH3) : (self->Set_CCR_A = TIM_CH4);

	(ch_B == TIM_CHANNEL_1) ? (self->Set_CCR_B = TIM_CH1) :
	(ch_B == TIM_CHANNEL_2) ? (self->Set_CCR_B = TIM_CH2) :
	(ch_B == TIM_CHANNEL_3) ? (self->Set_CCR_B = TIM_CH3) : (self->Set_CCR_B = TIM_CH4);

	return self;
}

static void Rotate_MOTOR(PWM_MOTOR *self, int_fast32_t PWM){
	uint32_t PWM_ = abs(PWM);
	if(PWM < 0){
		self->Set_CCR_A(self->in_A, PWM_);
		self->Set_CCR_B(self->in_B, 0);
	}
	else if(PWM > 0){
		self->Set_CCR_A(self->in_A, 0);
		self->Set_CCR_B(self->in_B, PWM_);
	}
	else{
		self->Set_CCR_A(self->in_A, 0);
		self->Set_CCR_B(self->in_B, 0);
	}
}

static inline void TIM_CH1(TIM_TypeDef *TIMx, int_fast32_t PWM){
	TIMx->CCR1 = PWM;
}
static inline void TIM_CH2(TIM_TypeDef *TIMx, int_fast32_t PWM){
	TIMx->CCR2 = PWM;
}
static inline void TIM_CH3(TIM_TypeDef *TIMx, int_fast32_t PWM){
	TIMx->CCR3 = PWM;
}
static inline void TIM_CH4(TIM_TypeDef *TIMx, int_fast32_t PWM){
	TIMx->CCR4 = PWM;
}
