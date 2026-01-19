#include <iostream>
#include <string>

// declare modes
void build_mode();
void search_mode();

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage:\n";
        std::cout << "  ./engine build\n";
        std::cout << "  ./engine search\n";
        return 0;
    }

    std::string mode = argv[1];

    if (mode == "build") {
        build_mode();
    } else if (mode == "search") {
        search_mode();
    } else {
        std::cout << "Unknown mode: " << mode << "\n";
    }

    return 0;
}
