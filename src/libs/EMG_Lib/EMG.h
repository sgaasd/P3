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
            int16_t x, y, z;
        }ACC;
        struct 
        {
            int16_t CH1, CH2;
        }EMG;
    }XBEE;

    HardwareSerial *XBEEserial;

    byte dataPkg[24] = {0x7E, 0x00, 0x14};




    int16_t readIndex = 0;              // the index of the current reading
    int16_t X;
    int16_t Y;
    int16_t Z;
    int16_t CH1;
    int16_t CH2;

    int16_t totalX = 0;                  // the running total
    int16_t totalY = 0;                  // the running total
    int16_t totalZ = 0;                  // the running total
    int16_t totalCH1 = 0;                  // the running total
    int16_t totalCH2 = 0;                  // the running total

    int16_t averageX = 0;                // the average
    int16_t averageY = 0;                // the average
    int16_t averageZ = 0;                // the average
    int16_t averageCH1 = 0;                // the average
    int16_t averageCH2 = 0;                // the average
    

public:
    void begin(HardwareSerial &Serial, uint32_t baudRate); //establishes the connection between microcontroller and XBee
	void updateData(); //update the value of accelerometer and emg channel if checksum is verified
	virtual ~EMGclass();

    int16_t getEMG_CH1(); //Return value of EMG CH 1
    int16_t getEMG_CH2(); //Return value of EMG CH 2

    int16_t getAccX(); //Return the acceleration in x-axis
    int16_t getAccY(); //Return the acceleration in y-axis
    int16_t getAccZ(); //Return the acceleration in z-axis


};


#endif