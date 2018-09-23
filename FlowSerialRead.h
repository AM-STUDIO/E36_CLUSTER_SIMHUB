#define FlowSerialBegin Serial.begin
#define FlowSerialAvailable Serial.available
#define FlowSerialFlush Serial.flush

int FlowSerialPosition = 0;
int FlowSerialTrigger = 8;
long fsr_startMillis;

int FlowSerialRead() {
	FlowSerialPosition++;
	if (FlowSerialPosition == FlowSerialTrigger) {
		FlowSerialPosition = 0;
		Serial.write(0x01);
		Serial.flush();
	}
	return Serial.read();
}

void FlowSerialWrite(uint8_t data) {
	Serial.write(0x02);
	Serial.write(data);
}

void FlowSerialPrint(char data)
{
	FlowSerialWrite(data);
}

void FlowSerialPrint(String& data)
{
	int len = data.length();
	for (int x = 0; x < len; x++)
		FlowSerialWrite(data.charAt(x));
}

void FlowSerialDebugPrintLn(String& data)
{
	Serial.write(0x15);
	Serial.println(data);
}

void FlowSerialDebugPrintLn(const char str[]) {
	Serial.write(0x15);
	Serial.println(str);
}

void FlowSerialPrint(const char str[]) {
	for (int x = 0; x < strlen(str); x++)
		FlowSerialWrite(str[x]);
}

int FlowSerialTimedRead()
{
	int c;
	fsr_startMillis = millis();
	do {
		c = Serial.read();
		if (c >= 0) {
			FlowSerialPosition++;
			if (FlowSerialPosition == FlowSerialTrigger) {
				FlowSerialPosition = 0;
				Serial.write(0x01);
				Serial.flush();
			}
			return c;
		}
	} while (millis() - fsr_startMillis < 100);
	return -1;     // -1 indicates timeout
}

String FlowSerialReadStringUntil(char terminator) {
	String ret;
	int c = FlowSerialTimedRead();
	while (c >= 0 && c != terminator)
	{
		ret += (char)c;
		c = FlowSerialTimedRead();
	}
	return ret;
}
