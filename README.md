# arg_workshop
Workshop for AlloSphere Research Group using [allolib](https://github.com/AlloSphere-Research-Group/allolib) and cmake.

### Requirements
Need Git & CMake installed

# Installation
### Fork the repository
Press the 'Fork' button to create your own forked repository.

### Clone the repository
On a shell/terminal:

    git clone --filter=blob:none --recurse-submodules --also-filter-submodules <url to your repository>

# Building your project
### How to compile / run
Edit CMakeLists.txt file as needed

    ./configure.sh
    ./run.sh

or if you're on Windows:

    ./configure.bat
    ./run.bat

This will configure and compile the project, and run the binary if compilation is successful.

Alternatively, you can open the CMakeLists.txt project in an IDE like VS Code, Visual Studio or Qt Creator and have the IDE manage the configuration and execution of cmake.

### How to perform a distclean
If you need to delete the build,

    ./distclean.sh

or

    ./distclean.bat

should recursively clean all the build directories of the project including those of allolib and its submodules.