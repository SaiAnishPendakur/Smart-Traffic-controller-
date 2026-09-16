# Smart-Traffic-controller-
"A beginner-friendly C++ traffic light simulation project"
# 🚦 Smart LED Traffic Light Controller
**A beginner-friendly C++ project for embedded systems and IoT education**

---

## 📋 Project Overview

A simulation of an intelligent traffic light controller system that:
- Controls RGB LED patterns for traffic lights (Red → Yellow → Green)
- Implements pedestrian button interrupt handling
- Tracks vehicle count and adjusts timing
- Provides real-time traffic statistics
- Logs events to a file

**Perfect for:** ECE/CSE students, IoT enthusiasts, embedded systems learners

---

## ✨ Features

✅ **Traffic Light Simulation**
- 3-color LED control (Red, Yellow, Green)
- Automatic light sequence with configurable timing
- Pedestrian crossing request handling

✅ **Vehicle Management**
- Vehicle detector that counts passing vehicles
- Adaptive timing based on traffic density
- Queue management

✅ **Logging & Statistics**
- Real-time event logging
- Traffic statistics analysis
- Cycle time tracking

✅ **User-Friendly Interface**
- Interactive menu system
- Real-time status display
- Manual override options

---

## 🛠️ Technology Stack

- **Language:** C++ (C++11 standard)
- **Build System:** CMake / Make
- **Platform:** Cross-platform (Windows, Linux, macOS)
- **Dependencies:** None (pure C++ Standard Library)

---

## 📁 Project Structure

```
smart-traffic-controller/
├── README.md                 # This file
├── CMakeLists.txt           # Build configuration
├── src/
│   ├── main.cpp             # Entry point
│   ├── TrafficLight.cpp      # Traffic light logic
│   ├── VehicleDetector.cpp   # Vehicle detection
│   └── Logger.cpp            # Event logging
├── include/
│   ├── TrafficLight.h
│   ├── VehicleDetector.h
│   └── Logger.h
├── docs/
│   ├── ARCHITECTURE.md       # System design
│   └── API.md               # Function documentation
├── examples/
│   └── usage_example.txt    # Sample outputs
└── LICENSE                   # MIT License
```

---

## 🚀 Quick Start

### Prerequisites
- C++ compiler (g++, clang, or MSVC)
- CMake 3.10+ (optional)
- Git

### Installation

**1. Clone the Repository**
```bash
git clone https://github.com/YOUR-USERNAME/smart-traffic-controller.git
cd smart-traffic-controller
```

**2. Build the Project**

**Option A: Using CMake**
```bash
mkdir build
cd build
cmake ..
make
./TrafficController
```

**Option B: Direct Compilation**
```bash
g++ -std=c++11 -I include src/*.cpp -o TrafficController
./TrafficController
```

**Option C: Windows (MSVC)**
```bash
g++ -std=c++11 -I include src/*.cpp -o TrafficController.exe
TrafficController.exe
```

### Run the Program
```bash
./TrafficController
```

---

## 📖 Usage

### Interactive Menu
```
===== TRAFFIC LIGHT CONTROLLER MENU =====
1. Start Traffic Light Simulation
2. Add Vehicle to Queue
3. Request Pedestrian Crossing
4. View Statistics
5. View Recent Events
6. Change Light Timing
7. Exit
Enter choice: 
```

### Example Session
```
$ ./TrafficController

Starting Traffic Light Controller...

[INFO] System initialized
[INFO] Current Light: RED (30 sec)

Menu:
1. Start Simulation
2. Add Vehicle
3. Request Crossing
...

Enter choice: 1
[INFO] Traffic light cycle started
[LIGHT] RED → (10 sec remaining)
[VEHICLE] Vehicle detected! Queue: 1
[LIGHT] GREEN → (25 sec)
[EVENT] Vehicle passed through intersection
```

---

## 💡 How It Works

### System Architecture

```
┌─────────────────────────────────────┐
│   Traffic Light Controller          │
├─────────────────────────────────────┤
│                                     │
│  ┌─────────────────────────────┐   │
│  │  Traffic Light Module       │   │
│  │  - RED (Stop - 30s)         │   │
│  │  - YELLOW (Caution - 5s)    │   │  
│  │  - GREEN (Go - 25s)         │   │
│  └─────────────────────────────┘   │
│            ↓ ↑                      │
│  ┌─────────────────────────────┐   │
│  │  Vehicle Detector           │   │
│  │  - Counts vehicles          │   │
│  │  - Adaptive timing          │   │
│  └─────────────────────────────┘   │
│            ↓ ↑                      │
│  ┌─────────────────────────────┐   │
│  │  Logger & Statistics        │   │
│  │  - Event tracking           │   │
│  │  - Performance analytics    │   │
│  └─────────────────────────────┘   │
│                                     │
└─────────────────────────────────────┘
```

### Traffic Light Sequence
1. **RED (30 seconds)** - Stop signal, vehicles queue up
2. **YELLOW (5 seconds)** - Caution signal, prepare to stop
3. **GREEN (25 seconds)** - Go signal, vehicles pass through
4. Repeat cycle...

### Adaptive Timing
- If vehicle queue > 5: GREEN extends to 35s
- If vehicle queue < 2: GREEN reduces to 15s
- Pedestrian request: Adds extra GREEN cycle

---

## 📚 Code Examples

### Basic Usage
```cpp
#include "TrafficLight.h"
#include "VehicleDetector.h"

int main() {
	TrafficLight light;
	VehicleDetector detector;

	// Start the system
	light.start();

	// Simulate vehicles
	detector.addVehicle();
	detector.addVehicle();

	// Get current state
	std::cout << light.getCurrentColor() << std::endl;

	return 0;
}
```

### Creating Custom Timing
```cpp
TrafficLight light;
light.setTiming(RED, 40);      // RED: 40 seconds
light.setTiming(YELLOW, 5);    // YELLOW: 5 seconds
light.setTiming(GREEN, 30);    // GREEN: 30 seconds
light.start();
```

---

## 🎓 Learning Outcomes

After completing this project, you'll understand:

✅ **C++ Fundamentals**
- Classes and objects
- Encapsulation and data hiding
- File I/O operations
- STL containers (vector, queue)

✅ **Software Design**
- Object-oriented programming (OOP)
- Module separation and clarity
- State machine pattern
- Design patterns

✅ **Embedded Systems Concepts**
- Real-time system simulation
- Event-driven programming
- Timer management
- Interrupt handling (simulated)

✅ **Practical Skills**
- Project structure and organization
- Build systems (CMake)
- Version control (Git)
- Documentation and commenting

---

## 📊 Sample Output

### Statistics Report
```
===== TRAFFIC STATISTICS =====
Total Vehicles Passed: 47
Total Cycles Completed: 8
Average Cycle Time: 62s
Peak Traffic Hour: 14:30-15:30
Queue Peak: 12 vehicles
Pedestrian Crossings: 3
System Uptime: 12 minutes 45 seconds
```

### Event Log
```
[14:23:45] [LIGHT] RED started
[14:23:50] [VEHICLE] Vehicle detected (Queue: 1)
[14:23:52] [VEHICLE] Vehicle detected (Queue: 2)
[14:24:15] [LIGHT] YELLOW started
[14:24:20] [LIGHT] GREEN started
[14:24:25] [EVENT] Vehicle passed through
[14:24:30] [EVENT] Vehicle passed through
```

---

## 🔧 Configuration

Edit `traffic_config.h` to customize:

```cpp
// Timing (in seconds)
#define RED_TIME 30
#define YELLOW_TIME 5
#define GREEN_TIME 25

// Thresholds
#define QUEUE_THRESHOLD_HIGH 5
#define QUEUE_THRESHOLD_LOW 2

// Extension times
#define GREEN_EXTENSION_TIME 10
```

---

## 🐛 Troubleshooting

| Issue | Solution |
|-------|----------|
| Compilation error | Ensure C++11 support: `g++ -std=c++11` |
| No log file created | Check write permissions in current directory |
| Timing seems off | Verify system clock and timer implementation |
| Linked list issues | Ensure proper memory management (no leaks) |

---

## 🚀 Enhancements & Future Work

**Tier 1: Basic Enhancements**
- [ ] Add emergency vehicle override
- [ ] Implement rush hour mode
- [ ] Add weather-based adjustments

**Tier 2: Advanced Features**
- [ ] Multi-intersection coordination
- [ ] Machine learning for traffic prediction
- [ ] Mobile app integration (via REST API)

**Tier 3: Hardware Integration**
- [ ] Connect to actual traffic sensors
- [ ] Control real LED lights (Arduino/Raspberry Pi)
- [ ] IoT cloud integration

---

## 👥 Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

---

## 📄 License

This project is licensed under the **MIT License** - see LICENSE file for details.

---

## 📞 Contact & Support

- **Author:** SAI ANISH A PENDAKUR
- **Email:** anishpendakur008@gmail.com
- **GitHub:** [SaiAnishPendakur](https://github.com/SaiAnishPendakur)

**Questions?** Open an issue on GitHub!

---

## 🎯 Beginner Tips

1. **Understand the Code First**
   - Read through files before running
   - Understand traffic light logic

2. **Modify and Experiment**
   - Change timing values
   - Add new features
   - Test different scenarios

3. **Learn by Building**
   - Extend with new features
   - Create your variation
   - Document your changes
