#include "mbed.h"

#define DEBUG 1
#define SAMPLERATE_MHZ 0.000001

DigitalOut led1(PB_5), led2(PB_6), led3(PB_7);
InterruptIn btn1(PA_6), btn2(PA_7), btn3(PA_8);
AnalogIn detector(PA_3), average(PA_4);
Serial uart(PA_9, PA_10);

Ticker sampleTimer;
int word = 0, bit = 32;
float det = 0, avg = 0;
bool lastSampleWasLow = true;

void btn1PressCb()
{
    uart.printf("Button 1 Pressed\r\n");
}

void btn1RelCb()
{
    uart.printf("Button 1 Released\r\n");
}

void btn2PressCb()
{
    uart.printf("Button 2 Pressed\r\n");
}

void btn2RelCb() 
{
    uart.printf("Button 2 Released\r\n");
}

void btn3PressCb()
{
    uart.printf("Button 3 Pressed\r\n");
}

void btn3RelCb() 
{
    uart.printf("Button 3 Released\r\n");
}

void uartCb() 
{
    // echo back 
    uart.printf("%c", uart.getc());
}   

void sample() {
    det = detector.read();
    avg = average.read();
    if ((det > avg) && lastSampleWasLow) {
        led1 = 0; // LED is ON (active-low)
#if DEBUG==1
        uart.printf("(1) detector/average: %2.5f / %2.5f \r\n", det * 3.3, avg * 3.3);
#endif
        word |= 1 << bit;
        lastSampleWasLow = false;
    } else {
        led1 = 1; // LED is OFF
#if DEBUG==1
        uart.printf("(0) detector/average: %2.5f / %2.5f \r\n", det * 3.3, avg * 3.3);
#endif  
        lastSampleWasLow = true;
    } 
    bit--;
    if (bit < 0) {
        uart.printf("%08x ", word);
        word = 0;
        bit = 32;
    }   
}

int main()
{
    // set uart baud and configure data-received callback
    uart.baud(115200);
    uart.attach(&uartCb);
    uart.printf("Planespotter Running.\r\n");
    
    // configure button press and release callbacks
    btn1.fall(&btn1PressCb);
    btn1.rise(&btn1RelCb);
    // set internal pull-up *after* attaching functions for byzantine mbed library reasons
    btn1.mode(PullUp);
    
    btn2.fall(&btn2PressCb);
    btn2.rise(&btn2RelCb);
    btn2.mode(PullUp);
        
    btn3.fall(&btn3PressCb);
    btn3.rise(&btn3RelCb);
    btn3.mode(PullUp);
     
    // initialize LEDs to OFF
    led1 = 1;
    led2 = 1;
    led3 = 1;

    // start the sampler
    sampleTimer.attach_us(&sample, 1.0 / SAMPLERATE_MHZ);
    
    // spin. Ticker interrupts.
    while (1) {
        wait (0.1);
    }
}
