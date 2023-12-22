


#include <stdio.h>
#include <unistd.h>
#include "devmap.h"
#include "wiringx.h"
#include "gpio_pinmux.h"
#include <stdbool.h>
#include "pwm-led.h"





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
void run_pulse (bool value){
    devmap_writel(PWM_START, 0); //clear the start bit
    if(value){
       devmap_writel(HLPERIDO2, Lduty*freq/100); // set helper period to high duty
        kick_and_wait();
        }
    
    else{
        devmap_writel (HLPERIDO2, Hduty*freq/100); //set helper period to low duty 23 works
        kick_and_wait();
    }
}
void address_led(uint8_t green, uint8_t red, uint8_t blue){
    send_bin(green);
    send_bin(red);
    send_bin(blue);
 }


void send_bin (uint8_t num){
    for (int i = 0; i < 8; i++){
        if (num >> i & 1 == 1){
            run_pulse(true);
        }
        else{
            run_pulse(false);
        }
        
         
    }
    
}
void pwm_cleanup(){
    devmap_writel(PWM_START, 0);
    devmap_writel(PWM_OE, 0);
    devmap_close(1024);
}


