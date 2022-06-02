# AGCPlusPlus
An attempt at creating a control pulse-level emulator of the Block II Apollo guidance computer.

## Why the AGC?
I've been wanting to learn a bit more about computer architecture and to test my programming skills, and watching CuriousMarc's YouTube series on their restoration of an actual original Apollo guidance computer really piqued my curiosity for a number of reasons:

- It's an incredibly unique machine, having been specifically created for space flight, navigation, and spacecraft operation/pilot assistance. While its architecture could theoretically be used as a general-purpose computer, it features dedicated multiplication and division logic, and various other features that allow it to perform complex scientific calculations with impressive accuracy given its size and relative simplicity.
- Because it was meant to be compact and power-efficient enough to fit on-board the Apollo craft, its design is simple enough for a single person to understand and replicate its design in a more abstract form like an emulator, given enough time to become familiar with the hardware.
- There is a copious amount of original documentation available, meaning that reverse-engineering is not required to understand the computer at a satisfactory level.
- The AGC is historically significant: it's hard to imagine that the moon landings would have been possible without a computer on-board to help the pilots with the myriad of tasks needed to get there.

## What's "Block II"?
When MIT/Draper Labs were originally contracted to build the Apollo guidance computer, the Apollo program was split into two distinct phases, "Block I" and "Block II". This refers primarily to the design of the Apollo spacecraft itself. Block I would be only the Command and Service Module, with no capability to dock with a Lunar Module (which had not been completed at the time Block I missions would begin). The plan was, after several Block I missions, crews would begin using the upgraded Block II spacecraft, which would include the Lunar Module and be capable of landing on the moon. The AGC would also be upgraded for the Block II missions, featuring expanded capabilities and larger memory capacity. However, after the tragic Apollo I fire, only a handful of un-crewed test missions would fly using Block I hardware. Therefore, the vast majority of mission and system software that can be found for the AGC comes from Block II spacecraft, making it preferable for emulation. Integrating Block I compatibility would be non-trivial, and although I do plan to eventually write a Block I emulator, it may require significant refactoring and rewriting of this emulator's code, and would be a long-term milestone rather than something I'm actively focusing on.

## What do you mean by "control pulse-level" emulator?
This refers to the abstraction level of the emulator. Generally speaking, we can describe how AGC executes its machine language instructions at four distinct levels of abstraction from the physical hardware, in descending order (most abstract/highest level to least abstract/lowest level):

1. the instruction level
2. the subinstruction/MCT level
3. the control pulse level
4. the hardware/logic gate level

I have no electrical engineering knowledge whatsoever, so developing a hardware-level emulator is basically out of the question, and there are already a couple of gate-accurate AGC simulator projects on GitHub at the time of writing, such as [this one by Mike Stewart](https://github.com/virtualagc/agc_simulation). There also exist instruction-level emulators, such as the venerable [VirtualAGC project by Ron Burkey and Mike Stewart](https://github.com/virtualagc/virtualagc). However, to my knowledge no one has designed an emulator that works on the control pulse abstraction level. There is at least one advantage to emulating the AGC in this way: Keeping the emulation somewhat close to the hardware allows me to strike what I feel is a "sweet spot" between accuracy and simplicity. Developing a hardware simulation requires extensive electrical knowledge and understanding of the physical layout of the computer, while opting for an instruction-level emulator requires significant workarounds for edge cases and other quirks of the hardware, making code complicated and potentially obtuse or hard to maintain. By emulating at a level between these two points, we maintain relative accuracy while not needing as many edge cases or complex code workarounds.

## Acknowledgements
- [Mike Stewart](https://github.com/thewonderidiot), for the many, many hours he spent teaching me about the AGC, assisted me with debugging and troubleshooting, and for being an all-around fantastic person. Without his guidance, this project would have never gotten off the ground.
- [Ron Burkey and the rest of the VirtualAGC contributors](https://github.com/virtualagc), for their years of hard work and dedication spent towards researching and documenting the AGC, as well as their impressive efforts developing the various toolchain components for the VirtualAGC project, including but not limited to the yaYUL compiler, which allowed me to write my own custom core rope programs for testing my emulator.
- [CuriousMarc](https://youtube.com/curiousmarc), for his excellent video series documenting their restoration of a real AGC, which inspired my interest in the computer to begin with.
- [The Project Apollo/NASSP development team](https://github.com/orbiternassp), for creating an incredible Apollo simulator which further piqued my interest into the Apollo program and space history.
- The entire staff of the original Apollo space program at NASA, MIT/Draper Labs, and beyond, for their incredible accomplishments, inventions, and contributions to the scientific world and society at large.
