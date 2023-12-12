


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
#define PCOUNT2 0x058
#define PWM_START 0x044
#define PWM_DONE 0x048
#define PWM_UPDATE 0x04C
#define PWM_MODE 0x040
#define PWM_OE 0x0D0
#define base PWM_BASE+PWM_GROUP


//settings for pwm
#define freq  800000// 800kHz
#define Hduty 75 //75%
#define Lduty 25 //25%
#define count 1//30 pulses
#define start 0b0100
#define count_mode 1<<10
#define pwmoe 0b0100


void setup_pwm(){
     devmap_open(base,1024);
    //set the pwm registers
    devmap_writel(PWM_OE, pwmoe); //output enable
    
    devmap_writel(PWM_MODE, count_mode);
    devmap_writel(PWM_START, 0);
    devmap_writel(PERIOD2, freq);
    devmap_writel(PCOUNT2, count);
}

void kick_and_wait(){
    devmap_writel(PWM_START, start);
    while((devmap_readl(PWM_DONE) & (1<<2)) == 0); //wait while done

    }

void run_pulse (int value){
    devmap_writel(PWM_START, 0); //set pwm start to 0
    if(value == 1){
        devmap_writel(HLPERIDO2, Hduty); // set helper period to high duty
        kick_and_wait();
        }
    
    else{
        devmap_writel (HLPERIDO2, Lduty); //set helper period to low duty
        kick_and_wait();
    }
}

void cleanup(){
    devmap_writel(PWM_START, 0);
    devmap_writel(PWM_OE, 0);
    devmap_close(1024);
}

void printbin(uint32_t x) {
    int i;
    for(i=31; i>=0; i--) {
        printf("%d", (x>>i)&1);
    }
    printf("\n");
}

int main() {

    set_func(2, 0x07);
    printf("Ready set go\n");



    //set the pwm registers
    setup_pwm();
    run_pulse(1);
    run_pulse(0);
    run_pulse(1);
    run_pulse(0);
    run_pulse(1);
    run_pulse(1);
    run_pulse(0);
    run_pulse(0);
    cleanup();

    

    return 0;
}