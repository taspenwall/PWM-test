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
#define num_leds 300



typedef struct {
    uint8_t GREEN;
    uint8_t RED;
    uint8_t BLUE;
} led_t;


void shiftSetColor(led_t *strand, const led_t *static_colors, int *currentColorIndex, int num_colors){
    for (int i = num_leds - 1; i > 4; i--){
        strand[i] = strand[i-1]; // shift down the row
    }


    for (int j=0; j<5; j++){
        strand[0+j] = static_colors[*currentColorIndex];
    }
    //strand[0] = static_colors[*currentColorIndex]; // set the first led to the current color
    *currentColorIndex = ((*currentColorIndex + 1) % num_colors); // increment the color index
    
    
}


int main (){

    set_func(PIN_NUM, 0x7);
    setup_pwm();
    
    const led_t static_colors[7] = {
        {0, 255, 0}, //red
        {65, 255, 0},//orange
        {255, 255, 0}, //yellow
        {255, 0, 0}, //green
        {150, 0, 150}, //indigo
        {0,150,250}, //violet
        {0, 0, 255}, //blue 
        
    };
   
    led_t strand[num_leds];

    int currentColorIndex = 0;

    

    while (true ){

        shiftSetColor(strand, static_colors, &currentColorIndex, sizeof(static_colors)/sizeof(static_colors[0])); // shift the colors down the strand, and set the first led to the next color
        for (int i = 0; i < num_leds; i++){
            address_led(strand[i].GREEN, strand[i].RED, strand[i].BLUE); //send to the leds
        }

       delayMicroseconds(1000000); 
    }
    
    pwm_cleanup();
    printf("Done\n");

    return 0;
}