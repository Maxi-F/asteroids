#pragma once

#include "raylib.h"
#include "utils/timer.h"

namespace Asteroids {
	namespace PowerUp {
		enum PowerUpType {
			MULTI_BULLET = 0,
			SHIELD = 1,
			MORE_POINTS = 2
		};

		struct PowerUp {
			Vector2 position;
			float radius;
			double lifetime;
			PowerUpType powerUpType;
		};

		PowerUp createPowerUp(Vector2 position);
		void drawPowerUp(PowerUp powerUp);
	}
}