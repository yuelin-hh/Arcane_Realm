#pragma once
#include "manager.h"
#include "retention.h"

#include <vector>

class RetentionManager:public Manager<RetentionManager>
{
	friend class Manager<RetentionManager>;
	struct RetentionStruct
	{
		Vector2 pos;
		Vector2 size;
		Retention retention;
		double angle = 0.0;
	};
	using RetentionList = std::vector<RetentionStruct>;
protected:
	RetentionManager();
	~RetentionManager();

public:
	void on_update(double delta);

	void on_renderer(SDL_Renderer* renderer);

	void set_retention(Animation* anim, Vector2 pos, Vector2 size, double angle = 0.0);

private:
	RetentionList retention_list;
};