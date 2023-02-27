#include <Arduino.h>

#define DEFAULT_MAX_MOISTURE_PERCENT 70
#define DEFAULT_MIN_MOISTURE_PERCENT 40

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
    return (1 - (getValue() / 1024)) * 100;
}

bool MoistureSensor::dryLimitReach() {
    if (_minPercentLimit > getPercent() && !_isDry)
        _isDry = true;
    return _isDry;
}

bool MoistureSensor::wetLimitReach() {
    if (_maxPercentLimit < getPercent() && _isDry)
        _isDry = false;
    return _isDry;
}

// Private
void MoistureSensor::setup() {
    pinMode(_pin, INPUT);
}

int MoistureSensor::getValue() {
    return analogRead(_pin);
}