#pragma once


uint8_t NBClockCmdArgPcs_ADJUST_CLOCK()
{
	return 7;
}


uint8_t NBClockCmd_ADJUST_CLOCK(AppArg* apparg, uint8_t cmdarg[8])
{
	tmElements_t adjust_tm;
	adjust_tm.Year   = cmdarg[0];
	adjust_tm.Month  = cmdarg[1];
	adjust_tm.Day    = cmdarg[2];
	adjust_tm.Wday   = cmdarg[3];
	adjust_tm.Hour   = cmdarg[4];
	adjust_tm.Minute = cmdarg[5];
	adjust_tm.Second = cmdarg[6];
	apparg->rtc->adjust( adjust_tm, 0);
	Serial.println("ADJUST_CLOCK");
	return 0;
}