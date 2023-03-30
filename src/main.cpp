#include "main.hpp" // This will be created in the "generated_src" folder at CMake build time.
#include "common/util_functions.hpp"
#include "common/global_definitions.hpp"

#include "block1/block1defs.hpp"

#include "block2/block2defs.hpp"
#include "block2/agc.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <argparse/argparse.hpp>

using namespace agcplusplus;

int main(int argc, char* argv[]) {
    // Set up output stream, default to std::cout, but could be a log file, etc.
    std::ostream& output = std::cout;

    // Print banner message
    output << "AGCPlusPlus version v" << AGCPlusPlus_VERSION_MAJOR << "." << AGCPlusPlus_VERSION_MINOR << '\n';

    // Define our program's arguments
    argparse::ArgumentParser mainArgs("AGCPlusPlus");
    mainArgs.add_argument("machine-type")
        .help("The machine type to emulate, either 'block1' or 'block2'");
    mainArgs.add_argument("rope-file")
        .help("The core rope program to load into fixed memory at startup");
    mainArgs.add_argument("--log-timepulse")
        .help("Whether to print CPU state information every timepulse.")
        .default_value(false)
        .implicit_value(true);
    mainArgs.add_argument("--log-mct")
        .help("Whether to print CPU state information every MCT (twelfth timepulse).")
        .default_value(false)
        .implicit_value(true);
    mainArgs.add_argument("--ignore-counters")
        .help("Ignore counter requests generated by the scaler, for debugging purposes. Doing this will break most official AGC software.")
        .default_value(false)
        .implicit_value(true);
    mainArgs.add_argument("--ignore-interrupts")
        .help("Ignore interrupt requests generated by the computer or external hardware, for debugging purposes. Doing this will break most official AGC software.")
        .default_value(false)
        .implicit_value(true);
    mainArgs.add_argument("--ignore-alarms")
        .help("Ignore hardware alarms generated by the computer, for debugging purposes. Doing this will break most official AGC software.")
        .default_value(false)
        .implicit_value(true);

    // Parse input arguments
    try {
        mainArgs.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << mainArgs;
        std::exit(1);
    }

    // Put the rest of our startup args into a struct to make passing it easier
    InitArguments init_args {
            (mainArgs["--log-mct"] == true),
            (mainArgs["--log-timepulse"] == true),
            (mainArgs["--ignore-counters"] == true),
            (mainArgs["--ignore-interrupts"] == true),
            (mainArgs["--ignore-alarms"] == true),
    };

    // Get the rope file path from our startup arguments
    auto rope_path = mainArgs.get<std::string>("rope-file");
    std::ifstream in_rope;
    in_rope.open(rope_path, std::ios::in | std::ios::binary);

    // Verify we can open the rope file
    if (!in_rope.is_open()) {
        std::cout << "Unable to open core rope file \"" << rope_path << "\"." << std::endl;
        std::exit(1);
    }

    // Load rope file into a temporary buffer, default to allocating the maximum expected size: Block II fixed memory size
    std::vector<word> rope_buffer;
    while (!in_rope.eof()) {
        word w = 0;
        in_rope.read(reinterpret_cast<char*>(&w), 2);
        word w_swapped = swap_endian<word>(w);
        rope_buffer.push_back(w_swapped);
    }
    in_rope.close();

    // Load data and prepare computer based on the machine type selected
    auto machine_type = mainArgs.get<std::string>("machine-type");
    if (machine_type == "block1") {
        // Check rope length
        if ((rope_buffer.size() - 1) != block1::MEM_FIXED_TOTAL_SIZE) {
            std::cout << "Warning: The core rope does not match the size of the machine's fixed memory." << std::endl;
        }

        // Initialize the Block I computer

    } else if (machine_type == "block2") {
        // Check rope length
        if ((rope_buffer.size() - 1) != block2::SIZE_FIXED_MEM) {
            std::cout << "Warning: The core rope does not match the size of the machine's fixed memory." << std::endl;
        }

        // Initialize the Block II computer
        block2::Agc computer(rope_buffer, init_args);

        // Start running
        computer.run();
    }

    // Exit with no errors if we reach here
    std::exit(0);
}