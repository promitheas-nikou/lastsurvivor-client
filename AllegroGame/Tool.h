#pragma once

#include <string>


class Tool
{
public:
	class ToolType {
	public:
		enum ToolType_t: char {
			NONE = 0b0000,
			PICKAXE = 0b0001,
			AXE = 0b0010,
			SHOVEL = 0b0100,
			PUMP = 0b1000
		};
	private:
		ToolType_t val;
	public:
		ToolType(char v = NONE);
		operator ToolType_t() const;
	};

	virtual ToolType GetToolType() const = 0;
	virtual float GetMiningDamage() const = 0;
	virtual int GetMiningLevel() const = 0;

	static ToolType GetToolTypeFromString(std::string str);

	virtual bool IsShovel() const;
	virtual bool IsPickaxe() const;
	virtual bool IsAxe() const;
	virtual bool IsPump() const;

	virtual ~Tool() = default;
};

using ToolType = Tool::ToolType;