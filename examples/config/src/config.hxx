#pragma once

#include <json>
#include <fstream>
#include <filesystem>

namespace Examples {
	class Config final {
	public:
		explicit Config() = default;
		explicit Config(const std::string& filename)
		{
			if (!load(filename))
				std::clog << "Unable to load file " << filename << std::endl;
		}

		~Config() = default;

		[[nodiscard]] bool load(const std::string& filename)
		{
			if (std::filesystem::exists(filename)) {
				std::ifstream(filename) >> _data;
				return true;
			}

			return false;
		}

		[[nodiscard]] bool save(const std::string& filename)
		{
			std::ofstream fout(filename);
			fout << json::pretty << _data << std::flush;
			const auto succeeded = fout.good();
			fout.close();
			const auto closeSucceeded = fout.good();
			return succeeded;
		}

		// Title
		std::string title() const { return _data.has("title") ? _data["title"].toString() : ""; }
		void setTitle(const std::string& title) { _data["title"] = title.c_str(); }

		// Bounds
		struct Rect {
			int x;
			int y;
			int width;
			int height;

			Rect() : x(0), y(0), width(0), height(0) { }
			Rect(int x_, int y_, int width_, int height_) : x(x_), y(y_), width(width_), height(height_) { }
		};

		const Rect bounds() const {
			if (!_data.has("bounds")) return Rect();
			const auto& bounds = _data["bounds"];
			return Rect(
				(int)bounds["x"],
				(int)bounds["y"],
				(int)bounds["width"],
				(int)bounds["height"]);
		}

		void setBounds(const Rect& rect) {
			auto& bounds = _data["bounds"];
			bounds["x"] = rect.x;
			bounds["y"] = rect.y;
			bounds["width"] = rect.width;
			bounds["height"] = rect.height;
		}

		// Activated
		bool activated() const { return _data.has("activated") && (bool)_data["activated"]; }
		void setActivated(bool activated) { _data["activated"] = activated; }

		// Application Entities
		struct AeTitle {
			std::string title;
			std::string ip;
			uint16_t port;
		};
		std::vector<AeTitle> aeTitles() const {
			if (!_data.has("aeTitles")) return {};
			std::vector<AeTitle> result;
			const auto& aeTitles = _data["aeTitles"];
			for (int i = 0; i < aeTitles.length(); ++i) {
				const auto& t = aeTitles[i];
				Config::AeTitle title;
				title.title = t["title"].toString();
				title.ip = t["ip"].toString();
				title.port = t["port"].toInt();
				result.push_back(title);
			}
			return result;
		}
		void clearAeTitles() { _data["aeTitles"] = json::data::emptyArray(); }
		void addAeTitle(const AeTitle& title) {
			auto& aeTitle = _data["aeTitles"][_data["aeTitles"].length()];
			aeTitle["title"] = title.title.c_str();
			aeTitle["ip"] = title.ip.c_str();
			aeTitle["port"] = title.port;
		}

	private:
		json::data _data;
	};
}