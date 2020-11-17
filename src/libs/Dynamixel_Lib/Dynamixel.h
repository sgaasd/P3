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

    static const int returnArrSIZE = 20;
    unsigned char ReturnPacket[returnArrSIZE] = {0};
    unsigned char ReturnArr[];
    void sendPacket(unsigned char *arr, int arrSIZE);
    unsigned char * readPacket();


public:
   // Dynamixel(/* args */);
 //   virtual ~Dynamixel();

    void begin(HardwareSerial &Serial, uint32_t baudRate, int8_t directionPINOUT);
    unsigned char ping(unsigned char MOTOR_ID);
    void getPosition(unsigned char MOTOR_ID);
    void enableTorque(unsigned char MOTOR_ID, unsigned char setVal);
    void SetPosition(unsigned char MOTOR_ID, unsigned short setVal);




};
//constructor
//Dynamixel::Dynamixel()
//{
//}
//Destructor
//Dynamixel::~Dynamixel()
//{
//}
