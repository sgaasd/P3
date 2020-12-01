#pragma once
#include "arduino.h"
#include <math.h>

#define pi 3.14159265359

 
class Dynamixelclass
{
private:
    HardwareSerial *DynamixelSerial;
    
    int8_t directionPIN;
    unsigned char ReturnPacket[20];

    //void clearSerialBuffer();
    void sendPacket(unsigned char *arr, int arrSIZE);
    unsigned char* sendNreadPacket(unsigned char *arr, int arrSIZE);
    unsigned short update_crc(unsigned char *data_blk_ptr, unsigned short data_blk_size);
    //double atan2(double numerator, double denominator);
    
    

public:
   // Dynamixel(/* args */);
 //   virtual ~Dynamixel();
    void clearSerialBuffer();
    void begin(HardwareSerial &Serial, uint32_t baudRate, int8_t directionPINOUT);
    unsigned char ping(unsigned char MOTOR_ID);
    short degreesToBits(float degrees);
    double rad2deg(double rad);
    double deg2rad(double deg);

    void setEnableTorque(unsigned char MOTOR_ID, unsigned char setVal, unsigned char setIntruction);
    void setPosition(unsigned char MOTOR_ID, signed short setVal, unsigned char setIntruction);
    void setPositionDegree(unsigned char MOTOR_ID, float setVal, unsigned char setIntruction);
    void setOperationMode(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    void setAction(unsigned char MOTOR_ID);
    void setPWM(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    void setVelocity(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    void setGain(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction, char setControllerGain);
    void setAccelerationProfile(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    void setVelocityProfile(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    void setStatusReturnLevel(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    void setMaxPosition(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    void setMinPosition(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    
    
    
    int32_t getPosition(unsigned char MOTOR_ID);
    float getPositionDegree(unsigned char MOTOR_ID);
    int32_t getVelocity(unsigned char MOTOR_ID);
    int32_t getPWM(unsigned char MOTOR_ID);
    int32_t getGain(unsigned char MOTOR_ID, char setControllerGain);
    int32_t getMovingstatus(unsigned char MOTOR_ID);
    bool getMoving(unsigned char MOTOR_ID);

    void inverseKinematics(double x, double y, double z);




};
//constructor
//Dynamixel::Dynamixel()
//{
//}
//Destructor
//Dynamixel::~Dynamixel()
//{
//}
