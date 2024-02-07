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
#include "i2c.h"
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

void TF_I2C_Send_Data (void);
void TF_I2C_Check_Address (void);
void TF_I2C_Check_Specific_Address (void);
void TF_I2C_Test_Gpio (void);
// void TF_Oled_Screen (void);
// void TF_Oled_Screen_Int (void);


// Module Functions ------------------------------------------------------------
void TF_Hardware_Tests (void)
{
    // TF_Led ();

    // TF_Encoder_1 ();

    // TF_Encoder_CheckSET1 ();
    // TF_Encoder_CheckCW1 ();
    // TF_Encoder_CheckCCW1 ();

    // TF_Encoder_CheckSET2 ();
    // TF_Encoder_CheckCW2 ();    
    // TF_Encoder_CheckCCW2 ();

    // TF_I2C_Send_Data ();
    // TF_I2C_Check_Address ();
    TF_I2C_Check_Specific_Address ();
    // TF_I2C_Test_Gpio ();
    
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


void TF_I2C_Send_Data (void)
{
    // dont use ints    
    I2C1_Init();
    Wait_ms(100);
    
    while (1)
    {
        Led_On();
        I2C1_SendByte (I2C_ADDRESS_SLV, 0x55);
        Led_Off();
        Wait_ms (30);
    }
    
}


void TF_I2C_Check_Address (void)
{
    // dont use ints
    Led_Off();
    
    I2C1_Init();
    Wait_ms(100);    
    
    while (1)
    {
        for (unsigned char i = 0; i < 128; i++)
        {
            // addr is right aligned
            // b0 = 0 for write b0 = 1 for read
            unsigned char addr = (i << 1) & 0xFE;    
            if (I2C1_SendAddr(addr) == 1)
            {
                Led_On();
                break;
            }
            
            Wait_ms(1);
            Led_Off();
            Wait_ms(9);
            // Wait_ms(10);
        }

        Wait_ms(999);
        Led_Off();
        
    }
}


void TF_I2C_Test_Gpio (void)
{
    unsigned long int temp;
    
    //PB6 Alternative I2C1_SCL -> To Gpio open drain
    //PB7 Alternative I2C1_SDA -> To Gpio open drain
    temp = GPIOB->CRL;
    temp &= 0x00FFFFFF;
    temp |= 0x66000000;
    GPIOB->CRL = temp;
    
    while (1)
    {
        // gpios to 1
        GPIOB->BSRR = 0x000000C0;
        Wait_ms (1);        
        GPIOB->BSRR = 0x00C00000;
        Wait_ms (1);
    }
}


void TF_I2C_Check_Specific_Address (void)
{
    // dont use ints
    Led_Off();
    
    I2C1_Init();
    Wait_ms(100);
    
    while (1)
    {
        // addr is right aligned
        // b0 = 0 for write b0 = 1 for read
        unsigned char addr = 0xA0;
        if (I2C1_SendAddr(addr) == 1)
        {
            Led_On();
        }
        Wait_ms(500);
        Led_Off();
    }
}


void TF_I2C_IS31 (void)
{
    // dont use ints
    Led_Off();
    
    I2C1_Init();
    SDB_CH1_OFF;
    Wait_ms(100);

    // use IS31 lib
    IS31FL3733 is31_ch1;
    
    while (1)
    {
        // addr is right aligned
        // b0 = 0 for write b0 = 1 for read
        unsigned char addr = 0xA0;
        if (I2C1_SendAddr(addr) == 1)
        {
            Led_On();
        }
        Wait_ms(500);
        Led_Off();
    }
}


//--- end of file ---//
