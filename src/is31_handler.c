//---------------------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### IS31_HANDLER.C ####################################
//---------------------------------------------------------
#include "is31_handler.h"
#include "i2c.h"

#include <string.h>
// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
unsigned char cmdbuf [256];

// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
unsigned char i2c_write_reg (unsigned char i2c_addr,
                             unsigned char reg_addr,
                             unsigned char *buffer,
                             unsigned char count)
{
    if (count > 254)
        return 1;    // HAL_ERROR
        
    memcpy ((cmdbuf+1), buffer, count);
    *cmdbuf = reg_addr;
    
    I2C1_SendMultiByte (cmdbuf, i2c_addr, count+1);

    return 0;    // HAL_OK
}


unsigned char i2c_read_reg (unsigned char i2c_addr,
                             unsigned char reg_addr,
                             unsigned char *buffer,
                             unsigned char count)
{
    return 0;    // HAL_OK
}

//--- end of file ---//
