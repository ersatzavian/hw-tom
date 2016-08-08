@ Lifted from http://www.martinhubacek.cz/arm/arm-cortex-bare-metal-assembly/02---arm-cortex-bare-metal-assembly-blinking-led

.thumb

@ Register addresses from STM32F0 reference manual
.equ PERIPH_BASE,           (0x40000000)
.equ AHBPERIPH_BASE,        (PERIPH_BASE + 0x00020000)
.equ AHB2PERIPH_BASE,        (PERIPH_BASE + 0x08000000)

.equ RCC_BASE ,             (AHBPERIPH_BASE + 0x00001000)
.equ GPIOB_BASE,             (AHB2PERIPH_BASE + 0x00000400)

@ Make start function global so the linker can see it later
.global _start

@ Vector table
.word               0x20001000        @ Vector #0 - Stack pointer init value (0x20000000 is RAM address and 0x1000 is 4kB size, stack grows "downwards")
.word               _start            @ Vector #1 - Reset vector - where the code begins
                                    @ Vector #3..#n - I don't use Systick and another interrupts right now
                                    @                so it is not necessary to define them and code can start here

.thumb_func                @ Force the assembler to call this function in Thumb mode, that means the least significant bit in address is set
                        @ Using this bit, the ARM core knows whether is jumping to the ARM or Thumb code, Cortex supports only Thumb
                        @ Also you can use ".type    _start, %function"
_start:

    @ Enable clock for GPIOB peripheral in RCC registers
    LDR r0, =(RCC_BASE + 0x14)
    LDR r1, =(1 << 18)
    STR r1, [r0]     @Store R0 value to r1
   
    @ Enable GPIOB pin 7 as output
    LDR r0, =(GPIOB_BASE + 0x00)
    LDR r1, =(1 << (9*2))    @ Every bin has 2 bit settings, hence *2
    STR r1, [r0]     @Store R0 value to r1
   

loop:

    @ Write high to pin PB7 (LED3)
    LDR r0, =(GPIOB_BASE + 0x14)
    LDR r1, =(1 << 7)
    STR r1, [r0]     @Store R1 value to address pointed by R0
   
    @ Dummy counter to slow down my loop
    LDR R0, =0
    LDR R1, =200000
    loop0:
    ADD R0, R0, #1
    cmp R0, R1
    bne loop0
   
    @ Write low to PB7
    LDR r0, =(GPIOB_BASE + 0x14)
    LDR r1, =(0)
    STR r1, [r0]     @Store R1 value to address pointed by R0

    @ Dummy counter to slow down my loop
    LDR R0, =0
    LDR R1, =200000
    loop1:
    ADD R0, R0, #1
    cmp R0, R1
    bne loop1

   
b loop