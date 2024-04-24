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
void CheckEncoderFreq (unsigned char encoder_index, unsigned char * encoder_value);
void CheckEncoderPwr (unsigned char encoder_index, unsigned char * encoder_value);
void CheckEncodersInput (void);


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

    I2C2_Init();
    Wait_ms(100);

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
    DisplayUpdateFreq (ENCODER_FRQ_P1, freq_p1);
    DisplayUpdateFreq (ENCODER_FRQ_P2, freq_p2);
    DisplayUpdateFreq (ENCODER_FRQ_P3, freq_p3);
    DisplayUpdateFreq (ENCODER_FRQ_P4, freq_p4);

    DisplayUpdate (ENCODER_PWR_P1, power_p1);
    DisplayUpdate (ENCODER_PWR_P2, power_p2);
    DisplayUpdate (ENCODER_PWR_P3, power_p3);
    DisplayUpdate (ENCODER_PWR_P4, power_p4);    
    
    // Comms_Send_Encoder_Data (ENCODER_DISPLAY_1, encoder1);    
    // Comms_Send_Encoder_Data (ENCODER_DISPLAY_2, encoder2);

    while (1)
    {
        // first part
        CheckEncoderFreq (ENCODER_FRQ_P1, &freq_p1);
        CheckEncoderPwr (ENCODER_PWR_P1, &power_p1);

        // second part
        CheckEncoderFreq (ENCODER_FRQ_P2, &freq_p2);
        CheckEncoderPwr (ENCODER_PWR_P2, &power_p2);

        // third part
        CheckEncoderFreq (ENCODER_FRQ_P3, &freq_p3);
        CheckEncoderPwr (ENCODER_PWR_P3, &power_p3);

        // fourth part
        CheckEncoderFreq (ENCODER_FRQ_P4, &freq_p4);
        CheckEncoderPwr (ENCODER_PWR_P4, &power_p4);
        
        Hard_Update_Encoders ();

        // check encoders input from rpi
        if (!timer_standby)
        {
            timer_standby = 200;
            CheckEncodersInput ();
        }
    }
}

//--- End of Main ---//


// Other Module Functions ------------------------------------------------------
void CheckEncoderFreq (unsigned char encoder_index, unsigned char * encoder_value)
{
    int update = 0;
    
    if (CheckCW (encoder_index))
    {
        if (*encoder_value)
            *encoder_value -= 1;

        update = 1;
    }

    if (CheckCCW (encoder_index))
    {
        if (*encoder_value < 11)
            *encoder_value += 1;

        update = 1;
    }

    if (update)
    {
        DisplayUpdateFreq (encoder_index, *encoder_value);
        Comms_Send_Encoder_Data (encoder_index, *encoder_value);
    }
}


void CheckEncoderPwr (unsigned char encoder_index, unsigned char * encoder_value)
{
    int update = 0;
    
    if (CheckCW (encoder_index))
    {
        if (*encoder_value)
            *encoder_value -= 1;

        update = 1;
    }

    if (CheckCCW (encoder_index))
    {
        if (*encoder_value < 5)
            *encoder_value += 1;

        update = 1;
    }

    if (update)
    {
        DisplayUpdate (encoder_index, *encoder_value);
        Comms_Send_Encoder_Data (encoder_index, *encoder_value);
    }    
}


unsigned char enc_buff [8];
void CheckEncodersInput (void)
{
    unsigned char buff [8];

    if (I2C2_ReadMultiByte (buff, 0x44 | 0x01, 8) == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            if (buff [i] != enc_buff [i])
            {
                enc_buff[i] = buff[i];
                if (i & 0x01)
                {
                    DisplayUpdate (i, enc_buff[i]);
                }
                else
                {
                    DisplayUpdateFreq (i, enc_buff[i]);                    
                }
            }
        }
    }
}


void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    if (timer_standby)
        timer_standby--;

// AntennaTimeouts ();

    // Treatment_Timeouts ();
    
    Hard_Timeouts();

    I2C_Timeouts ();
    
    
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

