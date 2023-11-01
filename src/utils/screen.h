#pragma once
#include "raylib.h"

namespace Asteroids {
	namespace ScreenUtils {
		struct Entity {
			Vector2 position;
			Vector2 velocity;
		};

		float getScreenWidth();
		float getScreenHeight();
		float getScaleRelativeByScreen(float value);
		void checkPositionByScreenBounds(Entity& entity);
	}
}
