/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t trigger = 0;
uint8_t play = 1;
uint16_t m_sec = 0;
uint8_t sec = 0;
uint8_t time = 0;
uint8_t display[6] = {0, 0, 0, 0, 0, 0};
uint16_t scale2freq[]= { //0为休止 从1-36 从低音Do 262Hz依次升高
        //休止
        1,
        //低DO
        262,
        //DO#
        277,
        //低2 RE
        294,
        //RE#
        311,
        //低3 MI
        330,
        //低4 FA
        349,
        //FA#
        370,
        //低5 SO
        392,
        //SO#
        415,
        //低6 LA
        440,
        //LA#
        466,
        //低7 SI
        494,
        //1 DO
        523,
        //DO#
        554,
        //中2 RE
        587,
        //RE#
        622,
        //中3 MI
        659,
        //中4 FA
        698,
        //FA#
        740,
        //中5 SO
        784,
        //SO#
        831,
        //中6 LA
        880,
        //LA#
        932,
        //中7 SI
        988,
        //高1 DO
        1046,
        //DO#
        1109,
        //高2 RE
        1175,
        //RE#
        1245,
        //高3 MI
        319,
        //高4 FA
        1397,
        //FA#
        1480,
        //高5 SO
        1568,
        //SO#
        1661,
        //高6 LA
        1760,
        //LA#
        1865,
        //高7 SI
        1967
};
uint8_t scale[] = { //乐谱 千本樱
//h1 四行为一个小节
20,20,20,20,22,22,22,22, //一行为一个4分音符
15,15,13,13,15,15,13,13,
20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,

20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,
18,18,18,18,17,17,17,17,
18,17,15,15,13,13,13,13,

20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,
20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,

20,20,20,20,22,22,22,22,
25,25,25,25,30,30,30,30,
29,29,30,30,29,29,27,27,
25,25,25,25,22,22,22,22,

//h2
20,20,20,20, 22,22,22,22,
15,15,13,13,15,15,13,13,
20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,

20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,
18,18,18,18,17,17,17,17,
18,17,15,15,13,13,13,13,

15,15,15,15,13,13,15,15,
18,18,18,18,15,15,18,18,
22,22,22,22,20,20,22,22,
25,25,25,25,22,22,25,25,

30,30,30,30,29,29,30,29,
27,27,27,27,25,25,25,25,
27,27,27,27,27,27,27,27,
15,15,15,15,18,18,18,18,

//h3
20,20,20,20, 22,22,22,22,
15,15,13,13,15,15,13,13,
20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,

20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,
18,18,18,18,17,17,17,17,
18,17,15,15,13,13,13,13,

20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,
20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,

20,20,20,20,22,22,22,22,
25,25,25,25,30,30,30,30,
29,29,30,30,29,29,27,27,
25,25,25,25,22,22,22,22,

//h4
20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,
20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,

20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,
18,18,18,18,17,17,17,17,
18,17,15,15,13,13,13,13,

20,20,18,18,22,22,25,25,
27,27,25,25,22,22,20,20,
15,15,15,15,18,18,18,18,
20,20,20,20,22,22,22,22,

15,15,15,15,15,0,15,15,
15,15,15,0,13,13,13,13,
15,15,15,15,15,15,15,15,
0,0,0,0,0,0,0,0,

//h5
15,15,15,15,15,15,15,0,
15,15,15,15,13,13,13,13,
15,15,15,15,18,18,18,0,
18,18,18,18,20,20,20,20,

15,15,15,15,15,15,15,0,
15,15,15,15,13,13,13,13,
15,15,15,15,13,13,13,0,
10,10,10,10,13,13,13,13,

15,15,15,15,15,15,15,0,
15,15,15,15,13,13,13,13,
15,15,15,15,18,18,18,0,
18,18,18,18,20,20,20,20,

22,22,22,22,22,22,22,22,
20,20,20,20,22,22,20,20,
18,18,18,18,18,18,18,18,
15,15,15,15,15,15,15,0,

//h6
15,15,15,15,15,15,15,0,
15,15,15,15,13,13,13,13,
15,15,15,15,18,18,18,0,
18,18,18,18,20,20,20,20,

15,15,15,15,15,15,15,0,
15,15,15,15,13,13,13,13,
15,15,15,15,13,13,13,0,
13,13,13,13,10,10,10,10,

15,15,15,15,15,15,15,0,
15,15,15,15,13,13,13,13,
15,15,15,15,18,18,18,0,
18,18,18,18,20,20,20,20,

22,22,22,22,22,22,22,22,
20,20,20,20,22,22,20,20,
18,18,18,18,18,18,18,18,
15,15,15,15,15,15,15,15,

//h7
18,18,18,18,18,18,18,18,
17,17,17,17,17,17,17,17,
15,15,15,15,15,15,15,15,
13,13,13,13,13,13,13,0,

13,13,13,13,13,13,15,15,
10,10,10,10,8,8,8,8,
10,10,10,10,10,10,10,10,
10,10,10,10,10,10,10,0,

10,10,10,10,13,13,13,13,
15,15,15,15,15,15,15,15,
20,20,20,20,20,20,20,20,
17,17,17,17,17,17,17,17,

18,18,18,18,18,18,18,18,
17,17,17,17,13,13,13,13,
15,15,15,15,15,15,15,15,
15,15,15,15,15,15,15,15,

//h8
18,18,18,18,18,18,18,18,
17,17,17,17,17,17,17,17,
15,15,15,15,15,15,15,15,
13,13,13,13,13,13,13,13,

13,13,13,13,13,13,15,15,
10,10,10,10,8,8,8,8,
10,10,10,10,10,10,10,0,
10,10,10,10,13,13,13,13,

15,15,15,0,15,15,15,15,
15,15,15,0,15,15,15,15,
18,18,18,18,18,18,18,18,
20,20,20,20,20,20,20,20,

17,17,17,17,17,17,17,17,
17,17,17,17,17,17,17,17,
17,17,17,17,0,0,0,0,
15,15,15,15,18,18,18,18,

//h9
20,20,20,0,20,20,20,20,
20,20,20,20,22,22,22,0,
22,22,22,22,22,22,22,22,
22,22,22,0,22,22,22,22,

25,25,25,25,27,27,27,27,
20,20,20,20,18,18,18,18,
22,22,22,22,22,22,22,22,
15,15,15,15,18,18,18,18,

20,20,20,20,20,0,20,20,
20,20,20,20,22,22,22,0,
22,22,22,22,22,22,22,22,
22,22,22,0,22,22,22,22,

23,23,23,23,22,22,22,22,
20,20,20,20,18,18,18,0,
18,18,18,18,18,18,18,18,
15,15,15,15,18,18,18,18,

//h10
20,20,20,20,20,0,20,20,
20,20,20,20,22,22,22,0,
22,22,22,22,22,22,22,22,
22,22,22,0,22,22,22,22,

25,25,25,25,27,27,27,27,
20,20,20,20,18,18,18,18,
22,22,22,22,22,22,22,22,
15,15,15,15,18,18,18,18,

23,23,23,23,23,23,23,23,
22,22,22,22,22,22,22,22,
20,20,20,20,20,20,20,20,
18,18,18,18,18,18,18,18,

20,20,20,20,22,22,22,22,
18,18,18,18,13,13,13,13,
15,15,15,15,15,15,15,0,
15,15,15,15,18,18,18,18,

//h9 2
20,20,20,20,20,0,20,20,
20,20,20,20,22,22,22,0,
22,22,22,22,22,22,22,22,
22,22,22,0,22,22,22,22,

25,25,25,25,27,27,27,27,
20,20,20,20,18,18,18,18,
22,22,22,22,22,22,22,22,
15,15,15,15,18,18,18,18,

20,20,20,20,20,0,20,20,
20,20,20,20,22,22,22,0,
22,22,22,22,22,22,22,22,
22,22,22,0,22,22,22,22,

23,23,23,23,22,22,22,22,
20,20,20,20,18,18,18,0,
18,18,18,18,18,18,18,18,
15,15,15,15,18,18,18,18,

//h10 2 + 11
20,20,20,20,20,0,20,20,
20,20,20,20,22,22,22,0,
22,22,22,22,22,22,22,22,
22,22,22,0,22,22,22,22,

25,25,25,25,27,27,27,27,
20,20,20,20,18,18,18,18,
22,22,22,22,22,22,22,22,
15,15,15,15,18,18,18,18,

23,23,23,23,23,23,23,23,
22,22,22,22,22,22,22,22,
20,20,20,20,20,20,20,20,
18,18,18,18,18,18,18,18,

20,20,20,20,18,18,18,18,
22,22,22,22,25,25,25,25,
27,27,27,27,27,27,27,27,
27,27,27,27,0,0,0,0,

//h3 2
20,20,20,20, 22,22,22,22,
15,15,13,13,15,15,13,13,
20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,

20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,
18,18,18,18,17,17,17,17,
18,17,15,15,13,13,13,13,

20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,
20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,

20,20,20,20,22,22,22,22,
25,25,25,25,30,30,30,30,
29,29,30,30,29,29,27,27,
25,25,25,25,22,22,22,22,

//h4 2
20,20,20,20, 22,22,22,22,
15,15,13,13,15,15,13,13,
20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,

20,20,20,20,22,22,22,22,
15,15,13,13,15,15,13,13,
18,18,18,18,17,17,17,17,
18,17,15,15,13,13,13,13,

20,20,18,18,22,22,25,25,
27,27,25,25,22,22,20,20,
15,15,15,15,15,15,18,18,
20,20,20,20,22,22,22,22,

15,15,15,15,15,0,15,15,
15,15,15,0,13,13,13,13,
15,15,15,15,15,15,15,15,
0,0,0,0,0,0,0,0,

//h12
18,18,18,18,18,18,18,18,
17,17,17,17,17,17,17,17,
15,15,15,15,15,15,15,15,
13,13,13,13,13,13,13,13,

13,13,13,13,13,13,15,15,
10,10,10,10,8,8,8,8,
10,10,10,10,10,10,10,10,
10,10,10,10,10,10,10,0,

10,10,10,10,13,13,13,13,
15,15,15,15,15,15,15,15,
20,20,20,20,20,20,20,20,
17,17,17,17,17,17,17,17,

18,18,18,18,18,18,18,18,
17,17,17,17,13,13,13,13,
15,15,15,15,15,15,15,15,
15,15,15,15,15,15,15,15,

//h13
18,18,18,18,18,18,18,18,
17,17,17,17,17,17,17,17,
15,15,15,15,15,15,15,15,
13,13,13,13,13,13,13,0,

13,13,13,13,13,13,15,15,
10,10,10,10,8,8,8,8,
10,10,10,10,10,10,10,0,
10,10,10,10,13,13,13,13,

15,15,15,0,15,15,15,15,
15,15,15,0,15,15,15,15,
18,18,18,18,18,18,18,18,
20,20,20,20,20,20,20,20,

17,17,17,17,17,17,17,17,
17,17,17,17,17,17,17,17,
17,17,17,17,0,0,0,0,
15,15,15,15,18,18,18,18,

//h14
20,20,20,20,20,0,20,20,
20,20,20,20,22,22,22,0,
22,22,22,22,22,22,22,22,
22,22,22,0,22,22,22,22,

25,25,25,25,27,27,27,27,
20,20,20,20,18,18,18,18,
22,22,22,22,22,22,22,22,
15,15,15,15,18,18,18,18,

20,20,20,20,20,0,20,20,
20,20,20,20,22,22,22,0,
22,22,22,22,22,22,22,22,
22,22,22,0,22,22,22,22,

23,23,23,23,22,22,22,22,
20,20,20,20,18,18,18,0,
18,18,18,18,18,18,18,18,
15,15,15,15,18,18,18,18,

//h15
20,20,20,20,20,0,20,20,
20,20,20,20,22,22,22,0,
22,22,22,22,22,22,22,22,
22,22,22,0,22,22,22,22,

25,25,25,25,27,27,27,27,
20,20,20,20,18,18,18,18,
22,22,22,22,22,22,22,22,
15,15,15,15,18,18,18,18,

23,23,23,23,23,23,23,23,
22,22,22,22,22,22,22,22,
20,20,20,20,20,20,20,20,
18,18,18,18,18,18,18,18,

20,20,20,20,22,22,22,22,
20,20,20,20,22,22,22,22,
22,22,22,22,22,22,22,22,
17,17,17,17,20,20,20,20,

//h16
22,22,22,22,22,0,22,22,
22,22,22,22,24,24,24,0,
24,24,24,24,24,24,24,24,
24,24,24,0,24,24,24,24,

27,27,27,27,29,29,29,29,
22,22,22,22,20,20,20,20,
24,24,24,24,24,24,24,24,
17,17,17,17,20,20,20,20,

22,22,22,22,22,0,22,22,
22,22,22,22,24,24,24,0,
24,24,24,24,24,24,24,24,
24,24,24,0,24,24,24,24,

25,25,25,25,24,24,24,24,
22,22,22,22,20,20,20,0,
20,20,20,20,20,20,20,20,
17,17,17,17,20,20,20,20,

//h17
22,22,22,22,22,0,22,22,
22,22,22,22,24,24,24,0,
24,24,24,24,24,24,24,24,
24,24,24,0,24,24,24,24,

27,27,27,27,29,29,29,29,
22,22,22,22,20,20,20,20,
24,24,24,24,24,24,24,24,
17,17,17,17,20,20,20,20,

25,25,25,25,25,25,25,25,
24,24,24,24,24,24,24,24,
22,22,22,22,22,22,22,22,
20,20,20,20,20,20,20,20,

22,22,22,22,20,20,20,20,
24,24,24,24,27,27,27,27,
29,29,29,29,29,29,29,29,
29,29,29,29,29,29,29,29,
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void DisplayDriver(){
    static uint8_t digit= 0;
    // Turn it off
    HAL_GPIO_WritePin(GPIOA,LED_EN0_Pin | LED_EN3_Pin | LED_EN4_Pin | LED_EN5_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB,LED_EN1_Pin | LED_EN2_Pin , GPIO_PIN_SET);

    //kill the upper pin when there is no need
    //if(sec < 1 && digit < 3) {digit++; return;}
    if(sec < 10 && digit < 2) {digit++; return;}
    if(sec < 100 && digit < 1) {digit++; return;}

    // Choose the pin
    switch (digit) {
        case 0:
            HAL_GPIO_WritePin(GPIOA, LED_EN0_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB, LED_P_Pin , GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOB, LED_EN1_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB, LED_P_Pin , GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOB, LED_EN2_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB, LED_P_Pin , GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOA, LED_EN3_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB, LED_P_Pin , GPIO_PIN_SET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOA, LED_EN4_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB, LED_P_Pin , GPIO_PIN_SET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOA, LED_EN5_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB, LED_P_Pin , GPIO_PIN_SET);
            break;
        default:
            break;
    }
    // Display display[]
    switch (display[digit]) {
        case 0:
            HAL_GPIO_WritePin(GPIOB, LED_A_Pin |LED_C_Pin | LED_E_Pin | LED_F_Pin | LED_B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, LED_B_Pin | LED_D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_G_Pin , GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOA, LED_B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_C_Pin | LED_B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, LED_D_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_A_Pin | LED_E_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_SET);

            break;
        case 2:
						HAL_GPIO_WritePin(GPIOA, LED_A_Pin | LED_E_Pin | LED_G_Pin | LED_B_Pin | LED_D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, LED_F_Pin | LED_C_Pin , GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_A_Pin | LED_E_Pin | LED_G_Pin | LED_B_Pin | LED_D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_F_Pin | LED_C_Pin , GPIO_PIN_SET);

            break;
        case 3:
            HAL_GPIO_WritePin(GPIOA, LED_A_Pin | LED_C_Pin | LED_G_Pin | LED_B_Pin | LED_D_Pin , GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, LED_E_Pin | LED_F_Pin , GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOB, LED_A_Pin | LED_C_Pin | LED_G_Pin | LED_B_Pin | LED_D_Pin , GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_E_Pin | LED_F_Pin , GPIO_PIN_SET);

            break;
        case 4:
            HAL_GPIO_WritePin(GPIOA, LED_B_Pin | LED_C_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_B_Pin | LED_C_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, LED_A_Pin | LED_D_Pin | LED_E_Pin , GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_A_Pin | LED_D_Pin | LED_E_Pin , GPIO_PIN_SET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOA, LED_A_Pin | LED_C_Pin | LED_D_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_A_Pin | LED_C_Pin | LED_D_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, LED_B_Pin | LED_E_Pin , GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_B_Pin | LED_E_Pin , GPIO_PIN_SET);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOA, LED_A_Pin | LED_C_Pin | LED_D_Pin | LED_E_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_A_Pin | LED_C_Pin | LED_D_Pin | LED_E_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, LED_B_Pin , GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_B_Pin , GPIO_PIN_SET);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOA, LED_A_Pin | LED_B_Pin | LED_C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_A_Pin | LED_B_Pin | LED_C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, LED_D_Pin | LED_E_Pin | LED_F_Pin | LED_G_Pin , GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_D_Pin | LED_E_Pin | LED_F_Pin | LED_G_Pin , GPIO_PIN_SET);
            break;
        case 8:
            HAL_GPIO_WritePin(GPIOA, LED_A_Pin | LED_B_Pin | LED_C_Pin | LED_D_Pin | LED_E_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_A_Pin | LED_B_Pin | LED_C_Pin | LED_D_Pin | LED_E_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_RESET);
            break;
        case 9:
            HAL_GPIO_WritePin(GPIOA, LED_A_Pin | LED_B_Pin | LED_C_Pin | LED_D_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_A_Pin | LED_B_Pin | LED_C_Pin | LED_D_Pin | LED_F_Pin | LED_G_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, LED_E_Pin , GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_E_Pin , GPIO_PIN_SET);
            break;
        default:
            break;
    }
    // Go to next pin
    digit++;
    if (digit > 5) { digit = 0; return;}

}


void GetTime(){
    if (m_sec >= 1000){
        m_sec = 0;
        sec++;
    }
    uint16_t m_sec_t = m_sec;
    uint8_t sec_t = sec;
    display[5] = m_sec_t % 10;
    m_sec_t /= 10;
    display[4] = m_sec_t % 10;
    m_sec_t /= 10;
    display[3] = m_sec_t % 10;
    display[2] = sec_t % 10;
    sec_t /= 10;
    display[1] = sec_t % 10;
    sec_t /= 10;
    display[0] = sec_t % 10;
    //操作

}

void Beep(){
    static uint32_t freq = 0; //当前需要播放的音符频率
    static uint32_t flag = 0; //当前需要播放的音符位数
    if(m_sec % 25== 0){ //25ms播放一个32分音符 视一个节拍为 0.025*32 s
        if (flag > 2560) flag = 0; //表明运行多少个音符后从头开始播放 输入scale的长度
        freq = scale2freq[scale[flag++]]; //查询当前需要播放的音符频率
        __HAL_TIM_SET_AUTORELOAD(&htim2,1000000/freq-1); //设置PWM周期
        __HAL_TIM_SET_COUNTER(&htim2,0); //重置PWM计数器
        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,(1000000/freq-1)>>1); //设置占空比【响度 目前为50%】
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); //启动PWM
    }
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_Base_Start_IT(&htim2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
        if(trigger == 0) {
            play = !play;
            if(play == 1 && sec == time){
                m_sec = 0;
                sec =0;
            }
            else{time = sec;}
            trigger = 1;
            HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
        }
        if(play == 1){
            GetTime();
            Beep();
        }

        DisplayDriver();
        HAL_Delay(1);
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1){
        m_sec++;
    }

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_PIN_SET == HAL_GPIO_ReadPin(BTN_0_GPIO_Port,BTN_0_Pin)) {
        trigger = 0;
    }
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
