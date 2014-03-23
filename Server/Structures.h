#pragma once

struct ObjectState
{
	unsigned short id;
	float position[3];
	float linearVelocity[3];
	float angularVelocity[3];
	float rotation;
};