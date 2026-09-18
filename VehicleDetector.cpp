#include "../include/VehicleDetector.h"
#include <iostream>

// Constructor
VehicleDetector::VehicleDetector() 
	: vehicleCount(0), 
	  maxQueueLength(0), 
	  totalVehiclesPassed(0) {
	std::cout << "[INFO] Vehicle Detector initialized" << std::endl;
}

// Add a vehicle to the queue
void VehicleDetector::addVehicle() {
	vehicleCount++;
	vehicleQueue.push(vehicleCount);
	std::cout << "[VEHICLE] Vehicle detected! Queue: " << vehicleQueue.size() << std::endl;

	// Track maximum queue length
	if ((int)vehicleQueue.size() > maxQueueLength) {
		maxQueueLength = vehicleQueue.size();
		std::cout << "[PEAK] New peak queue length: " << maxQueueLength << std::endl;
	}
}

// Remove a vehicle (passed through intersection)
void VehicleDetector::removeVehicle() {
	if (!vehicleQueue.empty()) {
		vehicleQueue.pop();
		totalVehiclesPassed++;
		std::cout << "[EVENT] Vehicle passed through intersection" << std::endl;
		std::cout << "[QUEUE] Remaining vehicles: " << vehicleQueue.size() << std::endl;
	}
}

// Get current queue length
int VehicleDetector::getQueueLength() const {
	return vehicleQueue.size();
}

// Get total vehicle count
int VehicleDetector::getVehicleCount() const {
	return vehicleCount;
}

// Get total vehicles that have passed
int VehicleDetector::getTotalVehiclesPassed() const {
	return totalVehiclesPassed;
}

// Check if traffic is at peak
bool VehicleDetector::isPeakTraffic() const {
	return vehicleQueue.size() >= 5;
}

// Destructor
VehicleDetector::~VehicleDetector() {
	std::cout << "[INFO] Vehicle Detector destroyed" << std::endl;
	std::cout << "[SUMMARY] Total vehicles: " << vehicleCount << std::endl;
	std::cout << "[SUMMARY] Vehicles passed: " << totalVehiclesPassed << std::endl;
}
