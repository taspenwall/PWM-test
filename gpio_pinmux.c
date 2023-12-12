// controls the pinmux of the gpios by writing to the registers


#include "devmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "gpio_pinmux.h"

#define PIN_MUX_BASE  0x03001000




struct pinlist cv180x_pin[] = {
	{ "GP0", 0x4c },				// IIC0_SCL
	{ "GP1", 0x50 },				// IIC0_SDA
	{ "GP2", 0x84 },				// SD1_GPIO1
	{ "GP3", 0x88 },				// SD1_GPIO0
	{ "GP4", 0x90 },				// SD1_D2
	{ "GP5", 0x94 },				// SD1_D1
	{ "GP6", 0xa0 },				// SD1_CLK
	{ "GP7", 0x9c },				// SD1_CMD
	{ "GP8", 0x98 },				// SD1_D0
	{ "GP9", 0x8c },				// SD1_D3
	{ "GP10", 0xf0 },				// PAD_MIPIRX1P
	{ "GP11", 0xf4 },				// PAD_MIPIRX0N
	{ "GP12", 0x24 },				// UART0_TX
	{ "GP13", 0x28 },				// UART0_RX
	{ "GP14", 0x1c },				// SD0_PWR_EN
	{ "GP15", 0x20 },				// SPK_EN
	{ "GP16", 0x3c },				// SPINOR_MISO
	{ "GP17", 0x40 },				// SPINOR_CS_X
	{ "GP18", 0x30 },				// SPINOR_SCK
	{ "GP19", 0x34 },				// SPINOR_MOSI
	{ "GP20", 0x38 },				// SPINOR_WP_X
	{ "GP21", 0x2c },				// SPINOR_HOLD_X
	{ "GP22", 0x68 },				// PWR_SEQ2
	{ "GP26", 0xa8 },				// ADC1
	{ "GP27", 0xac },				// USB_VBUS_DET

	{ "GP25", 0x12c },				// PAD_AUD_AOUTR
};

int get_func(int pin) {
    devmap_open(PIN_MUX_BASE+cv180x_pin[pin].offset, 4);
	uint32_t func = devmap_readl(0);
	devmap_close(4);
	return func;

}


void set_func(int pin, uint32_t set_func) {
	devmap_open(PIN_MUX_BASE+cv180x_pin[pin].offset, 4);
	devmap_writel(0, set_func);
	uint32_t func = devmap_readl(0);
	devmap_close(4);
}




