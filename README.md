# Corewar

Programming game. Bots, written in assembly-like language, battle in a circular memory area.

![](corewar_demo.gif)

## Description

This is the implementation of the programming game [Core War](https://en.wikipedia.org/wiki/Core_War).

*This is the project of the Algorithms branch of the School 42 curriculum. As a group project, it's done in collaboration with my 3 awesome schoolmates: @dstepanets, @github/anatoliinerus, @evlasov. I've written almost all VM code.*

**Detailed description of the task: [corewar.en.pdf](https://github.com/bjarne0706/corewar/blob/master/corewar.en.pdf)**

## Usage

Compile with `make`. Two executables will be created.

### Assembler

`./asm [bot.s]`   - this will compile a file *bot.s* into a bytecode file *bot.cor*.

Compiled bot then can be loaded into the virtual machine. Test \*.s files are located in `champs_s` directory. There are also precompiled bots \*.cor in `champs_cor` directory.

### Virtual Machine

Run like this:
```
	./corewar [-d N] [-s N] [-e / -E] [-v] [-l N] <[-n N] champ1.cor> <...>
```

Options:
```
	-n N	: Specify player's number (N >= 1 && N <= number_of_players (4 max))

	-v	: Visual mode (overrides dumps and logs)

	-d N (-dump N)	: Dump memory (32 octets/line) after N cycles then exit
	-D N		: same as -d but 64 octets/line
	-s N	: Run N cycles, dump memory (32 octets/line), pause, then repeat
	-S N	: same as -s but 64 octets/line
	-e / -E	: Dump memory at the end of a game (32 / 64 octets)

	-a	: Print output of 'aff' operation

	-l N	: Print logs. Add numbers together to enable several logs:
			1 - show lives
			2 - show cycles
			4 - show operations
			8 - show deaths
			16 - show PC movements (except for jumps)
```

**Tested only on Mac OS X.**
