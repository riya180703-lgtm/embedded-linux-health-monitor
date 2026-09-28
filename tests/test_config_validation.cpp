#include "config_manager.h"

#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        ConfigManager configManager("../tests/invalid_config.json");
        configManager.load();

        std::cerr << "Test failed: invalid configuration was accepted."
                  << std::endl;
        return 1;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "Invalid configuration rejected: "
                  << e.what() << std::endl;
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
}
