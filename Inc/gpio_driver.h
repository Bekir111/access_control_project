
#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include <stdint.h>
#include "f446re_gpio.h"

void GPIO_pin_mode(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t mode);
void GPIO_write_pin(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t state);
void GPIO_toogle_pin(GPIOx_typeDef* GPIOx, uint8_t pin);
void GPIO_pull_up(GPIOx_typeDef* GPIOx, uint8_t pin);
void GPIO_pull_up(GPIOx_typeDef* GPIOx, uint8_t pin);


#endif /* GPIO_DRIVER_H_ */
