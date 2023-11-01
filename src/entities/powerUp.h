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
			Timer::Timer lifetimeInMapTimer;
			PowerUpType powerUpType;
		};

		Texture2D getTexturePerType(PowerUpType powerUpType);
		PowerUp createPowerUp(Vector2 position);
		void drawPowerUp(PowerUp powerUp);
		void drawPowerUp(PowerUp powerUp, Color color);
		void pauseTimer(PowerUp& powerUp);
		void unpauseTimer(PowerUp& powerUp);
	}
}
