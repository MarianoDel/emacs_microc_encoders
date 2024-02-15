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

#include "is31_handler.h"
#include "is31fl3733.h"

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

void TF_I2C_IS31_P1_Low_Level (void);
void TF_I2C_IS31_P2_Low_Level (void);
void TF_I2C_IS31_P3_Low_Level (void);
void TF_I2C_IS31_P4_Low_Level (void);

void TF_I2C_IS31_P1_High_Level (void);
void TF_I2C_IS31_P4_High_Level (void);
void TF_I2C_IS31_P1_P4_High_Level (void);

void TF_I2C_IS31_One_by_One_High_Level (void);
void TF_I2C_IS31_Low_Level_Int (void);
void TF_I2C_IS31 (void);

void TF_IS31_Encoder (void);

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
    // TF_I2C_Check_Specific_Address ();
    // TF_I2C_Test_Gpio ();

    // TF_I2C_IS31_P1_Low_Level ();
    // TF_I2C_IS31_P2_Low_Level ();
    // TF_I2C_IS31_P3_Low_Level ();
    // TF_I2C_IS31_P4_Low_Level ();
    
    // TF_I2C_IS31_P1_High_Level ();
    // TF_I2C_IS31_P1_P4_High_Level ();

    TF_I2C_IS31_P4_High_Level ();
    // TF_I2C_IS31_One_by_One_High_Level ();
    // TF_I2C_IS31_Low_Level_Int ();
    // TF_I2C_IS31 ();

    

    // TF_IS31_Encoder ();
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


void TF_I2C_IS31_P1_Low_Level (void)
{
    // dont use ints
    Led_Off();

    SDB_CH1_OFF;
    SDB_CH2_ON;
    SDB_CH3_ON;
    SDB_CH4_ON;
    I2C1_Init();
    Wait_ms(100);

    unsigned char cmdbuf [194] = { 0 };
    int error = 0;
    unsigned char addr = 0xA0;

    I2C1_Reset ();


    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            Led_On();
            Wait_ms(250);
            Led_Off();
            Wait_ms(250);
        }

        error = 0;

        //
        // leave from shutdown
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 3
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x03;    // point to page 3
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf reg to normal
            cmdbuf[0] = 0x00;    // conf reg
            cmdbuf[1] = 0x01;    // shutdown to normal
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        //
        // set global current reg
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 3
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x03;    // point to page 3
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set gcc reg to 127
            cmdbuf[0] = 0x01;    // gcc reg
            cmdbuf[1] = 127;    // 127
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }
        
        // 
        // set 50% pwm
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 1
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x01;    // point to page 1
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set each pwm reg to 50%
            cmdbuf[0] = 0x00;    // conf reg
            for (int i = 0; i < 192; i++)
                cmdbuf[i+1] = 127;    // pwm value
    
            error = I2C1_SendMultiByte (cmdbuf, addr, 193);
        }

        // 
        // set all leds on
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {        
            // set conf cmd reg to page 0
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x00;    // point to page 0
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set each led to on
            cmdbuf[0] = 0x00;    // conf reg
            // for (int i = 0; i < 24; i++)
            //     cmdbuf[i+1] = 0xff;    // all ones

            // all blue
            cmdbuf[1] = 0x00;    // sw1 low
            cmdbuf[2] = 0x00;    // sw1 high
            cmdbuf[3] = 0x00;    // sw2 low
            cmdbuf[4] = 0x00;    // sw2 high
            cmdbuf[5] = 0xff;    // sw3 low
            cmdbuf[6] = 0xff;    // sw3 high
            cmdbuf[7] = 0x00;    // sw4 low
            cmdbuf[8] = 0x00;    // sw4 high
            cmdbuf[9] = 0x00;    // sw5 low
            cmdbuf[10] = 0x00;    // sw5 high
            cmdbuf[11] = 0xff;    // sw6 low
            cmdbuf[12] = 0xff;    // sw6 high
            cmdbuf[13] = 0x00;    // sw7 low
            cmdbuf[14] = 0x00;    // sw7 high
            cmdbuf[15] = 0x00;    // sw8 low
            cmdbuf[16] = 0x00;    // sw8 high
            cmdbuf[17] = 0xff;    // sw9 low
            cmdbuf[18] = 0xff;    // sw9 high
            cmdbuf[19] = 0x00;    // sw10 low
            cmdbuf[20] = 0x00;    // sw10 high
            cmdbuf[21] = 0x00;    // sw11 low
            cmdbuf[22] = 0x00;    // sw11 high
            cmdbuf[23] = 0xff;    // sw12 low
            cmdbuf[24] = 0xff;    // sw12 high
    
            error = I2C1_SendMultiByte (cmdbuf, addr, 25);
        }

        if (error)
        {
            for (int i = 0; i < 16; i++)
            {
                Led_On();
                Wait_ms(125);
                Led_Off();
                Wait_ms(125);
            }
            I2C1_Reset ();            
        }
        else
            Led_On();
    
        Wait_ms(20000);
    }
}


void TF_I2C_IS31_P1_High_Level (void)
{
    // dont use ints
    Led_Off();

    SDB_CH1_OFF;
    SDB_CH2_ON;
    SDB_CH3_ON;
    SDB_CH4_ON;
    I2C1_Init();
    Wait_ms(100);

    I2C1_Reset ();


    for (int i = 0; i < 3; i++)
    {
        Led_On();
        Wait_ms(250);
        Led_Off();
        Wait_ms(250);
    }

    unsigned char addr = 0xA0;
    
    IS31_Init(I2C_ADDR_P1);

    // set all red sw1 & cs1 - cs12
    for (int i = 0; i < 12; i++)
        IS31_SetPix (addr, 0, i, 127);
        
    // set all red sw4 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (addr, 3, i, 127);

    // set all red sw7 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (addr, 6, i, 127);
    
    // set all red sw10 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (addr, 9, i, 127);
    
    while (1);

}


void TF_I2C_IS31_P1_P4_High_Level (void)
{
    // dont use ints
    Led_Off();

    SDB_CH1_OFF;
    SDB_CH2_OFF;
    SDB_CH3_OFF;
    SDB_CH4_OFF;

    I2C1_Init();
    Wait_ms(100);
    I2C1_Reset ();


    for (int i = 0; i < 3; i++)
    {
        Led_On();
        Wait_ms(250);
        Led_Off();
        Wait_ms(250);
    }

    
    IS31_Init(I2C_ADDR_P1);
    IS31_Init(I2C_ADDR_P2);
    IS31_Init(I2C_ADDR_P3);
    IS31_Init(I2C_ADDR_P4);

    // set all red sw1 & cs1 - cs12
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P1, 0, i, 127);
        
    // set all red sw4 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P1, 3, i, 127);

    // set all red sw7 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P1, 6, i, 127);
    
    // set all red sw10 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P1, 9, i, 127);

    Wait_ms (1000);
    
    // set all red sw1 & cs1 - cs12
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P2, 0, i, 127);
        
    // set all red sw4 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P2, 3, i, 127);

    // set all red sw7 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P2, 6, i, 127);
    
    // set all red sw10 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P2, 9, i, 127);

    Wait_ms (1000);
    
    // set all red sw1 & cs1 - cs12
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P3, 0, i, 127);
        
    // set all red sw4 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P3, 3, i, 127);

    // set all red sw7 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P3, 6, i, 127);
    
    // set all red sw10 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P3, 9, i, 127);

    Wait_ms (1000);    

    // set all red sw1 & cs1 - cs12
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P4, 0, i, 127);
        
    // set all red sw4 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P4, 3, i, 127);

    // set all red sw7 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P4, 6, i, 127);
    
    // set all red sw10 & cs1 - cs12    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P4, 9, i, 127);
    
    while (1);

}


void TF_I2C_IS31_P4_High_Level (void)
{
    // dont use ints
    Led_Off();

    SDB_CH1_ON;
    SDB_CH2_ON;
    SDB_CH3_ON;
    SDB_CH4_OFF;
    I2C1_Init();
    Wait_ms(100);

    I2C1_Reset ();


    for (int i = 0; i < 3; i++)
    {
        Led_On();
        Wait_ms(250);
        Led_Off();
        Wait_ms(250);
    }

    IS31_Init(I2C_ADDR_P4);

    // set all red sw1 & cs1 - cs12
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P4, 0, i, 127);

    Wait_ms (1000);

    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P4, 1, i, 127);

    Wait_ms (1000);
    
    for (int i = 0; i < 12; i++)
        IS31_SetPix (I2C_ADDR_P4, 2, i, 127);
    
    // set all red sw4 & cs1 - cs12    
    // for (int i = 0; i < 12; i++)
    //     IS31_SetPix (addr, 3, i, 127);

    // set all red sw7 & cs1 - cs12    
    // for (int i = 0; i < 12; i++)
    //     IS31_SetPix (addr, 6, i, 127);
    
    // set all red sw10 & cs1 - cs12    
    // for (int i = 0; i < 12; i++)
    //     IS31_SetPix (addr, 9, i, 127);
    
    while (1);

}


void TF_I2C_IS31_One_by_One_High_Level (void)
{
    // dont use ints
    Led_Off();

    SDB_CH1_OFF;
    SDB_CH2_ON;
    SDB_CH3_ON;
    SDB_CH4_ON;
    I2C1_Init();
    Wait_ms(100);

    I2C1_Reset ();


    for (int i = 0; i < 3; i++)
    {
        Led_On();
        Wait_ms(250);
        Led_Off();
        Wait_ms(250);
    }

    IS31_Init(I2C_ADDR_P1);
    
    while (1)
    {
        // set all red increasing
        // for (int i = 0; i < 48; i++)
        // {
        //     IS31_SetLedRGB (i, 255, 0, 0);
        //     Wait_ms(300);
        // }
        // IS31_SetLed_AllOff();
        // Wait_ms(1000);

        // // set all red one by one        
        // for (int i = 0; i < 48; i++)
        // {
        //     IS31_SetLed_AllOff();            
        //     IS31_SetLedRGB (i, 255, 0, 0);
        //     Wait_ms(300);
        // }        
        // IS31_SetLed_AllOff();
        // Wait_ms(1000);

        
        // set all green increasing
        // for (int i = 0; i < 48; i++)
        // {
        //     IS31_SetLedRGB (i, 0, 255, 0);
        //     Wait_ms(300);
        // }
        // IS31_SetLed_AllOff();
        // Wait_ms(1000);

        // // set all green one by one        
        // for (int i = 0; i < 48; i++)
        // {
        //     IS31_SetLed_AllOff();            
        //     IS31_SetLedRGB (i, 0, 255, 0);
        //     Wait_ms(300);
        // }        
        // IS31_SetLed_AllOff();
        // Wait_ms(1000);

        // // set all blue increasing
        // for (int i = 0; i < 48; i++)
        // {
        //     IS31_SetLedRGB (i, 0, 0, 255);
        //     Wait_ms(300);
        // }
        // IS31_SetLed_AllOff();
        // Wait_ms(1000);

        // // set all blue one by one        
        // for (int i = 0; i < 48; i++)
        // {
        //     IS31_SetLed_AllOff();            
        //     IS31_SetLedRGB (i, 0, 0, 255);
        //     Wait_ms(300);
        // }        
        // IS31_SetLed_AllOff();
        // Wait_ms(1000);

        // set all yellow increasing
        for (int i = 0; i < 48; i++)
        {
            IS31_SetLedRGB (I2C_ADDR_P1, i, 127, 127, 0);
            // Wait_ms(300);
        }
        Wait_ms(1000);        
        IS31_SetLed_AllOff(I2C_ADDR_P1);
        Wait_ms(1000);

        // // set all yellow one by one        
        // for (int i = 0; i < 48; i++)
        // {
        //     IS31_SetLed_AllOff();            
        //     IS31_SetLedRGB (i, 127, 127, 0);
        //     Wait_ms(300);
        // }        
        // IS31_SetLed_AllOff();
        // Wait_ms(1000);
        
    }
}


void TF_IS31_Encoder (void)
{
    // dont use ints
    Led_Off();

    SDB_CH1_OFF;
    SDB_CH2_ON;
    SDB_CH3_ON;
    SDB_CH4_ON;
    I2C1_Init();
    Wait_ms(100);

    I2C1_Reset ();


    for (int i = 0; i < 3; i++)
    {
        Led_On();
        Wait_ms(250);
        Led_Off();
        Wait_ms(250);
    }

    IS31_Init(I2C_ADDR_P1);

    int encoder1_pos = 0;
    int encoder2_pos = 0;
    int center = 0;
        
    while (1)
    {
        // encoder first position        
        if (CheckCW (ENCODER_NUM_2))
        {
            if (encoder1_pos)    // >0
                encoder1_pos--;

            // encoder center
            center = encoder1_pos * 4;

            IS31_SetLed_AllOff(I2C_ADDR_P1);
            IS31_SetLedRGB (I2C_ADDR_P1, center + 0, 127, 0, 127);
            IS31_SetLedRGB (I2C_ADDR_P1, center + 1, 255, 0, 0);
            IS31_SetLedRGB (I2C_ADDR_P1, center + 2, 255, 0, 0);
            IS31_SetLedRGB (I2C_ADDR_P1, center + 3, 127, 0, 127);            
            
        }

        if (CheckCCW (ENCODER_NUM_2))
        {
            if (encoder1_pos < 5)
                encoder1_pos++;

            center = encoder1_pos * 4;

            IS31_SetLed_AllOff(I2C_ADDR_P1);
            IS31_SetLedRGB (I2C_ADDR_P1, center + 0, 127, 0, 127);
            IS31_SetLedRGB (I2C_ADDR_P1, center + 1, 255, 0, 0);
            IS31_SetLedRGB (I2C_ADDR_P1, center + 2, 255, 0, 0);
            IS31_SetLedRGB (I2C_ADDR_P1, center + 3, 127, 0, 127);            
            
        }
        
        Hard_Update_Encoders ();
                
    }
}


void TF_I2C_IS31_P2_Low_Level (void)
{
    // dont use ints
    Led_Off();

    SDB_CH1_ON;
    SDB_CH2_OFF;
    SDB_CH3_ON;
    SDB_CH4_ON;
    I2C1_Init();
    Wait_ms(100);

    unsigned char cmdbuf [194] = { 0 };
    int error = 0;
    unsigned char addr = 0xA6;

    I2C1_Reset ();

    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            Led_On();
            Wait_ms(250);
            Led_Off();
            Wait_ms(250);
        }

        error = 0;

        //
        // leave from shutdown
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 3
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x03;    // point to page 3
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf reg to normal
            cmdbuf[0] = 0x00;    // conf reg
            cmdbuf[1] = 0x01;    // shutdown to normal
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        //
        // set global current reg
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 3
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x03;    // point to page 3
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set gcc reg to 127
            cmdbuf[0] = 0x01;    // gcc reg
            cmdbuf[1] = 127;    // 127
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        // 
        // set 50% pwm
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 1
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x01;    // point to page 1
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set each pwm reg to 50%
            cmdbuf[0] = 0x00;    // conf reg
            for (int i = 0; i < 192; i++)
                cmdbuf[i+1] = 127;    // pwm value
    
            error = I2C1_SendMultiByte (cmdbuf, addr, 193);
        }

        // 
        // set all leds on
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {        
            // set conf cmd reg to page 0
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x00;    // point to page 0
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set each led to on
            cmdbuf[0] = 0x00;    // conf reg
            for (int i = 0; i < 24; i++)
                cmdbuf[i+1] = 0xff;    // all ones

            // cmdbuf[1] = 0x00;    // sw1 low
            // cmdbuf[2] = 0x00;    // sw1 high
            // cmdbuf[3] = 0x00;    // sw2 low
            // cmdbuf[4] = 0x00;    // sw2 high
            // cmdbuf[5] = 0xff;    // sw3 low
            // cmdbuf[6] = 0xff;    // sw3 high
            // cmdbuf[7] = 0x00;    // sw4 low
            // cmdbuf[8] = 0x00;    // sw4 high
            // cmdbuf[9] = 0x00;    // sw5 low
            // cmdbuf[10] = 0x00;    // sw5 high
            // cmdbuf[11] = 0xff;    // sw6 low
            // cmdbuf[12] = 0xff;    // sw6 high
            // cmdbuf[13] = 0x00;    // sw7 low
            // cmdbuf[14] = 0x00;    // sw7 high
            // cmdbuf[15] = 0x00;    // sw8 low
            // cmdbuf[16] = 0x00;    // sw8 high
            // cmdbuf[17] = 0xff;    // sw9 low
            // cmdbuf[18] = 0xff;    // sw9 high
            // cmdbuf[19] = 0x00;    // sw10 low
            // cmdbuf[20] = 0x00;    // sw10 high
            // cmdbuf[21] = 0x00;    // sw11 low
            // cmdbuf[22] = 0x00;    // sw11 high
            // cmdbuf[23] = 0xff;    // sw12 low
            // cmdbuf[24] = 0xff;    // sw12 high
    
            error = I2C1_SendMultiByte (cmdbuf, addr, 25);
        }

        if (error)
        {
            for (int i = 0; i < 16; i++)
            {
                Led_On();
                Wait_ms(125);
                Led_Off();
                Wait_ms(125);
            }
            I2C1_Reset ();
        }
        else
            Led_On();
    
        Wait_ms(20000);
    }
}


void TF_I2C_IS31_P3_Low_Level (void)
{
    // dont use ints
    Led_Off();

    SDB_CH1_ON;
    SDB_CH2_ON;
    SDB_CH3_OFF;
    SDB_CH4_ON;
    I2C1_Init();
    Wait_ms(100);

    unsigned char cmdbuf [194] = { 0 };
    int error = 0;
    unsigned char addr = 0xB8;

    I2C1_Reset ();

    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            Led_On();
            Wait_ms(250);
            Led_Off();
            Wait_ms(250);
        }

        error = 0;

        //
        // leave from shutdown
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 3
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x03;    // point to page 3
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf reg to normal
            cmdbuf[0] = 0x00;    // conf reg
            cmdbuf[1] = 0x01;    // shutdown to normal
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        //
        // set global current reg
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 3
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x03;    // point to page 3
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set gcc reg to 127
            cmdbuf[0] = 0x01;    // gcc reg
            cmdbuf[1] = 127;    // 127
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        // 
        // set 50% pwm
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 1
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x01;    // point to page 1
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set each pwm reg to 50%
            cmdbuf[0] = 0x00;    // conf reg
            for (int i = 0; i < 192; i++)
                cmdbuf[i+1] = 127;    // pwm value
    
            error = I2C1_SendMultiByte (cmdbuf, addr, 193);
        }

        // 
        // set all leds on
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {        
            // set conf cmd reg to page 0
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x00;    // point to page 0
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set each led to on
            cmdbuf[0] = 0x00;    // conf reg
            for (int i = 0; i < 24; i++)
                cmdbuf[i+1] = 0xff;    // all ones

            // cmdbuf[1] = 0x00;    // sw1 low
            // cmdbuf[2] = 0x00;    // sw1 high
            // cmdbuf[3] = 0x00;    // sw2 low
            // cmdbuf[4] = 0x00;    // sw2 high
            // cmdbuf[5] = 0xff;    // sw3 low
            // cmdbuf[6] = 0xff;    // sw3 high
            // cmdbuf[7] = 0x00;    // sw4 low
            // cmdbuf[8] = 0x00;    // sw4 high
            // cmdbuf[9] = 0x00;    // sw5 low
            // cmdbuf[10] = 0x00;    // sw5 high
            // cmdbuf[11] = 0xff;    // sw6 low
            // cmdbuf[12] = 0xff;    // sw6 high
            // cmdbuf[13] = 0x00;    // sw7 low
            // cmdbuf[14] = 0x00;    // sw7 high
            // cmdbuf[15] = 0x00;    // sw8 low
            // cmdbuf[16] = 0x00;    // sw8 high
            // cmdbuf[17] = 0xff;    // sw9 low
            // cmdbuf[18] = 0xff;    // sw9 high
            // cmdbuf[19] = 0x00;    // sw10 low
            // cmdbuf[20] = 0x00;    // sw10 high
            // cmdbuf[21] = 0x00;    // sw11 low
            // cmdbuf[22] = 0x00;    // sw11 high
            // cmdbuf[23] = 0xff;    // sw12 low
            // cmdbuf[24] = 0xff;    // sw12 high
    
            error = I2C1_SendMultiByte (cmdbuf, addr, 25);
        }

        if (error)
        {
            for (int i = 0; i < 16; i++)
            {
                Led_On();
                Wait_ms(125);
                Led_Off();
                Wait_ms(125);
            }
            I2C1_Reset ();
        }
        else
            Led_On();
    
        Wait_ms(20000);
    }
}


void TF_I2C_IS31_P4_Low_Level (void)
{
    // dont use ints
    Led_Off();

    SDB_CH1_ON;
    SDB_CH2_ON;
    SDB_CH3_ON;
    SDB_CH4_OFF;
    I2C1_Init();
    Wait_ms(100);

    unsigned char cmdbuf [194] = { 0 };
    int error = 0;
    unsigned char addr = 0xBE;

    I2C1_Reset ();

    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            Led_On();
            Wait_ms(250);
            Led_Off();
            Wait_ms(250);
        }

        error = 0;

        //
        // leave from shutdown
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 3
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x03;    // point to page 3
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf reg to normal
            cmdbuf[0] = 0x00;    // conf reg
            cmdbuf[1] = 0x01;    // shutdown to normal
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        //
        // set global current reg
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 3
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x03;    // point to page 3
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set gcc reg to 127
            cmdbuf[0] = 0x01;    // gcc reg
            cmdbuf[1] = 127;    // 127
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        // 
        // set 50% pwm
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set conf cmd reg to page 1
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x01;    // point to page 1
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set each pwm reg to 50%
            cmdbuf[0] = 0x00;    // conf reg
            for (int i = 0; i < 192; i++)
                cmdbuf[i+1] = 127;    // pwm value
    
            error = I2C1_SendMultiByte (cmdbuf, addr, 193);
        }

        // 
        // set all leds on
        //
        if (!error)
        {
            // unlock cmd reg
            cmdbuf[0] = 0xFE;    // register write lock
            cmdbuf[1] = 0xC5;    // write enable once
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {        
            // set conf cmd reg to page 0
            cmdbuf[0] = 0xFD;    // conf cmd reg
            cmdbuf[1] = 0x00;    // point to page 0
            error = I2C1_SendMultiByte (cmdbuf, addr, 2);
        }

        if (!error)
        {
            // set each led to on
            cmdbuf[0] = 0x00;    // conf reg
            for (int i = 0; i < 24; i++)
                cmdbuf[i+1] = 0xff;    // all ones

            // cmdbuf[1] = 0x00;    // sw1 low
            // cmdbuf[2] = 0x00;    // sw1 high
            // cmdbuf[3] = 0x00;    // sw2 low
            // cmdbuf[4] = 0x00;    // sw2 high
            // cmdbuf[5] = 0xff;    // sw3 low
            // cmdbuf[6] = 0xff;    // sw3 high
            // cmdbuf[7] = 0x00;    // sw4 low
            // cmdbuf[8] = 0x00;    // sw4 high
            // cmdbuf[9] = 0x00;    // sw5 low
            // cmdbuf[10] = 0x00;    // sw5 high
            // cmdbuf[11] = 0xff;    // sw6 low
            // cmdbuf[12] = 0xff;    // sw6 high
            // cmdbuf[13] = 0x00;    // sw7 low
            // cmdbuf[14] = 0x00;    // sw7 high
            // cmdbuf[15] = 0x00;    // sw8 low
            // cmdbuf[16] = 0x00;    // sw8 high
            // cmdbuf[17] = 0xff;    // sw9 low
            // cmdbuf[18] = 0xff;    // sw9 high
            // cmdbuf[19] = 0x00;    // sw10 low
            // cmdbuf[20] = 0x00;    // sw10 high
            // cmdbuf[21] = 0x00;    // sw11 low
            // cmdbuf[22] = 0x00;    // sw11 high
            // cmdbuf[23] = 0xff;    // sw12 low
            // cmdbuf[24] = 0xff;    // sw12 high
    
            error = I2C1_SendMultiByte (cmdbuf, addr, 25);
        }

        if (error)
        {
            for (int i = 0; i < 16; i++)
            {
                Led_On();
                Wait_ms(125);
                Led_Off();
                Wait_ms(125);
            }
            I2C1_Reset ();
        }
        else
            Led_On();
    
        Wait_ms(20000);
    }
}


void TF_I2C_IS31_Low_Level_Int (void)
{
    // use with ints
    Led_Off();

    SDB_CH1_OFF;
    SDB_CH2_ON;
    SDB_CH3_ON;
    SDB_CH4_ON;
    I2C1_Init();
    Wait_ms(100);

    unsigned char cmdbuf [194] = { 0 };

    I2C1_Reset ();


    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            Led_On();
            Wait_ms(250);
            Led_Off();
            Wait_ms(250);
        }


        //
        // leave from shutdown
        //
        // unlock cmd reg
        cmdbuf[0] = 0xFE;    // register write lock
        cmdbuf[1] = 0xC5;    // write enable once
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 2);

        // set conf cmd reg to page 3
        cmdbuf[0] = 0xFD;    // conf cmd reg
        cmdbuf[1] = 0x03;    // point to page 3
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 2);

        // set conf reg to normal
        cmdbuf[0] = 0x00;    // conf reg
        cmdbuf[1] = 0x01;    // shutdown to normal
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 2);

        //
        // set global current reg
        //
        // unlock cmd reg
        cmdbuf[0] = 0xFE;    // register write lock
        cmdbuf[1] = 0xC5;    // write enable once
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 2);

        // set conf cmd reg to page 3
        cmdbuf[0] = 0xFD;    // conf cmd reg
        cmdbuf[1] = 0x03;    // point to page 3
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 2);

        // set gcc reg to 127
        cmdbuf[0] = 0x01;    // gcc reg
        cmdbuf[1] = 127;    // 127
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 2);

        // 
        // set 50% pwm
        //
        // unlock cmd reg
        cmdbuf[0] = 0xFE;    // register write lock
        cmdbuf[1] = 0xC5;    // write enable once
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 2);        

        // set conf cmd reg to page 1
        cmdbuf[0] = 0xFD;    // conf cmd reg
        cmdbuf[1] = 0x01;    // point to page 1
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 2);

        // set each pwm reg to 50%
        cmdbuf[0] = 0x00;    // conf reg
        for (int i = 0; i < 192; i++)
            cmdbuf[i+1] = 127;    // pwm value
    
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 193);

        // 
        // set all leds on
        //
        // unlock cmd reg
        cmdbuf[0] = 0xFE;    // register write lock
        cmdbuf[1] = 0xC5;    // write enable once
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 2);

        // set conf cmd reg to page 0
        cmdbuf[0] = 0xFD;    // conf cmd reg
        cmdbuf[1] = 0x00;    // point to page 0
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 2);

        // set each led to on
        cmdbuf[0] = 0x00;    // conf reg
        for (int i = 0; i < 24; i++)
            cmdbuf[i+1] = 0xff;    // all ones

        // cmdbuf[1] = 0x00;    // sw1 low
        // cmdbuf[2] = 0x00;    // sw1 high
        // cmdbuf[3] = 0x00;    // sw2 low
        // cmdbuf[4] = 0x00;    // sw2 high
        // cmdbuf[5] = 0xff;    // sw3 low
        // cmdbuf[6] = 0xff;    // sw3 high
        // cmdbuf[7] = 0x00;    // sw4 low
        // cmdbuf[8] = 0x00;    // sw4 high
        // cmdbuf[9] = 0x00;    // sw5 low
        // cmdbuf[10] = 0x00;    // sw5 high
        // cmdbuf[11] = 0xff;    // sw6 low
        // cmdbuf[12] = 0xff;    // sw6 high
        // cmdbuf[13] = 0x00;    // sw7 low
        // cmdbuf[14] = 0x00;    // sw7 high
        // cmdbuf[15] = 0x00;    // sw8 low
        // cmdbuf[16] = 0x00;    // sw8 high
        // cmdbuf[17] = 0xff;    // sw9 low
        // cmdbuf[18] = 0xff;    // sw9 high
        // cmdbuf[19] = 0x00;    // sw10 low
        // cmdbuf[20] = 0x00;    // sw10 high
        // cmdbuf[21] = 0x00;    // sw11 low
        // cmdbuf[22] = 0x00;    // sw11 high
        // cmdbuf[23] = 0xff;    // sw12 low
        // cmdbuf[24] = 0xff;    // sw12 high
    
        I2C1_SendMultiByte_Int (0xA0, cmdbuf, 25);

        Led_On();
    
        Wait_ms(20000);
    }
}


void TF_I2C_IS31_P3_High_Level (void)
{
    // dont use ints
    Led_Off();

    SDB_CH1_OFF;
    SDB_CH2_ON;
    SDB_CH3_ON;
    SDB_CH4_ON;
    I2C1_Init();
    Wait_ms(100);

    I2C1_Reset ();


    for (int i = 0; i < 3; i++)
    {
        Led_On();
        Wait_ms(250);
        Led_Off();
        Wait_ms(250);
    }

    IS31_Init(I2C_ADDR_P3);
    
    while (1)
    {

        // set all red
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 255, 0, 0);
    
        Wait_ms(10000);

        // set all green
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 0, 255, 0);
    
        Wait_ms(10000);
        
        // set all blue
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 0, 0, 255);
    
        Wait_ms(10000);

        IS31_SetLed_AllOff(I2C_ADDR_P3);
        
        // dimmer red
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 16, 0, 0);
        Wait_ms(1000);
        
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 128, 0, 0);
        Wait_ms(1000);
        
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 255, 0, 0);
        Wait_ms(1000);
        
        IS31_SetLed_AllOff(I2C_ADDR_P3);

        // dimmer green
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 0, 16, 0);
        Wait_ms(1000);
        
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 0, 128, 0);
        Wait_ms(1000);
        
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 0, 255, 0);
        Wait_ms(1000);
        
        IS31_SetLed_AllOff(I2C_ADDR_P3);

        // dimmer blue
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 0, 0, 16);
        Wait_ms(1000);
        
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 0, 0, 128);
        Wait_ms(1000);
        
        for (int i = 0; i < 48; i++)
            IS31_SetLedRGB (I2C_ADDR_P3, i, 0, 0, 255);
        Wait_ms(1000);        

        IS31_SetLed_AllOff(I2C_ADDR_P3);
                
    }
}

// void TF_I2C_IS31 (void)
// {
//     // dont use ints
//     Led_Off();
    
//     I2C1_Init();
//     SDB_CH1_OFF;
//     Wait_ms(100);

//     // use IS31 lib
//     IS31FL3733 is31_ch1;

//     is31_ch1.address = IS31FL3733_I2C_ADDR(ADDR_GND, ADDR_GND);
//     is31_ch1.i2c_write_reg = &i2c_write_reg;
//     is31_ch1.i2c_read_reg = &i2c_read_reg;

//     // Initialize device.
//     IS31FL3733_Init (&is31_ch1);
    
//     // Set Global Current Control.
//     IS31FL3733_SetGCC (&is31_ch1, 127);

//     // ## PWM mode ## 
//     // Draw something in PWM mode, e.g. set LED brightness at position {1;2} to maximum level:
//     // Set PWM value for LED at {1;2}.
//     // IS31FL3733_SetLEDPWM (&is31_ch1, 1, 2, 255);
//     IS31FL3733_SetLEDPWM (&is31_ch1, IS31FL3733_SW, IS31FL3733_CS, 255);    
//     // Turn on LED at position {1;2}.
//     // IS31FL3733_SetLEDState (&is31_ch1, 1, 2, IS31FL3733_LED_STATE_ON);
//     IS31FL3733_SetLEDState (&is31_ch1, IS31FL3733_SW, IS31FL3733_CS, IS31FL3733_LED_STATE_ON);    
    

    
//     while (1);
// }


//--- end of file ---//
