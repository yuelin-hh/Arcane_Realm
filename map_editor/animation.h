#pragma once
#include "timer.h"
#include "vector2.h"

#include <SDL.h>
#include <vector>
#include <functional>

class Animation
{
public:
	typedef std::function<void()> PlayCallback;
	Animation();
	~Animation();

	void reset();

	void set_frame_data(SDL_Texture* texture, int num_h, int num_v, const std::vector<int>& idx_list);

	void set_loop(bool is_loop);

	void set_interval(double interval);

	void set_on_finished(PlayCallback on_finished);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer, const SDL_Point& pos_dst, double angle = 0) const;

	void on_render(SDL_Renderer* renderer, const SDL_Rect& rect_dst, double angle = 0) const;

	void set_scaling(double scaling);
private:
	Timer timer;
	double scaling = 1;
	bool is_loop = true;
	size_t idx_frame = 0;
	PlayCallback on_finished;
	SDL_Texture* texture = nullptr;
	std::vector<SDL_Rect> rect_src_list;
	int width_frame = 0, height_frame = 0;
};

Animation::Animation()
{
	timer.set_one_shot(false);
	timer.set_on_timeout(
		[&]()
		{
			idx_frame++;
			if (idx_frame >= rect_src_list.size())
			{
				idx_frame = is_loop ? 0 : rect_src_list.size() - 1;
				if (!is_loop && on_finished)
					on_finished();
			}
		}
	);
}

Animation::~Animation()
{

}

void Animation::reset()
{
	timer.restart();

	idx_frame = 0;
}

void Animation::set_frame_data(SDL_Texture* texture, int num_h, int num_v, const std::vector<int>& idx_list)
{
	int width_tex, height_tex;

	this->texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &width_tex, &height_tex);
	width_frame = width_tex / num_h, height_frame = height_tex / num_v;

	rect_src_list.resize(idx_list.size());
	for (size_t i = 0; i < idx_list.size(); i++)
	{
		int idx = idx_list[i];
		SDL_Rect& rect_src = rect_src_list[i];

		rect_src.x = (idx % num_h) * width_frame;
		rect_src.y = (idx / num_h) * height_frame;
		rect_src.w = width_frame, rect_src.h = height_frame;
	}
}

void Animation::set_loop(bool is_loop)
{
	this->is_loop = is_loop;
}

void Animation::set_interval(double interval)
{
	timer.set_wait_time(interval);
}

void Animation::set_on_finished(PlayCallback on_finished)
{
	this->on_finished = on_finished;
}

void Animation::on_update(double delta)
{
	timer.on_update(delta);
}

void Animation::on_render(SDL_Renderer* renderer, const SDL_Point& pos_dst, double angle) const
{
	static SDL_Rect rect_dst;

	rect_dst.x = pos_dst.x;
	rect_dst.y = pos_dst.y;
	rect_dst.w = (int)(width_frame * scaling);
	rect_dst.h = (int)(height_frame * scaling);

	SDL_RenderCopyEx(renderer, texture, &rect_src_list[idx_frame], &rect_dst, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Animation::on_render(SDL_Renderer* renderer, const SDL_Rect& rect_dst, double angle) const
{
	SDL_RenderCopyEx(renderer, texture, &rect_src_list[idx_frame], &rect_dst, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Animation::set_scaling(double scaling)
{
	this->scaling = scaling;
}