#include "EMG.h"



void EMGclass::begin(HardwareSerial &Serial, uint32_t baudRate){ // turns on the desried Serial port with specific baudrate
    XBEEserial = &Serial;
    XBEEserial->begin(baudRate);
}


void EMGclass::updateData(){ //update the value of accelerometer and emg channel if checksum is verified  
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
                    XBEE.ACC.z = dataPkg[14] | dataPkg[13] << 8;
                    XBEE.ACC.y = dataPkg[16] | dataPkg[15] << 8;
                    XBEE.ACC.x = dataPkg[18] | dataPkg[17] << 8;

                    XBEE.EMG.CH1 = dataPkg[20] | dataPkg[19] << 8;
                    XBEE.EMG.CH2 = dataPkg[22] | dataPkg[21] << 8;
				}
            }
        }
    }   
}

uint16_t EMGclass::getEMG_CH1(){ //Return value of EMG CH 1
    return XBEE.EMG.CH1;
}

uint16_t EMGclass::getEMG_CH2(){ //Return value of EMG CH 2
    return XBEE.EMG.CH2;
}


uint16_t EMGclass::getAccX(){ //Return the acceleration in x-axis
    return XBEE.ACC.x;
}

uint16_t EMGclass::getAccY(){ //Return the acceleration in y-axis
    return XBEE.ACC.y;
}

uint16_t EMGclass::getAccZ(){ //Return the acceleration in z-axis
    return XBEE.ACC.z;
}



EMGclass::~EMGclass() {
	XBEEserial->end();
}