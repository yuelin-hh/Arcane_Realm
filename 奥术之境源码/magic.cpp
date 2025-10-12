#include "magic.h"

Magic::Magic()
{
	const ResourcesManager::FontPool& font_pool
		= ResourcesManager::instance()->get_font_pool();

	font = font_pool.find(ResID::Font_Main)->second;

	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_ui = tex_pool.find(ResID::Tex_MagicUI)->second;

	anim_ui_can_release.set_loop(true);
	anim_ui_can_release.set_interval(0.3);
	anim_ui_can_release.set_frame_data(tex_ui, 2, 1, { 0 });

	anim_ui_cannot_release.set_loop(true);
	anim_ui_cannot_release.set_interval(0.3);
	anim_ui_cannot_release.set_frame_data(tex_ui, 2, 1, { 1 });
}

Magic::~Magic()
{
}

void Magic::small_number_on_render(SDL_Renderer* renderer)
{
	std::string red_val = std::to_string((int)(consumption));
	SDL_Surface* red_surface = TTF_RenderUTF8_Blended(font, red_val.c_str(), color_red);
	SDL_Texture* red_texture = SDL_CreateTextureFromSurface(renderer, red_surface);

	std::string black_val = std::to_string((int)(consumption));
	SDL_Surface* black_surface = TTF_RenderUTF8_Blended(font, black_val.c_str(), color_black);
	SDL_Texture* black_texture = SDL_CreateTextureFromSurface(renderer, black_surface);

	SDL_Rect rect;
	rect.x = (int)(position_angle.x + 70);
	rect.y = (int)(position_angle.y + 2);
	rect.w = red_surface->w;
	rect.h = red_surface->h;
	if (is_mp_sufficien)
		SDL_RenderCopy(renderer, black_texture, NULL, &rect);
	else
		SDL_RenderCopy(renderer, red_texture, NULL, &rect);

	SDL_DestroyTexture(red_texture);
	SDL_FreeSurface(red_surface);
	SDL_DestroyTexture(black_texture);
	SDL_FreeSurface(black_surface);
}

void Magic::big_number_on_recder(SDL_Renderer* renderer)
{
	std::string red_val = std::to_string((int)(consumption));
	SDL_Surface* red_surface = TTF_RenderUTF8_Blended(font, red_val.c_str(), color_red);
	SDL_Texture* red_texture = SDL_CreateTextureFromSurface(renderer, red_surface);

	std::string black_val = std::to_string((int)(consumption));
	SDL_Surface* black_surface = TTF_RenderUTF8_Blended(font, black_val.c_str(), color_black);
	SDL_Texture* black_texture = SDL_CreateTextureFromSurface(renderer, black_surface);

	SDL_Rect rect;
	rect.x = (int)(position_angle.x + 102);
	rect.y = (int)(position_angle.y - 156);
	rect.w = red_surface->w * 2;
	rect.h = red_surface->h * 2;
	if (is_mp_sufficien)
		SDL_RenderCopy(renderer, black_texture, NULL, &rect);
	else
		SDL_RenderCopy(renderer, red_texture, NULL, &rect);

	SDL_DestroyTexture(red_texture);
	SDL_FreeSurface(red_surface);
	SDL_DestroyTexture(black_texture);
	SDL_FreeSurface(black_surface);
}