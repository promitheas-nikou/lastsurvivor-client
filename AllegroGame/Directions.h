#pragma once
#include "stdint.h"
#include <string>

class Direction {
public:
	enum _dirType : uint8_t {
		NORTH = 0,
		EAST = 1,
		SOUTH = 2,
		WEST = 3,
		UP = 4,
		DOWN = 5,
		AETHER = 6
	};
private:
public:
	_dirType value;
	constexpr Direction(_dirType dir);
	operator _dirType() const;
	Direction(uint8_t dir);
	explicit operator bool() const = delete;
	constexpr bool operator==(Direction a) const;
	constexpr bool operator!=(Direction a) const;
	Direction operator>>(int s) const;
	Direction operator<<(int s) const;
	Direction GetOpposite() const;
	Direction operator-() const;
	static Direction GetDefaultDirection();
	uint8_t GetRawValue() const;
	Direction();
	std::string ToString() const;
};