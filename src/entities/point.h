#pragma once
#include "raylib.h"

namespace Asteroids {
	namespace Point {
		struct Point {
			Vector2 position;
			Vector2 direction;
			float velocity;
			float acceleration;
			float radius;
			int points;
		};

		Point createPointFrom(Vector2 asteroidPosition, Vector2 spaceshipPosition, int points);
		void updatePoint(Point& point, Vector2 spaceshipPosition);
		void drawPoint(Point point);
	}
}
