# Build Instructions

## Prerequisites
- C++ compiler (g++, clang, or MSVC)
- CMake 3.10 or higher
- Git

## Option 1: Using CMake (Recommended)

```bash
# Clone the repository
git clone https://github.com/YOUR-USERNAME/smart-traffic-controller.git
cd smart-traffic-controller

# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Compile
make

# Run the program
./bin/TrafficController
```

## Option 2: Direct Compilation (Linux/macOS)

```bash
cd smart-traffic-controller
g++ -std=c++11 -I. src/*.cpp -o TrafficController
./TrafficController
```

## Option 3: Direct Compilation (Windows - PowerShell)

```powershell
cd smart-traffic-controller
g++ -std=c++11 -I. src/*.cpp -o TrafficController.exe
.\TrafficController.exe
```

## Option 4: Visual Studio (Windows)

```bash
# In Developer Command Prompt
cd smart-traffic-controller
cl /std:latest /I. src\*.cpp /o TrafficController.exe
TrafficController.exe
```

## Output

After running successfully, you should see:

```
╔══════════════════════════════════════════════════════╗
║   SMART LED TRAFFIC LIGHT CONTROLLER                ║
║   An Educational C++ Project for ECE Students       ║
║   Version 1.0 | License: MIT                        ║
╚══════════════════════════════════════════════════════╝

[INFO] Traffic Light initialized
[INFO] Vehicle Detector initialized
[INFO] Logger initialized - File: traffic_events.log
========================================
 TRAFFIC LIGHT CONTROLLER - MAIN MENU
========================================
1. Start/Resume Traffic Light Simulation
...
```

## Troubleshooting

| Issue | Solution |
|-------|----------|
| `g++: command not found` | Install MinGW or use WSL on Windows |
| CMake not found | Install CMake from cmake.org |
| Compilation errors | Ensure C++11 support: `g++ -std=c++11` |
| Permission denied | Make executable: `chmod +x TrafficController` |

## Clean Build

```bash
cd build
rm -rf *
cmake ..
make
```

## Generate Log Files

After running the program, check:
- `traffic_events.log` - All events logged to file
- Console output - Real-time status

