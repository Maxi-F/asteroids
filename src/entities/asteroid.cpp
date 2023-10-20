#include "asteroid.h"

#include "raymath.h"

#include "constants/dimensions.h"
#include "utils/math.h"
#include "utils/screen.h"

namespace Asteroids {
	namespace Asteroid {
		static const float SMALL_ASTEROID_RADIUS = 25;
		static const float MEDIUM_ASTEROID_RADIUS = 50;
		static const float BIG_ASTEROID_RADIUS = 100;
		static const float SMALL_ASTEROID_VELOCITY = 100.0f;
		static const float MEDIUM_ASTEROID_VELOCITY = 50.0f;
		static const float BIG_ASTEROID_VELOCITY = 25.0f;

		enum ScreenPartPerValue {
			TOP = 0,
			LEFT = 1,
			RIGHT = 2,
			BOTTOM = 3
		};

		static float getRadiusPerType(AsteroidType type) {
			switch (type) {
				case AsteroidType::SMALL:
					return SMALL_ASTEROID_RADIUS;
				case AsteroidType::MEDIUM:
					return MEDIUM_ASTEROID_RADIUS;
				case AsteroidType::BIG:
					return BIG_ASTEROID_RADIUS;
				default:
					return 0;
			}
		}

		static Vector2 getRandomStartPositionPerValue(ScreenPartPerValue value) {
			switch (value) {
				case ScreenPartPerValue::TOP:
					return { static_cast<float>(GetRandomValue(0, static_cast<int>(SCREEN_DIMENSIONS.x))), 0 };
				case ScreenPartPerValue::BOTTOM:
					return { static_cast<float>(GetRandomValue(0, static_cast<int>(SCREEN_DIMENSIONS.x))), SCREEN_DIMENSIONS.y };
				case ScreenPartPerValue::LEFT:
					return { 0, static_cast<float>(GetRandomValue(0, static_cast<int>(SCREEN_DIMENSIONS.y))) };
				case ScreenPartPerValue::RIGHT:
					return { SCREEN_DIMENSIONS.x, static_cast<float>(GetRandomValue(0, static_cast<int>(SCREEN_DIMENSIONS.y))) };
				default:
					return { 0, 0 };
			}
		}

		static AsteroidType getNextType(AsteroidType type) {
			switch (type) {
				case AsteroidType::BIG:
					return AsteroidType::MEDIUM;
				case AsteroidType::MEDIUM:
					return AsteroidType::SMALL;
				default:
					return AsteroidType::SMALL;
			}
		}

		static float getVelocityByType(AsteroidType type) {
			switch (type) {
			case AsteroidType::SMALL:
				return SMALL_ASTEROID_VELOCITY;
			case AsteroidType::MEDIUM:
				return MEDIUM_ASTEROID_VELOCITY;
			case AsteroidType::BIG:
				return BIG_ASTEROID_VELOCITY;
			default:
				return 0;
			}
		}

		static Vector2 getDirectionPerStartPosition(ScreenPartPerValue value) {
			Vector2 normalizedDirection = Vector2Normalize({ static_cast<float>(GetRandomValue(1, 5)), static_cast<float>(GetRandomValue(1, 5)) });
			switch (value) {
			case ScreenPartPerValue::TOP:
				return { getRandomNegativeOrPositive() * normalizedDirection.x, normalizedDirection.y };
			case ScreenPartPerValue::BOTTOM:
				return { getRandomNegativeOrPositive() * normalizedDirection.x, -normalizedDirection.y };
			case ScreenPartPerValue::LEFT:
				return { normalizedDirection.x, getRandomNegativeOrPositive() * normalizedDirection.y };
			case ScreenPartPerValue::RIGHT:
				return { -normalizedDirection.x, getRandomNegativeOrPositive() * normalizedDirection.y };
			default:
				return { 0, 0 };
			}
		}

		static void updateAsteroidByScreenCollision(Asteroid& asteroid) {
			ScreenUtils::Entity asteroidEntity = { asteroid.position, Vector2Scale(asteroid.direction, asteroid.velocity) };
			ScreenUtils::checkPositionByScreenBounds(asteroidEntity);

			asteroid.position = asteroidEntity.position;
		}

		Asteroid createAsteroid(AsteroidType type) {
			ScreenPartPerValue screenPartInitPart = static_cast<ScreenPartPerValue>(GetRandomValue(0, 3));
			Vector2 initPosition = getRandomStartPositionPerValue(screenPartInitPart);
			Vector2 direction = getDirectionPerStartPosition(screenPartInitPart);
			float velocity = getVelocityByType(type);

			return {
				initPosition,
				direction,
				velocity,
				type,
				getRadiusPerType(type)
			};
		};

		Asteroid createDividedAsteroidFrom(Asteroid asteroid, bool clockWise) {
			AsteroidType nextAsteroidType = getNextType(asteroid.type);
			Vector2 newDirection;
			
			if (clockWise) {
				newDirection = { asteroid.direction.y, -asteroid.direction.x };
			}
			else { 
				newDirection = { -asteroid.direction.y, asteroid.direction.x };
			};

			return {
				asteroid.position,
				newDirection,
				getVelocityByType(nextAsteroidType),
				nextAsteroidType,
				getRadiusPerType(nextAsteroidType)
			};
		}

		void updateAsteroid(Asteroid& asteroid) {
			asteroid.position = Vector2Add(asteroid.position, Vector2Scale(asteroid.direction, asteroid.velocity * GetFrameTime()));

			updateAsteroidByScreenCollision(asteroid);
		};

		bool isIndivisible(Asteroid asteroid) {
			return asteroid.type == AsteroidType::SMALL;
		};

		void drawAsteroid(Asteroid asteroid) {
			DrawCircle(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroid.radius, RED);
		};
	}
}
