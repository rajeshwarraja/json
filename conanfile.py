from conans import ConanFile, CMake, tools


class JsonConan(ConanFile):
    name = "json"
    version = "1.1.0"
    license = "MIT License"
    author = "R. Raja rajeshwarraja@gmail.com"
    url = "https://github.com/rajeshwarraja/json"
    description = "JavaScript Object Notation Data Interchange Format Library"
    topics = ("json", "parser")
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="./")
        cmake.build()

    def package(self):
        self.copy("*", dst="include", src="json/include")

    def package_info(self):
        self.cpp_info.libs = ["json"]

