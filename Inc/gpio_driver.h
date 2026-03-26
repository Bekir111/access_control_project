
#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include <stdint.h>
#include "f446re_gpio.h"

void GPIO_pin_mode(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t mode);
void GPIO_write_pin(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t state);
void GPIO_toogle_pin(GPIOx_typeDef* GPIOx, uint8_t pin);
void GPIO_pull_up(GPIOx_typeDef* GPIOx, uint8_t pin);
void GPIO_pull_up(GPIOx_typeDef* GPIOx, uint8_t pin);
void GPIO_AF_selection_low(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t af_mode);
void GPIO_output_type(GPIOx_typeDef* GPIOx, uint8_t pin, uint8_t o_type);

#endif /* GPIO_DRIVER_H_ */
