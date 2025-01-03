#pragma once
#include <string>
#include <unordered_map>
#include "SFML/Graphics.hpp"

/**
 * Contains all the data required to create an animation
 */
struct AnimationData
{
	int startFrame;
	int endFrame;
	float frameDuration;

};

/**
 * Contains all the data required to create a sprite
 */
struct SpriteData
{
	std::string id{"NULL"};
	sf::Texture texture;
	int spriteSheetRows{0};
	int spriteSheetColumns{0};
	std::unordered_map<std::string, AnimationData> animations{};

};

//--EXAMPLE JSON FILE--
//
//{
//    "id": "attack",
//        "texturePath" : "assets/attack.png",
//        "animations" : {
//        "idle": {
//            "startFrame": 0,
//                "frameCount" : 4,
//                "frameDuration" : 0.2
//        },
//            "run" : {
//            "startFrame": 4,
//                "frameCount" : 6,
//                "frameDuration" : 0.1
//        }
//    },
//        "spriteSheetRows": 2,
//        "spriteSheetColumns": 2
//}
