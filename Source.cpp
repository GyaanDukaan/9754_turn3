#include <iostream>
#include <cassert>
#include <memory>
#include <utility>

// Base class for electronic device control using CRTP
template <typename Derived>
class ElectronicDeviceControl {
public:
    // Turn on the device
    void turnOn() {
        static_cast<Derived*>(this)->doTurnOn();
    }

    // Turn off the device
    void turnOff() {
        static_cast<Derived*>(this)->doTurnOff();
    }

    virtual ~ElectronicDeviceControl() {}
};

// LightControl class
class LightControl : public ElectronicDeviceControl<LightControl> {
private:
    bool isOn;

public:
    LightControl() : isOn(false) {}

    // Turn on the light and set its state to ON
    void doTurnOn() {
        isOn = true;
        std::cout << "Light is ON" << std::endl;
    }

    // Turn off the light and set its state to OFF
    void doTurnOff() {
        isOn = false;
        std::cout << "Light is OFF" << std::endl;
    }

    bool isLightOn() const {
        return isOn;
    }

    // Rule of Five: Ensures proper copy/move semantics
    LightControl(const LightControl& other) : isOn(other.isOn) {}
    LightControl& operator=(const LightControl& other) {
        if (this != &other) {
            isOn = other.isOn;
        }
        return *this;
    }
    LightControl(LightControl&& other) noexcept : isOn(other.isOn) {
        other.isOn = false;
    }
    LightControl& operator=(LightControl&& other) noexcept {
        if (this != &other) {
            isOn = other.isOn;
            other.isOn = false;
        }
        return *this;
    }
    ~LightControl() = default;
};

// ThermostatControl class
class ThermostatControl : public ElectronicDeviceControl<ThermostatControl> {
private:
    bool isOn;
    int temperature;

public:
    ThermostatControl() : isOn(false), temperature(20) {}

    // Turn on the thermostat and set its state to ON
    void doTurnOn() {
        isOn = true;
        std::cout << "Thermostat is ON" << std::endl;
    }

    // Turn off the thermostat and set its state to OFF
    void doTurnOff() {
        isOn = false;
        std::cout << "Thermostat is OFF" << std::endl;
    }

    // Set the temperature, ensuring it's within valid range and the thermostat is on
    void setTemperature(int temp) {
        if (isOn && temp >= 10 && temp <= 30) {
            temperature = temp;
            std::cout << "Thermostat temperature set to: " << temp << std::endl;
        }
        else if (!isOn) {
            std::cout << "Cannot set temperature, thermostat is off." << std::endl;
        }
        else {
            std::cout << "Invalid temperature. Temperature must be between 10 and 30." << std::endl;
        }
    }

    int getTemperature() const {
        return temperature;
    }

    // Rule of Five: Ensures proper copy/move semantics
    ThermostatControl(const ThermostatControl& other) : isOn(other.isOn), temperature(other.temperature) {}
    ThermostatControl& operator=(const ThermostatControl& other) {
        if (this != &other) {
            isOn = other.isOn;
            temperature = other.temperature;
        }
        return *this;
    }
    ThermostatControl(ThermostatControl&& other) noexcept : isOn(other.isOn), temperature(other.temperature) {
        other.isOn = false;
        other.temperature = 0;
    }
    ThermostatControl& operator=(ThermostatControl&& other) noexcept {
        if (this != &other) {
            isOn = other.isOn;
            temperature = other.temperature;
            other.isOn = false;
            other.temperature = 0;
        }
        return *this;
    }
    ~ThermostatControl() = default;
};

// SmartLockControl class
class SmartLockControl : public ElectronicDeviceControl<SmartLockControl> {
private:
    bool isLocked;

public:
    SmartLockControl() : isLocked(true) {}

    // Turn on the smart lock and set it to an unlocked state
    void doTurnOn() {
        isLocked = false;
        std::cout << "Smart Lock is UNLOCKED" << std::endl;
    }

    // Turn off the smart lock and set it to a locked state
    void doTurnOff() {
        isLocked = true;
        std::cout << "Smart Lock is LOCKED" << std::endl;
    }

    // Getter method renamed to avoid conflict with the member variable
    bool getLockStatus() const {
        return isLocked;
    }

    // Rule of Five: Ensures proper copy/move semantics
    SmartLockControl(const SmartLockControl& other) : isLocked(other.isLocked) {}
    SmartLockControl& operator=(const SmartLockControl& other) {
        if (this != &other) {
            isLocked = other.isLocked;
        }
        return *this;
    }
    SmartLockControl(SmartLockControl&& other) noexcept : isLocked(other.isLocked) {
        other.isLocked = true;
    }
    SmartLockControl& operator=(SmartLockControl&& other) noexcept {
        if (this != &other) {
            isLocked = other.isLocked;
            other.isLocked = true;
        }
        return *this;
    }
    ~SmartLockControl() = default;
};

// GarageDoorControl class
class GarageDoorControl : public ElectronicDeviceControl<GarageDoorControl> {
private:
    bool isOpen;

public:
    GarageDoorControl() : isOpen(false) {}

    // Turn on the garage door and set it to an open state
    void doTurnOn() {
        isOpen = true;
        std::cout << "Garage Door is OPEN" << std::endl;
    }

    // Turn off the garage door and set it to a closed state
    void doTurnOff() {
        isOpen = false;
        std::cout << "Garage Door is CLOSED" << std::endl;
    }

    // Getter for open status
    bool getIsOpen() const { // Renamed to avoid conflict
        return isOpen;
    }

    // Rule of Five: Ensures proper copy/move semantics
    GarageDoorControl(const GarageDoorControl& other) : isOpen(other.isOpen) {}
    GarageDoorControl& operator=(const GarageDoorControl& other) {
        if (this != &other) {
            isOpen = other.isOpen;
        }
        return *this;
    }
    GarageDoorControl(GarageDoorControl&& other) noexcept : isOpen(other.isOpen) {
        other.isOpen = false;
    }
    GarageDoorControl& operator=(GarageDoorControl&& other) noexcept {
        if (this != &other) {
            isOpen = other.isOpen;
            other.isOpen = false;
        }
        return *this;
    }
    ~GarageDoorControl() = default;
};

// Test cases using assert
void runTests() {
    // LightControl tests
    LightControl light;
    assert(!light.isLightOn());

    light.turnOn();
    assert(light.isLightOn());

    light.turnOff();
    assert(!light.isLightOn());

    // ThermostatControl tests
    ThermostatControl thermostat;
    assert(thermostat.getTemperature() == 20);

    thermostat.setTemperature(25);
    assert(thermostat.getTemperature() == 25);

    thermostat.turnOff();
    thermostat.setTemperature(30);  // Should not change temperature since it's off
    assert(thermostat.getTemperature() == 25);

    // SmartLockControl tests
    SmartLockControl lock;
    assert(lock.getLockStatus() == true);

    lock.turnOn();
    assert(!lock.getLockStatus());

    lock.turnOff();
    assert(lock.getLockStatus());

    // GarageDoorControl tests
    GarageDoorControl garageDoor;
    assert(!garageDoor.getIsOpen());

    garageDoor.turnOn();
    assert(garageDoor.getIsOpen());

    garageDoor.turnOff();
    assert(!garageDoor.getIsOpen());
}

// Main function to run the tests
int main() {
    runTests();
    return 0;
}
