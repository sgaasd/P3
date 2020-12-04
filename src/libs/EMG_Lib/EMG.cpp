#include "EMG.h"



void EMGclass::begin(HardwareSerial &Serial, uint32_t baudRate){ // turns on the desried Serial port with specific baudrate
    XBEEserial = &Serial;
    XBEEserial->begin(baudRate);
}

void EMGclass::updateData(){ //update the value of accelerometer and emg channel if checksum is verified
    static const int16_t numReadings = 10;
    int16_t readingsX[numReadings];      // the readings from the input
    int16_t readingsY[numReadings];      // the readings from the input
    int16_t readingsZ[numReadings];      // the readings from the input
    int16_t readingsCH1[numReadings];      // the readings from the input
    int16_t readingsCH2[numReadings];      // the readings from the input

    
    while (XBEEserial->available()) { //check incoming data
		if (XBEEserial->read() == 0x7E){ //check the start of new packet
			if (XBEEserial->read() == 0x00 && XBEEserial->read() == 0x14) { //check that 14 bytes are being received
				int16_t checkSum = 0;

				for (int i = 3; i < 24; i++) { //read data from serial and store it in array
					dataPkg[i] = XBEEserial->read();
					checkSum = checkSum + dataPkg[i]; //calculate checksum
				}

				 //verify checksum, if true, update the values of the accelerometer and emg channels.
                while(checkSum > 0xFF){
                    checkSum-=256;
                }

                if(checkSum == 255){
                    XBEE.ACC.x = (dataPkg[13] << 8) + dataPkg[14];
                    XBEE.ACC.y = (dataPkg[15] << 8) + dataPkg[16];
                    XBEE.ACC.z = (dataPkg[17] << 8) + dataPkg[18];

                    XBEE.EMG.CH1 = (dataPkg[19] << 8) + dataPkg[20];
                    XBEE.EMG.CH2 = (dataPkg[21] << 8) + dataPkg[22];

                    // subtract the last reading:
                    totalX = totalX - readingsX[readIndex];
                    totalY = totalY - readingsY[readIndex];
                    totalZ = totalZ - readingsZ[readIndex];
                    totalCH1 = totalCH1 - readingsCH1[readIndex];
                    totalCH2 = totalCH2 - readingsCH2[readIndex];     
                    
                    // read from the sensor:
                    readingsX[readIndex] = X;
                    readingsY[readIndex] = Y;
                    readingsZ[readIndex] = Z;
                    readingsCH1[readIndex] = CH1;
                    readingsCH2[readIndex] = CH2;

                    // add the reading to the total:
                    totalX += readingsX[readIndex];
                    totalY += readingsY[readIndex];
                    totalZ += readingsZ[readIndex];
                    totalCH1 += readingsCH1[readIndex];
                    totalCH2 += readingsCH2[readIndex];

                    // advance to the next position in the array:
                    readIndex ++;

                    // if we're at the end of the array...
                    if (readIndex >= numReadings) {
                        // ...wrap around to the beginning:
                        readIndex = 0;
                    }
                    // calculate the average:
                //    XBEE.ACC.x = (totalX / numReadings);
                //    XBEE.ACC.y = (totalY / numReadings);
                //    XBEE.ACC.z = (totalZ / numReadings);
                //    XBEE.EMG.CH1 = (totalCH1 / numReadings);
                //    XBEE.EMG.CH2 = (totalCH2 / numReadings);
				}
            }
        }
    }   
}

int16_t EMGclass::getEMG_CH1(){ //Return value of EMG CH 1
    return XBEE.EMG.CH1;
}

int16_t EMGclass::getEMG_CH2(){ //Return value of EMG CH 2
    return XBEE.EMG.CH2;
}


int16_t EMGclass::getAccX(){ //Return the acceleration in x-axis
    return XBEE.ACC.x;
}

int16_t EMGclass::getAccY(){ //Return the acceleration in y-axis
    return XBEE.ACC.y;
}

int16_t EMGclass::getAccZ(){ //Return the acceleration in z-axis
    return XBEE.ACC.z;
}



EMGclass::~EMGclass() {
	XBEEserial->end();
}
