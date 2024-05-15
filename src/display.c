//---------------------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### DISPLAY.C #########################################
//---------------------------------------------------------
#include "display.h"
#include "is31_handler.h"


// Private Types Constants and Macros ------------------------------------------


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
unsigned char freq_rgb_lateral [] = {0, 255, 0};
unsigned char freq_rgb_center [] = {255, 0, 0};
unsigned char pwr_rgb_lateral [] = {127, 0, 127};
unsigned char pwr_rgb_center [] = {255, 0, 0};


// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
void DisplayUpdate (unsigned char encoder_display, unsigned char encoder_position)
{
    unsigned short center;
    unsigned char * pc;
    unsigned char * pl;

    pc = pwr_rgb_center;
    pl = pwr_rgb_lateral;

    // encoder center
    center = 23 - encoder_position * 4;
    
    switch (encoder_display)
    {
    case ENCODER_DISPLAY_1:
        // IS31_SetLed_HighHalfOff(I2C_ADDR_P1);
        
        // center += 24;        
        // IS31_SetLedRGB (I2C_ADDR_P1, center + 0, 0, 255, 0);
        // IS31_SetLedRGB (I2C_ADDR_P1, center + 1, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P1, center + 2, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P1, center + 3, 0, 255, 0);        
        break;
        
    case ENCODER_DISPLAY_2:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P1);
        
        IS31_SetLedRGB (I2C_ADDR_P1, center - 0, *(pl + 0), *(pl + 1), *(pl + 2));
        IS31_SetLedRGB (I2C_ADDR_P1, center - 1, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P1, center - 2, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P1, center - 3, *(pl + 0), *(pl + 1), *(pl + 2));
        break;
        
    case ENCODER_DISPLAY_3:
        // IS31_SetLed_HighHalfOff(I2C_ADDR_P2);
        
        // center += 24;        
        // IS31_SetLedRGB (I2C_ADDR_P2, center + 0, 0, 255, 0);
        // IS31_SetLedRGB (I2C_ADDR_P2, center + 1, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P2, center + 2, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P2, center + 3, 0, 255, 0);
        break;
        
    case ENCODER_DISPLAY_4:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P2);
        
        IS31_SetLedRGB (I2C_ADDR_P2, center - 0, *(pl + 0), *(pl + 1), *(pl + 2));
        IS31_SetLedRGB (I2C_ADDR_P2, center - 1, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P2, center - 2, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P2, center - 3, *(pl + 0), *(pl + 1), *(pl + 2));
        break;
        
    case ENCODER_DISPLAY_5:
        // IS31_SetLed_HighHalfOff(I2C_ADDR_P3);
        
        // center += 24;        
        // IS31_SetLedRGB (I2C_ADDR_P3, center + 0, 0, 255, 0);
        // IS31_SetLedRGB (I2C_ADDR_P3, center + 1, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P3, center + 2, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P3, center + 3, 0, 255, 0);        
        
        break;
    case ENCODER_DISPLAY_6:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P3);
        
        IS31_SetLedRGB (I2C_ADDR_P3, center - 0, *(pl + 0), *(pl + 1), *(pl + 2));
        IS31_SetLedRGB (I2C_ADDR_P3, center - 1, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P3, center - 2, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P3, center - 3, *(pl + 0), *(pl + 1), *(pl + 2));
        break;
        
    case ENCODER_DISPLAY_7:
        // IS31_SetLed_HighHalfOff(I2C_ADDR_P4);
        
        // center += 24;        
        // IS31_SetLedRGB (I2C_ADDR_P4, center + 0, 0, 255, 0);
        // IS31_SetLedRGB (I2C_ADDR_P4, center + 1, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P4, center + 2, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P4, center + 3, 0, 255, 0);        
        
        break;
    case ENCODER_DISPLAY_8:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P4);
        
        IS31_SetLedRGB (I2C_ADDR_P4, center - 0, *(pl + 0), *(pl + 1), *(pl + 2));
        IS31_SetLedRGB (I2C_ADDR_P4, center - 1, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P4, center - 2, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P4, center - 3, *(pl + 0), *(pl + 1), *(pl + 2));
        break;
        
    default:
        break;
    }
}


void DisplaySinglePix (unsigned char encoder_display, unsigned char pix_index)
{
    unsigned short center;
    
    if (pix_index > 23)
        pix_index = 23;

    if (encoder_display & 0x01)
        center = 23;
    else
        center = 47;
    
    switch (encoder_display)
    {
    case ENCODER_DISPLAY_1:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P1);
        IS31_SetLedRGB (I2C_ADDR_P1, center - pix_index, 85, 85, 85);
        break;
        
    case ENCODER_DISPLAY_2:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P1);        
        IS31_SetLedRGB (I2C_ADDR_P1, center - pix_index, 85, 85, 85);
        break;
        
    case ENCODER_DISPLAY_3:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P2);
        IS31_SetLedRGB (I2C_ADDR_P2, center - pix_index, 85, 85, 85);
        break;
        
    case ENCODER_DISPLAY_4:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P2);
        IS31_SetLedRGB (I2C_ADDR_P2, center - pix_index, 85, 85, 85);
        break;
        
    case ENCODER_DISPLAY_5:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P3);
        IS31_SetLedRGB (I2C_ADDR_P3, center - pix_index, 85, 85, 85);
        break;
        
    case ENCODER_DISPLAY_6:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P3);
        IS31_SetLedRGB (I2C_ADDR_P3, center - pix_index, 85, 85, 85);
        break;
        
    case ENCODER_DISPLAY_7:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P4);
        IS31_SetLedRGB (I2C_ADDR_P4, center - pix_index, 85, 85, 85);
        break;
        
    case ENCODER_DISPLAY_8:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P4);
        IS31_SetLedRGB (I2C_ADDR_P4, center - pix_index, 85, 85, 85);
        break;
        
    default:
        break;
    }
}


void DisplayUpdateFreq (unsigned char encoder_display, unsigned char encoder_position)
{
    unsigned short center;
    unsigned char * pc;
    unsigned char * pl;

    pc = freq_rgb_center;
    pl = freq_rgb_lateral;

    // check odd
    // if (encoder_display & 0x01)    // 0 2 4 6 for freq
    //     return;
    
    // encoder center
    center = 47 - encoder_position * 2;

    // unsigned char addr = 0;

    switch (encoder_display)
    {
    case ENCODER_DISPLAY_1:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P1);
        
        // center += 24;        
        // IS31_SetLedRGB (I2C_ADDR_P1, center + 0, 0, 255, 0);
        // IS31_SetLedRGB (I2C_ADDR_P1, center + 1, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P1, center + 2, 0, 255, 0);
        IS31_SetLedRGB (I2C_ADDR_P1, center - 0, *(pl + 0), *(pl + 1), *(pl + 2));
        IS31_SetLedRGB (I2C_ADDR_P1, center - 1, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P1, center - 2, *(pl + 0), *(pl + 1), *(pl + 2));
        break;
        
    case ENCODER_DISPLAY_2:
        break;
        
    case ENCODER_DISPLAY_3:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P2);
        
        // center += 24;        
        // IS31_SetLedRGB (I2C_ADDR_P2, center + 0, 0, 255, 0);
        // IS31_SetLedRGB (I2C_ADDR_P2, center + 1, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P2, center + 2, 0, 255, 0);
        IS31_SetLedRGB (I2C_ADDR_P2, center - 0, *(pl + 0), *(pl + 1), *(pl + 2));
        IS31_SetLedRGB (I2C_ADDR_P2, center - 1, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P2, center - 2, *(pl + 0), *(pl + 1), *(pl + 2));
        break;
        
    case ENCODER_DISPLAY_4:
        break;
        
    case ENCODER_DISPLAY_5:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P3);
        
        // center += 24;        
        // IS31_SetLedRGB (I2C_ADDR_P3, center + 0, 0, 255, 0);
        // IS31_SetLedRGB (I2C_ADDR_P3, center + 1, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P3, center + 2, 0, 255, 0);
        IS31_SetLedRGB (I2C_ADDR_P3, center - 0, *(pl + 0), *(pl + 1), *(pl + 2));
        IS31_SetLedRGB (I2C_ADDR_P3, center - 1, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P3, center - 2, *(pl + 0), *(pl + 1), *(pl + 2));
        break;
    case ENCODER_DISPLAY_6:
        break;
        
    case ENCODER_DISPLAY_7:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P4);
        
        // center += 24;        
        // IS31_SetLedRGB (I2C_ADDR_P4, center + 0, 0, 255, 0);
        // IS31_SetLedRGB (I2C_ADDR_P4, center + 1, 255, 0, 0);
        // IS31_SetLedRGB (I2C_ADDR_P4, center + 2, 0, 255, 0);
        IS31_SetLedRGB (I2C_ADDR_P4, center - 0, *(pl + 0), *(pl + 1), *(pl + 2));
        IS31_SetLedRGB (I2C_ADDR_P4, center - 1, *(pc + 0), *(pc + 1), *(pc + 2));
        IS31_SetLedRGB (I2C_ADDR_P4, center - 2, *(pl + 0), *(pl + 1), *(pl + 2));
        break;
        
    case ENCODER_DISPLAY_8:
        break;
        
    default:
        break;
    }
}


// red-green
const unsigned char l_rgb_color_0 [] = {0, 255, 0};
const unsigned char c_rgb_color_0 [] = {255, 0, 0};
// red-violet
const unsigned char l_rgb_color_1 [] = {127, 0, 127};
const unsigned char c_rgb_color_1 [] = {255, 0, 0};
// red-blue
const unsigned char l_rgb_color_2 [] = {0, 0, 255};
const unsigned char c_rgb_color_2 [] = {255, 0, 0};
// red-white
const unsigned char l_rgb_color_3 [] = {85, 85, 85};
const unsigned char c_rgb_color_3 [] = {255, 0, 0};
// blue-yellow
const unsigned char l_rgb_color_4 [] = {0, 127, 127};
const unsigned char c_rgb_color_4 [] = {0, 0, 255};
// blue-white
const unsigned char l_rgb_color_5 [] = {85, 85, 85};
const unsigned char c_rgb_color_5 [] = {0, 0, 255};
// green-white
const unsigned char l_rgb_color_6 [] = {85, 85, 85};
const unsigned char c_rgb_color_6 [] = {0, 255, 0};
// green-blue
const unsigned char l_rgb_color_7 [] = {0, 0, 255};
const unsigned char c_rgb_color_7 [] = {0, 255, 0};

unsigned char last_freq_color_code = 0;
void DisplayUpdateRgbFreq (unsigned char color_code)
{
    if (last_freq_color_code == color_code)
        return;

    switch (color_code)
    {
    case 0:
        for (int i = 0; i < 3; i++)
        {
            freq_rgb_lateral[i] =  l_rgb_color_0[i];
            freq_rgb_center[i] =  c_rgb_color_0[i];
        }
        break;
    case 1:
        for (int i = 0; i < 3; i++)
        {
            freq_rgb_lateral[i] =  l_rgb_color_1[i];
            freq_rgb_center[i] =  c_rgb_color_1[i];
        }
        break;
    case 2:
        for (int i = 0; i < 3; i++)
        {
            freq_rgb_lateral[i] =  l_rgb_color_2[i];
            freq_rgb_center[i] =  c_rgb_color_2[i];
        }
        break;
    case 3:
        for (int i = 0; i < 3; i++)
        {
            freq_rgb_lateral[i] =  l_rgb_color_3[i];
            freq_rgb_center[i] =  c_rgb_color_3[i];
        }
        break;
    case 4:
        for (int i = 0; i < 3; i++)
        {
            freq_rgb_lateral[i] =  l_rgb_color_4[i];
            freq_rgb_center[i] =  c_rgb_color_4[i];
        }
        break;
    case 5:
        for (int i = 0; i < 3; i++)
        {
            freq_rgb_lateral[i] =  l_rgb_color_5[i];
            freq_rgb_center[i] =  c_rgb_color_5[i];
        }
        break;
    case 6:
        for (int i = 0; i < 3; i++)
        {
            freq_rgb_lateral[i] =  l_rgb_color_6[i];
            freq_rgb_center[i] =  c_rgb_color_6[i];
        }
        break;
    case 7:
        for (int i = 0; i < 3; i++)
        {
            freq_rgb_lateral[i] =  l_rgb_color_7[i];
            freq_rgb_center[i] =  c_rgb_color_7[i];
        }
        break;

    default:
        break;
    }
}


unsigned char last_pwr_color_code = 0;
void DisplayUpdateRgbPwr (unsigned char color_code)
{
    if (last_pwr_color_code == color_code)
        return;
        
    switch (color_code)
    {
    case 0:
        for (int i = 0; i < 3; i++)
        {
            pwr_rgb_lateral[i] =  l_rgb_color_0[i];
            pwr_rgb_center[i] =  c_rgb_color_0[i];
        }
        break;
    case 1:
        for (int i = 0; i < 3; i++)
        {
            pwr_rgb_lateral[i] =  l_rgb_color_1[i];
            pwr_rgb_center[i] =  c_rgb_color_1[i];
        }
        break;
    case 2:
        for (int i = 0; i < 3; i++)
        {
            pwr_rgb_lateral[i] =  l_rgb_color_2[i];
            pwr_rgb_center[i] =  c_rgb_color_2[i];
        }
        break;
    case 3:
        for (int i = 0; i < 3; i++)
        {
            pwr_rgb_lateral[i] =  l_rgb_color_3[i];
            pwr_rgb_center[i] =  c_rgb_color_3[i];
        }
        break;
    case 4:
        for (int i = 0; i < 3; i++)
        {
            pwr_rgb_lateral[i] =  l_rgb_color_4[i];
            pwr_rgb_center[i] =  c_rgb_color_4[i];
        }
        break;
    case 5:
        for (int i = 0; i < 3; i++)
        {
            pwr_rgb_lateral[i] =  l_rgb_color_5[i];
            pwr_rgb_center[i] =  c_rgb_color_5[i];
        }
        break;
    case 6:
        for (int i = 0; i < 3; i++)
        {
            pwr_rgb_lateral[i] =  l_rgb_color_6[i];
            pwr_rgb_center[i] =  c_rgb_color_6[i];
        }
        break;
    case 7:
        for (int i = 0; i < 3; i++)
        {
            pwr_rgb_lateral[i] =  l_rgb_color_7[i];
            pwr_rgb_center[i] =  c_rgb_color_7[i];
        }
        break;

    default:
        break;
    }
}
//--- end of file ---//

