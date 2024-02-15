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


// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
void DisplayUpdate (unsigned char encoder_display, unsigned char encoder_position)
{
    unsigned short center;

    // encoder center
    center = encoder_position * 4;
    
    switch (encoder_display)
    {
    case ENCODER_DISPLAY_1:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P1);
        
        center += 24;        
        IS31_SetLedRGB (I2C_ADDR_P1, center + 0, 0, 255, 0);
        IS31_SetLedRGB (I2C_ADDR_P1, center + 1, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P1, center + 2, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P1, center + 3, 0, 255, 0);        
        break;
        
    case ENCODER_DISPLAY_2:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P1);
        
        IS31_SetLedRGB (I2C_ADDR_P1, center + 0, 127, 0, 127);
        IS31_SetLedRGB (I2C_ADDR_P1, center + 1, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P1, center + 2, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P1, center + 3, 127, 0, 127);        
        break;
        
    case ENCODER_DISPLAY_3:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P2);
        
        center += 24;        
        IS31_SetLedRGB (I2C_ADDR_P2, center + 0, 0, 255, 0);
        IS31_SetLedRGB (I2C_ADDR_P2, center + 1, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P2, center + 2, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P2, center + 3, 0, 255, 0);
        break;
        
    case ENCODER_DISPLAY_4:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P2);
        
        IS31_SetLedRGB (I2C_ADDR_P2, center + 0, 127, 0, 127);
        IS31_SetLedRGB (I2C_ADDR_P2, center + 1, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P2, center + 2, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P2, center + 3, 127, 0, 127);        
        break;
        
    case ENCODER_DISPLAY_5:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P3);
        
        center += 24;        
        IS31_SetLedRGB (I2C_ADDR_P3, center + 0, 0, 255, 0);
        IS31_SetLedRGB (I2C_ADDR_P3, center + 1, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P3, center + 2, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P3, center + 3, 0, 255, 0);        
        
        break;
    case ENCODER_DISPLAY_6:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P3);
        
        IS31_SetLedRGB (I2C_ADDR_P3, center + 0, 127, 0, 127);
        IS31_SetLedRGB (I2C_ADDR_P3, center + 1, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P3, center + 2, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P3, center + 3, 127, 0, 127);                
        break;
        
    case ENCODER_DISPLAY_7:
        IS31_SetLed_HighHalfOff(I2C_ADDR_P4);
        
        center += 24;        
        IS31_SetLedRGB (I2C_ADDR_P4, center + 0, 0, 255, 0);
        IS31_SetLedRGB (I2C_ADDR_P4, center + 1, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P4, center + 2, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P4, center + 3, 0, 255, 0);        
        
        break;
    case ENCODER_DISPLAY_8:
        IS31_SetLed_LowHalfOff(I2C_ADDR_P4);
        
        IS31_SetLedRGB (I2C_ADDR_P4, center + 0, 127, 0, 127);
        IS31_SetLedRGB (I2C_ADDR_P4, center + 1, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P4, center + 2, 255, 0, 0);
        IS31_SetLedRGB (I2C_ADDR_P4, center + 3, 127, 0, 127);
        break;
        
    default:
        break;
    }
}


//--- end of file ---//

