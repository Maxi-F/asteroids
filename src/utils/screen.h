#pragma once

#include "raylib.h"

namespace Asteroids {
	namespace ScreenUtils {
		struct Entity {
			Vector2 position;
			Vector2 velocity;
		};

		void checkPositionByScreenBounds(Entity& entity);
	}
}
