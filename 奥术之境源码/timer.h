#pragma once

#include <functional>
/*
* set_wait_time�趨��ʱʱ��
* set_one_shoot�趨���δ���
* set_on_timeout�趨�����ص�
* restart���¿�ʼ
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