#pragma once
#include "force.h"
#include "accelerated_speed.h"
#include "velocity.h"
#include "impulse.h"
#include "vector2.h"
//#include "manager.h"
//#include "physics_engine_manager.h"

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>

//class PhysicsEngineManager;

enum class Shape
{
	Square,
	Circle
};

class PhysicsBox
{
public:
	PhysicsBox(Vector2 size, double m, Vector2& position, int code);
	PhysicsBox(double radius, double m, Vector2& position, int code);
	~PhysicsBox();

public:
	//friend class PhysicsEngineManager;

	void on_update(double delta)
	{
		recode_force();
		recode_accelerated_speed(delta);
		recode_inpulse();
		recode_friction(delta);
	}

	void on_render(SDL_Renderer* renderer);

	void add_accelerated_speed(AcceleratedSpeed a1)
	{
		a += a1;
	}

	void add_force(Force F1)
	{
		F += F1;
	}

	void add_impulse(Impulse I1)
	{
		//std::cout << I1.x << "  " << I1.y << std::endl;
		I += I1;
	}

	void set_u(double u)
	{
		this->u = u;
	}

	Impulse get_impulse()
	{
		return Impulse(v, m);
	}

	Impulse get_impulse_x()
	{
		Velocity v1(v.x, 0);
		return Impulse(v1, m);
	}

	Impulse get_impulse_y()
	{
		Velocity v1(0, v.y);
		return Impulse(v1, m);
	}

	double get_weight()
	{
		return m;
	}

	Velocity get_velocity()
	{
		return v;
	}

	double get_friction()
	{
		return m * 10 * u;
	}

	void set_can_bounce()
	{
		can_bounce = true;
	}

	void set_cannot_bounce()
	{
		can_bounce = false;
	}

	bool is_can_bounce()
	{ 
		return can_bounce;
	}

	Vector2 get_position()
	{
		return position;
	}

	Vector2 get_size()
	{
		return size;
	}

	void move(Vector2 x)
	{
		position += x;
	}

private:
	void recode_force()
	{
		a += F / m;
		F.clear();
	}

	void recode_accelerated_speed(double t)
	{
		v += a * t;
		a.clear();
	}

	void recode_inpulse()
	{
		v += I / m;
		I.clear();
	}

	void recode_friction(double t)
	{
		Force f(-v.direction().normalize().x * u * m * 10, -v.direction().normalize().y * u * m * 10);

		add_force(f);
		recode_force();

		if (v.x < 0)
		{
			if (v.x + (a * t).x >= 0)
				v.x = 0;
			else
				v.x += (a * t).x;
		}
		else if (v.x > 0)
		{
			if (v.x + (a * t).x <= 0)
				v.x = 0;
			else
				v.x += (a * t).x;
		}

		if (v.y < 0)
		{
			if (v.y + (a * t).y >= 0)
				v.y = 0;
			else
				v.y += (a * t).y;
		}
		else if (v.y > 0)
		{
			if (v.y + (a * t).y <= 0)
				v.y = 0;
			else
				v.y += (a * t).y;
		}

		a.clear();
	}

private:
	Vector2& position;
	Vector2 size;
	double radius = 0;
	int code = 0;
	Shape shape;

	bool can_bounce = false;

	double u = 0;
	double m = 0;
	Velocity v;
	Force F;
	AcceleratedSpeed a;
	Impulse I;

};
