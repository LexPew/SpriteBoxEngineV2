#include "Core/AssetManager.h"

#include <iostream>
#include "fstream"
#include "Core/Utils/json.hpp"

bool AssetManager::LoadSprite(const std::string& p_path)
{
	std::ifstream jsonFile(p_path);
	if(!jsonFile.is_open())
	{
		std::cerr << "Failed to open JSON file " << p_path << "\n";
		return false;
	}
	nlohmann::json jsonData;
	jsonFile >> jsonData;

	SpriteData spriteData;

	//General sprite things

	spriteData.id = jsonData["id"];
	spriteData.spriteSheetRows = jsonData["spriteSheetRows"];
	spriteData.spriteSheetColumns = jsonData["spriteSheetColumns"];

	//Load texture
	std::string texturePath = jsonData["texturePath"];
	if(!spriteData.texture.loadFromFile(texturePath))
	{
		std::cerr << "Failed to load texture: " << texturePath << "\n";
		return false;
	}

	//Loop through all animations and create new data structs for them to then add to the map in SpriteData
	for(auto& [animName, animDetails] : jsonData["animations"].items())
	{
		AnimationData animationData;
		animationData.startFrame = animDetails["startFrame"];
		animationData.frameCount = animDetails["frameCount"];
		animationData.frameDuration = animDetails["frameDuration"];
		spriteData.animations[animName] = animationData;
	}

	m_sprites.insert({ spriteData.id, spriteData });
}

SpriteData AssetManager::LoadDefaultSprite() const
{
	SpriteData placeholder;
	placeholder.id = "default";
	return placeholder;
}

const SpriteData& AssetManager::GetSprite(const std::string& p_id) const
{
	//If our unordered map contains 
	if(m_sprites.find(p_id) != m_sprites.end())
	{
		return m_sprites.find(p_id)->second;
	}
	return LoadDefaultSprite();
}
