#include <iostream>
#include "System.hpp"

int main(void) {
    try {
        System sys;

        while (!sys.shouldExit()) {
            sys.update();
        }
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
