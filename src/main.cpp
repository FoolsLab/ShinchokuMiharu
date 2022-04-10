#include <iostream>
#include "app/Charactor.hpp"
#include "sys/System.hpp"

int main(void) {
    try {
        System sys;
        Charactor charactor(&sys.getWindow());

        while (!sys.shouldExit()) {
            sys.update();
            charactor.update();
        }
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
