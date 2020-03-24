//TODO: add to readme; explain each field;
//TODO: add to a Shared library
NoiseMonitorMessage
{
	uint32_t Timestamp;
	uint8_t BatteryVoltage;
	int8_t BoardTemperature;
	uint32_t Lat;
	uint32_t Long;
	uint32_t Noise;
}