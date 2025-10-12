#include "mouse_manager.h"
#include "tools.h"

MouseManager::MouseManager()
{
	mouse_box = CollisionManager::instance()->create_mouse_box(5, relative_position);
	mouse_box->set_layer_src(tools::to_ten("10"));
	mouse_box->set_layer_dst(tools::to_ten("10100"));
	mouse_box->set_on_collide([&]() {

		});

	camera_position = CameraManager::instance()->get_position();
}

MouseManager::~MouseManager()
{
	enemy_list.clear();
}

void MouseManager::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		position.x = event.motion.x;
		position.y = event.motion.y;
		
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			left_button_on_click();
			break;
		case SDL_BUTTON_RIGHT:
			right_button_on_click();
			break;
		case SDL_BUTTON_MIDDLE:
			middle_button_on_click();
			break;
		default:
			break;
		}
	default:
		break;
	}
}

const std::shared_ptr<Object> MouseManager::get_target_enemy(Vector2 player_pos, double radious)
{

	relative_position.x = position.x + camera_position->x - 640;
	relative_position.y = position.y + camera_position->y - 360;

	for (auto object : enemy_list)
	{
		if (CollisionManager::instance()->check_mouse_collide(object->get_collide_box())
			&& (object->get_position() - player_pos).length() <= radious)
		{
			return object;
		}
	}

	return nullptr;
}