#pragma once

#include <functional>
/*
* set_wait_time设定计时时间
* set_one_shoot设定单次触发
* set_on_timeout设定触发回调
* restart重新开始
*/
class Timer
{
public:
	Timer();
	~Timer();

	void restart();

	void set_wait_time(double val);

	void set_one_shot(bool flag);

	void set_on_timeout(std::function<void()> on_timeout);

	void pause();

	void resume();

	void on_update(double delta);

private:
	double pass_time = 0;
	double wait_time = 0;
	bool paused = false;
	bool shotted = false;
	bool one_shot = false;
	std::function<void()> on_timeout;

};