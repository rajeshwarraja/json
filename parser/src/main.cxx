#include <json>
#include <iostream>
#include <fstream>

int main(int argc, char*argv[]) {
    json::data json;
    try {
        std::cin >> json;
        std::clog << json << std::endl;
    } catch(std::exception) {
        std::cerr << "Failed to parse json stream" << std::endl;
        return -1;
    }
    std::cout << "JSON stream parsed successfully" << std::endl;
    return 0;
}