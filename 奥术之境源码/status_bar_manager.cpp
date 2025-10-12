#include "status_bar_manager.h"

#include <string>

StatusBarManager::StatusBarManager()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_status_bar = tex_pool.find(ResID::Tex_StatusBar)->second;
	SDL_Texture* tex_photo = tex_pool.find(ResID::Tex_ClaudePhoto)->second;

	anim_status_bar.set_loop(true);
	anim_status_bar.set_interval(0.3);
	anim_status_bar.set_frame_data(tex_status_bar, 1, 1, { 0 });

	anim_photo.set_loop(true);
	anim_photo.set_interval(0.3);
	anim_photo.set_scaling(0.2);
	anim_photo.set_frame_data(tex_photo, 1, 1, { 0 });

	position.x = 0, position.y = 0;

	const ResourcesManager::FontPool& font_pool
		= ResourcesManager::instance()->get_font_pool();

	font = font_pool.find(ResID::Font_Main)->second;
}

StatusBarManager::~StatusBarManager()
{

}

void StatusBarManager::number_on_renderer(SDL_Renderer* renderer)
{
	SDL_Rect rect;

	rect.x = 144;
	rect.y = 96;
	rect.h = 12;
	rect.w = (int)(184 * hp / max_hp);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);

	rect.y = 124;
	rect.w = (int)(184 * mp / max_mp);
	SDL_SetRenderDrawColor(renderer, 50, 100, 255, 255);
	SDL_RenderFillRect(renderer, &rect);

	SDL_Color color = { 0,0,0,255 };
	SDL_Surface* slash_surface = TTF_RenderUTF8_Blended(font, u8"/", color);
	SDL_Texture* slash_texture = SDL_CreateTextureFromSurface(renderer, slash_surface);

	std::string hp_val = std::to_string((int)(hp));
	SDL_Surface* hp_surface = TTF_RenderUTF8_Blended(font, hp_val.c_str(), color);
	SDL_Texture* hp_texture = SDL_CreateTextureFromSurface(renderer, hp_surface);

	std::string max_hp_val = std::to_string((int)(max_hp));
	SDL_Surface* max_hp_surface = TTF_RenderText_Solid(font, max_hp_val.c_str(), color);
	SDL_Texture* max_hp_texture = SDL_CreateTextureFromSurface(renderer, max_hp_surface);

	std::string mp_val = std::to_string((int)(mp));
	SDL_Surface* mp_surface = TTF_RenderText_Solid(font, mp_val.c_str(), color);
	SDL_Texture* mp_texture = SDL_CreateTextureFromSurface(renderer, mp_surface);

	std::string max_mp_val = std::to_string((int)(max_mp));
	SDL_Surface* max_mp_surface = TTF_RenderText_Solid(font, max_mp_val.c_str(), color);
	SDL_Texture* max_mp_texture = SDL_CreateTextureFromSurface(renderer, max_mp_surface);

	SDL_Rect rect_text;

	rect_text.h = slash_surface->h;
	rect_text.w = slash_surface->w;
	rect_text.y = 96;
	rect_text.x = 236;
	SDL_RenderCopy(renderer, slash_texture, NULL, &rect_text);
	rect_text.y = 124;
	SDL_RenderCopy(renderer, slash_texture, NULL, &rect_text);

	rect_text.y = 96;
	rect_text.x = 200;
	rect_text.h = hp_surface->h;
	rect_text.w = hp_surface->w;
	SDL_RenderCopy(renderer, hp_texture, NULL, &rect_text);
	rect_text.x = 260;
	rect_text.h = max_hp_surface->h;
	rect_text.w = max_hp_surface->w;
	SDL_RenderCopy(renderer, max_hp_texture, NULL, &rect_text);

	rect_text.y = 124;
	rect_text.x = 212;
	rect_text.h = mp_surface->h;
	rect_text.w = mp_surface->w;
	SDL_RenderCopy(renderer, mp_texture, NULL, &rect_text);
	rect_text.x = 260;
	rect_text.h = max_mp_surface->h;
	rect_text.w = max_mp_surface->w;
	SDL_RenderCopy(renderer, max_mp_texture, NULL, &rect_text);

	SDL_DestroyTexture(slash_texture);
	SDL_FreeSurface(slash_surface);
	SDL_DestroyTexture(hp_texture);
	SDL_FreeSurface(hp_surface);
	SDL_DestroyTexture(max_hp_texture);
	SDL_FreeSurface(max_hp_surface);
	SDL_DestroyTexture(mp_texture);
	SDL_FreeSurface(mp_surface);
	SDL_DestroyTexture(max_mp_texture);
	SDL_FreeSurface(max_mp_surface);
}

void StatusBarManager::on_update(double delta)
{

}

void StatusBarManager::on_render(SDL_Renderer* renderer)
{
	SDL_Point point;
	point.x = position.x;
	point.y = position.y;
	anim_status_bar.on_render_lock(renderer, point);
	point.x += 8;
	point.y += 8;
	anim_photo.on_render_lock(renderer, point);

	number_on_renderer(renderer);
}

void StatusBarManager::set_hp(double max_hp, double hp)
{
	this->max_hp = max_hp;
	this->hp = hp;
}

void StatusBarManager::set_mp(double max_mp, double mp)
{
	this->max_mp = max_mp;
	this->mp = mp;
}