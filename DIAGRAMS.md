# 📐 ASCII Diagrams & Visual Documentation

**Detailed visual representations of the Smart Traffic Light Controller system**

---

## 1. Complete System Architecture

```
╔═══════════════════════════════════════════════════════════════════╗
║                    SMART TRAFFIC CONTROLLER                       ║
║                          OVERVIEW                                 ║
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

---

## 2. Traffic Light State Machine (Detailed)

```
					╔════════════════════════════╗
					║  TRAFFIC LIGHT STATE FLOW  ║
					╚═════════════╤══════════════╝
								  │
						START → nextColor()
								  │
				 ┌────────────────▼─────────────────┐
				 │                                  │
	┌────────────┴──────────────┐        ┌──────────┴────────────┐
	│                           │        │                       │
	▼                           │        │                       ▼
╔═════════════════╗             │        │              ╔═════════════════╗
║      RED        ║             │        │              ║     SYSTEM      ║
║  (30 seconds)   ║             │        │              ║    RUNNING      ║
║                 ║             │        │              ║                 ║
║ Vehicles Queue  ║             │        │              ║ Simulate until  ║
║ Up Here         ║             │        │              ║ user stops      ║
╚═════╤═══════════╝             │        │              ╚═════════════════╝
	  │                         │        │                       │
	  │                         │        │                       │
	  │ ← Timing Complete       │        │                       │
	  │ ← Call nextColor()      │        │                       │
	  │                         │        │                       │
	┌─▼──────────────┐          │        │                ┌──────┴────────┐
	│                │          │        │                │               │
	▼                ▼          │        │                ▼               │
╔═════════════════╗  │          │        │            ╔═════════════════╗│
║     GREEN       │  │          │        │            │     CYCLE       ││
║ (25 seconds)    │  │          │        │            │    COUNTER      ││
║                 │  │          │        │            ║  Incremented    ││
║ Vehicles Pass   │  │          │        │            ║  Every    RED   ││
║ Through        │  │          │        │            ║  Cycle      │   ││
╚═════╤═══════════╝  │          │        │            ║         cycleCount++
	  │               │          │        │            ║                 ║
	  │               │          │        │            └─────┬───────────╝
	  │ nextColor()   │          │        │                  │
	  │               │          │        │                  │
	┌─▼───────────────┴──────────┘        │                  │
	│                                     │                  │
  ┌─▼──────────────┐                      │                  │
  │                │                      │                  │
  ▼                ▼                      │                  │
╔═════════════════╗                       │                  │
║     YELLOW      │                       │                  │
║  (5 seconds)    │                       │                  │
║                 │                       │                  │
║ Caution Signal  │                       │                  │
║ Prepare to Stop │                       │                  │
╚═════╤═══════════╝                       │                  │
	  │                                   │                  │
	  │ nextColor()                       │                  │
	  │                                   │                  │
	  └─────────────────┬─────────────────┴──────────────────┘
						│
				   Back to RED
				   Cycle Repeats
```

---

## 3. Vehicle Queue State Diagram

```
╔════════════════════════════════════════════════════════════╗
║           VEHICLE QUEUE MANAGEMENT FLOW                    ║
╚═══════════════╤═════════════════════════════════════════════╝
				│
				│ User Action: addVehicle()
				│
				│
	┌───────────▼────────────────┐
	│   NEW VEHICLE ARRIVED      │
	│   vehicleQueue.push(id)    │
	│   vehicleCount++           │
	└───────────┬────────────────┘
				│
				│ Check Peak Status
				│
	┌───────────▼────────────────────────┐
	│   Queue Length > 5?                │
	└───────┬──────────────────┬─────────┘
			│ YES              │ NO
	┌───────▼─────────┐   ┌────▼────────────┐
	│ isPeakTraffic   │   │ Normal Traffic   │
	│    = TRUE       │   │ isPeakTraffic    │
	│                 │   │    = FALSE       │
	│ Alert: PEAK! ⚠️  │   │                  │
	└────────┬────────┘   └────┬─────────────┘
			 │                 │
			 └────────┬────────┘
					  │
	   Update maxQueueLength if needed
					  │
	┌─────────────────▼────────────────────────┐
	│    QUEUE STATE:                          │
	│    Front: [1] [2] [3] [4] Back           │
	│    Length: 4                              │
	│    Peak Seen: 5                           │
	│    Status: Peak Traffic = YES             │
	└─────────────────┬────────────────────────┘
					  │
		   Light turns GREEN?
					  │
		 ┌────────────┴──────────┐
		 │                       │
	┌────▼──────┐        ┌───────▼──────┐
	│ YES ✓     │        │ NO ✗         │
	│           │        │              │
	│ removeVehicle()    │ WAIT         │
	│ vehicleQueue.pop() │ Vehicles stay│
	│ totalPassed++      │ in queue     │
	└────┬──────┘        └──────────────┘
		 │
	┌────▼────────────────────────────┐
	│ Queue After Pass:                │
	│ Front: [2] [3] [4] Back          │
	│ Length: 3                         │
	│ totalVehiclesPassed: 1            │
	└────┬────────────────────────────┘
		 │
	Continue processing or wait for RED


	╔═════════════════════════════════════════════════════════╗
	║          QUEUE VISUAL EXAMPLE (Multiple Cycles)        ║
	╠═════════════════════════════════════════════════════════╣
	║                                                         ║
	║ CYCLE 1: RED                                            ║
	║   Queue: [1] [2] [3] ──→ Length: 3                     ║
	║                                                         ║
	║ CYCLE 1: GREEN                                          ║
	║   Process: Vehicle 1 passes                             ║
	║   Queue: [2] [3] ──→ Length: 2                         ║
	║                                                         ║
	║ CYCLE 2: RED                                            ║
	║   New arrival: Vehicle 4                               ║
	║   Queue: [2] [3] [4] ──→ Length: 3                    ║
	║                                                         ║
	║ CYCLE 2: GREEN                                          ║
	║   Process: Vehicle 2 passes                             ║
	║   Queue: [3] [4] ──→ Length: 2                         ║
	║   Total Passed: 2                                       ║
	║                                                         ║
	║ And so on...                                            ║
	║                                                         ║
	╚═════════════════════════════════════════════════════════╝
```

---

## 4. Event Logging & File I/O

```
╔═══════════════════════════════════════════════════════════╗
║            LOGGING & FILE I/O PROCESS                     ║
╚═════════════╤═════════════════════════════════════════════╝
			  │
		 Event Occurs:
		 • Vehicle detected
		 • Light changed
		 • Statistics logged
			  │
	┌─────────▼─────────────┐
	│  Create Event String  │
	│  Add Timestamp        │
	│  Format Message       │
	└─────────┬─────────────┘
			  │
	┌─────────▼──────────────────────────┐
	│  log Event:                        │
	│  "[14:23:45] [VEHICLE] Detected"   │
	│  "[14:23:50] [LIGHT] GREEN"        │
	│  "[14:24:00] [STATS] Data..."      │
	└─────────┬──────────────────────────┘
			  │
		 ┌────┴────┐
		 │          │
	┌────▼────┐  ┌──▼──────────────┐
	│ Console │  │ File     .log    │
	│ Output  │  │ Write & Flush    │
	│ Display │  │ Persistent       │
	│ Immediate   │ Storage         │
	└────────┘  └──────────────────┘
			  │
		 Memory Buffer:
		 vector<string> events
			  │
		 User Request:
		 View Events?
			  │
	┌─────────▼──────────────────────┐
	│ Display Last N Events:          │
	│ ├ [HH:MM:SS] [TYPE] Message    │
	│ ├ [HH:MM:SS] [TYPE] Message    │
	│ ├ [HH:MM:SS] [TYPE] Message    │
	│ └ [HH:MM:SS] [TYPE] Message    │
	└─────────┬──────────────────────┘
			  │
	┌─────────▼──────────────────────┐
	│ On Program Exit:                │
	│ logger.saveToFile()             │
	│ │                               │
	│ └─ Flush all buffers            │
	│    Write final logs             │
	│    Close file gracefully        │
	│                                 │
	│ Result: Complete log saved in   │
	│ traffic_events.log              │
	└─────────────────────────────────┘
```

---

## 5. Timing & Simulation Loop

```
╔════════════════════════════════════════════════════════════╗
║              SIMULATION TIMING DIAGRAM                     ║
╠════════════════════════════════════════════════════════════╣
║                                                            ║
║ Time: 0s ─────── 10s ─────── 20s ─────── 30s ──────── 60s ║
║        │          │          │          │            │    ║
║  ┌─────▼──────────▼──────────▼──────────▼────────────▼─┐  ║
║  │                                                     │  ║
║  │  RED (30s)      GREEN (25s)    YELLOW (5s)  RED   │  ║
║  │  ─────────      ───────────    ──────────  ──────  │  ║
║  │      │              │              │        │     │  ║
║  │  Vehicles       Vehicles       Prepare  Cycle    │  ║
║  │  collect (1,2)  pass (1,2)     Stop 1   Count++   │  ║
║  │      │              │              │        │     │  ║
║  │  Q: [1,2]      Q: [empty]      Q: [  ]  Q: [3]    │  ║
║  │                                                     │  ║
║  └─────────────────────────────────────────────────────┘  ║
║        │          │          │          │            │    ║
║  0s   10s       25s        30s        35s           60s   ║
║                                                            ║
║  Every Second: Display status                             ║
║  ┌──────────────────────────────────┐                    ║
║  │[RED] 28s | Vehicles: 2 | Cycle: 0│                    ║
║  │[RED] 27s | Vehicles: 3 | Cycle: 0│                    ║
║  │[RED] 26s | Vehicles: 2 | Cycle: 0│                    ║
║  │[GREEN] 24s | Vehicles: 1 | Cycle: 0│                  ║
║  │[GREEN] 23s | Vehicles: 0 | Cycle: 0│                  ║
║  │[YELLOW] 4s | Vehicles: 0 | Cycle: 0│                  ║
║  │[RED] 29s | Vehicles: 1 | Cycle: 1│                    ║
║  └──────────────────────────────────┘                    ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝
```

---

## 6. Class Hierarchy & Relationships

```
						┌──────────────┐
						│   Logger     │
						│   (Utility)  │
						└──────┬───────┘
							   │
				   Logs all events from:
					   │          │
					   ▼          ▼
			  ┌──────────────┐  ┌─────────────────┐
			  │TrafficLight  │  │VehicleDetector  │
			  │              │  │                 │
			  │• Manages     │  │• Manages Queue  │
			  │  Light State │  │• Tracks Vehicles│
			  │• Timing      │  │• Statistics     │
			  │• Transitions │  │                 │
			  └──────┬───────┘  └────────┬────────┘
					 │                   │
					 └─────────┬─────────┘
							   │
						 Uses Both Classes
							   │
							   ▼
					  ┌─────────────────┐
					  │  main.cpp       │
					  │  (Application)  │
					  │                 │
					  │• Menu System    │
					  │• User Input     │
					  │• Simulation     │
					  │• Coordination   │
					  └─────────────────┘
							   │
						 Displays to
							   │
							   ▼
					  ┌─────────────────┐
					  │   Console/User  │
					  │   Interactive   │
					  └─────────────────┘
```

---

## 7. Data Flow During Simulation

```
╔════════════════════════════════════════════════════════════╗
║              DATA FLOW: SIMULATION CYCLE                   ║
╚═════════════╤══════════════════════════════════════════════╝
			  │
	┌─────────▼──────────────────┐
	│  START SIMULATION LOOP      │
	│  (60 seconds duration)      │
	└─────────┬──────────────────┘
			  │
	┌─────────▼──────────────────────────────┐
	│  EACH SECOND (while running):          │
	│                                        │
	│  1. Display Current Status              │
	│     trafficLight.getRemainingTime()    │
	│     detector.getQueueLength()           │
	│     trafficLight.getCycleCount()        │
	│                                        │
	└─────────┬──────────────────────────────┘
			  │
	┌─────────▼──────────────────┐
	│  EVERY 3 SECONDS:           │
	│  Simulate Vehicle Arrival   │
	│  detector.addVehicle()      │
	│  logger.logVehicleDetected()│
	└─────────┬──────────────────┘
			  │
	┌─────────▼──────────────────────────┐
	│  IF Light = GREEN:                 │
	│  Process Queue                      │
	│  if (queue > 0)                     │
	│    detector.removeVehicle()         │
	│    logger.logEvent("Passed")        │
	└─────────┬──────────────────────────┘
			  │
	┌─────────▼────────────────────────────┐
	│  EVERY 10 SECONDS:                  │
	│  Transition Light Color              │
	│  trafficLight.nextColor()            │
	│  logger.logLightChange()             │
	└─────────┬────────────────────────────┘
			  │
	┌─────────▼──────────────────┐
	│  SLEEP 1 SECOND            │
	│  this_thread::sleep_for()  │
	└─────────┬──────────────────┘
			  │
			  │ Time < 60 seconds?
			  │
		 YES ─┴─→ Continue Loop

		 NO ───→ END SIMULATION

	┌────────────────────────────────────┐
	│  AFTER SIMULATION:                 │
	│  Display Final Statistics:         │
	│  • Total Vehicles                  │
	│  • Vehicles Passed                 │
	│  • Peak Queue Length               │
	│  • Total Cycles                    │
	│  • All Events Logged               │
	└────────────────────────────────────┘
```

---

## 8. Memory & Object Lifecycle

```
╔═══════════════════════════════════════════════════════════╗
║            OBJECT CREATION & CLEANUP                      ║
╠═══════════════════════════════════════════════════════════╣
║                                                           ║
║ PROGRAM START                                             ║
║      │                                                    ║
║      ▼                                                    ║
║  ┌─────────────────────────────────────┐                ║
║  │ Stack Allocation:                   │                ║
║  │ • TrafficLight light            ────┼──┐             ║
║  │ • VehicleDetector detector      ────┼──┼──┐          ║
║  │ • Logger logger("log.txt")      ────┼──┼──┼──┐       ║
║  │                                 │  │  │  │       ║
║  └─────────────────────────────────┼──┼──┼──┼───┘       ║
║                                    │  │  │  │            ║
║                    OBJECTS READY;  │  │  │  │            ║
║                    CONSTRUCTORS    │  │  │  │            ║
║                    CALLED          │  │  │  │            ║
║                                    │  │  │  │            ║
║  ┌────────────────────────────────┴──┴──┴──┴───┐        ║
║  │ DURING RUNNING:                           │        ║
║  │ • trafficLight.start()                     │        ║
║  │ • detector.addVehicle() [many times]       │        ║
║  │ • logger.logEvent() [many times]           │        ║
║  │                                            │        ║
║  │ Memory Used:                               │        ║
║  │ • trafficLight: ~100 bytes                 │        ║
║  │ • detector: queue buffer grows             │        ║
║  │ • logger: eventLog vector grows            │        ║
║  └────────────────────────────────┬───────────┘        ║
║                                   │                    ║
║  ┌────────────────────────────────▼───────┐           ║
║  │ PROGRAM END (User selects Exit):       │           ║
║  │                                        │           ║
║  │ • trafficLight.~TrafficLight()         │           ║
║  │ • detector.~VehicleDetector()          │           ║
║  │ • logger.~Logger()                     │           ║
║  │                                        │           ║
║  │ DESTRUCTORS CALLED:                    │           ║
║  │ └─ Close log file                      │           ║
║  │ └─ Flush buffers                       │           ║
║  │ └─ Free memory                         │           ║
║  │ └─ Return resources                    │           ║
║  └────────────────────────────────────────┘           ║
║                                                           ║
║  PROGRAM TERMINATES                                      ║
║                                                           ║
╚═══════════════════════════════════════════════════════════╝
```

---

**All diagrams reference the actual code in src/*.cpp and show how components work together!**
