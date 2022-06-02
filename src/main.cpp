#include "main.hpp" // This will be created in generated_src folder at compile time
#include "agc.hpp"
#include "globaldefs.hpp"
#include <array>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <argparse/argparse.hpp>

using namespace agcplusplus;

template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}


int main(int argc, char* argv[])
{
    // Print splash and version info
    std::cout << "AGCPlusPlus version v" << AGCPlusPlus_VERSION_MAJOR << "." << AGCPlusPlus_VERSION_MINOR << '\n';

    // Define our argument parser and startup arguments
    argparse::ArgumentParser program("AGCPlusPlus");
    program.add_argument("rope")
            .help("The core rope program to load into fixed memory at startup");

    // Parse input arguments
    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    // Get the rope file path from our startup arguments
    std::string rope_path = program.get<std::string>("rope");
    std::ifstream in_rope;
    in_rope.open(rope_path, std::ios::in | std::ios::binary | std::ios::ate);

    // Verify we can open the rope file
    if (!in_rope.is_open()) {
        std::cout << "Unable to open core rope file \"" << rope_path << "\".\n";
        std::exit(1);
    }

    // Check rope length
    uint64_t size = in_rope.tellg();
    if ((size / 2) != SIZE_FIXED_MEM) {
        std::cout << "Warning: Provided core rope file does not match the size of the AGC's fixed memory.\n";
    }

    // Seek to the start of the file, since we open it at the end to check its length
    in_rope.seekg(0, std::ios::beg);

    // Read the rope data (flipping endianness because AGC is big-endian)
    std::array<word, SIZE_FIXED_MEM> rope_data;
    uint32_t words_read = 0;
    while (words_read < SIZE_FIXED_MEM) {
        if (in_rope.eof()) {
            rope_data[words_read] = 0;
        } else {
            char word_raw[2];
            in_rope.read(word_raw, 2);
            word w = *((word*)word_raw);
            word w_swapped = swap_endian<word>(w);
            rope_data[words_read] = w_swapped;
        }
        ++words_read;
    }
    in_rope.close();

    // Initialize the computer with the rope data
    Agc computer(rope_data);

    // Start running
    computer.run();

    // Exit with no errors if we reach here
    std::exit(0);
}
