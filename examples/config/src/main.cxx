#include "config.hxx"

using namespace Examples;

void display(const Config& config)
{
	const auto rect = config.bounds();
	std::cout
		<< "Configuration" << std::endl
		<< "    Title: " << config.title() << std::endl
		<< "   Bounds: [" << rect.x << ", " << rect.y << ", " << rect.width << ", " << rect.height << "]" << std::endl
		<< "   Active: " << std::boolalpha << config.activated() << std::endl
		<< " AE Title: " << std::endl;
	const auto titles = config.aeTitles();
	if (titles.empty())
		std::cout << "  - None" << std::endl;
	else
		std::for_each(begin(titles), end(titles), [](const Config::AeTitle& t) { 
			std::cout << "  - Title: " << t.title << ", IP: " << t.ip << ", " << t.port << std::endl; 
		});
}

int main(int argc, char* argv[]) {
	Config config;

	display(config);

	if(!config.load("./example.config.json"))
		std::cerr << "Failed to load configuration" << std::endl;

	display(config);

	config.setActivated(!config.activated());
	config.clearAeTitles();
	config.addAeTitle(Config::AeTitle{ "APP_TITLE", "192.0.0.2", 2020 });

	if (!config.save("./example.config.json"))
		std::cerr << "Failed to store configuration" << std::endl;

	display(config);

	return 0;
}