#include <Arduino.h>
#include <utils/PINS.h>

class Sensors
{
private:
	bool sensor_a_state;
	bool sensor_b_state;
	bool sensor_c_state;
	const int SIDE_A_ID = 0;
	const int SIDE_B_ID = 1;
	const int SIDE_C_ID = 2;

public:
	void setup();
	bool getSensor(int side_id);
	void testSensors();
	
};