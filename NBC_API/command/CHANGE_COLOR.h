#pragma once


uint8_t NBClockCmdArgPcs_CHANGE_COLOR()
{
	return 4;
}


uint8_t NBClockCmd_CHANGE_COLOR(AppArg* apparg, uint8_t cmdarg[])
{
	apparg->global_color[ cmdarg[0]].element[HSV_H] = cmdarg[1];
	apparg->global_color[ cmdarg[0]].element[HSV_S] = cmdarg[2];
	apparg->global_color[ cmdarg[0]].element[HSV_V] = cmdarg[3];
	saveColorWave(apparg);
	return 0;
}