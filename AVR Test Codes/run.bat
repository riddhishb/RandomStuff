@echo off
 
echo ""

echo ""

echo "Script for compiling and uploading AVR codes to the Microcontroller"

echo ""

echo "/////////////////////General Info//////////////////////"

echo "Created By: Riddhish Bhalodia"
echo "With Programmer: USBASP and MUC: ATMEGA32"

echo "So change the script accordingly! Enjoy!"

echo "///////////////////////////////////////////////////////"

echo ""

echo ""


set /p test="Enter name of .c file : "

	avr-gcc -g -Os -mmcu=atmega32 -c %test%.c
	
	avr-gcc -g -mmcu=atmega32 -o %test%.elf %test%.o
	
	avr-objcopy -j .text -j .data -O ihex %test%.elf %test%.hex

	
	
	echo ""
	
	echo "Compilation Successful, Now Burning"

	
	avrdude -p m32 -c usbasp -U flash:w:%test%.hex:i