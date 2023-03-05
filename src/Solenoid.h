#include <Arduino.h>

class Solenoid
{
private:
    // Variables
    int _solenoidPin;
    bool _activeMode;
    
    // Functions
    

public:
    Solenoid(int solenoidPin, bool activeMode);
    void setup();
    // ~Solenoid();
    void on();
    void off();
};

Solenoid::Solenoid(int solenoidPin, bool activeMode = HIGH)
{
    _solenoidPin = solenoidPin;
    _activeMode = activeMode;

    setup();
}

// Solenoid::~Solenoid()
// {
// }

void Solenoid::setup()
{
    pinMode(_solenoidPin, OUTPUT);

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