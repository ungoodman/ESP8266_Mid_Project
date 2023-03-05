#include <Arduino.h>

#define DEFAULT_MAX_MOISTURE_PERCENT 70
#define DEFAULT_MIN_MOISTURE_PERCENT 40

// #define ESP8266_VERSION
#ifndef ESP8266_VERSION
#define ANALOG_MAX_BIT 4096
#else 
#define ANALOG_MAX_BIT 1024
#endif

class MoistureSensor
{
private:
    /* data */
    int _pin;
    int _maxPercentLimit;
    int _minPercentLimit;
    int _moistureValue;
    bool _isDry;

    void setup();
    int getValue();
public:
    MoistureSensor(int pin, int maxPercentLimit, int minPercentLimit);
    // ~MoistureSensor();
    
    float getPercent();
    bool wetLimitReach();
    bool dryLimitReach();
};

MoistureSensor::MoistureSensor(int pin, int maxPercentLimit = DEFAULT_MAX_MOISTURE_PERCENT, int minPercentLimit = DEFAULT_MIN_MOISTURE_PERCENT)
{
    _pin = pin;
    _maxPercentLimit = maxPercentLimit;
    _minPercentLimit = minPercentLimit;

    setup();
}

// MoistureSensor::~MoistureSensor()
// {
// }

// Public
float MoistureSensor::getPercent() {
    return ((ANALOG_MAX_BIT - getValue()) * 100) / ANALOG_MAX_BIT;
}

bool MoistureSensor::dryLimitReach() {
    if (getPercent() <= _minPercentLimit && _isDry != true)
        _isDry = true;
    return _isDry;
}

bool MoistureSensor::wetLimitReach() {
    if (getPercent() >= _maxPercentLimit && _isDry == true)
        _isDry = false;
    return !_isDry;
}

// Private
void MoistureSensor::setup() {
    pinMode(_pin, INPUT);
}

int MoistureSensor::getValue() {
    return analogRead(_pin);
}