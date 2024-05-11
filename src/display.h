//---------------------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### DISPLAY.H #########################################
//---------------------------------------------------------
#ifndef _DISPLAY_H_
#define _DISPLAY_H_


// Module Exported Types Constants and Macros ----------------------------------
#define ENCODER_DISPLAY_1    0
#define ENCODER_DISPLAY_2    1
#define ENCODER_DISPLAY_3    2
#define ENCODER_DISPLAY_4    3
#define ENCODER_DISPLAY_5    4
#define ENCODER_DISPLAY_6    5
#define ENCODER_DISPLAY_7    6
#define ENCODER_DISPLAY_8    7


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------


// Module Exported Functions --------------------------------------------------
void DisplayUpdate (unsigned char encoder_dispay, unsigned char encoder_position);
void DisplayUpdateFreq (unsigned char encoder_display, unsigned char encoder_position);
void DisplayUpdatePwr (unsigned char encoder_display, unsigned char encoder_position);
void CommsUpdate (unsigned char encoder_dispay, unsigned char encoder_position);
void DisplaySinglePix (unsigned char encoder_display, unsigned char pix_index);

#endif    /* _DISPLAY_H_ */

//--- end of file ---//

