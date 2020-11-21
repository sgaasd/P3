/*
#include "Arduino.h"
#include "Register_Map.h"

#ifndef CRUSTCRAWLER_H_
#define CRUSTCRAWLER_H_

#define TX_BUFFER_SIZE 40		//size of transmitted array in bytes
#define RX_BUFFER_SIZE 40		//size of received array in bytes

#if defined(__MK66FX1M0__) || defined(__MK64FX512__) || defined(__MK20DX256__) || defined(__MK20DX128__) || defined(__MKL26Z64__) || defined(CORE_TEENSY)
	#define square(x) pow(x, 2)			//square function implementation for teensy
#endif

#define LOW_BYTE(x)  (x & 0xFF)		//returns byte with low significant bit
#define HIGH_BYTE(x) ((x >> 8) & 0xFF) //returns byte with high significant bit

class CrustCrawler {
private:
	const uint8_t _NUM_OF_SERVOS = 5;		//number of servos
	const uint8_t _GRIPPER_ID = 0x66;		//shadow ID for the gripper
	const uint8_t _ID_ARR[4] = { 1, 2, 3, _GRIPPER_ID};		//servo's IDs
	const uint8_t _GRIPPER_ID_ARR[2] = { 4, 5 };		//IDs of the gripper's servos
	const uint16_t _MIN_POSITION[4] = { 0, 1800, 845, 2030 };		//servos minimum position limit
	const uint16_t _MAX_POSITION[4] = { 4095, 4095, 3250, 3300 };		//servos maximum position limit
	uint8_t _arrTx[TX_BUFFER_SIZE] = { 0xFF, 0xFF, 0xFD, 0x00 };		//stores the instruction packet of the servos
	uint8_t _arrRx[RX_BUFFER_SIZE] = { 0xFF, 0xFF, 0xFD, 0x00 };		//stores the return status of the servos
uint8_t _controlPin; //pin to control the direction of the data transmition

public:
	CrustCrawler();
	virtual ~CrustCrawler();

	void begin(HardwareSerial &Serial, uint8_t controlPin);		//initialize the connection between the microcontroller and the robot
	void enableTorque(bool isEnable);		//enable the torque for all servos
	void returnLevel(uint8_t level);		//set the return level register of the servos
	void returnDelay(uint8_t val);		//set the return delay register of the servos
	void operatingMode(uint8_t opMode);		//select operating mode to control the servos
	void baudRate(uint8_t baud);		//allows selecting different baudrates to communicate with the servos
	void setDriveMode(uint8_t id, uint8_t mode);		//mode to select direction of rotation of servos (clockwise/counterclockwise)
	void setShadowID(uint8_t id, uint8_t secID);		//set shadow ID for a servo
	void busWatchdog(uint8_t val);		//refers to bus watchdog timer in the servos
	void clearBusWatchdog();		//clears/resets the busWatchdog register

	void setMaxPosition(uint8_t id, uint32_t maxPos);		//set the maximum position limit
	void setMinPosition(uint8_t id, uint32_t minPos);		//set the minimum position limit
	int32_t updatePosition(uint8_t id);		//returns the current position

	void moveJoint(uint8_t id, int32_t angle, bool isDeg = false);		//moves one joint in either steps or degrees
	void moveJoints(int32_t theta1, int32_t theta2, int32_t theta3, int32_t thetaGripper, bool isDeg = false);		//moves the whole robot

	void openGripper();		//open gripper
	void closeGripper(); //close gripper

	void profileVelocity(uint32_t vel);		//set the value profile velocity register
	void profileAcceleration(uint32_t acc);		//set the value profile acceleration register
	void maxProfileAcceleration(uint32_t limit);		//set the maximum profile acceleration
	void maxProfileVelocity(uint32_t limit); //set the maximum profile velocity
	void maxVelocity(uint32_t vel); // Sets the maximum velocity in register

	void setPGain(uint8_t id, uint16_t dGain);		//set P-gain value for one servo
	void setIGain(uint8_t id, uint16_t dGain);		//set I-gain value for one servo
	void setDGain(uint8_t id, uint16_t dGain);		//set D-gain value for one servo
	void pGain(uint16_t pGain);		//set P-gain value for all servo
	void iGain(uint16_t iGain);		//set I-gain value for all servo
	void dGain(uint16_t dGain); //set D-gain value for all servo

private:
	bool _noErrorOccurred();		//returns true if the servo's return status has no error
	bool _verifyChecksum(uint16_t dataLength);		//calculate the checksum and return true if received checksum equals calculated one
	void _statusPacket(uint16_t dataLength);		//store the received data in _arrRx
	void _readInstruction(uint8_t id, uint16_t fromRegister, uint16_t dataLength);		//send read instruction to a specific servo
	template<typename T> T _readData(uint8_t id, uint16_t dataLength);		//template to return data read from the servo's registers after combining the bytes together
	template<typename T> void _writeInstruction(uint8_t id, uint16_t toRegister, uint16_t dataLength, T dataValue);		//send write instruction
	template<typename T> void _syncWriteInstruction(uint16_t toRegister, uint16_t dataLength, T data1, T data2, T data3, T data4);		//send sync write instruction
	void _clearBuffer();		//clear the serial receive buffer
	void _sendCommand(uint8_t *arr, uint16_t length);		//handles communicating with the servos other RS485
	uint16_t _update_crc(uint8_t *arr, uint16_t length);		//returns the calculated CRC checksum

HardwareSerial *_pSerial; //hardware serial
};

#endif

*/