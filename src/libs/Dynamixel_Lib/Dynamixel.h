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

    void setEnableTorque(unsigned char MOTOR_ID, unsigned char setVal, unsigned char setIntruction);
    void setPosition(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    void setOperationMode(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    void setAction(unsigned char MOTOR_ID);
    void setPWM(unsigned char MOTOR_ID, unsigned short setVal, unsigned char setIntruction);
    
    int32_t getPosition(unsigned char MOTOR_ID);
    int32_t getVelocity(unsigned char MOTOR_ID);
    int32_t getPWM(unsigned char MOTOR_ID);

    




};
//constructor
//Dynamixel::Dynamixel()
//{
//}
//Destructor
//Dynamixel::~Dynamixel()
//{
//}
