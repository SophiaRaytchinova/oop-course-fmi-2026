#include <iostream>

class Switchable {
public:
    virtual ~Switchable() = default;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

class TemperatureControllable {
public:
    virtual ~TemperatureControllable() = default;

    virtual void setTemperature(int degrees) = 0;
};

class VideoRecordable {
public:
    virtual ~VideoRecordable() = default;

    virtual void recordVideo() = 0;
};

class MusicPlayable {
public:
    virtual ~MusicPlayable() = default;

    virtual void playMusic() = 0;
};

class SmartLight : public Switchable {
public:
    void turnOn() override {
        std::cout << "Light is on\n";
    }

    void turnOff() override {
        std::cout << "Light is off\n";
    }
};

class SmartThermostat : public Switchable, public TemperatureControllable {
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
};

class SecurityCamera : public Switchable, public VideoRecordable {
public:
    void turnOn() override {
        std::cout << "Camera is on\n";
    }

    void turnOff() override {
        std::cout << "Camera is off\n";
    }

    void recordVideo() override {
        std::cout << "Recording video\n";
    }
};

class SmartSpeaker : public Switchable, public MusicPlayable {
public:
    void turnOn() override {
        std::cout << "Speaker is on\n";
    }

    void turnOff() override {
        std::cout << "Speaker is off\n";
    }

    void playMusic() override {
        std::cout << "Playing music\n";
    }
};

void startDevice(Switchable& device) {
    device.turnOn();
}

void changeTemperature(TemperatureControllable& device, int degrees) {
    device.setTemperature(degrees);
}

void startRecording(VideoRecordable& device) {
    device.recordVideo();
}

void playSong(MusicPlayable& device) {
    device.playMusic();
}

int main() {
    SmartLight light;
    SmartThermostat thermostat;
    SecurityCamera camera;
    SmartSpeaker speaker;

    startDevice(light);
    startDevice(thermostat);
    startDevice(camera);
    startDevice(speaker);

    changeTemperature(thermostat, 22);
    startRecording(camera);
    playSong(speaker);

    // These lines won't compile, which is good:
    //
    // changeTemperature(light, 22);
    // startRecording(speaker);
    // playSong(thermostat);
    //

    return 0;
}
