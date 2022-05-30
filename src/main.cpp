#include <iostream>
#include "main.hpp" // This will be created in generated_src folder at compile time
#include "agc.hpp"

int main()
{
    std::cout << "AGCPlusPlus version v" << AGCPlusPlus_VERSION_MAJOR << "." << AGCPlusPlus_VERSION_MINOR << std::endl;
    
    Agc computer;

    computer.Run();
    
    return 0;
}
