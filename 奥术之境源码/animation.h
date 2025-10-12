#pragma once

#include "timer.h"
#include "vector2.h"
#include "camera_manager.h"

#include <SDL.h>
#include <vector>
#include <functional>

/*
* set_frame_data(����һ��ͼ�м��ţ��м��У�ȡ�ļ���ͼ)
* set_loop�趨�Ƿ�ѭ������
* set_interval�趨֡���
* set_scaling�趨���ű�����Ĭ��Ϊһ
* set_on_finish�趨�������ص�
*/
class Animation
{
public:
	typedef std::function<void()> PlayCallback;

public:
	Animation();

	~Animation();

	void reset();

	void set_frame_data(SDL_Texture* texture, int num_h, int num_v, const std::vector<int>& idx_list);

	void set_loop(bool is_loop);

	void set_interval(double interval);

	void set_on_finished(PlayCallback on_finished);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer, const SDL_Point& pos_dst, double angle = 0) const;

	void on_render_lock(SDL_Renderer* renderer, const SDL_Point& pos_dst, double angle = 0) const;

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