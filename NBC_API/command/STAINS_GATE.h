#pragma once


uint8_t NBClockCmdArgPcs_STAINS_GATE()
{
	return 1;
}


uint8_t NBClockCmd_STAINS_GATE(AppArg* apparg, uint8_t cmdarg[8])
{
	apparg->stainsgate_flag.flag = cmdarg[0];
	return 0;
}