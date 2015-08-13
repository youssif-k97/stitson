#ifndef COMMAND_H
#define COMMAND_H

#define MINDISTANCE 4

#include "mthread.h"
#include "wheel.h"
#include "speaker.h"
#include "hcsr04.h"

class Command : public Thread
{
public:
    Command(Wheel* FL, Wheel* FR, Wheel* RL, Wheel* RR, Speaker* speaker, HCSR04* D);

    void setSpeed(float speed); // 0-1
    float getSpeed();
    
    void setMaxMovementTime(int millis);

    void goForward();
    void goBackward();
    void stop();
    void turnLeft();
    void turnRight();
    
    void play(Melody melody, int count); // -1 means until stop    

protected:
    bool loop();
    
private:
    void startTimer();

    float speed;
    int maxMovement;     
    long endTime;
    bool forward; 
    
    Wheel* FL;
    Wheel* FR;
    Wheel* RL;
    Wheel* RR;
    Speaker* speaker;
    HCSR04* D;
};

#endif  // COMMAND_H
