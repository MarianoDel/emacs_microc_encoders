//---------------------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### IS31_HANDLER.C ####################################
//---------------------------------------------------------
#include "is31_handler.h"
#include "i2c.h"

#include <string.h>

// Private Types Constants and Macros ------------------------------------------
#define CS01    0x0000
#define CS02    0x1000
#define CS03    0x2000
#define CS04    0x3000
#define CS05    0x4000
#define CS06    0x5000
#define CS07    0x6000
#define CS08    0x7000
#define CS09    0x8000
#define CS10    0x9000
#define CS11    0xA000
#define CS12    0xB000

#define SWR01    0x0000
#define SWR02    0x0100
#define SWR03    0x0200
#define SWR04    0x0300
#define SWR05    0x0400
#define SWR06    0x0500
#define SWR07    0x0600
#define SWR08    0x0700
#define SWR09    0x0800
#define SWR10    0x0900
#define SWR11    0x0A00
#define SWR12    0x0B00
#define SWR13    0x0C00
#define SWR14    0x0D00
#define SWR15    0x0E00
#define SWR16    0x0F00

#define SWG01    0x0000
#define SWG02    0x0010
#define SWG03    0x0020
#define SWG04    0x0030
#define SWG05    0x0040
#define SWG06    0x0050
#define SWG07    0x0060
#define SWG08    0x0070
#define SWG09    0x0080
#define SWG10    0x0090
#define SWG11    0x00A0
#define SWG12    0x00B0
#define SWG13    0x00C0
#define SWG14    0x00D0
#define SWG15    0x00E0
#define SWG16    0x00F0

#define SWB01    0x0000
#define SWB02    0x0001
#define SWB03    0x0002
#define SWB04    0x0003
#define SWB05    0x0004
#define SWB06    0x0005
#define SWB07    0x0006
#define SWB08    0x0007
#define SWB09    0x0008
#define SWB10    0x0009
#define SWB11    0x000A
#define SWB12    0x000B
#define SWB13    0x000C
#define SWB14    0x000D
#define SWB15    0x000E
#define SWB16    0x000F


#define LED01_CS_SW    (CS01 | SWR01 | SWG02 | SWB03)
#define LED02_CS_SW    (CS02 | SWR01 | SWG02 | SWB03)
#define LED03_CS_SW    (CS03 | SWR01 | SWG02 | SWB03)
#define LED04_CS_SW    (CS04 | SWR01 | SWG02 | SWB03)
#define LED05_CS_SW    (CS05 | SWR01 | SWG02 | SWB03)
#define LED06_CS_SW    (CS06 | SWR01 | SWG02 | SWB03)
#define LED07_CS_SW    (CS07 | SWR01 | SWG02 | SWB03)
#define LED08_CS_SW    (CS08 | SWR01 | SWG02 | SWB03)
#define LED09_CS_SW    (CS09 | SWR01 | SWG02 | SWB03)
#define LED10_CS_SW    (CS10 | SWR01 | SWG02 | SWB03)
#define LED11_CS_SW    (CS11 | SWR01 | SWG02 | SWB03)
#define LED12_CS_SW    (CS12 | SWR01 | SWG02 | SWB03)
#define LED13_CS_SW    (CS12 | SWR04 | SWG05 | SWB06)
#define LED14_CS_SW    (CS11 | SWR04 | SWG05 | SWB06)
#define LED15_CS_SW    (CS10 | SWR04 | SWG05 | SWB06)
#define LED16_CS_SW    (CS09 | SWR04 | SWG05 | SWB06)
#define LED17_CS_SW    (CS08 | SWR04 | SWG05 | SWB06)
#define LED18_CS_SW    (CS07 | SWR04 | SWG05 | SWB06)
#define LED19_CS_SW    (CS06 | SWR04 | SWG05 | SWB06)
#define LED20_CS_SW    (CS05 | SWR04 | SWG05 | SWB06)
#define LED21_CS_SW    (CS04 | SWR04 | SWG05 | SWB06)
#define LED22_CS_SW    (CS03 | SWR04 | SWG05 | SWB06) 
#define LED23_CS_SW    (CS02 | SWR04 | SWG05 | SWB06)
#define LED24_CS_SW    (CS01 | SWR04 | SWG05 | SWB06)

#define LED25_CS_SW    (CS01 | SWR07 | SWG08 | SWB09)
#define LED26_CS_SW    (CS02 | SWR07 | SWG08 | SWB09)
#define LED27_CS_SW    (CS03 | SWR07 | SWG08 | SWB09)
#define LED28_CS_SW    (CS04 | SWR07 | SWG08 | SWB09)
#define LED29_CS_SW    (CS05 | SWR07 | SWG08 | SWB09)
#define LED30_CS_SW    (CS06 | SWR07 | SWG08 | SWB09)
#define LED31_CS_SW    (CS07 | SWR07 | SWG08 | SWB09)
#define LED32_CS_SW    (CS08 | SWR07 | SWG08 | SWB09)
#define LED33_CS_SW    (CS09 | SWR07 | SWG08 | SWB09)
#define LED34_CS_SW    (CS10 | SWR07 | SWG08 | SWB09)
#define LED35_CS_SW    (CS11 | SWR07 | SWG08 | SWB09)
#define LED36_CS_SW    (CS12 | SWR07 | SWG08 | SWB09)
#define LED37_CS_SW    (CS12 | SWR10 | SWG11 | SWB12)
#define LED38_CS_SW    (CS11 | SWR10 | SWG11 | SWB12)
#define LED39_CS_SW    (CS10 | SWR10 | SWG11 | SWB12)
#define LED40_CS_SW    (CS09 | SWR10 | SWG11 | SWB12)
#define LED41_CS_SW    (CS08 | SWR10 | SWG11 | SWB12)
#define LED42_CS_SW    (CS07 | SWR10 | SWG11 | SWB12)
#define LED43_CS_SW    (CS06 | SWR10 | SWG11 | SWB12)
#define LED44_CS_SW    (CS05 | SWR10 | SWG11 | SWB12)
#define LED45_CS_SW    (CS04 | SWR10 | SWG11 | SWB12)
#define LED46_CS_SW    (CS03 | SWR10 | SWG11 | SWB12)
#define LED47_CS_SW    (CS02 | SWR10 | SWG11 | SWB12)
#define LED48_CS_SW    (CS01 | SWR10 | SWG11 | SWB12)

// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
unsigned char cmdbuf [194];
// unsigned char on_off_led [24 * 4] = { 0 };
unsigned char on_off_led [24] = { 0 };
unsigned short led_coordinate [48] = {LED01_CS_SW, LED02_CS_SW, LED03_CS_SW, LED04_CS_SW,
                                      LED05_CS_SW, LED06_CS_SW, LED07_CS_SW, LED08_CS_SW,
                                      LED09_CS_SW, LED10_CS_SW, LED11_CS_SW, LED12_CS_SW,
                                      LED13_CS_SW, LED14_CS_SW, LED15_CS_SW, LED16_CS_SW,
                                      LED17_CS_SW, LED18_CS_SW, LED19_CS_SW, LED20_CS_SW,
                                      LED21_CS_SW, LED22_CS_SW, LED23_CS_SW, LED24_CS_SW,
                                      LED25_CS_SW, LED26_CS_SW, LED27_CS_SW, LED28_CS_SW,
                                      LED29_CS_SW, LED30_CS_SW, LED31_CS_SW, LED32_CS_SW,
                                      LED33_CS_SW, LED34_CS_SW, LED35_CS_SW, LED36_CS_SW,
                                      LED37_CS_SW, LED38_CS_SW, LED39_CS_SW, LED40_CS_SW,
                                      LED41_CS_SW, LED42_CS_SW, LED43_CS_SW, LED44_CS_SW,
                                      LED45_CS_SW, LED46_CS_SW, LED47_CS_SW, LED48_CS_SW};


// Module Private Functions ----------------------------------------------------
unsigned char IS31_Pwm_Coordinate (unsigned char sw, unsigned char cs);
void IS31_SetPix (unsigned char addr, unsigned char sw, unsigned char cs, unsigned char pwm);
void IS31_OnOff_Coordinate (unsigned char sw,
                            unsigned char cs,
                            unsigned char * reg_pos,
                            unsigned char * reg_val);

void IS31_SetLed_All (unsigned char addr, unsigned char on_off);
void IS31_SetOnOff_Register (unsigned char addr, unsigned char on_off_reg_pos, unsigned char on_off_reg_val);
void IS31_SetGcc_Register (unsigned char adddr, unsigned char gcc);

void IS31_CmdReg_Unlock (unsigned char addr);
void IS31_CmdReg_Page (unsigned char addr, unsigned char page);
void IS31_SetReg_Value (unsigned char addr, unsigned char reg, unsigned char value);

// unsigned char addr = 0xA0;

// Module Functions ------------------------------------------------------------
void IS31_Init (unsigned char addr)
{
    // leave from shutdown
    IS31_CmdReg_Unlock (addr);
    IS31_CmdReg_Page (addr, 3);
    IS31_SetReg_Value (addr, 0, 1);

    // set global current reg    
    IS31_SetGcc_Register (addr, 127);

    // set all leds off
    IS31_SetLed_AllOff(addr);

}


void IS31_SetLedRGB (unsigned char addr, unsigned char led, unsigned char r, unsigned char g, unsigned char b)
{
    // one cs three sw; nibbles -> cs,r_sw,g_sw,b_sw
    unsigned char cs = 0;
    unsigned char r_sw = 0;
    unsigned char g_sw = 0;
    unsigned char b_sw = 0;

    unsigned short led_nibbles = led_coordinate[led];
    unsigned short calc;

    calc = (led_nibbles >> 12) & 0x000F;
    cs = (unsigned char) calc;

    calc = (led_nibbles >> 8) & 0x000F;
    r_sw = (unsigned char) calc;

    calc = (led_nibbles >> 4) & 0x000F;
    g_sw = (unsigned char) calc;

    calc = led_nibbles & 0x000F;
    b_sw = (unsigned char) calc;

    // set R pix
    IS31_SetPix (addr, r_sw, cs, r);
    // set G pix
    IS31_SetPix (addr, g_sw, cs, g);
    // set B pix
    IS31_SetPix (addr, b_sw, cs, b);
}


void IS31_SetLed_All (unsigned char addr, unsigned char on_off)
{
    // unsigned char on_off_offset = 0;
    
    IS31_CmdReg_Unlock (addr);
    IS31_CmdReg_Page (addr, 0);

    // if (addr == I2C_ADDR_P1)
    //     on_off_offset = 0;    // OFFSET_P1
    // else if (addr == I2C_ADDR_P2)
    //     on_off_offset = 24;    //OFFSET_P2
    // else if (addr == I2C_ADDR_P3)
    //     on_off_offset = 48;    //OFFSET_P3
    // else
    //     on_off_offset = 72;    //OFFSET_P4
    
    // set each led to on
    cmdbuf[0] = 0x00;    // conf reg

    unsigned char all_value = 0;
    if (on_off)
        all_value = 0xff;    // all ones
    
    for (int i = 0; i < 24; i++)
    {
        cmdbuf[i+1] = all_value;
        // on_off_led[i+on_off_offset] = all_value;
        on_off_led[i] = all_value;        
    }

    I2C1_SendMultiByte (cmdbuf, addr, 25);    

}


void IS31_SetLed_LowHalfOff (unsigned char addr)
{
    // unsigned char on_off_offset = 0;
    
    IS31_CmdReg_Unlock (addr);
    IS31_CmdReg_Page (addr, 0);
    
    // if (addr == I2C_ADDR_P1)
    //     on_off_offset = 0;    // OFFSET_P1
    // else if (addr == I2C_ADDR_P2)
    //     on_off_offset = 24;    //OFFSET_P2
    // else if (addr == I2C_ADDR_P3)
    //     on_off_offset = 48;    //OFFSET_P3
    // else
    //     on_off_offset = 72;    //OFFSET_P4

    // set each led to on
    cmdbuf[0] = 0x00;    // conf reg
    
    for (int i = 0; i < 12; i++)
    {
        cmdbuf[i+1] = 0;
        // on_off_led[i+on_off_offset] = 0;
        on_off_led[i] = 0;        
    }

    I2C1_SendMultiByte (cmdbuf, addr, 13);

}


void IS31_SetLed_HighHalfOff (unsigned char addr)
{
    // unsigned char on_off_offset = 0;
    
    IS31_CmdReg_Unlock (addr);
    IS31_CmdReg_Page (addr, 0);
    
    // if (addr == I2C_ADDR_P1)
    //     on_off_offset = 0;    // OFFSET_P1
    // else if (addr == I2C_ADDR_P2)
    //     on_off_offset = 24;    //OFFSET_P2
    // else if (addr == I2C_ADDR_P3)
    //     on_off_offset = 48;    //OFFSET_P3
    // else
    //     on_off_offset = 72;    //OFFSET_P4

    // set each led to on
    cmdbuf[0] = 0x00;    // conf reg
    
    for (int i = 0; i < 12; i++)
        // cmdbuf[i+1] = on_off_led[i+on_off_offset];
        cmdbuf[i+1] = on_off_led[i];

    for (int i = 12; i < 24; i++)
    {
        cmdbuf[i+1] = 0;
        // on_off_led[i+on_off_offset] = 0;
        on_off_led[i] = 0;        
    }

    I2C1_SendMultiByte (cmdbuf, addr, 25);

}


void IS31_SetLed_AllOn (unsigned char addr)
{
    IS31_SetLed_All (addr, 1);
}


void IS31_SetLed_AllOff (unsigned char addr)
{
    IS31_SetLed_All (addr, 0);
}


void IS31_SetGcc_Register (unsigned char addr, unsigned char gcc)
{
    IS31_CmdReg_Unlock(addr);
    IS31_CmdReg_Page(addr, 3);
    IS31_SetReg_Value (addr, 1, gcc);    
}


void IS31_SetOnOff_Register (unsigned char addr, unsigned char on_off_reg_pos, unsigned char on_off_reg_val)
{
    IS31_CmdReg_Unlock (addr);
    IS31_CmdReg_Page (addr, 0);
    IS31_SetReg_Value (addr, on_off_reg_pos, on_off_reg_val);
}


void IS31_CmdReg_Unlock (unsigned char addr)
{
    // unlock cmd reg
    cmdbuf[0] = 0xFE;    // register write lock
    cmdbuf[1] = 0xC5;    // write enable once
    I2C1_SendMultiByte (cmdbuf, addr, 2);    
}


void IS31_CmdReg_Page (unsigned char addr, unsigned char page)
{
    // set conf cmd reg to page 1
    cmdbuf[0] = 0xFD;    // conf cmd reg
    cmdbuf[1] = page;    // point to page
    I2C1_SendMultiByte (cmdbuf, addr, 2);    
}


void IS31_SetReg_Value (unsigned char addr, unsigned char reg, unsigned char value)
{
    cmdbuf[0] = reg;
    cmdbuf[1] = value;
    I2C1_SendMultiByte (cmdbuf, addr, 2);    
}


void IS31_SetPwm_Register (unsigned char addr, unsigned char pwm_pos, unsigned char pwm_value)
{
    IS31_CmdReg_Unlock (addr);
    IS31_CmdReg_Page (addr, 1);
    IS31_SetReg_Value (addr, pwm_pos, pwm_value);
}


void IS31_SetPix (unsigned char addr, unsigned char sw, unsigned char cs, unsigned char pwm)
{
    // unsigned char on_off_offset = 0;
    unsigned char on_off_reg_pos = 0;
    unsigned char on_off_reg_val = 0;    
    unsigned char coor_pwm = 0;

    // if (addr == I2C_ADDR_P1)
    //     on_off_offset = 0;    // OFFSET_P1
    // else if (addr == I2C_ADDR_P2)
    //     on_off_offset = 24;    //OFFSET_P2
    // else if (addr == I2C_ADDR_P3)
    //     on_off_offset = 48;    //OFFSET_P3
    // else
    //     on_off_offset = 72;    //OFFSET_P4
    
    IS31_OnOff_Coordinate (sw, cs, &on_off_reg_pos, &on_off_reg_val);
    coor_pwm = IS31_Pwm_Coordinate (sw, cs);
    
    if (!pwm)
    {
        // set the pix off
        // on_off_led[on_off_reg_pos + on_off_offset] &= (unsigned char) (~on_off_reg_val);
        // on_off_reg_val = on_off_led[on_off_reg_pos + on_off_offset];
        on_off_led[on_off_reg_pos] &= (unsigned char) (~on_off_reg_val);        
        on_off_reg_val = on_off_led[on_off_reg_pos];        

        IS31_SetOnOff_Register (addr, on_off_reg_pos, on_off_reg_val);
        return;
    }

    // set pix pwm
    IS31_SetPwm_Register (addr, coor_pwm, pwm);

    // set pix to on
    // on_off_led[on_off_reg_pos + on_off_offset] |= on_off_reg_val;
    // on_off_reg_val = on_off_led[on_off_reg_pos + on_off_offset];        
    on_off_led[on_off_reg_pos] |= on_off_reg_val;
    on_off_reg_val = on_off_led[on_off_reg_pos];

    IS31_SetOnOff_Register (addr, on_off_reg_pos, on_off_reg_val);    
}


// sw1 = 0 sw16 = 15; cs1 = 0 cs16 = 15; 
void IS31_OnOff_Coordinate (unsigned char sw,
                            unsigned char cs,
                            unsigned char * reg_pos,
                            unsigned char * reg_val)
{
    *reg_pos = sw * 2;

    if (cs > 7)
    {
        *reg_pos += 1;
        cs -= 8;
    }

    *reg_val = 1 << cs;
}


// sw1 = 0 sw16 = 15; cs1 = 0 cs16 = 15;
unsigned char IS31_Pwm_Coordinate (unsigned char sw, unsigned char cs)
{
    unsigned short reg_pos = 0;
    
    reg_pos = (sw + 1) * (cs + 1) - 1;

    return (unsigned char) reg_pos;
}


//--- end of file ---//

