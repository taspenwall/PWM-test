//  This will be the led runner

#include <stdio.h>
#include "devmap.h"
#include "wiringx.h"
#include "gpio_pinmux.h"
#include "pwm-led.h"
#include <signal.h>





#define PIN_NUM 2 //GPIO 2 
int num_leds = 1;



typedef struct {
    uint8_t GREEN;
    uint8_t RED;
    uint8_t BLUE;
} led_t;


void handle_sigint(int sig) 
{ 
    pwm_cleanup();
    printf("Caught signal %d\n", sig);
    exit(0);
} 



/*void shiftSetColor(led_t *strand, const led_t *static_colors, int *currentColorIndex, int num_colors){
    for (int i = num_leds - 1; i >=5 ; i--){
        strand[i] = strand[i-5]; // shift down the row
    }


    for (int j=0; j<5; j++){ // make the 1st 5 leds the current color
        strand[j] = static_colors[*currentColorIndex];
    }
    //strand[0] = static_colors[*currentColorIndex]; // set the first led to the current color
    *currentColorIndex = ((*currentColorIndex + 1) % num_colors); // increment the color index
    
    
}
*/

int main (){
    
    
    signal(SIGINT, handle_sigint);
    set_func(PIN_NUM, 0x7);//if you change the pin number you need to lookup the function number of the PWM pin in the excel sheet.
    setup_pwm();
    
    const led_t static_colors[7] = {
        {0, 255, 0}, //red
        {65, 255, 0},//orange
        {255, 255, 0}, //yellow
        {255, 0, 0}, //green
        {150, 0, 150}, //indigo
        {0, 0, 255}, //blue 
        {0, 255, 100}, //violet
        
        
    };
   
    led_t strand[num_leds];

    int currentColorIndex = 0;
    printf("starting MTF\n");

    for (int k = 0; k < 300; k++) {
    
        printf("sending\n");
        for (int i = 0; i < num_leds; i++){
            address_led(0, 255, 0);
            delayMicroseconds(30); //send to the leds
        }
    
        delayMicroseconds(25000);
    
        
         num_leds += 1;
}   
    
        
         
    /*while (1){

        shiftSetColor(strand, static_colors, &currentColorIndex, sizeof(static_colors)/sizeof(static_colors[0])); // shift the colors down the strand, and set the first led to the next color
        for (int i = 0; i < num_leds; i++){
            address_led(strand[i].GREEN, strand[i].RED, strand[i].BLUE); //send to the leds
        }

       delayMicroseconds(500000); 
    }
    */

   for (int i = 0; i < num_leds; i++){
            address_led(0, 0, 0); //send to the leds
        }
    return 0;
}