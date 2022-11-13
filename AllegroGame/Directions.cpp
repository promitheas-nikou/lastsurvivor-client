#include "Directions.h"

constexpr Direction::Direction(_dirType val) : value{ val }
{}

Direction::operator _dirType() const
{
	return value;
}

Direction::Direction(uint8_t dir) : Direction(_dirType(dir))
{}

Direction Direction::GetOpposite() const
{
	switch (value) {
	case NORTH:
		return SOUTH;
	case SOUTH:
		return NORTH;
	case EAST:
		return WEST;
	case WEST:
		return EAST;
	case UP:
		return DOWN;
	case DOWN:
		return UP;
	case AETHER:
	default:
		return AETHER;
	}
}

Direction Direction::operator-() const
{
	return GetOpposite();
}

Direction Direction::GetDefaultDirection()
{
	return Direction();
}

uint8_t Direction::GetRawValue() const
{
	return value;
}

Direction::Direction(): Direction(NORTH)
{}

std::string Direction::ToString() const
{
	switch (value) {
	case NORTH:
		return "NORTH";
	case SOUTH:
		return "SOUTH";
	case EAST:
		return "EAST";
	case WEST:
		return "WEST";
	case UP:
		return "UP";
	case DOWN:
		return "DOWN";
	case AETHER:
		return "AETHER";
	}
}

constexpr bool Direction::operator==(Direction a) const
{
	return a.value == value;
}

constexpr bool Direction::operator!=(Direction a) const
{
	return a.value != value;
}

Direction Direction::operator>>(int s) const
{
	if (value < 4)
		return _dirType((value + s) % 4);
	return value;
}

Direction Direction::operator<<(int s) const
{
	s %= 4;
	if (value < 4)
		return _dirType((value - s + 8) % 4);
	return value;
}

