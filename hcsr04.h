#ifndef HCSR04_H
#define HCSR04_H

#include <NewPing.h>

class HCSR04 : public Thread
{
public:
    HCSR04(int triggerPin, int echoPin);
        
    long measure();

    void echoCheck();
    
protected:
    bool loop();
private:
    NewPing* sonar;
    long lastMeasureTime;
    int lastMeasure;
};

#endif  // HCSR04_H
