all: Makefile main.c
	avr-gcc -Os -DF_CPU=1000000UL -mmcu=attiny4313 -c -o main.o main.c
	avr-gcc -mmcu=attiny4313 main.o -o main
	avr-objcopy -O ihex -R .eeprom main main.hex

flash: main.hex
	avrdude -p ATtiny4313 -c avrispmkII -P /dev/ttyUSB0 -e -U flash:w:main.hex

clean:
	rm main.o main main.hex
