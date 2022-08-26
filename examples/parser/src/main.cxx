#include <json>

int main(int argc, char* argv[]) {
	std::clog
		<< "Awaiting input data..." << std::endl;
	json::data json;
	try {
		std::cin >> json;
		std::cout << json::pretty << json << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Failed to parse json stream" << std::endl
			<< "Exception: " << e.what() << std::endl;

		return -1;
	}
	std::clog << "JSON stream parsed successfully" << std::endl;
	return 0;
}