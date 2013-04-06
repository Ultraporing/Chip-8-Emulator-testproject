#pragma once

class Chip8
{
	// Opcodes 35 in Total
	unsigned short opcode;
	// 4K built in Memory
	unsigned char memory[4096];
	// CPU Registers 15x 8-bit, 16th Register = 'carry flag'
	unsigned char V[16];
	// Index Register can have values: 0x000 - 0xFFF
	unsigned short I;
	// Program counter can have values: 0x000 - 0xFFF
	unsigned short pc;

	// System Memory map
	// 0x000 - 0x1FF = Chip 8 interpreter (contains font set in emu)
	// 0x050 - 0x0A0 = Used for the built in 4x5 pixel font set (0-F)
	// 0x200 - 0xFFF = Program ROM and work RAM

	// Graphics, screen size 64x32 pixel states 1 or 0
	unsigned char gfx[64 * 32];

	// Timer Registers at 60Hz if set above zero they count down to zero
	unsigned char delay_timer;
	// System buzzer sounds when sound timer reaches zero
	unsigned char sound_timer;

	// stack + stack pointer
	unsigned short stack[16];
	unsigned short sp;

	// Hex based keypad (0x0 - 0xF), array holds the key states
	unsigned char key[16];
};
