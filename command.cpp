#include "command.h"

Command::Command(Wheel* FL, Wheel* FR, Wheel* RL, Wheel* RR, Speaker* speaker, SonarNP* D, Light* light)
{
    this->FL = FL;
    this->FR = FR;
    this->RL = RL;
    this->RR = RR;
    this->speaker = speaker;
    this->D = D;
    this->light = light;
        
    this->speed = 0;
    this->maxMovement = 25;
    this->endTime = 0; // turn off timer
    this->forward = false;
}

void Command::play(Melody melody, int count)
{
    speaker->play(melody, count);  
}

void Command::mute()
{
    speaker->stop();  
}

void Command::lightOn()
{
    light->start();  
}

void Command::lightOff()
{
    light->stop();  
}

void Command::setSpeed(float speed)
{
    this->speed = speed;

    FL->setSpeed(speed);  
    FR->setSpeed(speed);    
    RL->setSpeed(speed);  
    RR->setSpeed(speed);    
}

float Command::getSpeed()
{
    return this->speed;  
}

void Command::setMaxMovementTime(int millis)
{
    this->maxMovement = millis; 
}

void Command::startTimer()
{
  this->endTime = millis() + this->maxMovement;
}

void Command::goForward()
{
    if(D->measure()< (MINDISTANCE * (1 + getSpeed() * 2))) return;

    forward = true;  

    FL->goForward();
    FR->goForward();    
    RL->goForward();
    RR->goForward();        
    this->startTimer();    
}

void Command::goBackward()
{ 
    forward = false;  
  
    FL->goBackward();
    FR->goBackward();    
    RL->goBackward();
    RR->goBackward();    
    this->startTimer();
}

void Command::stop()
{
    forward = false;  
    speed = 0;
    
    FL->stop();
    FR->stop();    
    RL->stop();
    RR->stop();
    this->endTime = 0; // turn off timer                
}

void Command::turnLeft()
{
    forward = false;  
    
    FL->stop();
    FR->goForward();    
    RL->stop();
    RR->goForward();
    this->startTimer();    
}

void Command::turnRight()
{
    forward = false;  
  
    FR->stop();
    FL->goForward();    
    RL->goForward();
    RR->stop();    
    this->startTimer();  
}

bool Command::loop()
{
    if(millis() > this->endTime)
    {
      this->stop();
    }  
    
    if(D->measure()< (MINDISTANCE * (1 + getSpeed() * 2)) && this->forward)
    {
      this->stop();
    }
    
    return true;    
}

