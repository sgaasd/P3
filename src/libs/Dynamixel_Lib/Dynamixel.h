#pragma once
#include "arduino.h"

 
class Dynamixelclass
{
private:
    HardwareSerial *DynamixelSerial;
    
    int8_t directionPIN;
    unsigned char ReturnPacket[20];

    void clearSerialBuffer();
    void sendPacket(unsigned char *arr, int arrSIZE);
    unsigned char* sendNreadPacket(unsigned char *arr, int arrSIZE);
    unsigned short update_crc(unsigned char *data_blk_ptr, unsigned short data_blk_size);
    
    
    


public:
   // Dynamixel(/* args */);
 //   virtual ~Dynamixel();

    void begin(HardwareSerial &Serial, uint32_t baudRate, int8_t directionPINOUT);
    unsigned char ping(unsigned char MOTOR_ID);
    void enableTorque(unsigned char MOTOR_ID, unsigned char setVal);
    void setPosition(unsigned char MOTOR_ID, unsigned short setVal);
    void operationMode(unsigned char MOTOR_ID, unsigned short setVal);
    
    int32_t getPosition(unsigned char MOTOR_ID);
    int32_t getVelocity(unsigned char MOTOR_ID);
    int32_t getPMW(unsigned char MOTOR_ID);

    




};
//constructor
//Dynamixel::Dynamixel()
//{
//}
//Destructor
//Dynamixel::~Dynamixel()
//{
//}
