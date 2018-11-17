#include <iostream>

char* ss;

int main(int argc, char* args[]) {
    if (argc == 1) {
        std::cout << "No simulation string received." << std::endl;
        return -1;
    } else {
        ss = args[1];
        // TODO: Simulation logic
    }
    return 0;
}