#pragma once
#include "raylib.h"

#include "utils/math.h"

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
			AsteroidType type;
			float radius;
			Texture2D texture;
			int points = 150;
			float angle = 0;
			bool shouldDivide = false;
		};

		Asteroid createAsteroid(AsteroidType type, Circle prohibitedInitRadius);
		Asteroid createDividedAsteroidFrom(Asteroid asteroid, bool clockWise);
		void updateAsteroid(Asteroid& asteroid);
		bool isIndivisible(Asteroid asteroid);
		void drawAsteroid(Asteroid asteroid);
	}
}
