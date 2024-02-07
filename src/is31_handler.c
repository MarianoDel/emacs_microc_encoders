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


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
unsigned char i2c_write_reg (unsigned char i2c_addr,
                             unsigned char reg_addr,
                             unsigned char *buffer,
                             unsigned char count)
{
    

void I2C1_SendMultiByte (unsigned char *pdata, unsigned char addr, unsigned short size);

    //return HAL_I2C_Mem_Write (&hi2c1, i2c_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, buffer, count, 1);
}
    
unsigned chart i2c_read_reg (unsigned char i2c_addr, unsigned char reg_addr, unsigned char *buffer, unsigned char count)
{
    return HAL_I2C_Mem_Read (&hi2c1, i2c_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, buffer, count, 1);
}

//--- end of file ---//

