//---------------------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### COMMS.C ###########################################
//---------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "comms.h"
#include "i2c.h"
// #include "answers_defs.h"
// #include "hard.h"



#include <string.h>
#include <stdio.h>
// #include <stdlib.h>


// Module Private Types Constants and Macros -----------------------------------
// char s_ans_ok [] = {"ok\n"};
// char s_ans_nok [] = {"nok\n"};
// #define SIZEOF_LOCAL_BUFF    128
#define COMMS_TT_RELOAD    3000


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
// char local_buff [SIZEOF_LOCAL_BUFF];
volatile unsigned short comms_timeout = 0;
    

// Module Private Functions ----------------------------------------------------
// static void Comms_Messages (char * msg_str);


// Module Functions ------------------------------------------------------------
void Comms_Timeouts (void)
{
    if (comms_timeout)
        comms_timeout--;
}


unsigned char Comms_Rpi_Answering (void)
{
    if (comms_timeout)
        return 1;
    
    return 0;
}


void Comms_Send_Encoder_Data (unsigned char encoder_number, unsigned char position)
{
    char buff [100];

    sprintf(buff, "enc %d pos %d", encoder_number, position);
    I2C2_SendMultiByte((unsigned char *) buff, 0x44, strlen(buff));        
}


void Comms_Send_Encoder_Data_Deltas (unsigned char encoder_number, enc_delta_e delta)
{
    char buff [100];

    if (delta == ENCOD_UPDATE_UP)
    {
        sprintf(buff, "enc + %d", encoder_number);
        I2C2_SendMultiByte((unsigned char *) buff, 0x44, strlen(buff));
    }
    else if (delta == ENCOD_UPDATE_DWN)
    {
        sprintf(buff, "enc - %d", encoder_number);
        I2C2_SendMultiByte((unsigned char *) buff, 0x44, strlen(buff));
    }
}


//---- End of File ----//
