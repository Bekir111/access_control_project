
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
#define			I2C_CR1_PE				(0x1 << 0)
#define			I2C_CR1_SMBUS			(0x1 << 1)
#define			I2C_CR1_SMBTYPE			(0x1 << 3)
#define			I2C_CR1_ENARP			(0x1 << 4)
#define			I2C_CR1_ENPEC			(0x1 << 5)
#define			I2C_CR1_ENGC			(0x1 << 6)
#define			I2C_CR1_NOSTRETCH		(0x1 << 7)
#define			I2C_CR1_START			(0x1 << 8)
#define			I2C_CR1_STOP			(0x1 << 9)
#define			I2C_CR1_ACK				(0x1 << 10)
#define			I2C_CR1_POS				(0x1 << 11)
#define			I2C_CR1_PEC				(0x1 << 12)
#define			I2C_CR1_ALERT			(0x1 << 13)
#define			I2C_CR1_SWRST			(0x1 << 15)

//Macros for CR2						//For now will be 16MHz.
										//After the prototype it will be 45MHz
#define			I2C_CR2_FREQ_TEST		(0b010000 << 0)
#define			I2C_CR2_FREQ			(0b101101 << 0)
#define			I2C_CR2_ITERREN			(0x1 << 8)
#define			I2C_CR2_ITEVTEN			(0x1 << 9)
#define			I2C_CR2_ITBUFEN			(0x1 << 10)

//Macros for SR1
#define			I2C_SR1_SB				(0x1 << 0)
#define			I2C_SR1_ADDR			(0x1 << 1)
#define			I2C_SR1_BTF				(0x1 << 2)
#define			I2C_SR1_ADD10			(0x1 << 3)
#define			I2C_SR1_STOPF			(0x1 << 4)
#define			I2C_SR1_RxNE			(0x1 << 6)
#define			I2C_SR1_TxE				(0x1 << 7)
#define			I2C_SR1_BERR			(0x1 << 8)
#define			I2C_SR1_ARLO			(0x1 << 9)
#define			I2C_SR1_AF				(0x1 << 10)
#define			I2C_SR1_OVR				(0x1 << 11)
#define			I2C_SR1_PECERR			(0x1 << 12)
#define			I2C_SR1_TIMEOUT			(0x1 << 14)
#define			I2C_SR1_SMBALERT		(0x1 << 15)

//Macros for SR2
#define			I2C_SR2_MSL				(0x1 << 0)
#define			I2C_SR2_BUSY			(0x1 << 1)
#define			I2C_SR2_TRA				(0x1 << 2)
#define			I2C_SR2_GENCALL			(0x1 << 4)
#define			I2C_SR2_SMBDEFAULT		(0x1 << 5)
#define			I2C_SR2_SMBHOST			(0x1 << 6)
#define			I2C_SR2_DUALF			(0x1 << 7)

//Macros for CCR
#define 		I2C_CCR_DUTY			(0x1 << 14)
#define 		I2C_CCR_SM				(0x0 << 15)
#define 		I2C_CCR_FM				(0x1 << 15)



#endif /* F446RE_I2C_H_ */
