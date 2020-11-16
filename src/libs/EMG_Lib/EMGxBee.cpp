#include "EMGxBee.h"

void EMGxBee::begin(HardwareSerial &serial, uint32_t baudRate) { //establishes the connection between microcontroller and XBee
	xBeeSerial = &serial;
	xBeeSerial->begin(baudRate);
}

uint16_t EMGxBee::getAccZ() { //returns acceleration in z-axis
	return s_data.z;
}

uint16_t EMGxBee::getAccY() { //returns acceleration in y-axis
	return s_data.y;
}

uint16_t EMGxBee::getAccX() { //returns acceleration in x-axis
	return s_data.x;
}

uint16_t EMGxBee::getEMG1() { //returns emg channel 1 value
	return s_data.emg1;
}

uint16_t EMGxBee::getEMG2() { //returns emg channel 1 value
	return s_data.emg2;
}

void EMGxBee::updateData() { //updates data when a new package is received

	while (xBeeSerial->available()) { //check incoming data
		if (xBeeSerial->read() == 0x7E) //check the start of new packet
			if (xBeeSerial->read() == 0x00 && xBeeSerial->read() == 0x14) { //check that 14 bytes are being received
				uint16_t checkSum = 0;

				for (int i = 0; i < 21; i++) { //read data from serial and store it in array
					arr[i] = xBeeSerial->read();
					checkSum = checkSum + arr[i]; //calculate checksum
				}

				if ((checkSum & 0xFF) == 0xFF) { //verify checksum, if true, update the values of the accelerometer and emg channels.
					uint16_t tmpData = arr[10];
					s_data.z = (tmpData << 8) | arr[11];
					tmpData = arr[12];
					s_data.y = (tmpData << 8) | arr[13];
					tmpData = arr[14];
					s_data.x = (tmpData << 8) | arr[15];
					tmpData = arr[16];
					s_data.emg1 = (tmpData << 8) | arr[17];
					tmpData = arr[18];
					s_data.emg2 = (tmpData << 8) | arr[19];
				}
			}
	}
}

EMGxBee::~EMGxBee() {
	xBeeSerial->end();
}
