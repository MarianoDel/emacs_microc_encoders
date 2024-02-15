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
void CheckEncoder (unsigned char encoder_index, unsigned char * encoder_value);


// Module Functions ------------------------------------------------------------
int main (void)
{
    // Gpio Configuration.
    GpioInit();
    
    // Systick Timer Activation
    if (SysTick_Config(64000))
        SysTickError();

    // Hardware Tests
    // TF_Hardware_Tests ();

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
    unsigned char freq_p1 = 0;
    unsigned char freq_p2 = 0;
    unsigned char freq_p3 = 0;
    unsigned char freq_p4 = 0;    
    unsigned char power_p1 = 0;
    unsigned char power_p2 = 0;
    unsigned char power_p3 = 0;
    unsigned char power_p4 = 0;    

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
    DisplayUpdate (ENCODER_FRQ_P1, freq_p1);
    DisplayUpdate (ENCODER_FRQ_P2, freq_p2);
    DisplayUpdate (ENCODER_FRQ_P3, freq_p3);
    DisplayUpdate (ENCODER_FRQ_P4, freq_p4);

    DisplayUpdate (ENCODER_PWR_P1, power_p1);
    DisplayUpdate (ENCODER_PWR_P2, power_p2);
    DisplayUpdate (ENCODER_PWR_P3, power_p3);
    DisplayUpdate (ENCODER_PWR_P4, power_p4);    
    
    // Comms_Send_Encoder_Data (ENCODER_DISPLAY_1, encoder1);    
    // Comms_Send_Encoder_Data (ENCODER_DISPLAY_2, encoder2);

    while (1)
    {
        // first part
        CheckEncoder (ENCODER_FRQ_P1, &freq_p1);
        CheckEncoder (ENCODER_PWR_P1, &power_p1);

        // second part
        CheckEncoder (ENCODER_FRQ_P2, &freq_p2);
        CheckEncoder (ENCODER_PWR_P2, &power_p2);

        // third part
        CheckEncoder (ENCODER_FRQ_P3, &freq_p3);
        CheckEncoder (ENCODER_PWR_P3, &power_p3);

        // fourth part
        CheckEncoder (ENCODER_FRQ_P4, &freq_p4);
        CheckEncoder (ENCODER_PWR_P4, &power_p4);
        
        Hard_Update_Encoders ();            
        
    }
}

//--- End of Main ---//


// Other Module Functions ------------------------------------------------------
void CheckEncoder (unsigned char encoder_index, unsigned char * encoder_value)
{
    if (CheckCW (encoder_index))
    {
        if (*encoder_value)
            *encoder_value -= 1;

        DisplayUpdate (encoder_index, *encoder_value);
        // Comms_Send_Encoder_Data (encoder_index, encoder1);
    }

    if (CheckCCW (encoder_index))
    {
        if (*encoder_value < 5)
            *encoder_value += 1;

        DisplayUpdate (encoder_index, *encoder_value);
        // Comms_Send_Encoder_Data (encoder_index, encoder1);
    }
    
}
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

