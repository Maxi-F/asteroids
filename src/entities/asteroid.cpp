#include "asteroid.h"

#include "raymath.h"

#include "constants/dimensions.h"
#include "utils/math.h"
#include "utils/screen.h"
#include "assets/assetManager.h"

namespace Asteroids {
	namespace Asteroid {
		static const float SMALL_ASTEROID_RADIUS = 25;
		static const float MEDIUM_ASTEROID_RADIUS = 50;
		static const float BIG_ASTEROID_RADIUS = 100;
		static const float SMALL_ASTEROID_VELOCITY = 100.0f;
		static const float MEDIUM_ASTEROID_VELOCITY = 50.0f;
		static const float BIG_ASTEROID_VELOCITY = 25.0f;
		static const float SMALL_PLUS_ANGLE = 20.0f;
		static const float MEDIUM_PLUS_ANGLE = 10.0f;
		static const float BIG_PLUS_ANGLE = 5.0f;

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

		static float getPlusAnglePerType(AsteroidType type) {
			switch (type) {
			case AsteroidType::SMALL:
				return SMALL_PLUS_ANGLE;
			case AsteroidType::MEDIUM:
				return MEDIUM_PLUS_ANGLE;
			case AsteroidType::BIG:
				return BIG_PLUS_ANGLE;
			default:
				return 0;
			}
		}

		static Texture2D getTexturePerType(AsteroidType type) {
			switch (type) {
			case AsteroidType::SMALL:
				return AssetManager::getTexture(AssetManager::SMALL_ASTEROID);
			case AsteroidType::MEDIUM:
				return AssetManager::getTexture(GetRandomValue(1, 2) == 1 ? AssetManager::MEDIUM_ASTEROID_1 : AssetManager::MEDIUM_ASTEROID_2);
			case AsteroidType::BIG:
				return AssetManager::getTexture(AssetManager::BIG_ASTEROID);
			default:
				return AssetManager::getTexture(AssetManager::SMALL_ASTEROID);
			}
		}

		static Vector2 getRandomStartPositionPerValue(ScreenPartPerValue value, Circle prohibitedInitRadius, float asteroidRadius) {
			Vector2 initPosition;

			switch (value) {
				case ScreenPartPerValue::TOP:
					initPosition = { static_cast<float>(GetRandomValue(0, static_cast<int>(SCREEN_DIMENSIONS.x))), 0 };
					break;
				case ScreenPartPerValue::BOTTOM:
					initPosition = { static_cast<float>(GetRandomValue(0, static_cast<int>(SCREEN_DIMENSIONS.x))), SCREEN_DIMENSIONS.y };
					break;
				case ScreenPartPerValue::LEFT:
					initPosition = { 0, static_cast<float>(GetRandomValue(0, static_cast<int>(SCREEN_DIMENSIONS.y))) };
					break;
				case ScreenPartPerValue::RIGHT:
					initPosition = { SCREEN_DIMENSIONS.x, static_cast<float>(GetRandomValue(0, static_cast<int>(SCREEN_DIMENSIONS.y))) };
					break;
				default:
					initPosition = { 0, 0 };
					break;
			}

			if (checkCircleCollision({ initPosition, asteroidRadius }, prohibitedInitRadius)) {
				initPosition = getRandomStartPositionPerValue(value, prohibitedInitRadius, asteroidRadius);
			}

			return initPosition;
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

		Asteroid createAsteroid(AsteroidType type, Circle prohibitedInitRadius) {
			ScreenPartPerValue screenPartInitPart = static_cast<ScreenPartPerValue>(GetRandomValue(0, 3));
			float radius = getRadiusPerType(type);
			
			Vector2 initPosition = getRandomStartPositionPerValue(screenPartInitPart, prohibitedInitRadius, radius);
			Vector2 direction = getDirectionPerStartPosition(screenPartInitPart);
			float velocity = getVelocityByType(type);

			return {
				initPosition,
				direction,
				velocity,
				type,
				radius,
				getTexturePerType(type)
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
				getRadiusPerType(nextAsteroidType),
				getTexturePerType(nextAsteroidType)
			};
		}

		void updateAsteroid(Asteroid& asteroid) {
			asteroid.position = Vector2Add(asteroid.position, Vector2Scale(asteroid.direction, asteroid.velocity * GetFrameTime()));
			asteroid.angle += getPlusAnglePerType(asteroid.type) * GetFrameTime();

			updateAsteroidByScreenCollision(asteroid);
		};

		bool isIndivisible(Asteroid asteroid) {
			return asteroid.type == AsteroidType::SMALL;
		};

		void drawAsteroid(Asteroid asteroid) {
			Texture2D texture = asteroid.texture;

#ifdef _DEBUG
			DrawCircle(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroid.radius, RED);
#endif

			Rectangle srcRectangle = {
				0,
				0,
				static_cast<float>(texture.width),
				static_cast<float>(texture.height)
			};

			Rectangle destRectangle = {
				asteroid.position.x,
				asteroid.position.y,
				asteroid.radius * 2,
				asteroid.radius * 2
			};

			Vector2 origin = {
				static_cast<float>(asteroid.radius),
				static_cast<float>(asteroid.radius)
			};

			DrawTexturePro(
				texture,
				srcRectangle,
				destRectangle,
				origin,
				asteroid.angle,
				WHITE
			);
		};
	}
}
