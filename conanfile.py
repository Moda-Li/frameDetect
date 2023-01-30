from conans import ConanFile, CMake


class FrameDetectConan(ConanFile):
    name = "frameDetect"
    version = "1.0.0"
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of FrameDetect here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake"
    #exports_sources = "src/*"

    def config_options(self):
        del self.settings.compiler.libcxx
        if self.settings.os == "Windows":
            del self.options.fPIC

    def source(self):
        self.run("git clone git@github.com:Moda-Li/frameDetect.git")
    
    def buildAndroid(self, cmake, cmake_options):
        cmake.generator = "Unix Makefiles"
        
        cmake_options.append("-DCMAKE_CXX_COMPILER=gcc")
        cmake_options.append("-DANDROID_TOOLCHAIN=gcc")
        cmake_options.append("-DCMAKE_CXX_FLAGS=-frtti -fexceptions -DANDROID_OLD_NDK")
        if(self.settings.arch == "armv7"):
            cmake_options.append("-DANDROID_ABI=armeabi-v7a")
        elif(self.settings.arch == "armv8"):
            cmake_options.append("-DANDROID_ABI=arm64-v8a")
        
    def build(self):
        cmake = CMake(self)
        cmake_options = []
        #cmake.configure(source_folder="src")
        if(self.settings.os == "Android"):
                self.buildAndroid(cmake, cmake_options)
        elif(self.settings.compiler == "Visual Studio"):
            cmake_options.append("-DEVENT__ENABLE_VERBOSE_DEBUG=OFF")
        cmake.configure(source_folder = "frameDetect", args=cmake_options)
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("frameDetect.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["frameDetect"]
