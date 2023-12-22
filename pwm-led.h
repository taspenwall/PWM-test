#ifndef PWM_LED_H
#define PWM_LED_H

#ifdef __cplusplus
extern "C" {
#endif

// Include necessary libraries
#include <stdint.h>

//registers for pwm
#define PWM_BASE 0x03060000
#define PWM_GROUP 0x2000
#define PERIOD2 0x014
#define HLPERIDO2 0x010
#define PCOUNT2 0x058
#define PWM_START 0x044
#define PWM_DONE 0x048
#define PWM_UPDATE 0x04C
#define PWM_MODE 0x040
#define PWM_OE 0x0D0
#define base PWM_BASE+PWM_GROUP

#define CLK_BASE 0x03002000
#define CLK_PWM 0x120


//settings for pwm
#define freq  100   // 125 is the calcualted for 800kHz calulated frequency,  It seem that I have to go way lower for a 1.25us period.
#define Hduty  65  //56% is the claculated duty cycle for .7us high time to write a 1
#define Lduty  10  //28%  is the claculated duty cycle for .35us high time   to write a 0
#define count 1//30 pulses
#define start 0b0100
#define pwm_mode (1<<10) // set the pmode to to pulse 1<<num+8 and set the polarity to control the high period 1<<2
#define pwmoe 0b0100

// Function prototypes
void address_led(uint8_t green, uint8_t red, uint8_t blue);
void send_bin (uint8_t num);
void pwm_init(uint32_t frequency, uint8_t duty_cycle);
void pwm_set_duty_cycle(uint8_t duty_cycle);
void pwm_start(void);
void pwm_stop(void);

#ifdef __cplusplus
}
#endif

#endif // PWM_LED_H