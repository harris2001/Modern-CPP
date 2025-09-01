# Modern-CPP

This repository contains a collection of small, self-contained C++ examples organized by language standard.  
Each example demonstrates a specific feature, such as the Rule of Five (C++11), `if constexpr` (C++17), or Concepts (C++20).  

The goal is to provide minimal, compilable examples that can be used as a reference or starting point when learning modern C++.

## Build & Run
Each file has been included in the CMakeLists fo

```bash
cmake -S . -B build
cmake --build build
```

To build only a single example, specify the target:

```bash
cmake --build build --target rule_of_five
```

## Running Examples
The compiled executables are placed in the corresponding build subfolders:
```bash
./build/C++11/rule_of_five
./build/C++17/structured_bindings
./build/C++20/imports
```

## Running everything as Tests
If CTest is enabled, all examples can be registerd as test and run with:
```bash
cd build
ctest --output-on-failure
```

## License
This project is licensed under the MIT License (i.e. free to use, modify and share the code for learning and teaching)

