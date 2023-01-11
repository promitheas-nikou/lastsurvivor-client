#pragma once
#include <queue>

namespace DebugInfo
{
	constexpr int TICKS_RECORD_NUM = 50;
	extern std::queue<double> ticksEnd;
	constexpr int FRAMES_RECORD_NUM = 100;
	extern std::queue<double> framesEnd;
};

