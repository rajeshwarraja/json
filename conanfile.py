from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.errors import ConanInvalidConfiguration


class JsonConan(ConanFile):
    name = "json"
    license = "MIT"
    url = "auto"

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    exports_sources = "examples/*", "include/*", "src/*", "test/*", "CMakeLists.txt"

    def validate(self):
        if self.info.settings.os == "Macos":
            raise ConanInvalidConfiguration("Macos not supported")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.build_modules = {"cmake": ["cmake/Json.cmake"]}
