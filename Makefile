all: my_game.z64

my_game.z64: main.c
	mips64-elf-gcc -g -O2 -march=vr4300 -mabi=32 -I$(N64_INST)/mips64-elf/include -L$(N64_INST)/mips64-elf/lib -o my_game.elf main.c -ldragon -lc -lm -ldragonsys
	n64tool -l 2M -t "My Game" -h $(N64_INST)/mips64-elf/lib/header my_game.z64 my_game.elf
	chksum64 my_game.z64

clean:
	rm -f *.elf *.z64

.PHONY: all clean
