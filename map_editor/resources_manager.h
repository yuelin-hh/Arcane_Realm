#pragma once

#include "manager.h"

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <unordered_map>

enum class ResID
{
	Tex_UI,
	Tex_Tile
};

class ResourcesManager : public Manager<ResourcesManager>
{
	friend class Manager<ResourcesManager>;
protected:
	ResourcesManager();
	~ResourcesManager();

public:
	typedef std::unordered_map<ResID, TTF_Font*> FontPool;
	typedef std::unordered_map<ResID, SDL_Texture*> TexturePool;

	bool load_from_file(SDL_Renderer* renderer)
	{
		texture_pool[ResID::Tex_UI] = IMG_LoadTexture(renderer, "resources/ui.png");
		texture_pool[ResID::Tex_Tile] = IMG_LoadTexture(renderer, "resources/tile.png");

		for (const auto& pair : texture_pool)
			if (!pair.second) return false;

		for (const auto& pair : font_pool)
			if (!pair.second) return false;

		return true;
	}

	const FontPool& get_font_pool()
	{
		return font_pool;
	}

	const TexturePool& get_texture_pool()
	{
		return texture_pool;
	}

private:
	FontPool font_pool;
	TexturePool texture_pool;
};

ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{
}