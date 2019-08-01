# Corewar

Programming game. Bots, written in assembly-like language, battle in a circular memory area.

![](corewar_demo.gif)

## Description

Algorithmic project on graph theory. It's something like a logistics planner for an ant farm  :) The goal is to move a random number of ants in a labyrinth from the *Start* room to the *End* room in a minimum number of moves.

*This is the project of the Algorithms branch of the School 42 curriculum.*

**Detailed description of the task: [corewar.en.pdf](https://github.com/bjarne0706/corewar/blob/master/corewar.en.pdf)**

## Usage

Compile with `make`. Two executables will be created.

#### Assembler

`./asm [bot.s]`   - this will compile a file *bot.s* into a bytecode file *bot.cor*.

Compiled bot then can be loaded into the virtual machine. Test \*.s files are located in `champs` directory. There are also precompiled bots \*.cor in `test_bots` directory.






**Tested only on Mac OS X.**
