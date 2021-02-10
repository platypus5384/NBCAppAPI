#pragma once


uint8_t NBClockCmdArgPcs_CHANGE_WAVE()
{
	return 8;
}


uint8_t NBClockCmd_CHANGE_WAVE(AppArg* apparg, uint8_t cmdarg[8])
{
	Wave wave;
	wave.enable    = cmdarg[2];
	wave.peroid_ms = (cmdarg[3] << 8) | cmdarg[4];
	wave.amp       = cmdarg[5];
	wave.faze      = (cmdarg[6] << 8) | cmdarg[7];
	apparg->global_wave[ cmdarg[1]][ cmdarg[0]] = wave;
	saveColorWave(apparg);
	return 0;
}