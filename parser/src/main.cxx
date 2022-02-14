#include <json>
#include <iostream>

int main(int argc, char* argv[]) {
	json::data json;
	try {
		std::cin >> json;
		std::clog << json::pretty << json << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Failed to parse json stream" << std::endl
			<< "Exception: " << e.what() << std::endl;

		return -1;
	}
	std::cout << "JSON stream parsed successfully" << std::endl;
	return 0;
}