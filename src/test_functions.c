//----------------------------------------------------------
// #### MAGNET PROJECT - Custom Board ####
// ## Internal Test Functions Module
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### TEST_FUNCTIONS.C ###################################
//----------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "test_functions.h"
#include "hard.h"
#include "stm32f10x.h"
#include "gpio.h"
// #include "adc.h"
// #include "usart_channels.h"
// #include "usart.h"
// #include "dma.h"
#include "tim.h"

#include <stdio.h>
#include <string.h>


// Externals -------------------------------------------------------------------
extern volatile unsigned short timer_standby;


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------
void TF_Led (void);

void TF_Encoder_1 (void);

void TF_Encoder_CheckSET1 (void);
void TF_Encoder_CheckCW1 (void);
void TF_Encoder_CheckCCW1 (void);

void TF_Encoder_CheckSET2 (void);
void TF_Encoder_CheckCW2 (void);
void TF_Encoder_CheckCCW2 (void);



// Module Functions ------------------------------------------------------------
void TF_Hardware_Tests (void)
{
    // TF_Led ();

    // TF_Encoder_1 ();

    // TF_Encoder_CheckSET1 ();
    // TF_Encoder_CheckCW1 ();
    // TF_Encoder_CheckCCW1 ();

    TF_Encoder_CheckSET2 ();
    // TF_Encoder_CheckCW2 ();    
    // TF_Encoder_CheckCCW2 ();
    
}


void TF_Led (void)
{
    while (1)
    {
        Wait_ms(1000);

        if (Led_Is_On())
        {
            Led_Off();
        }
        else
        {
            Led_On();
        }
    }
}


void TF_Encoder_1 (void)
{
    while (1)
    {
        if (EN_SW_1)
            Led_On();
        else
            Led_Off();

        Wait_ms(500);
    }
}


void TF_Encoder_CheckSET1 (void)
{
    while (1)
    {
        if (CheckSET (ENCODER_NUM_1) > SW_NO)
            Led_On();
        else
            Led_Off();

        Hard_Update_Switches ();
    }
}


void TF_Encoder_CheckCW1 (void)
{
    while (1)
    {
        if (CheckCW (ENCODER_NUM_1))
            timer_standby = 50;

        if (timer_standby)
            Led_On();
        else
            Led_Off();

        Hard_Update_Encoders ();
    }
}


void TF_Encoder_CheckCCW1 (void)
{
    while (1)
    {
        if (CheckCCW (ENCODER_NUM_1))
            timer_standby = 50;

        if (timer_standby)
            Led_On();
        else
            Led_Off();

        Hard_Update_Encoders ();
    }
}


void TF_Encoder_CheckSET2 (void)
{
    while (1)
    {
        if (CheckSET (ENCODER_NUM_2) > SW_NO)
            Led_On();
        else
            Led_Off();

        Hard_Update_Switches ();
    }
}


void TF_Encoder_CheckCW2 (void)
{
    while (1)
    {
        if (CheckCW (ENCODER_NUM_2))
            timer_standby = 50;

        if (timer_standby)
            Led_On();
        else
            Led_Off();

        Hard_Update_Encoders ();
    }
}


void TF_Encoder_CheckCCW2 (void)
{
    while (1)
    {
        if (CheckCCW (ENCODER_NUM_2))
            timer_standby = 50;

        if (timer_standby)
            Led_On();
        else
            Led_Off();

        Hard_Update_Encoders ();
    }
}



//--- end of file ---//
