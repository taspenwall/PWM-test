//  This will be the led runner

#include <stdio.h>
#include <unistd.h>
#include "devmap.h"
#include "wiringx.h"
#include "gpio_pinmux.h"
#include <stdlib.h>
#include "pwm-led.h"
#include <stdbool.h>




#define PIN_NUM 2
#define num_leds 3



typedef struct {
    uint8_t GREEN;
    uint8_t RED;
    uint8_t BLUE;
} led_t;


int main (){

    set_func(PIN_NUM, 0x7);
    setup_pwm();
    bool state = true;

    while (1){
      
    
    
    led_t led[num_leds];

        if(state){

        for (int i = 0; i < num_leds; i++){
            if (i%2 == 0){
            led[i].GREEN = 55;
            led[i].RED = 0;
            led[i].BLUE = 0;
            }

        else {
            led[i].GREEN = 0;
            led[i].RED = 55;
            led[i].BLUE = 0;
            }
        }
        }
        else {
            for (int i = 0; i < num_leds; i++){
            if (i%2 == 0){
            led[i].GREEN = 0;
            led[i].RED = 55;
            led[i].BLUE = 0;
            }

        else {
            led[i].GREEN = 55;
            led[i].RED = 0;
            led[i].BLUE = 0;
            }
        }
        }

    for (int i = 0; i < num_leds; i++){
        address_led(led[i].GREEN, led[i].RED, led[i].BLUE);
        
    }
    state = !state;
    delayMicroseconds(1000000);

    
    }
    pwm_cleanup();

    return 0;
}