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
unsigned char i2c_write_reg (unsigned char i2c_addr,
                             unsigned char reg_addr,
                             unsigned char *buffer,
                             unsigned char count);


unsigned char i2c_read_reg (unsigned char i2c_addr,
                             unsigned char reg_addr,
                             unsigned char *buffer,
                             unsigned char count);

#endif    /* _IS31_HANDLER_H_ */

//--- end of file ---//

