/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "PWM_Motor.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN 0 */
PWM_MOTOR *Motor1;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 2 */  
  Motor1 = Init_Motor(&htim1, &htim1, TIM_CHANNEL_1, TIM_CHANNEL_2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    int pwm = 430;
	  Motor1->Move_MOTOR(Motor1, pwm);

  }
  /* USER CODE END 3 */
}
