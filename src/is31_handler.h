//---------------------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### IS31_HANDLER.H ####################################
//---------------------------------------------------------
#ifndef _IS31_HANDLER_H_
#define _IS31_HANDLER_H_


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------


// Module Exported Functions ---------------------------------------------------
void IS31_Init (void);
void IS31_SetLed_AllOn (void);
void IS31_SetLed_AllOff (void);
void IS31_SetLedRGB (unsigned char led, unsigned char r, unsigned char g, unsigned char b);



#endif    /* _IS31_HANDLER_H_ */

//--- end of file ---//

