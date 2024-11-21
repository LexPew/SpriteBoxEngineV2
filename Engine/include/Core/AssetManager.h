#pragma once
#include "SpriteData.h"
/**
 * Loads and manages any assets using JSON
 */
class AssetManager
{
private:
	std::unordered_map<std::string, SpriteData> m_sprites;
public:
	AssetManager() = default;
	~AssetManager() = default;

	//--SPRITE MANAGEMENT--

	/**
	 * Loads a sprite using a json asset file 
	 * @param p_path File path of the json sprite asset
	 */
	bool LoadSprite(const std::string& p_path);

	SpriteData LoadDefaultSprite() const;
	/**
	 * Returns spriteData of sprite(ID) if found and loaded
	 * @param p_id Sprite Id
	 */
	const SpriteData& GetSprite(const std::string& p_id) const;



};

