#include "globaldefs.hpp"
#include "cpu.hpp"

#pragma once

namespace agcplusplus {
// Involuntary control pulse implicitly triggered by DV1.
// Sets bit 12 of S, redirecting erasable memory reads
// during division sequences.
static void _8xp5(Cpu& cpu) {
    cpu.s |= 04000;
}

// Copy A1-16 into X1-16 by private line.
static void a2x(Cpu& cpu) {
    cpu.x = cpu.a;
    cpu.update_adder();
}

// Set bit 15 of X to 1.
static void b15x(Cpu& cpu) {
    cpu.x |= 040000;
    cpu.update_adder();
}

// Insert carry into bit 1 of the adder.
static void ci(Cpu& cpu) {
    cpu.ci = true;
    cpu.update_adder();
}

// Clear X conditional on the outcome of TSGU.
// X is cleared if BR1 = 0. Used in divide.
static void clxc(Cpu& cpu) {
    if ((cpu.br & 0b10) == 0) {
        cpu.x = 0;
        cpu.update_adder();
    }
}

// Cause divide staging by a simple rule.
// Also permit staging to occur at Time3 of
// divide cycles (not emulated in AGCPlusPlus).
static void dvst(Cpu& cpu) {
    cpu.dv = true;
}

// Set the Extend flip flop.
static void ext(Cpu& cpu) {
    cpu.extend_next = true;
}
}
