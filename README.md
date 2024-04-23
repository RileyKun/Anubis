# Anubis
A free open-source cheat for Team Fortress 2.
## About
Anubis is a free, minimalist, open-source cheat for Team Fortress 2. It currently only supports the 32-bit version of the latest game binaries.
## How to download?
Currently, there are no compiled release builds of the cheat. Release builds of the cheat will be published when features are properly written.
## How to contribute?
Contributions are always welcome! Follow the setup instructions and guidelines below for more info.
### Setup
 - Clone the repository. You can either hit the green code button or run `git clone https://github.com/RileyKun/Anubis.git` to clone.
 - Setup clang-format with the `.clang-format` file in the repository. If you do not have clang-format, please download it or an appropriate plugin for it in your IDE. (If you are on Visual Studio or JetBrains CLion, this will not be an issue.
 - Setup CMake. If you do not have CMake downloaded, you can obtain it [here](https://cmake.org/download/) or through a package manager of your choice. (CMake can be easily downloaded on Visual Studio through the VS Installer and comes bundled with stock installations of JetBrains CLion)
### Compiling
You may either use the compile.bat script in the repository (if you are using a text editor that does not have a supported build system or if you are building from the command line) or use the CMake build system within your IDE. For toolchains, dependencies and more, see the guidelines section.
### Guidelines
**Formatting**  
All commits must be formatted using the clang-format standard set in the repository. If you are unable to use clang-format, the summary of the coding style is this:
- Indentations are 2 spaces wide across ALL files. We use spaces, not tabs.
- Opening braces must be on the same line as the start of a statement, function declaration, etc.
- Namespaces should not see any indentations. You must comment the namespace after the ending brace.
- Case labels in switch statements must be indented along with the code inside them.
- Do not use header guards **whatsoever!**
- Template functions declared as inline must all be on the same line.
- Functions that need wrapping must align with the parameters on the first line.
- You must wrap if the column count exceeds 100, **no exceptions**.  

**Style**
- Do not use C-Style casts unless it's explicit what you are doing. Use C++ style casts as much as possible.
- Do not use the new operator whenever possible.
- Please only include what you are using in a piece of code. Read more about it [here](https://google.github.io/styleguide/cppguide.html#Include_What_You_Use)
- Do not use the auto keyword on explicit types.
- Unless required, every header file should have a matching `.cpp` file. header files must be named `.hpp`

**Toolchains & Dependencies**  
Our dependencies are the following:
- CPM.cmake
- SafetyHook
- Zydis (required by SafetyHook)
- OpenGL Mathematics
- Dear ImGui

If a change you wish to make requires a dependency be added, **please make a GitHub issue before commiting!** Failure to do this will result in your PR being rejected. We want Anubis to be lightweight and as free from dependencies as possible.  
We code in focus for the MSVC. We do not support the GCC or other compilers. You may use clang-cl under the MSVC. If you cannot compile using clang-cl, please make a GitHub issue.
## License
Licensed under the GNU-GPL v3.0 License. See the LICENSE file for more information.
> Copyright (C) 2024 RileyKun
