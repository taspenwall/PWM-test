


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

#define CLK_BASE 0x03002000
#define CLK_PWM 0x120


//settings for pwm
#define freq  125// 125 is the calcualted for 800kHz calulated frequency,  It seem that I have to go way lower for a 1.25us period.
#define Hduty  12//56% is the claculated duty cycle for .7us high time to write a 1
#define Lduty  1//28%  is the claculated duty cycle for .35us high time   to write a 0
#define count 1//30 pulses
#define start 0b0100
#define pwm_mode ((1<<10) | (1<<2)) // set the pmode to to pulse 1<<num+8 and set the polarity to control the high period 1<<2
#define pwmoe 0b0100






void setup_pwm(){
     devmap_open(base,1024);
    //set the pwm registers
    devmap_writel(PWM_OE, pwmoe); //output enable
    
    devmap_writel(PWM_MODE, pwm_mode); //set count mode and polarity
    devmap_writel(PWM_START, 0); //set start to 0
    devmap_writel(PERIOD2, freq); //set period to 800kHz
    devmap_writel(PCOUNT2, count);  //set for 1 pulse
    

}

void kick_and_wait(){
    devmap_writel(PWM_START, start);
    while(devmap_readl(PWM_DONE) == 0);

}
void run_pulse (int value){
    devmap_writel(PWM_START, 0); //clear the start bit
    if(value == 1){
       devmap_writel(HLPERIDO2, Hduty*freq/100); // set helper period to high duty
        kick_and_wait();
        }
    
    else{
        devmap_writel (HLPERIDO2, Lduty*freq/100); //set helper period to low duty 23 works
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
    printf("Ready set go 1,0,0\n");

   

    //set the pwm registers
    setup_pwm();
    
    run_pulse(1);
    run_pulse(1);
    run_pulse(0);
    run_pulse(0);
    

    

    printf("mode: ");


    
    cleanup();
    
    

    return 0;
}