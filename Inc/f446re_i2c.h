
#ifndef F446RE_I2C_H_
#define F446RE_I2C_H_

#define 		APB1_BASE_ADDR			0x40000000UL
#define 		I2C1_ADDR				(APB1_BASE_ADDR + 0x5400UL)
#define 		I2C2_ADDR				(APB1_BASE_ADDR + 0x5800UL)
#define 		I2C3_ADDR				(APB1_BASE_ADDR + 0x5C00UL)

typedef struct{

	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
	volatile uint32_t FLTR;

}I2C_typeDef;

#define			I2C1 					((I2C_typeDef *) I2C1_ADDR)


//Macros for CR1
#define			PE						(0x1 << 0)
#define			SMBUS					(0x1 << 1)
#define			SMBTYPE					(0x1 << 3)
#define			ENARP					(0x1 << 4)
#define			ENPEC					(0x1 << 5)
#define			ENGC					(0x1 << 6)
#define			NOSTRETCH				(0x1 << 7)
#define			START					(0x1 << 8)
#define			STOP					(0x1 << 9)
#define			ACK						(0x1 << 10)
#define			POS						(0x1 << 11)
#define			PEC						(0x1 << 12)
#define			ALERT					(0x1 << 13)
#define			SWRST					(0x1 << 15)

//Macros for CR2

#endif /* F446RE_I2C_H_ */
