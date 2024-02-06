//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### HARD.C #################################
//---------------------------------------------
#include "hard.h"
#include "stm32f10x.h"

#include <stdio.h>


// Module Private Types Constants and Macros -----------------------------------
#define SWITCHES_TIMER_RELOAD    5
#define SWITCHES_THRESHOLD_FULL	1000		//5 segundos
#define SWITCHES_THRESHOLD_HALF	100		//1 segundo
#define SWITCHES_THRESHOLD_MIN	5		//25 ms

#define ENCODER_COUNTER_ROOF    10
#define ENCODER_COUNTER_THRESHOLD    3


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
volatile unsigned char switches_timer = 0;


// Module Private Functions ----------------------------------------------------
void Update_All_Encoders_Filters (void);
void Update_Encoder_Filter (unsigned char encoder_num);
void Update_Encoder (unsigned char encoder_num);
void Update_Switch (unsigned char encoder_num);

unsigned char Hard_Get_Encoders_Clk (unsigned char encoder_num);
unsigned char Hard_Get_Encoders_Dt (unsigned char encoder_num);
unsigned char Hard_Get_Encoders_Sw (unsigned char encoder_num);

// Module Functions ------------------------------------------------------------
void Led_On (void)
{
    LED_ON;
}


void Led_Off (void)
{
    LED_OFF;
}


unsigned char Led_Is_On (void)
{
    return LED;
}


void Hard_Timeouts (void)
{
    if (switches_timer)
        switches_timer--;
    
    // UpdateSwitches();    // calls it on main

    Update_All_Encoders_Filters ();

}


// Encoder Routines ------------------------------------------------------------
unsigned short sw_set_cntr[8] = { 0 };
resp_sw_t CheckSET (unsigned char encoder_num)
{
    resp_sw_t sw = SW_NO;
    unsigned short * psw;

    psw = &sw_set_cntr[encoder_num];
    
    if (*psw > SWITCHES_THRESHOLD_FULL)
        sw = SW_FULL;
    else if (*psw > SWITCHES_THRESHOLD_HALF)
        sw = SW_HALF;
    else if (*psw > SWITCHES_THRESHOLD_MIN)
        sw = SW_MIN;

    return sw;    
}


void Hard_Update_Switches (void)
{
    if (!switches_timer)
    {
        for (int i = 0; i < 8; i++)
            Update_Switch (i);

        switches_timer = SWITCHES_TIMER_RELOAD;
    }       
}


void Update_Switch (unsigned char encoder_num)
{
    unsigned char sw = 0;
    unsigned short * psw;

    if (encoder_num > ENCODER_NUM_8)
        encoder_num = ENCODER_NUM_8;
    
    sw = Hard_Get_Encoders_Sw (encoder_num);
    psw = &sw_set_cntr[encoder_num];

    if (sw)
        *psw += 1;
    else if (*psw > 50)
        *psw -= 50;
    else if (*psw > 10)
        *psw -= 5;
    else if (*psw)
        *psw -= 1;
}       


volatile unsigned char enc_clk_cntr[8] = { 0 };
volatile unsigned char enc_dt_cntr[8] = { 0 };
void Update_Encoder_Filter (unsigned char encoder_num)
{
    unsigned char clk = 0;
    unsigned char dt = 0;
    volatile unsigned char * pclk;
    volatile unsigned char * pdt;

    if (encoder_num > ENCODER_NUM_8)
        encoder_num = ENCODER_NUM_8;    

    clk = Hard_Get_Encoders_Clk (encoder_num);
    dt = Hard_Get_Encoders_Dt (encoder_num);
    pclk = &enc_clk_cntr[encoder_num];
    pdt = &enc_dt_cntr[encoder_num];
    
    if (clk)
    {
        if (*pclk < ENCODER_COUNTER_ROOF)
            *pclk += 1;
    }
    else
    {
        if (*pclk)
            *pclk -= 1;        
    }

    if (dt)
    {
        if (*pdt < ENCODER_COUNTER_ROOF)
            *pdt += 1;
    }
    else
    {
        if (*pdt)
            *pdt -= 1;        
    }
}


void Update_All_Encoders_Filters (void)
{
    for (int i = 0; i < 8; i++)
        Update_Encoder_Filter (i);
}


unsigned char encoder_last_clk [8] = { 0 };
unsigned char encoder_ccw [8] = { 0 };
unsigned char encoder_cw [8] = { 0 };
void Hard_Update_Encoders (void)
{
    for (int i = 0; i < 8; i++)
        Update_Encoder (i);
}


void Update_Encoder (unsigned char encoder_num)
{
    unsigned char current_clk = 0;
    volatile unsigned char * pclk;
    volatile unsigned char * pdt;
    unsigned char * plast_clk;    
    unsigned char * pcw;
    unsigned char * pccw;

    if (encoder_num > ENCODER_NUM_8)
        encoder_num = ENCODER_NUM_8;    

    pclk = &enc_clk_cntr[encoder_num];
    pdt = &enc_dt_cntr[encoder_num];
    plast_clk = &encoder_last_clk[encoder_num];
    pcw = &encoder_cw[encoder_num];
    pccw = &encoder_ccw[encoder_num];
    
    //check if we have rising edge on clk
    if (*pclk > ENCODER_COUNTER_THRESHOLD)
        current_clk = 1;
    
    if ((*plast_clk == 0) && (current_clk == 1))    //rising edge
    {
        //have a new clock edge
        if (*pdt > ENCODER_COUNTER_THRESHOLD)
        {
#ifdef USE_ENCODER_DIRECT
            //CW
            if (*pcw < 1)
                *pcw += 1;
#else
            if (*pccw < 1)
                *pccw += 1;
#endif
        }
        else
        {
#ifdef USE_ENCODER_DIRECT
            //CCW
            if (*pccw < 1)
                *pccw += 1;            
#else
            //CW
            if (*pcw < 1)
                *pcw += 1;            
#endif
        }
    }

    if (*plast_clk != current_clk)
        *plast_clk = current_clk;
}


unsigned char CheckCCW (unsigned char encoder_num)
{
    unsigned char a = 0;
    unsigned char * pccw;

    if (encoder_num > ENCODER_NUM_8)
        encoder_num = ENCODER_NUM_8;

    pccw = &encoder_ccw[encoder_num];
    
    if (*pccw)
    {
        *pccw -= 1;
        a = 1;
    }
    
    return a;
}


unsigned char CheckCW (unsigned char encoder_num)
{
    unsigned char a = 0;
    unsigned char * pcw;

    if (encoder_num > ENCODER_NUM_8)
        encoder_num = ENCODER_NUM_8;
    
    pcw = &encoder_cw[encoder_num];
    
    if (*pcw)
    {
        *pcw -= 1;
        a = 1;
    }
    
    return a;
}


unsigned char Hard_Get_Encoders_Clk (unsigned char encoder_num)
{
    if (encoder_num == ENCODER_NUM_1)
        return EN_CK_1;
    else if (encoder_num == ENCODER_NUM_2)
        return EN_CK_2;
    else if (encoder_num == ENCODER_NUM_3)
        return EN_CK_3;
    else if (encoder_num == ENCODER_NUM_4)
        return EN_CK_4;
    else if (encoder_num == ENCODER_NUM_5)
        return EN_CK_5;
    else if (encoder_num == ENCODER_NUM_6)
        return EN_CK_6;
    else if (encoder_num == ENCODER_NUM_7)
        return EN_CK_7;
    else if (encoder_num == ENCODER_NUM_8)
        return EN_CK_8;

    // default to ENCODER_NUM_1
    return EN_CK_1;
}


unsigned char Hard_Get_Encoders_Dt (unsigned char encoder_num)
{
    if (encoder_num == ENCODER_NUM_1)
        return EN_DT_1;
    else if (encoder_num == ENCODER_NUM_2)
        return EN_DT_2;
    else if (encoder_num == ENCODER_NUM_3)
        return EN_DT_3;
    else if (encoder_num == ENCODER_NUM_4)
        return EN_DT_4;
    else if (encoder_num == ENCODER_NUM_5)
        return EN_DT_5;
    else if (encoder_num == ENCODER_NUM_6)
        return EN_DT_6;
    else if (encoder_num == ENCODER_NUM_7)
        return EN_DT_7;
    else if (encoder_num == ENCODER_NUM_8)
        return EN_DT_8;

    // default to ENCODER_NUM_1
    return EN_DT_1;
}


unsigned char Hard_Get_Encoders_Sw (unsigned char encoder_num)
{
    if (encoder_num == ENCODER_NUM_1)
        return EN_SW_1;
    else if (encoder_num == ENCODER_NUM_2)
        return EN_SW_2;
    else if (encoder_num == ENCODER_NUM_3)
        return EN_SW_3;
    else if (encoder_num == ENCODER_NUM_4)
        return EN_SW_4;
    else if (encoder_num == ENCODER_NUM_5)
        return EN_SW_5;
    else if (encoder_num == ENCODER_NUM_6)
        return EN_SW_6;
    else if (encoder_num == ENCODER_NUM_7)
        return EN_SW_7;
    else if (encoder_num == ENCODER_NUM_8)
        return EN_SW_8;

    // default to ENCODER_NUM_1
    return EN_SW_1;
}

// End of Encoder Routines -----------------------------------------------------

//--- end of file ---//
