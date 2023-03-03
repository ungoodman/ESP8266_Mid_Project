#include <Arduino.h>

class Solenoid
{
private:
    // Variables
    int _solenoidPin;
    int _ledPin;
    bool _activeMode;
    
    // Functions
    void setup();

public:
    Solenoid(int solenoidPin, int ledPin);
    Solenoid(int solenoidPin, int ledPin, bool activeMode);
    // ~Solenoid();
    void on();
    void off();
};

Solenoid::Solenoid(int solenoidPin, int ledPin)
{
    Solenoid(solenoidPin, ledPin, HIGH);
}

Solenoid::Solenoid(int solenoidPin, int ledPin, bool activeMode)
{
    _solenoidPin = solenoidPin;
    _ledPin = ledPin;
    _activeMode = activeMode;

    setup();
}

// Solenoid::~Solenoid()
// {
// }

void Solenoid::setup()
{
    pinMode(_solenoidPin, OUTPUT);
    pinMode(_ledPin, OUTPUT);

    digitalWrite(_solenoidPin, !_activeMode);
}

void Solenoid::on()
{
    digitalWrite(_solenoidPin, _activeMode);
}

void Solenoid::off()
{
    digitalWrite(_solenoidPin, !_activeMode);
}