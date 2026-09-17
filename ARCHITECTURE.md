# System Architecture & Design

## Overview

The Smart Traffic Light Controller is built using **Object-Oriented Programming (OOP)** principles with clear separation of concerns.

### System Architecture Diagram

```
╔═══════════════════════════════════════════════════════════════════╗
║                    SMART TRAFFIC CONTROLLER                       ║
║                     (main.cpp - Entry Point)                      ║
╠═══════════════════════════════════════════════════════════════════╣
║                                                                   ║
║  ┌──────────────────────┐  ┌──────────────────────┐  ┌─────────┐ ║
║  │  TrafficLight        │  │  VehicleDetector     │  │ Logger  │ ║
║  │  ================    │  │  ================    │  │ ======= │ ║
║  │                      │  │                      │  │         │ ║
║  │ • currentColor       │  │ • vehicleQueue       │  │ • Events│ ║
║  │ • redTime (30s)      │  │ • vehicleCount       │  │ • Logs  │ ║
║  │ • yellowTime (5s)    │  │ • maxQueueLength     │  │ • File  │ ║
║  │ • greenTime (25s)    │  │ • totalPassed        │  │ • Stats │ ║
║  │ • cycleCount         │  │                      │  │         │ ║
║  │                      │  │ METHODS:             │  │ METHODS:│ ║
║  │ METHODS:             │  │ • addVehicle()       │  │ • log   │ ║
║  │ • start()            │  │ • removeVehicle()    │  │ • save  │ ║
║  │ • stop()             │  │ • getQueueLength()   │  │ • display
║  │ • nextColor()        │  │ • isPeakTraffic()    │  │         │ ║
║  │ • setTiming()        │  │ • getTotalPassed()   │  │         │ ║
║  │                      │  │                      │  │         │ ║
║  └──────────┬───────────┘  └──────────┬───────────┘  └────┬────┘ ║
║             │                         │                    │      ║
║             │         INTERACT        │                    │      ║
║             └──────────┬──────────────┬────────────────────┘      ║
║                        │              │                          ║
║                        ↓              ↓                          ║
║            ┌───────────────────────────────────┐                ║
║            │  INTERACTIVE MENU SYSTEM          │                ║
║            │  ├─ 1. Start Simulation            │                ║
║            │  ├─ 2. Add Vehicle                 │                ║
║            │  ├─ 3. Pedestrian Request          │                ║
║            │  ├─ 4. View Statistics             │                ║
║            │  ├─ 5. View Events                 │                ║
║            │  ├─ 6. Change Timing               │                ║
║            │  └─ 7. Exit                        │                ║
║            └───────────────────────────────────┘                ║
║                                                                   ║
╚═══════════════════════════════════════════════════════════════════╝
```

## Component Design

### 1. TrafficLight Class

**Purpose:** Manages traffic light states and timing

**Key Features:**
- State management (RED, YELLOW, GREEN)
- Configurable timing for each color
- Cycle counting
- Timestamp tracking

**State Machine:**
```
	┌─────────┐
	│   RED   │
	│  (30s)  │
	└────┬────┘
		 │ nextColor()
		 ↓
	┌──────────┐
	│  GREEN   │
	│  (25s)   │
	└────┬─────┘
		 │ nextColor()
		 ↓
	┌──────────┐
	│  YELLOW  │
	│   (5s)   │
	└────┬─────┘
		 │ nextColor()
		 ↓
	   START
```

**Public Methods:**
```cpp
void start()                    // Start the light system
void stop()                     // Stop the system
void nextColor()                // Transition to next color
std::string getCurrentColorName() // Get color as string
int getRemainingTime()          // Get seconds remaining
void setTiming(LightColor, int) // Set custom timing
```

### 2. VehicleDetector Class

**Purpose:** Manages vehicle detection and queue

**Data Structures:**
- `vehicleQueue` (std::queue<int>) - FIFO vehicle queue
- `vehicleCount` (int) - Total vehicles detected
- `maxQueueLength` (int) - Peak queue size

**Queue Operations:**
```
Add Vehicle (enqueue)
	↓
Check if Peak Traffic
	↓
Remove Vehicle (dequeue) on GREEN
	↓
Update Statistics
```

**Public Methods:**
```cpp
void addVehicle()               // Add vehicle to queue
void removeVehicle()             // Remove vehicle (passed through)
int getQueueLength()             // Get current queue size
int getTotalVehiclesPassed()     // Get total passed vehicles
bool isPeakTraffic()             // Check if queue >= 5
```

### 3. Logger Class

**Purpose:** Event logging and file management

**Log Format:**
```
[HH:MM:SS] [EVENT_TYPE] Message
Example:
[14:23:45] [VEHICLE] Vehicle detected at intersection
[14:23:50] [LIGHT] Light changed to GREEN for 25 seconds
```

**Features:**
- Timestamped events
- File I/O with auto-flush
- In-memory event buffer
- Statistics logging

**Public Methods:**
```cpp
void logEvent(const std::string& event)
void logVehicleDetected(int queueLength)
void logLightChange(const std::string& color, int duration)
void logStatistics(int vehicles, int cycles, double avgTime)
void displayLog()                // Print to console
void saveToFile()                // Flush to file
```

## Data Flow

```
User Input
	│
	↓
┌─────────────────────────────────┐
│  Process Menu Selection         │
├─────────────────────────────────┤
│ 1. Add vehicles → VehicleDetector
│ 2. Change timing → TrafficLight
│ 3. Get stats → Extract from all
│ 4. View logs → Logger
└─────────────────────────────────┘
	│
	↓
π Update Internal State
	│
	↓
┌─────────────────────────────────┐
│  Execute Action                 │
├─────────────────────────────────┤
│ - Change light color
│ - Process queue
│ - Adapt timing
│ - Log event
└─────────────────────────────────┘
	│
	↓
Display Output & Logged Events
```

## Simulation Logic

**Main Loop (runSimulation function):**
```cpp
while (simulationTime < 60) {
	// 1. Display status
	// 2. Random vehicle arrivals (every 3s)
	// 3. Process GREEN state (remove vehicles)
	// 4. Transition colors (every 10s)
	// 5. Sleep 1 second
	// 6. Increment timer
}
```

**Timing Sequence:**
```
Time: 0-10s   → RED light, vehicles queue up
Time: 10-35s  → GREEN light, vehicles pass
Time: 35-40s  → YELLOW light, caution
Time: 40-70s  → RED light (next cycle)
```

## Memory Management

- **Stack Allocation:** All class objects created on stack
- **Automatic Cleanup:** Destructors called at scope exit
- **No Memory Leaks:** No dynamic allocation (new/delete)
- **Queue Management:** std::queue handles auto deletion

## Design Patterns Used

### 1. State Pattern
Traffic light implements finite state machine (FSM) for color transitions

### 2. Producer-Consumer Pattern
Vehicles are produced (detected) and consumed (passed through)

### 3. Logger Pattern
Separation of concerns: logging independent of business logic

### 4. Configuration Pattern
Timing values can be changed at runtime via setTiming()

## Performance Characteristics

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Add Vehicle | O(1) | O(n) |
| Remove Vehicle | O(1) | O(1) |
| Get Queue Length | O(1) | O(1) |
| Log Event | O(n) | O(n) |
| Change Timing | O(1) | O(1) |

Where n = number of logged events

## Extensibility

The design allows easy additions:

```cpp
// Add new light color
enum LightColor { RED, YELLOW, GREEN, FLASHING_YELLOW };

// Add event types
void Logger::logPedestrianRequest() { ... }
void Logger::logEmergencyVehicle() { ... }

// Add detector features
bool VehicleDetector::isEmergencyVehicle() { ... }
void VehicleDetector::prioritizeQueue() { ... }
```

## Testing Recommendations

1. **Unit Tests:** Test individual classes in isolation
2. **Integration Tests:** Test class interactions
3. **Simulation Tests:** Verify entire workflow
4. **Edge Cases:** Empty queue, max vehicles, timing edge cases

