#include "../include/TrafficLight.h"
#include <iostream>
#include <iomanip>

// Constructor - Initialize with default timing
TrafficLight::TrafficLight() 
	: currentColor(RED), 
	  redTime(30), 
	  yellowTime(5), 
	  greenTime(25), 
	  cycleCount(0), 
	  isRunning(false) {
	std::cout << "[INFO] Traffic Light initialized" << std::endl;
	std::cout << "[CONFIG] RED: " << redTime << "s, YELLOW: " << yellowTime 
			  << "s, GREEN: " << greenTime << "s" << std::endl;
}

// Start the traffic light system
void TrafficLight::start() {
	isRunning = true;
	startTime = std::chrono::system_clock::now();
	std::cout << "[INFO] Traffic light started" << std::endl;
	std::cout << "[LIGHT] RED → (" << redTime << " sec)" << std::endl;
}

// Stop the traffic light system
void TrafficLight::stop() {
	isRunning = false;
	std::cout << "[INFO] Traffic light stopped" << std::endl;
	std::cout << "[STATS] Total cycles completed: " << cycleCount << std::endl;
}

// Transition to next light color
void TrafficLight::nextColor() {
	if (!isRunning) return;

	switch (currentColor) {
		case RED:
			currentColor = GREEN;
			std::cout << "[LIGHT] GREEN → (" << greenTime << " sec)" << std::endl;
			break;

		case GREEN:
			currentColor = YELLOW;
			std::cout << "[LIGHT] YELLOW → (" << yellowTime << " sec)" << std::endl;
			break;

		case YELLOW:
			currentColor = RED;
			cycleCount++;
			std::cout << "[LIGHT] RED → (" << redTime << " sec)" << std::endl;
			std::cout << "[CYCLE] Cycle #" << cycleCount << " completed" << std::endl;
			break;
	}

	startTime = std::chrono::system_clock::now();
}

// Get current color name as string
std::string TrafficLight::getCurrentColorName() const {
	switch (currentColor) {
		case RED:    return "RED";
		case YELLOW: return "YELLOW";
		case GREEN:  return "GREEN";
		default:     return "UNKNOWN";
	}
}

// Get remaining time for current color
int TrafficLight::getRemainingTime() const {
	if (!isRunning) return 0;

	auto elapsed = std::chrono::system_clock::now() - startTime;
	int seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();

	int totalTime;
	switch (currentColor) {
		case RED:    totalTime = redTime; break;
		case YELLOW: totalTime = yellowTime; break;
		case GREEN:  totalTime = greenTime; break;
		default:     totalTime = 0;
	}

	return std::max(0, totalTime - seconds);
}

// Set custom timing for a color
void TrafficLight::setTiming(LightColor color, int seconds) {
	if (seconds <= 0) {
		std::cerr << "[ERROR] Invalid timing value" << std::endl;
		return;
	}

	switch (color) {
		case RED:
			redTime = seconds;
			std::cout << "[CONFIG] RED time set to " << seconds << " seconds" << std::endl;
			break;

		case YELLOW:
			yellowTime = seconds;
			std::cout << "[CONFIG] YELLOW time set to " << seconds << " seconds" << std::endl;
			break;

		case GREEN:
			greenTime = seconds;
			std::cout << "[CONFIG] GREEN time set to " << seconds << " seconds" << std::endl;
			break;
	}
}

// Destructor
TrafficLight::~TrafficLight() {
	if (isRunning) {
		stop();
	}
	std::cout << "[INFO] Traffic Light destroyed" << std::endl;
}
