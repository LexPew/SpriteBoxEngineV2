#pragma once
#include "SpriteData.h"

#include <filesystem>
#include <iostream>
/**
 * Loads and manages any assets using JSON
 */
class AssetManager
{
private:
	static AssetManager* instance;
	std::filesystem::path assetRoot; //Root directory for assets
	

	std::unordered_map<std::string, SpriteData> m_sprites;
public:
	AssetManager()
	{
		if (instance != nullptr)
		{
			delete instance;
		}
		instance = this;
	}
	~AssetManager() = default;

	static AssetManager& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new AssetManager();
		}
		return *instance;
	}
	void SetAssetRoot(const std::string& p_rootPath)
	{
		assetRoot = p_rootPath;
	}

	std::string ResolvePath(const std::string& p_relativePath) const;

	//--SPRITE MANAGEMENT--

	/**
	 * Loads a sprite using a json asset file 
	 * @param p_path File path of the json sprite asset
	 */
	bool LoadSprite(const std::string& p_path);


	/**
	 * Returns spriteData of sprite(ID) if found and loaded
	 * @param p_id Sprite Id
	 */
	const SpriteData& GetSprite(const std::string& p_id) const;



};

