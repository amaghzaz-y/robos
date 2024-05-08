#pragma once
const float correctif = 1.025;

class Steps
{
public:
	long M1;
	long M2;
	long M3;
	Steps(long m1, long m2, long m3);
	long *Positions();
};