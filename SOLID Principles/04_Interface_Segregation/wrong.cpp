#include <iostream>
#include <stdexcept>

class SmartDevice {
public:
    virtual ~SmartDevice() = default;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

    virtual void setTemperature(int degrees) = 0;
    virtual void recordVideo() = 0;
    virtual void playMusic() = 0;
};

class SmartLight : public SmartDevice {
public:
    void turnOn() override {
        std::cout << "Light is on\n";
    }

    void turnOff() override {
        std::cout << "Light is off\n";
    }

    void setTemperature(int degrees) override {
        throw std::runtime_error("SmartLight cannot set temperature");
    }

    void recordVideo() override {
        throw std::runtime_error("SmartLight cannot record video");
    }

    void playMusic() override {
        throw std::runtime_error("SmartLight cannot play music");
    }
};

class SmartThermostat : public SmartDevice {
public:
    void turnOn() override {
        std::cout << "Thermostat is on\n";
    }

    void turnOff() override {
        std::cout << "Thermostat is off\n";
    }

    void setTemperature(int degrees) override {
        std::cout << "Temperature set to " << degrees << " degrees\n";
    }

    void recordVideo() override {
        throw std::runtime_error("SmartThermostat cannot record video");
    }

    void playMusic() override {
        throw std::runtime_error("SmartThermostat cannot play music");
    }
};

class SmartSpeaker : public SmartDevice {
public:
    void turnOn() override {
        std::cout << "Speaker is on\n";
    }

    void turnOff() override {
        std::cout << "Speaker is off\n";
    }

    void setTemperature(int degrees) override {
        throw std::runtime_error("SmartSpeaker cannot set temperature");
    }

    void recordVideo() override {
        throw std::runtime_error("SmartSpeaker cannot record video");
    }

    void playMusic() override {
        std::cout << "Playing music\n";
    }
};

void startDevice(SmartDevice& device) {
    device.turnOn();
}

void changeTemperature(SmartDevice& device, int degrees) {
    device.setTemperature(degrees);
}

int main() {
    SmartLight light;
    SmartThermostat thermostat;
    SmartSpeaker speaker;

    startDevice(light);
    startDevice(thermostat);
    startDevice(speaker);

    changeTemperature(thermostat, 22); // OK

    try {
        changeTemperature(light, 22);  // Runtime error
    } catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << '\n';
    }

    return 0;
}
