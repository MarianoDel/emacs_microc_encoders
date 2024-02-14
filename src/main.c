//---------------------------------------------------------------
// #### PROJECT MICRO-CURRENTS ENCODERS F103 - Custom Board #####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### MAIN.C ##################################################
//---------------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "stm32f10x.h"
#include "hard.h"

#include "tim.h"
#include "gpio.h"
#include "i2c.h"

#include "is31_handler.h"
#include "test_functions.h"
#include "display.h"
#include "comms.h"

#include <stdio.h>
#include <string.h>


// Private Types Constants and Macros ------------------------------------------


// Externals -------------------------------------------------------------------
//--- Externals from timers
volatile unsigned short timer_standby = 0;
volatile unsigned short wait_ms_var = 0;


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------
void TimingDelay_Decrement(void);
void SysTickError (void);



// Module Functions ------------------------------------------------------------
int main (void)
{
    // Gpio Configuration.
    GpioInit();
    
    // Systick Timer Activation
    if (SysTick_Config(64000))
        SysTickError();

    // Hardware Tests
    TF_Hardware_Tests ();

    // --- main program inits. ---
    // //-- DMA configuration.
    // DMAConfig();
    // DMA_ENABLE;
    
    // //-- ADC with DMA
    // AdcConfig();
    // // ADC_START;

    // //-- DAC init for signal generation
    // DAC_Config ();
    // DAC_Output1(1400);
    
    // //-- Comms with rasp
    // Usart1Config ();

    // //-- Comms with probes
    // // Usart3Config ();

    // //-- TIM1 for signals module sequence ready
    // TIM6_Init();
    // TIM7_Init();
    //-- Starts with all channels disabled
    // Ena_Ch1_Off();
    // Ena_Ch2_Off();
    // Ena_Ch3_Off();
    // Ena_Ch4_Off();

    // //-- Comms with rasp & channels
    // UsartRpiConfig ();
    // UsartChannel1Config ();
    // UsartChannel2Config ();

    // char buff [120];
    // char buff_tx [128];
    unsigned char encoder1 = 0;
    unsigned char encoder2 = 0;

    SDB_CH1_OFF;
    SDB_CH2_OFF;
    SDB_CH3_OFF;
    SDB_CH4_OFF;

    I2C1_Init();
    Wait_ms(100);
    I2C1_Reset ();

    I2C2_Init();
    Wait_ms(100);
    I2C2_Reset ();
    
    for (int i = 0; i < 3; i++)
    {
        Led_On();
        Wait_ms(250);
        Led_Off();
        Wait_ms(250);
    }

    IS31_Init (I2C_ADDR_P1);
    IS31_Init (I2C_ADDR_P2);
    IS31_Init (I2C_ADDR_P3);
    IS31_Init (I2C_ADDR_P4);        
    
    //-- Main Loop --------------------------
    DisplayUpdate (ENCODER_DISPLAY_1, encoder1);
    // Comms_Send_Encoder_Data (ENCODER_DISPLAY_1, encoder1);
    DisplayUpdate (ENCODER_DISPLAY_2, encoder2);
    // Comms_Send_Encoder_Data (ENCODER_DISPLAY_2, encoder2);

    while (1)
    {
        // first encoder
        if (CheckCW (ENCODER_NUM_1))
        {
            if (encoder1)
                encoder1--;

            DisplayUpdate (ENCODER_DISPLAY_1, encoder1);
            // Comms_Send_Encoder_Data (ENCODER_DISPLAY_1, encoder1);
        }

        if (CheckCCW (ENCODER_NUM_1))
        {
            if (encoder1 < 5)
                encoder1++;

            DisplayUpdate (ENCODER_DISPLAY_1, encoder1);
            // Comms_Send_Encoder_Data (ENCODER_DISPLAY_1, encoder1);
        }

        // second encoder
        if (CheckCW (ENCODER_NUM_2))
        {
            if (encoder2)
                encoder2--;

            DisplayUpdate (ENCODER_DISPLAY_2, encoder2);
            // Comms_Send_Encoder_Data (ENCODER_DISPLAY_2, encoder2);
        }

        if (CheckCCW (ENCODER_NUM_2))
        {
            if (encoder2 < 5)
                encoder2++;

            DisplayUpdate (ENCODER_DISPLAY_2, encoder2);
            // Comms_Send_Encoder_Data (ENCODER_DISPLAY_2, encoder2);
        }
        
        Hard_Update_Encoders ();            
        
    }
}

//--- End of Main ---//


// Other Module Functions ------------------------------------------------------
// extern void TF_Prot_Int_Handler (unsigned char ch);
// void EXTI2_IRQHandler (void)
// {
//     if(EXTI->PR & EXTI_PR_PR2)    //Line2
//     {
//         Signals_Overcurrent_Handler (CH3);
//         // TF_Prot_Int_Handler (3);    // PROT_CH3 for tests
//         EXTI->PR |= EXTI_PR_PR2;
//     }
// }


// void EXTI4_IRQHandler (void)
// {
//     if(EXTI->PR & EXTI_PR_PR4)    //Line4
//     {
//         Signals_Overcurrent_Handler (CH4);        
//         // TF_Prot_Int_Handler (4);    // PROT_CH4 for tests
//         EXTI->PR |= EXTI_PR_PR4;
//     }
// }


// void EXTI15_10_IRQHandler (void)
// {
//     if(EXTI->PR & EXTI_PR_PR13)    //Line13
//     {
//         Signals_Overcurrent_Handler (CH2);
//         // TF_Prot_Int_Handler (2);    // PROT_CH2 for tests
//         EXTI->PR |= EXTI_PR_PR13;
//     }
//     else if (EXTI->PR & EXTI_PR_PR15)    //Line15
//     {
//         Signals_Overcurrent_Handler (CH1);        
//         // TF_Prot_Int_Handler (1);    // PROT_CH1 for tests
//         EXTI->PR |= EXTI_PR_PR15;
//     }
// }


void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    if (timer_standby)
        timer_standby--;

// AntennaTimeouts ();

    // Treatment_Timeouts ();
    
    Hard_Timeouts();
    
}


void SysTickError (void)
{
    //Capture systick error...
    while (1)
    {
        if (LED)
            LED_OFF;
        else
            LED_ON;

        for (unsigned char i = 0; i < 255; i++)
        {
            asm ("nop \n\t"
                 "nop \n\t"
                 "nop \n\t" );
        }
    }
}

//--- end of file ---//

