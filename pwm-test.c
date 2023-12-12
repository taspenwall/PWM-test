


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
#define freq  100000// 1KHz
#define duty 75 //75%
#define count 3//30 pulses
#define start 0b0100

#define pwmoe 0b0100


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
    devmap_open(base,1024);

    volatile uint32_t pwmoei =  devmap_readl(PWM_OE);
    printf("pwmoei: ");
    printbin(pwmoei);
    printf("\n");

    devmap_writel(PWM_OE, 0b1111);
    pwmoei =  devmap_readl(PWM_OE);
    printf("pwmoei after: ");
    printbin(pwmoei);
    printf("\n");
    
    

    devmap_writel(PWM_START, 0b0000);
    volatile uint32_t startstatus0 =  devmap_readl(PWM_START);
    printf("startstatus0: ");
    printbin(startstatus0);
    printf("\n");

    

    devmap_writel(PERIOD2, freq);
    volatile uint32_t period2i =  devmap_readl(PERIOD2);
    printf("period2i: %d\n", period2i);
    devmap_writel(HLPERIDO2, freq/4);
    volatile uint32_t hlperiod2i =  devmap_readl(HLPERIDO2);
    printf("hlperiod2i: %d\n", hlperiod2i);

    devmap_writel(PCOUNT2, count);
    volatile uint32_t pcount2i =  devmap_readl(PCOUNT2);
    printf("pcount2i: %d\n", pcount2i);

    devmap_writel(PWM_MODE,(1<<10));
    volatile uint32_t pinmodei =  devmap_readl(PWM_MODE);
    printf("pinmodei: %d\n", pinmodei);

    volatile uint32_t startstatus =  devmap_readl(PWM_START);
    printf("startstatus b4: ");
    printbin(startstatus);
    printf("\n");

    devmap_writel(PWM_START, start);
    startstatus =  devmap_readl(PWM_START);
    printf("startstatus after: ");
    printbin(startstatus);
    printf("\n");



    

    devmap_close(208);

/*    devmap_open(base+PERIOD2,4);
    volatile uint32_t period2 =  devmap_readl(0);
    printf("period2: %02x\n", period2);
    devmap_close(4);

    devmap_open(base+HLPERIDO2,4);
    volatile uint32_t hlperiod2 =  devmap_readl(0);
    printf("hlperiod2: %02x\n", hlperiod2);
    devmap_close(4);
    
    devmap_open(base+PCOUNT2,4);
    volatile uint32_t pcount2 =  devmap_readl(0);
    printf("pcount2: %02x\n", pcount2);
    devmap_close(4);

    devmap_open(base+PWM_MODE,4);
    volatile uint32_t pinmode =  devmap_readl(0);
    printf("pinmode: %02x\n", pinmode);
    devmap_close(4);



    devmap_open(base+PWM_START,4);
    uint32_t startstatus2 =  devmap_readl(0);
    printf("startstatus2: ");
    printbin(startstatus2);
    printf("\n");
    devmap_close(4);
*/
  
    for (int i = 0; i < 15; i++){
        devmap_open(base+PWM_DONE,4);
        uint32_t donestatus =  devmap_readl(0);
        printf("donestatus: ");
        printbin(donestatus);
        printf("\n");
        devmap_close(4);
        sleep(1);   


    
    }     

    

    return 0;
}