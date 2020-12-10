#pragma once

#include <Arduino.h>

#ifndef EMG_H
#define EMG_H


class EMGclass{
private:
    struct 
    {
        struct 
        {
            uint16_t x, y, z;
        }ACC;
        struct 
        {
            uint16_t CH1, CH2;
        }EMG;
    }XBEE;
uint16_t i = 0;
    HardwareSerial *XBEEserial;

    byte dataPkg[24] = {0x7E, 0x00, 0x14};

    uint16_t totalX = 0;                  // the running total of X
    uint16_t totalY = 0;                  // the running total of Y
    uint16_t totalZ = 0;                  // the running total of Z
    uint16_t totalCH1 = 0;                  // the running total of EMG CH1
    uint16_t totalCH2 = 0;                  // the running total of EMG CH2
    
    uint16_t readIndex = 0;              // the index of the current reading
    uint16_t X;
    uint16_t Y;
    uint16_t Z;
    uint16_t CH1;
    uint16_t CH2;


    uint16_t averageX = 0;                // the average
    uint16_t averageY = 0;                // the average
    uint16_t averageZ = 0;                // the average
    uint16_t averageCH1 = 0;                // the average
    uint16_t averageCH2 = 0;                // the average
    

public:
    void begin(HardwareSerial &Serial, uint32_t baudRate); //establishes the connection between microcontroller and XBee
	void updateData(); //update the value of accelerometer and emg channel if checksum is verified
	virtual ~EMGclass();

    uint16_t getEMG_CH1(); //Return value of EMG CH 1
    uint16_t getEMG_CH2(); //Return value of EMG CH 2

    uint16_t getAccX(); //Return the acceleration in x-axis
    uint16_t getAccY(); //Return the acceleration in y-axis
    uint16_t getAccZ(); //Return the acceleration in z-axis


};


#endif