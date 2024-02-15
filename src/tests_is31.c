//---------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    TEST PLATFORM FOR FIRMWARE
// ##
// #### TESTS.C ###############################
//---------------------------------------------

// Includes Modules for tests --------------------------------------------------
#include "is31_handler.h"


// helper modules
#include "tests_ok.h"

#include <stdio.h>
#include <string.h>


// Types Constants and Macros --------------------------------------------------


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------



// Module Functions to Test ----------------------------------------------------
void Test_IS31_Pwm_Coordinate (void);
void Test_IS31_OnOff_Coordinate (void);


// Module Auxiliary Functions --------------------------------------------------
unsigned char I2C1_SendMultiByte (unsigned char *pdata, unsigned char addr, unsigned short size);

// Tests Module Auxiliary or General Functions ---------------------------------


// Module Functions ------------------------------------------------------------
int main (int argc, char *argv[])
{

    // Test_IS31_Pwm_Coordinate ();

    Test_IS31_OnOff_Coordinate ();
    
    return 0;
}


void Test_IS31_Pwm_Coordinate (void)
{
    int posi = 0;
    for (int sw = 0; sw < 12; sw++)
    {
        for (int cs = 0; cs < 16; cs++)
        {
            posi = IS31_Pwm_Coordinate (sw, cs);
            printf("sw: %d cs: %d posi: %d\n",sw,cs,posi);
        }
    }
}


void Test_IS31_OnOff_Coordinate (void)
{
    unsigned char reg = 0;
    unsigned char val = 0;
    
    for (int sw = 0; sw < 12; sw++)
    {
        for (int cs = 0; cs < 16; cs++)
        {
            IS31_OnOff_Coordinate (sw, cs, &reg, &val);
            printf("sw: %d cs: %d reg: %d val: %d\n",sw,cs,reg,val);
        }
    }
    
}


unsigned char I2C1_SendMultiByte (unsigned char *pdata, unsigned char addr, unsigned short size)
{
}

//--- end of file ---//


