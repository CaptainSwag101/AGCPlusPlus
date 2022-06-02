#include "globaldefs.hpp"
#include "cpu.hpp"

#pragma once

namespace agcplusplus {
// Involuntary control pulse implicitly triggered by DV1.
// Sets bit 12 of S, redirecting erasable memory reads
// during division sequences.
static void _8xp5(Cpu& cpu);

// Copy A1-16 into X1-16 by private line.
static void a2x(Cpu& cpu);

// Set bit 15 of X to 1.
static void b15x(Cpu& cpu);

// Insert carry into bit 1 of the adder.
static void ci(Cpu& cpu);

// Clear X conditional on the outcome of TSGU.
// X is cleared if BR1 = 0. Used in divide.
static void clxc(Cpu& cpu);

// Cause divide staging by a simple rule.
// Also permit staging to occur at Time3 of
// divide cycles (not emulated in AGCPlusPlus).
static void dvst(Cpu& cpu);

// Set the Extend flip flop.
static void ext(Cpu& cpu);

// Next instruction is to be loaded into SQ. Also
// frees certain restrictions- permits increments and
// interrupts.
static void nisq(Cpu& cpu);

// Read A1-16 to WL1-16.
static void ra(Cpu& cpu);

// Read address of next cycle. This appears at the end
// of an instruction and normally is interpreted
// as RG. If the next instruction is to be a
// pseudo code (INHINT, RELINT, EXTEND), it is instead
// interpreted as RZ ST2.
static void rad(Cpu& cpu);

// Read B1-16 to WL1-16.
static void rb(Cpu& cpu);

// Read the content of B inverted: C1-16 to WL1-16.
static void rc(Cpu& cpu);

// Read the content of the input or output channel
// specified by the current content of S:
// Channel bits 1-14 to WL1-14, and bit 16 to WL15,16.
// Channels 1 and 2 read as RL and RQ.
static void rch(Cpu& cpu);

// Read G1-16 to WL1-16
static void rg(Cpu& cpu);

// Read L1-14 to WL1-14, and L16 to WL15 and 16.
static void rl(Cpu& cpu);

// Read low bits of B to WL1-10.
static void rl10bb(Cpu& cpu);

// Read Q1-16 to WL1-16.
static void rq(Cpu& cpu);

// Read the content of central store defined by
// the address currently in S:
// Central store bits 1-16 are copied to WL1-16.
static void rsc(Cpu& cpu);

// Place octal 004000 = Block 2 start address on the WL's.
static void rstrt(Cpu& cpu);

// Read U1-16 to WL1-16.
static void ru(Cpu& cpu);

// Read Z1-16 to WL1-16.
static void rz(Cpu& cpu);

// Set Stage2 flip flop next T12.
static void st2(Cpu& cpu);

// Clear and write WL1-16 into A1-16.
static void wa(Cpu& cpu);

// Clear and write WL1-16 into B1-16.
static void wb(Cpu& cpu);

// Clear and write WL1-16 into G1-16 except
// for addresses octal 20-23, which cause editing.
static void wg(Cpu& cpu);

// Clear and write WL1-16 into Q1-16.
static void wq(Cpu& cpu);

// Clear and write WL1-12 into S1-12.
static void ws(Cpu& cpu);

// Clear and write WL1-16 into the central register
// specified by the current content of S. Bits
// 1-16 into positions 1-16.
static void wsc(Cpu& cpu);

// Clear Y and X. Write WL1-16 into Y1-16.
static void wy(Cpu& cpu);

// Clear Y and X. Write WL1-12 into Y1-12.
static void wy12(Cpu& cpu);

// Clear and write WL1-16 into Z1-16.
static void wz(Cpu& cpu);
}
