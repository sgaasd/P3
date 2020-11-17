#pragma once
#include "arduino.h"

 
class Dynamixelclass
{
private:
    HardwareSerial *DynamixelSerial;
    unsigned short update_crc(unsigned char *data_blk_ptr, unsigned short data_blk_size);
    int8_t directionPIN;
    void clearSerialBuffer();
    //initialize the ReturnPacket with dynamic array size
    unsigned char ReturnPacket[20];

    struct 
    {
        unsigned char a,b,c,d,e,f;
    }modtaget;

    
    void sendPacket(unsigned char *arr, int arrSIZE);
    //void readPacket();


public:
   // Dynamixel(/* args */);
 //   virtual ~Dynamixel();

    void begin(HardwareSerial &Serial, uint32_t baudRate, int8_t directionPINOUT);
    void ping(unsigned char MOTOR_ID);
    void getPosition(unsigned char MOTOR_ID);
    void enableTorque(unsigned char MOTOR_ID, unsigned char setVal);
    void setPosition(unsigned char MOTOR_ID, unsigned short setVal);
    void operationMode(unsigned char MOTOR_ID, unsigned short setVal);
    unsigned char readPacket();




};
//constructor
//Dynamixel::Dynamixel()
//{
//}
//Destructor
//Dynamixel::~Dynamixel()
//{
//}
