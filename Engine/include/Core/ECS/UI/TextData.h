#pragma once
#include <string>
#include <SFML/Graphics/Color.hpp>
#include <cereal/types/string.hpp>

#include "Core/Color4.h"

//Struct: TextData
//Purpose: Holds data for rendering text
struct TextData
{
	TextData() = default;
	TextData(const std::string& p_text, int p_fontSize, const Color4 p_color, const std::string& p_fontId)
		: text(p_text), fontSize(p_fontSize), color(p_color), fontId(p_fontId) {
	}
	std::string fontId{"NULL"};
	std::string text{"Hi, please assign me some text"};
	int fontSize{30};
	Color4 color{ 255,255,255,255 };
	
	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(text, fontSize, color, fontId);
	}
};
