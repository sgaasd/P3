#pragma once
#include "arduino.h"


class Dynamixel
{
private:
    HardwareSerial *DynamixelSerial;
    unsigned short update_crc(unsigned char *data_blk_ptr, unsigned short data_blk_size);
    int8_t directionPIN;
    void clearSerialBuffer();
    //initialize the ReturnPacket with dynamic array size

    static const int returnArrSIZE = 20;
    byte ReturnPacket[returnArrSIZE] = {0};
    void sendPacket();
    void readPacket();


public:
   // Dynamixel(/* args */);
    ~Dynamixel();

    void begin(HardwareSerial &Serial, uint32_t baudRate, int8_t directionPINOUT);
    bool ping(byte MOTOR_ID);
    void getPosition();



};
//constructor
//Dynamixel::Dynamixel()
//{
//}
//Destructor
Dynamixel::~Dynamixel()
{
}
