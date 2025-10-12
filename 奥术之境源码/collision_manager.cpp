#ifdef _DEBUG
#define IS_DEBUG true
#else
#define IS_DEBUG false
#endif 

#include "collision_manager.h"

Vector2 nearest_point(const Vector2& circle_pos, const Vector2& rect_pos, const Vector2& rect_size)
{
	double k = (circle_pos.y - rect_pos.y) / (circle_pos.x - rect_pos.x);
	double b = circle_pos.y - k * circle_pos.x;

	auto f1 = [k, b](double x) {return (k * x + b); };
	auto f2 = [k, b](double y) {return ((y - b) / k); };
	Vector2 point;

	if (circle_pos.x <= rect_pos.x)
	{
		point.x = rect_pos.x - rect_size.x / 2;
		point.y = f1(point.x);
	}
	else
	{
		point.x = rect_pos.x + rect_size.x / 2;
		point.y = f1(point.x);
	}

	if (point.y >= rect_pos.y - rect_size.y / 2 && point.y <= rect_pos.y + rect_size.y / 2)
		return point;

	if (circle_pos.y <= rect_pos.y)
	{
		point.y = rect_pos.y - rect_size.y / 2;
		point.x = f2(point.y);
	}
	else
	{
		point.y = rect_pos.y + rect_size.y / 2;
		point.x = f2(point.y);
	}

	return point;
}

bool square_square(std::shared_ptr<CollideBox> src, std::shared_ptr<CollideBox> dst)
{
	if (abs(src->get_position().x - dst->get_position().x) < (src->get_size().x + dst->get_size().x) / 2 &&
		abs(src->get_position().y - dst->get_position().y) < (src->get_size().y + dst->get_size().y) / 2)
	{
		return true;
	}
	else return false;
}

bool square_circle(std::shared_ptr<CollideBox> src, std::shared_ptr<CollideBox> dst)
{
	if (dst->get_position().x >= src->get_position().x - src->get_size().x / 2 &&
		dst->get_position().x <= src->get_position().x + src->get_size().x / 2 &&
		dst->get_position().y >= src->get_position().y - src->get_size().y / 2 &&
		dst->get_position().y <= src->get_position().y + src->get_size().y / 2)
		return true;

	Vector2 point = nearest_point(dst->get_position(), src->get_position(), src->get_size());

	if ((point - dst->get_position()).length() <= dst->get_radius())
		return true;
	return false;
}

bool circle_square(std::shared_ptr<CollideBox> src, std::shared_ptr<CollideBox> dst)
{
	if (src->get_position().x >= dst->get_position().x - dst->get_size().x / 2 &&
		src->get_position().x <= dst->get_position().x + dst->get_size().x / 2 &&
		src->get_position().y >= dst->get_position().y - dst->get_size().y / 2 &&
		src->get_position().y <= dst->get_position().y + dst->get_size().y / 2)
		return true;

	Vector2 point = nearest_point(src->get_position(), dst->get_position(), dst->get_size());

	if ((point - src->get_position()).length() <= src->get_radius())
		return true;
	return false;
}

bool circle_circle(std::shared_ptr<CollideBox> src, std::shared_ptr<CollideBox> dst)
{
	if ((src->get_position() - dst->get_position()).length() < (src->get_radius() + dst->get_radius()))
		return true;
	else return false;
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
	collide_box_list.clear();
}

void CollisionManager::on_update(double delta)
{
	check_collide();
	remove_invalid_box();
}

void CollisionManager::on_render(SDL_Renderer* renderer)
{
	if (!IS_DEBUG)
		return;

	for (auto& box : collide_box_list)
	{
		box->on_render(renderer);
	}

	mouse_box->on_render(renderer);
}

std::shared_ptr<CollideBox> CollisionManager::create_collide_box(Vector2 size, const Vector2& position)
{
	std::shared_ptr<CollideBox> box = std::make_shared<CollideBox>(CollisionShape::Spuare, size, position, code);
	code++;
	collide_box_list.push_back(box);
	return box;
}

std::shared_ptr<CollideBox> CollisionManager::create_collide_box(double radius, const Vector2& position)
{
	std::shared_ptr<CollideBox> box = std::make_shared<CollideBox>(CollisionShape::Circle, radius, position, code);
	code++;
	collide_box_list.push_back(box);
	return box;
}

std::shared_ptr<CollideBox> CollisionManager::create_mouse_box(double radius, const Vector2& position)
{
	std::shared_ptr<CollideBox> box = std::make_shared<CollideBox>(CollisionShape::Circle, radius, position, 0);
	mouse_box = box;
	return box;
}

bool CollisionManager::check_mouse_collide(std::shared_ptr<CollideBox> box)
{
	if (!box->is_enable()) return false;

	if (box->get_shape() == CollisionShape::Spuare)
	{
		if (circle_square(mouse_box, box))
		{
			return true;
		}
	}
	else if (box->get_shape() == CollisionShape::Circle)
	{
		if (circle_circle(mouse_box, box))
		{
			return true;
		}
	}

	return false;
}

void CollisionManager::remove_invalid_box()
{
	for (auto it = collide_box_list.begin(); it != collide_box_list.end();)
	{
		if ((*it)->can_remove())
		{
			it = collide_box_list.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void CollisionManager::check_collide()
{
	for (auto box_src : collide_box_list)
	{
		if (!box_src->is_enable()) continue;

		if(box_src->get_lock_target() == 0)
			for (auto box_dst : collide_box_list)
			{
				if (!box_dst->is_enable() || !(box_src->get_layer_dst() & box_dst->get_layer_src()) || box_src == box_dst) continue;

				if (box_src->get_shape() == CollisionShape::Spuare && box_dst->get_shape() == CollisionShape::Spuare)
				{
					if (square_square(box_src, box_dst))
					{
						if (box_src->get_is_self())
						{
							box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
							continue;
						}
						box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
						box_dst->is_need_damage() ? box_dst->is_on_collide(box_src->get_damage(), box_src->get_buff()) : box_dst->is_on_collide();
					}
				}
				else if (box_src->get_shape() == CollisionShape::Spuare && box_dst->get_shape() == CollisionShape::Circle)
				{
					if (square_circle(box_src, box_dst))
					{
						if (box_src->get_is_self())
						{
							box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
							continue;
						}
						box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
						box_dst->is_need_damage() ? box_dst->is_on_collide(box_src->get_damage(), box_src->get_buff()) : box_dst->is_on_collide();
					}
				}
				else if (box_src->get_shape() == CollisionShape::Circle && box_dst->get_shape() == CollisionShape::Spuare)
				{
					if (circle_square(box_src, box_dst))
					{
						if (box_src->get_is_self())
						{
							box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
							continue;
						}
						box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
						box_dst->is_need_damage() ? box_dst->is_on_collide(box_src->get_damage(), box_src->get_buff()) : box_dst->is_on_collide();
					}
				}
				else if (box_src->get_shape() == CollisionShape::Circle && box_dst->get_shape() == CollisionShape::Circle)
				{
					if (circle_circle(box_src, box_dst))
					{
						if (box_src->get_is_self())
						{
							box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
							continue;
						}
						box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
						box_dst->is_need_damage() ? box_dst->is_on_collide(box_src->get_damage(), box_src->get_buff()) : box_dst->is_on_collide();
					}
				}
			}
		else
			for (auto box_dst : collide_box_list)
			{
				if (!box_dst->is_enable() || box_src->get_lock_target()!=box_dst->get_code()) continue;

				if (box_src->get_shape() == CollisionShape::Spuare && box_dst->get_shape() == CollisionShape::Spuare)
				{
					if (square_square(box_src, box_dst))
					{
						if (box_src->get_is_self())
						{
							box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
							continue;
						}
						box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
						box_dst->is_need_damage() ? box_dst->is_on_collide(box_src->get_damage(), box_src->get_buff()) : box_dst->is_on_collide();
					}
				}
				else if (box_src->get_shape() == CollisionShape::Spuare && box_dst->get_shape() == CollisionShape::Circle)
				{
					if (square_circle(box_src, box_dst))
					{
						if (box_src->get_is_self())
						{
							box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
							continue;
						}
						box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
						box_dst->is_need_damage() ? box_dst->is_on_collide(box_src->get_damage(), box_src->get_buff()) : box_dst->is_on_collide();
					}
				}
				else if (box_src->get_shape() == CollisionShape::Circle && box_dst->get_shape() == CollisionShape::Spuare)
				{
					if (circle_square(box_src, box_dst))
					{
						if (box_src->get_is_self())
						{
							box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
							continue;
						}
						box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
						box_dst->is_need_damage() ? box_dst->is_on_collide(box_src->get_damage(), box_src->get_buff()) : box_dst->is_on_collide();
					}
				}
				else if (box_src->get_shape() == CollisionShape::Circle && box_dst->get_shape() == CollisionShape::Circle)
				{
					if (circle_circle(box_src, box_dst))
					{
						if (box_src->get_is_self())
						{
							box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
							continue;
						}
						box_src->is_need_damage() ? box_src->is_on_collide(box_dst->get_damage(), box_src->get_buff()) : box_src->is_on_collide();
						box_dst->is_need_damage() ? box_dst->is_on_collide(box_src->get_damage(), box_src->get_buff()) : box_dst->is_on_collide();
					}
				}
			}
	}
}