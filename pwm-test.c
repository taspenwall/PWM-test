


#include <stdio.h>
#include <unistd.h>
#include "devmap.h"
#include "wiringx.h"
#include "gpio_pinmux.h"



//registers for pwm
#define PWM_BASE 0x03060000
#define PWM_GROUP 0x2000
#define PERIOD2 0x014
#define HLPERIDO2 0x010
#define PCOUNT2 0x085
#define PWM_START 0x044
#define PWM_DONE 0x048
#define PWM_UPDATE 0x04C
#define PWM_MODE 0x040
#define PWM_OE 0x0D0
#define base PWM_BASE+PWM_GROUP


//settings for pwm
#define freq  100000// 1KHz
#define duty 75 //75%
#define count 0x1E //30 pulses
#define start 0b0100
#define pinmode 1<<10
#define pwmoe 0b0100




int main() {

    set_func(2, 0x07);
    printf("Ready set go\n");

    devmap_open(PWM_BASE+PWM_GROUP, 208);
    printf("map is open\n");

    //enable the PWM2
    devmap_writel(PWM_OE, pwmoe);
    uint32_t pwmoe_stat = devmap_readl(PWM_OE);
    printf("PWM OE is set to %02x\n", pwmoe_stat);
    
    volatile uint32_t done = devmap_readl(PWM_DONE);
    printf("PWM DONE is set to %02x\n", done);

    devmap_writel(PERIOD2, freq);
    volatile uint32_t period = devmap_readl(PERIOD2);
    printf("Period is set to %d\n", period);
    
    devmap_writel(HLPERIDO2, duty);
    volatile uint32_t hlperiod = devmap_readl(HLPERIDO2);
    printf("HLPeriod is set to %d\n", hlperiod);
    
    devmap_writel(PCOUNT2, count);
    volatile uint32_t pcount = devmap_readl(PERIOD2);
    printf("Pcount is set to %d\n", pcount);
    
    

    devmap_writel(PWM_MODE, pinmode);
    volatile uint32_t pwmmode = devmap_readl(base+PWM_MODE);
    printf("PWM mode is set to %d\n", pwmmode);
    
    
    done = devmap_readl(base+PWM_DONE);
    printf("PWM DONE is set to %d\n", done);
    
    
    sleep(5);
    devmap_writel(base+PWM_START, start);
    volatile uint32_t pwmstart = devmap_readl(base+PWM_START);
    printf("PWM start is set to %02x\n", pwmstart);

    for (int i ; i < 100; i++) {
        done = devmap_readl(base+PWM_DONE);
        printf("PWM done is set to %02X\n", done);
        printf("PWM is running, checking if done...\n");
        delayMicroseconds(500000);
    }
    
    printf("PWM is done\n");
    devmap_close(80);

    return 0;
}