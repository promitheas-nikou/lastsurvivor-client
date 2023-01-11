#pragma once
#include <stdint.h>

namespace HazardWarnings {
	typedef uint32_t special_warning_t;
	constexpr special_warning_t PYROPHORIC = 0x00000001;
	constexpr special_warning_t TOXIC = 0x00000002;
	constexpr special_warning_t CRYOGENIC = 0x00000004;
	constexpr special_warning_t RADIOACTIVE = 0x00000008;
	constexpr special_warning_t INFLAMMABLE = 0x00000010;
	constexpr special_warning_t BURNING = 0x00000020;
	constexpr special_warning_t ACIDIC = 0x00000100;
	constexpr special_warning_t ALKALINE = 0x00000200;
};

