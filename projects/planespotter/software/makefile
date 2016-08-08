all: asmtest.bin

asmtest.o: asmtest.S
	arm-none-eabi-as -mthumb -o asmtest.o asmtest.S

asmtest.elf: asmtest.o
	arm-none-eabi-ld -Ttext 0x8000000 asmtest.o -o asmtest.elf

asmtest.bin: asmtest.elf
	arm-none-eabi-objcopy -S -O binary asmtest.elf asmtest.bin
	arm-none-eabi-size asmtest.elf

clean:
	rm asmtest.elf asmtest.o asmtest.bin a.out