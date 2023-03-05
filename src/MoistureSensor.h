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
    bool limitReachCheck(bool condition);
public:
    MoistureSensor(int pin, int maxPercentLimit, int minPercentLimit);
    // ~MoistureSensor();
    
    int getPercent();
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
int MoistureSensor::getPercent() {
    int percent = ((ANALOG_MAX_BIT - getValue()) * 100) / ANALOG_MAX_BIT;
    Serial.println("Percent: " + String(percent));
    return percent;
}

bool MoistureSensor::dryLimitReach() {
    return limitReachCheck(getPercent() <= _minPercentLimit && !_isDry);
}

bool MoistureSensor::wetLimitReach() {
    return limitReachCheck(getPercent() >= _maxPercentLimit && _isDry);
}

// Private
void MoistureSensor::setup() {
    pinMode(_pin, INPUT);
}

int MoistureSensor::getValue() {
    return analogRead(_pin);
}

bool MoistureSensor::limitReachCheck(bool condition) {
    if (condition){
        _isDry = !_isDry;
        return true;
    }
    return false;
}