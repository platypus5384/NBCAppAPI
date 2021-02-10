#pragma once


uint8_t NBClockCmdArgPcs_ACK()
{
	return 0;
}


uint8_t NBClockCmd_ACK(AppArg* apparg, uint8_t cmdarg[8])
{
	Serial.println("ACK");
	return 0;
}