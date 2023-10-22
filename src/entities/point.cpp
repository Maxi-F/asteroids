#include "point.h"

#include "raymath.h"

#include <iostream>

namespace Asteroids {
	namespace Point {
		static const float INITIAL_VELOCITY = -800.0f;
		static const float ACCELERATION = 3000.0f;
		static const float POINT_RADIUS = 10.0f;

		static Vector2 getPointDirection(Vector2 asteroidPosition, Vector2 spaceshipPosition) {
			return Vector2Normalize(Vector2Subtract(asteroidPosition, spaceshipPosition));
		}

		Point createPointFrom(Vector2 asteroidPosition, Vector2 spaceshipPosition, int points) {
			Vector2 direction = getPointDirection(spaceshipPosition, asteroidPosition);

			return {
				asteroidPosition,
				direction,
				INITIAL_VELOCITY,
				ACCELERATION,
				POINT_RADIUS,
				points
			};
		};

		void updatePoint(Point& point, Vector2 spaceshipPosition) {
			point.direction = getPointDirection(spaceshipPosition, point.position);
			
			point.velocity += point.acceleration * GetFrameTime();

			point.position = Vector2Add(point.position, Vector2Scale(point.direction, point.velocity * GetFrameTime()));
		};
		
		void drawPoint(Point point) {
			DrawCircle(static_cast<int>(point.position.x), static_cast<int>(point.position.y), point.radius, PINK);
		};
	}
}
