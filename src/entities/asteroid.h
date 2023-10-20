#pragma once
#include "raylib.h"

namespace Asteroids {
	namespace Asteroid {
		enum AsteroidType {
			SMALL = 0,
			MEDIUM,
			BIG,
			TYPES_QUANTITY
		};

		struct Asteroid {
			Vector2 position;
			Vector2 direction;
			float velocity;
			float radius;
			bool shouldDivide = false;
			bool shouldRemove = false;
		};

		Asteroid createAsteroid(AsteroidType type);
		void updateAsteroid(Asteroid& asteroid);
		void drawAsteroid(Asteroid asteroid);
	}
}
