#pragma once


uint8_t NBClockCmdArgPcs_WHO()
{
	return 0;
}


uint8_t NBClockCmd_WHO(AppArg* apparg, uint8_t cmdarg[8])
{
	Serial.println("NBC");
	Serial.println("SoftVer2");
	return 0;
}