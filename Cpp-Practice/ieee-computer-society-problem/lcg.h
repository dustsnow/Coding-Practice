#include <math.h>
#include <stdlib.h>
#ifndef LCG_H
#define LCG_H
class LCG{
	static const int a = 1664525;
	static const int c = 1013904223;
	int seed;
	public:
		static const long m = 281474976710656;
		LCG(int seed){
			this->seed = seed;
		}
		int rand(int upperBound){
			int xNext;
			xNext = (seed*a+c)%m;
			seed = xNext;
			return abs(xNext%upperBound+1);
		}
};


#endif
