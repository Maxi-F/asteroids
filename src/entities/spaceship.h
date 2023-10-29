#pragma once

#include "raylib.h"

#include "utils/timer.h"

namespace Asteroids {
	namespace Spaceship {
		struct Ship {
			float shipRadius;
			float rotation;
			float acceleration;

			Vector2 position;
			Vector2 direction;
			Vector2 velocity;
			Texture2D texture;
			bool isPropulsing = false;
		};

		Ship createSpaceship();
		void updateSpaceship(Ship &spaceShip);
		void restartSpaceship(Ship &spaceShip);
		void drawSpaceship(Ship spaceShip, bool isDeathPlaying, Timer::Timer deathTimer);
	}
}
