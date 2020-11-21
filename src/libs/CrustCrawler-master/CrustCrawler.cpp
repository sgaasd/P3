/*
#include <math.h>
#include "CrustCrawler.h"

CrustCrawler::CrustCrawler() {
}

CrustCrawler::~CrustCrawler() {
	_pSerial->end();
}

void CrustCrawler::begin(HardwareSerial &serial, uint8_t controlPin) {
	_controlPin = controlPin;
	pinMode(_controlPin, OUTPUT);

	_pSerial = &serial;
	_pSerial->begin(115200);		//start communicating over serial using 115200 baudrate

#if defined(__MK66FX1M0__) || defined(__MK64FX512__) || defined(__MK20DX256__) || defined(__MK20DX128__) || defined(__MKL26Z64__) || defined(CORE_TEENSY)		//check if teensy board is used
	_pSerial->transmitterEnable(_controlPin);		//teensy specific function that handles RS485 communication
#endif

	CrustCrawler::returnDelay(10);		//servos will return status packet after 20uS (10 * 2uS)
	CrustCrawler::busWatchdog(0);		//clears the busWatchdog timer
	CrustCrawler::returnLevel(PING_READ_INSTRUCTION);		//servos will only return status packet when using ping or read instruction
	CrustCrawler::operatingMode(POSITION_MODE);		//select operating mode (position control mode)

	for (int i = 0; i < 3; i++){		//set joint limit for robot without gripper
		CrustCrawler::setMinPosition(_ID_ARR[i], _MIN_POSITION[i]);
		CrustCrawler::setMaxPosition(_ID_ARR[i], _MAX_POSITION[i]);
	}

	for (int i = 0; i < 2; i++){		//set shadow ID, drive mode and joint limit for both of gripper's servos
		CrustCrawler::setShadowID(_GRIPPER_ID_ARR[i], _GRIPPER_ID);
		CrustCrawler::setDriveMode(_GRIPPER_ID_ARR[i], CCW + i);
		CrustCrawler::setMinPosition(_GRIPPER_ID_ARR[i], _MIN_POSITION[3]);
		CrustCrawler::setMaxPosition(_GRIPPER_ID_ARR[i], _MAX_POSITION[3]);
	}
}

void CrustCrawler::returnLevel(uint8_t level) {
	CrustCrawler::_writeInstruction <uint8_t> (BROADCASTER_ID, STATUS_RETURN_LEVEL, 0x01, level);
}

void CrustCrawler::enableTorque(bool isEnable) {
	CrustCrawler::_writeInstruction <uint8_t> (BROADCASTER_ID, TORQUE_ENABLE, 0x01, isEnable);
}

void CrustCrawler::baudRate(uint8_t baud) {
	CrustCrawler::_writeInstruction <uint8_t> (BROADCASTER_ID, BAUD_RATE, 0x01, baud);
}

void CrustCrawler::operatingMode(uint8_t opMode) {
	CrustCrawler::_writeInstruction <uint8_t> (BROADCASTER_ID, OPERATING_MODE, 0x01, opMode);
}

void CrustCrawler::setShadowID(uint8_t id, uint8_t secID) {
	CrustCrawler::_writeInstruction <uint8_t> (id, SHADOW_ID, 0x01, secID);
}

void CrustCrawler::setDriveMode(uint8_t id, uint8_t mode) {
	CrustCrawler::_writeInstruction <uint8_t> (id, DRIVE_MODE, 0x01, mode);
}

void CrustCrawler::openGripper() {
	CrustCrawler::_writeInstruction <int32_t> (_GRIPPER_ID, GOAL_POSITION, 0x04, 2450);
}

void CrustCrawler::closeGripper() {
	CrustCrawler::_writeInstruction <int32_t> (_GRIPPER_ID, GOAL_POSITION, 0x04, 2040);
}

void CrustCrawler::moveJoint(uint8_t id, int32_t angle, bool isDeg) {
	if (isDeg == true)		//if true maps the angle from degrees to steps
		angle = map(angle, -180, 180, 0, 4095);

	CrustCrawler::_writeInstruction <int32_t> (id, GOAL_POSITION, 0x04, angle);
}

void CrustCrawler::moveJoints(int32_t theta1, int32_t theta2, int32_t theta3, int32_t thetaGripper, bool isDeg) {
	if (isDeg == true) {		//if true maps the angles from degrees to steps
		theta1 = map(theta1, -180, 180, 0, 4095);
		theta2 = map(theta2, -180, 180, 0, 4095);
		theta3 = map(theta3, -180, 180, 0, 4095);
		thetaGripper = map(thetaGripper, -180, 180, 0, 4095);
	}
	CrustCrawler::_syncWriteInstruction <int32_t> (GOAL_POSITION, 0x04, theta1, theta2, theta3, thetaGripper);
}

int32_t CrustCrawler::updatePosition(uint8_t id) {
	CrustCrawler::_readInstruction(id, PRESENT_POSITION, 0x04);
	CrustCrawler::_statusPacket(0x04);

	if (CrustCrawler::_noErrorOccurred() && CrustCrawler::_verifyChecksum(0x04))
		return CrustCrawler::_readData <int32_t> (id, 0x04);
}

void CrustCrawler::profileVelocity(uint32_t vel) {
	CrustCrawler::_writeInstruction <uint32_t> (BROADCASTER_ID, PROFILE_VELOCITY, 0x04, vel);
}

void CrustCrawler::profileAcceleration(uint32_t acc) {
	CrustCrawler::_writeInstruction <uint32_t> (BROADCASTER_ID, PROFILE_ACCELERATION, 0x04, acc);
}

void CrustCrawler::maxProfileAcceleration(uint32_t limit) {
	CrustCrawler::_writeInstruction <uint32_t> (BROADCASTER_ID, MAXIMUM_ACCELERATION_LIMIT, 0x04, limit);
}

void CrustCrawler::maxProfileVelocity(uint32_t limit) {
	CrustCrawler::_writeInstruction <uint32_t> (BROADCASTER_ID, MAXIMUM_VELOCITY_LIMIT, 0x04, limit);
}

void CrustCrawler::pGain(uint16_t pGain) {
	CrustCrawler::_writeInstruction <uint16_t> (BROADCASTER_ID, POSITION_P_GAIN, 0x02, pGain);
}

void CrustCrawler::iGain(uint16_t iGain) {
	CrustCrawler::_writeInstruction <uint16_t> (BROADCASTER_ID, POSITION_I_GAIN, 0x02, iGain);
}

void CrustCrawler::dGain(uint16_t dGain) {
	CrustCrawler::_writeInstruction <uint16_t> (BROADCASTER_ID, POSITION_D_GAIN, 0x02, dGain);
}

void CrustCrawler::setPGain(uint8_t id, uint16_t pGain) {
	CrustCrawler::_writeInstruction <uint16_t> (id, POSITION_P_GAIN, 0x02, pGain);
}

void CrustCrawler::setIGain(uint8_t id, uint16_t iGain) {
	CrustCrawler::_writeInstruction <uint16_t> (id, POSITION_I_GAIN, 0x02, iGain);
}

void CrustCrawler::setDGain(uint8_t id, uint16_t dGain) {
	CrustCrawler::_writeInstruction <uint16_t> (id, POSITION_D_GAIN, 0x02, dGain);
}

void CrustCrawler::setMaxPosition(uint8_t id, uint32_t maxPos) {
	CrustCrawler::_writeInstruction <uint32_t> (id, MAXIMUM_POSITION_LIMIT, 0x04, maxPos);
}

void CrustCrawler::setMinPosition(uint8_t id, uint32_t minPos) {
	CrustCrawler::_writeInstruction <uint32_t> (id, MINIMUM_POSITION_LIMIT, 0x04, minPos);
}

void CrustCrawler::busWatchdog(uint8_t val) {
	CrustCrawler::_writeInstruction <uint8_t> (BROADCASTER_ID, BUS_WATCHDOG, 0x01, val);
}

void CrustCrawler::clearBusWatchdog() {
	CrustCrawler::_writeInstruction <uint8_t> (BROADCASTER_ID, BUS_WATCHDOG, 0x01, 0x00);
}

void CrustCrawler::returnDelay(uint8_t val) {
	CrustCrawler::_writeInstruction <uint8_t> (BROADCASTER_ID, RESPONSE_DELAY_TIME, 0x01, val);
}

void CrustCrawler::_clearBuffer() {
#if defined(__MK66FX1M0__) || defined(__MK64FX512__) || defined(__MK20DX256__) || defined(__MK20DX128__) || defined(__MKL26Z64__) || defined(CORE_TEENSY)		//check if teensy board is used
	_pSerial->clear();		//function to clear serial receive buffer for teensy board
#else
	while (_pSerial->available())
		_pSerial->read();
#endif
}

void CrustCrawler::_statusPacket(uint16_t dataLength) {
	while (_pSerial->available()) {		//if data is available
		if (_pSerial->read() == 0xFF && _pSerial->read() == 0xFF && _pSerial->read() == 0xFD && _pSerial->read() == 0x00)		//check for new instruction packet
			for (int i = 4; i < 11 + dataLength; i++)		//store the received bytes in the receive array _arrRx
				_arrRx[i] = _pSerial->read();
	}
}

bool CrustCrawler::_verifyChecksum(uint16_t dataLength) {
	uint16_t checkSum, receivedCheckSum = 0;

	checkSum = CrustCrawler::_update_crc(_arrRx, dataLength + 11);
	receivedCheckSum = _arrRx[dataLength + 10];
	receivedCheckSum = (receivedCheckSum << 8) | _arrRx[dataLength + 9];

	return (checkSum == receivedCheckSum);		//return true if calculated and received checksum match
}

bool CrustCrawler::_noErrorOccurred() {
	return (_arrRx[7] == STATUS && _arrRx[8] == NO_ERROR);		//return true if a new status packet is received with no error
}

template<typename T>
T CrustCrawler::_readData(uint8_t id, uint16_t dataLength) {
	T tmpData, receivedData = 0;

	for (int i = 0; i < dataLength; i++) {		//combine the data bytes into their original value
		tmpData = _arrRx[9 + i];
		receivedData |= (tmpData << 8 * i);
	}

	return receivedData;
}

void CrustCrawler::_readInstruction(uint8_t id, uint16_t fromRegister, uint16_t dataLength) {
	uint16_t len = dataLength + 3;
	uint16_t arrLen = len + 7;

	_arrTx[4] = id;		//the servo's ID
	_arrTx[5] = LOW_BYTE(len);		//low byte of the length of the instruction packet
	_arrTx[6] = HIGH_BYTE(len);		//high byte of the length of the instruction packet
	_arrTx[7] = READ;		//read instruction
	_arrTx[8] = LOW_BYTE(fromRegister);		//low byte of register to read from
	_arrTx[9] = HIGH_BYTE(fromRegister);		//high byte of register to read from
	_arrTx[10] = LOW_BYTE(dataLength);		//low byte of size of data to read
	_arrTx[11] = HIGH_BYTE(dataLength);		//high byte of size of data to read

	CrustCrawler::_sendCommand(_arrTx, arrLen);
}

template<typename T>
void CrustCrawler::_writeInstruction(uint8_t id, uint16_t toRegister, uint16_t dataLength, T dataValue) {
	uint16_t len = dataLength + 5;
	uint16_t arrLen = len + 7;

	_arrTx[4] = id;		//the servo's ID
	_arrTx[5] = LOW_BYTE(len);		//low byte of the length of the instruction packet
	_arrTx[6] = HIGH_BYTE(len);		//high byte of the length of the instruction packet
	_arrTx[7] = WRITE;		//write instruction
	_arrTx[8] = LOW_BYTE(toRegister);		//low byte of register to write to
	_arrTx[9] = HIGH_BYTE(toRegister);		//high byte of register to write to

	for (int i = 0; i < dataLength; i++) {		//split the sent value into byte sequence
		_arrTx[10 + i] = (dataValue >> (8 * i)) & 0xFF;
	}

	CrustCrawler::_sendCommand(_arrTx, arrLen);
}

template<typename T>
void CrustCrawler::_syncWriteInstruction(uint16_t toRegister, uint16_t dataLength, T data1, T data2, T data3, T data4) {
	uint16_t len = (_NUM_OF_SERVOS - 1) + (_NUM_OF_SERVOS - 1) * dataLength + 7;
	uint16_t arrLen = len + 7;
	uint8_t value[_NUM_OF_SERVOS - 1][dataLength];		//stores all the sent data

	_arrTx[4] = BROADCASTER_ID;		//Broadcaster ID required when sending sync write instruction
	_arrTx[5] = LOW_BYTE(len);		//low byte of the length of the instruction packet
	_arrTx[6] = HIGH_BYTE(len);		//high byte of the length of the instruction packet
	_arrTx[7] = SYNC_WRITE;		//sync write instruction
	_arrTx[8] = LOW_BYTE(toRegister);		//low byte of register to write to
	_arrTx[9] = HIGH_BYTE(toRegister);		//high byte of register to write to
	_arrTx[10] = LOW_BYTE(dataLength);		//low byte of size of data to write (has to be the same size for all the servos)
	_arrTx[11] = HIGH_BYTE(dataLength);		//high byte of size of data to write (has to be the same size for all the servos)

	for (int i = 0; i < (_NUM_OF_SERVOS - 1); i++) {		//split data into byte sequence and store it in 2d array
		if (i == 0)
			for (int j = 0; j < dataLength; j++)
				value[i][j] = (data1 >> (8 * j)) & 0xFF;
		else if (i == 1)
			for (int j = 0; j < dataLength; j++)
				value[i][j] = (data2 >> (8 * j)) & 0xFF;
		else if (i == 2)
			for (int j = 0; j < dataLength; j++)
				value[i][j] = (data3 >> (8 * j)) & 0xFF;
		else if (i == 3)
			for (int j = 0; j < dataLength; j++)
				value[i][j] = (data4 >> (8 * j)) & 0xFF;
	}

	for (int i = 0; i < (_NUM_OF_SERVOS - 1); i++) {
		_arrTx[12 + i + i * dataLength] = _ID_ARR[i];
		for (int j = 0; j < dataLength; j++)
			_arrTx[13 + i + i * dataLength + j] = value[i][j];
	}

	CrustCrawler::_sendCommand(_arrTx, arrLen);
}

void CrustCrawler::_sendCommand(uint8_t *arr, uint16_t length) {
	uint16_t CRC = 0;
	CRC = CrustCrawler::_update_crc(arr, length - 2);
	arr[length - 2] = LOW_BYTE(CRC);
	arr[length - 1] = HIGH_BYTE(CRC);

#if defined(__MK66FX1M0__) || defined(__MK64FX512__) || defined(__MK20DX256__) || defined(__MK20DX128__) || defined(__MKL26Z64__) || defined(CORE_TEENSY)
	_pSerial->write(arr, length);
	_pSerial->flush();
#else
	digitalWrite(_controlPin, TRANSMIT);
	_pSerial->write(arr, length);
	_pSerial->flush();
	digitalWrite(_controlPin, RECEIVE);
#endif
}

uint16_t CrustCrawler::_update_crc(uint8_t *arr, uint16_t length) {
	uint16_t i, j = 0;
	uint16_t crc_accum = 0;
	uint16_t crc_table[256] = { 0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E,
			0x0014, 0x8011, 0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D,
			0x8027, 0x0022, 0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D,
			0x8077, 0x0072, 0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E,
			0x0044, 0x8041, 0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD,
			0x80D7, 0x00D2, 0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE,
			0x00E4, 0x80E1, 0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE,
			0x00B4, 0x80B1, 0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D,
			0x8087, 0x0082, 0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D,
			0x8197, 0x0192, 0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE,
			0x01A4, 0x81A1, 0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE,
			0x01F4, 0x81F1, 0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD,
			0x81C7, 0x01C2, 0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E,
			0x0154, 0x8151, 0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D,
			0x8167, 0x0162, 0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D,
			0x8137, 0x0132, 0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E,
			0x0104, 0x8101, 0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D,
			0x8317, 0x0312, 0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E,
			0x0324, 0x8321, 0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E,
			0x0374, 0x8371, 0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D,
			0x8347, 0x0342, 0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE,
			0x03D4, 0x83D1, 0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED,
			0x83E7, 0x03E2, 0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD,
			0x83B7, 0x03B2, 0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E,
			0x0384, 0x8381, 0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E,
			0x0294, 0x8291, 0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD,
			0x82A7, 0x02A2, 0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD,
			0x82F7, 0x02F2, 0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE,
			0x02C4, 0x82C1, 0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D,
			0x8257, 0x0252, 0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E,
			0x0264, 0x8261, 0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E,
			0x0234, 0x8231, 0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D,
			0x8207, 0x0202 };

	for (j = 0; j < length; j++) {
		i = ((crc_accum >> 8) ^ arr[j]) & 0xFF;
		crc_accum = (crc_accum << 8) ^ crc_table[i];
	}
	return crc_accum;
}
*/