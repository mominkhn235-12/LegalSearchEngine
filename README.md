# Pakistan Legal Case Search Engine

## Build

Build with a C++17 compiler that supports `std::filesystem` (GCC 8 or newer, or a
current MSVC/Clang toolchain). From the project root, compile all source files:

```sh
g++ -std=c++17 -Wall -Wextra -Isrc src/main.cpp src/DocumentLoader.cpp src/IndexBuilder.cpp src/TextProcessor.cpp src/SearchModule.cpp -o main
```

In VS Code, use **Terminal: Run Build Task** to run the configured build task.

## Run

Run the executable from the project root so it can read the `data` directory,
then enter a single keyword when prompted:

```sh
./main
```

The search keyword is normalized by `TextProcessor` and searched as one token.
