//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### HARD.H #################################
//---------------------------------------------

#ifndef HARD_H_
#define HARD_H_


//----------- Defines For Configuration -------------

//----- Board Configuration -------------------//
//--- Hardware ------------------//
#define HARDWARE_VERSION_1_0    // first prototype


//--- Software ------------------//
#define FIRMWARE_VERSION_1_0    // init version


//--- Serial Number / Device Id Bytes length ----------
#define USE_DEVICE_ID_4BYTES
// #define USE_DEVICE_ID_12BYTES


//-------- Oscillator and Crystal selection (Freq in startup_clocks.h) ---
#define HSI_INTERNAL_RC
// #define HSE_CRYSTAL_OSC

#ifdef HSE_CRYSTAL_OSC
// #define CRYSTAL_8MHZ
#define CRYSTAL_12MHZ
#endif

#ifdef HSE_CRYSTAL_OSC
// #define SYSCLK_FREQ_72MHz
#define SYSCLK_FREQ_8MHz
#endif

#ifdef HSI_INTERNAL_RC
#define SYSCLK_FREQ_64MHz
// #define SYSCLK_FREQ_8MHz
#endif

//-------- End Of Defines For Configuration ------




//--- Hardware & Software Messages ------------------//
#ifdef HARDWARE_VERSION_1_0
#define HARD "Hardware Version: 1.0"
#endif
#ifdef FIRMWARE_VERSION_1_0
#define SOFT "Firmware Version: 1.0"
#endif
//--- End of Hardware & Software Messages ------------------//



// Exported Types --------------------------------------------------------------
#ifdef HARDWARE_VERSION_1_0

// PA defines ----
// PA0 NC

// PA1 PA2 PA3
#define EN_SW_1    ((GPIOA->IDR & 0x0002) == 0)
#define EN_CK_1    ((GPIOA->IDR & 0x0004) == 0)
#define EN_DT_1    ((GPIOA->IDR & 0x0008) == 0)

// PA4 PA5 PA6
#define EN_SW_2    ((GPIOA->IDR & 0x0010) == 0)
#define EN_CK_2    ((GPIOA->IDR & 0x0020) == 0)
#define EN_DT_2    ((GPIOA->IDR & 0x0040) == 0)

// PA7
#define EN_SW_3    ((GPIOA->IDR & 0x0080) == 0)

// PA8
#define SDB_CH2    ((GPIOA->ODR & 0x0100) == 0)
#define SDB_CH2_OFF    (GPIOA->BSRR = 0x00000100)
#define SDB_CH2_ON    (GPIOA->BSRR = 0x01000000)

// PA9 NC

// PA10
#define SDB_CH3    ((GPIOA->ODR & 0x0400) == 0)
#define SDB_CH3_OFF    (GPIOA->BSRR = 0x00000400)
#define SDB_CH3_ON    (GPIOA->BSRR = 0x04000000)

// PA11 NC

// PA12
#define SDB_CH4    ((GPIOA->ODR & 0x1000) == 0)
#define SDB_CH4_OFF    (GPIOA->BSRR = 0x00001000)
#define SDB_CH4_ON    (GPIOA->BSRR = 0x10000000)

// PA13 PA14 PA15 NC jtag

// PB defines ----
// PB0 PB1 PB2
#define EN_SW_4    ((GPIOB->IDR & 0x0001) == 0)
#define EN_CK_4    ((GPIOB->IDR & 0x0002) == 0)
#define EN_DT_4    ((GPIOB->IDR & 0x0004) == 0)

// PB3 PB4 NC jtag

// PB5
#define EN_CK_8    ((GPIOB->IDR & 0x0020) == 0)

// PB6 PB7 Alternative I2C1_SCL I2C1_SDA

// PB8
#define EN_DT_8    ((GPIOB->IDR & 0x0100) == 0)

// PB9 NC

// PB10 PB11 Alternative I2C2_SCL I2C2_SDA

// PB12 PB13 PB4
#define EN_SW_6    ((GPIOB->IDR & 0x1000) == 0)
#define EN_CK_6    ((GPIOB->IDR & 0x2000) == 0)
#define EN_DT_6    ((GPIOB->IDR & 0x4000) == 0)

// PB15
#define EN_SW_5    ((GPIOB->IDR & 0x8000) == 0)

// PC defines ----
// PC0
#define LED    ((GPIOC->ODR & 0x0001) != 0)
#define LED_ON    (GPIOC->BSRR = 0x00000001)
#define LED_OFF    (GPIOC->BSRR = 0x00010000)

// PC1
// PC2
// PC3 NC

// PC4 PC5
#define EN_CK_3    ((GPIOC->IDR & 0x0010) == 0)
#define EN_DT_3    ((GPIOC->IDR & 0x0020) == 0)

// PC6 PC7
#define EN_CK_5    ((GPIOC->IDR & 0x0040) == 0)
#define EN_DT_5    ((GPIOC->IDR & 0x0080) == 0)

// PC8
#define SDB_CH1    ((GPIOC->ODR & 0x0100) == 0)
#define SDB_CH1_OFF    (GPIOC->BSRR = 0x00000100)
#define SDB_CH1_ON    (GPIOC->BSRR = 0x01000000)

// PC9 NC

// PC10 PC11 PC12
#define EN_SW_7    ((GPIOC->IDR & 0x0400) == 0)
#define EN_CK_7    ((GPIOC->IDR & 0x0800) == 0)
#define EN_DT_7    ((GPIOC->IDR & 0x1000) == 0)

// PC13 PC14 PC15 NC

// PD defines ----
// PD0 PD1 NC

// PD2 
#define EN_SW_8    ((GPIOD->IDR & 0x0004) == 0)

#endif //HARDWARE_VERSION_1_0


// Encoders Index Number
#define ENCODER_NUM_1    0
#define ENCODER_NUM_2    1
#define ENCODER_NUM_3    2
#define ENCODER_NUM_4    3
#define ENCODER_NUM_5    4
#define ENCODER_NUM_6    5
#define ENCODER_NUM_7    6
#define ENCODER_NUM_8    7

typedef enum {
    SW_NO = 0,
    SW_MIN,
    SW_HALF,
    SW_FULL
    
} resp_sw_t;


// Module Exported Functions ---------------------------------------------------
void Led_On (void);
void Led_Off (void);
unsigned char Led_Is_On (void);

resp_sw_t CheckSET (unsigned char encoder_num);
unsigned char CheckCCW (unsigned char encoder_num);
unsigned char CheckCW (unsigned char encoder_num);

void Hard_Timeouts (void);
void Hard_Update_Switches (void);
void Hard_Update_Encoders (void);


#endif
