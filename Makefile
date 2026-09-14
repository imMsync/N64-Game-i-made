all: my_game.z64

my_game.z64: main.c
	libdragon-cc -o my_game.elf main.c
	libdragon-romstage -o my_game.z64 my_game.elf

clean:
	rm -f *.elf *.z64

.PHONY: all clean
