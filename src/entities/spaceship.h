#pragma once

#include "raylib.h"

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
		};

		Ship createSpaceship();
		void updateSpaceship(Ship &spaceShip);
		void drawSpaceship(Ship spaceShip);
	}
}
