#include "parser.h"

int main() {
    while (true) {
        char c;
        std::cin >> c;
        std::cout << mux::calculator::makeOperator(c) << std::endl;
    }
}