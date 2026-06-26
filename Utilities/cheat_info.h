#pragma once

#include "util/types.hpp"

#include <string>

enum class cheat_type : u8
{
	unsigned_8_cheat,
	unsigned_16_cheat,
	unsigned_32_cheat,
	unsigned_64_cheat,
	signed_8_cheat,
	signed_16_cheat,
	signed_32_cheat,
	signed_64_cheat,
	float_32_cheat,
	max
};

constexpr u8 cheat_type_max = static_cast<u8>(cheat_type::max);

enum class search_compare_mode : u8
{
	unknown_initial,
	equal,
	not_equal,
	greater_than,
	less_than,
	between,
	changed,
	unchanged,
	increased,
	decreased,
	increased_by,
	decreased_by,
	max
};

constexpr u8 search_compare_mode_max = static_cast<u8>(search_compare_mode::max);

struct cheat_info
{
	std::string game{};
	std::string description{};
	cheat_type type = cheat_type::max;
	u32 offset{};
	std::string red_script{};

	bool from_str(std::string_view cheat_line);
	std::string to_str() const;
};
