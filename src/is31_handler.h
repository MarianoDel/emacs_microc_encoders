//---------------------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### IS31_HANDLER.H ####################################
//---------------------------------------------------------
#ifndef _IS31_HANDLER_H_
#define _IS31_HANDLER_H_


// Module Exported Types Constants and Macros ----------------------------------
#define I2C_ADDR_P1    0xA0
#define I2C_ADDR_P2    0xA6
#define I2C_ADDR_P3    0xB8
#define I2C_ADDR_P4    0xBE


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------


// Module Exported Functions ---------------------------------------------------
void IS31_Init (unsigned char addr);
void IS31_SetLed_AllOn (unsigned char addr);
void IS31_SetLed_AllOff (unsigned char addr);
void IS31_SetLed_LowHalfOff (unsigned char addr);
void IS31_SetLed_HighHalfOff (unsigned char addr);
void IS31_SetLedRGB (unsigned char addr,
                     unsigned char led,
                     unsigned char r,
                     unsigned char g,
                     unsigned char b);



#endif    /* _IS31_HANDLER_H_ */

//--- end of file ---//

