#pragma once

struct Color4
{
	int r{0};
	int g{0};
	int b{0};
	int a{0};

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(r, g, b, a);
	}
};