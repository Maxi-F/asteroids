#include "point.h"

#include "raymath.h"

#include "assets/assetManager.h"

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
#ifdef _DEBUG
			DrawCircle(static_cast<int>(point.position.x), static_cast<int>(point.position.y), point.radius, PINK);
#endif
			Texture2D texture = AssetManager::getTexture(AssetManager::POINT);

			Rectangle srcRectangle = {
				0,
				0,
				static_cast<float>(texture.width),
				static_cast<float>(texture.height)
			};

			Rectangle destRectangle = {
				point.position.x,
				point.position.y,
				point.radius * 2,
				point.radius * 2
			};

			Vector2 origin = {
				static_cast<float>(point.radius),
				static_cast<float>(point.radius)
			};

			DrawTexturePro(
				texture,
				srcRectangle,
				destRectangle,
				origin,
				0,
				WHITE
			);
		};
	}
}
