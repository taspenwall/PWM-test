// controls the pinmux of the gpios by writing to the registers

#ifndef GPIO_PINMUX_H
#define GPIO_PINMUX_H


#include "devmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define PIN_MUX_BASE  0x03001000





struct pinlist {
	char name[32];
	uint32_t offset;
};

extern struct pinlist cv180x_pin[];

int get_func(int pin);
void set_func(int pin, uint32_t set_func);

#endif
