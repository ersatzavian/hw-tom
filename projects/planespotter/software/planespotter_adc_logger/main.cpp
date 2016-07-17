#include "mbed.h"

DigitalOut led1(PB_5), led2(PB_6), led3(PB_7);
InterruptIn btn1(PA_6), btn2(PA_7), btn3(PA_8);
AnalogIn detector(PA_3), average(PA_4);
Serial uart(PA_9, PA_10);

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

int main()
{
    // set uart baud and configure data-received callback
    uart.baud(115200);
    uart.attach(&uartCb);
    
    // configure button press and release callbacks
    btn1.fall(&btn1PressCb);
    btn1.rise(&btn1RelCb);
    btn2.fall(&btn2PressCb);
    btn2.rise(&btn2RelCb);
    btn3.fall(&btn3PressCb);
    btn3.rise(&btn3RelCb);
    
    // initialize LEDs to OFF
    led1 = 1;
    led2 = 1;
    led3 = 1;

    while(1) {
        led1 = 0; // LED is ON (active-low)
        wait(0.2); // 200 ms on 
        led1 = 1; // LED is OFF
        wait(0.8); // 800 ms off
        
        uart.printf("detector/average: %2.2f / %2.2f\r\n", detector.read() * 3.3, average.read() * 3.3);
    }
}
