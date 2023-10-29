#include "powerUp.h"

#include "assets/assetManager.h"

namespace Asteroids {
	namespace PowerUp {
		static const float POWER_UP_RADIUS = 20.0f;
		static const double MULTI_BULLET_LIFETIME = 15.0;
		static const double MORE_POINTS_LIFETIME = 15.0;
		static const double SHIELD_LIFETIME = 10.0;
		static const double LIFETIME_IN_MAP = 5.0;

		static Color getColorPerType(PowerUpType powerUpType) {
			switch (powerUpType) {
				case PowerUpType::MULTI_BULLET:
					return GREEN;
				case PowerUpType::SHIELD:
					return VIOLET;
				case PowerUpType::MORE_POINTS:
					return BLUE;
				default:
					return BLACK;
			}
		}

		static Texture2D getTexturePerType(PowerUpType powerUpType) {
			switch (powerUpType) {
			case PowerUpType::MULTI_BULLET:
				return AssetManager::getTexture(AssetManager::BULLETS_POWER_UP);
			case PowerUpType::SHIELD:
				return AssetManager::getTexture(AssetManager::SHIELD_POWER_UP);
			case PowerUpType::MORE_POINTS:
				return AssetManager::getTexture(AssetManager::POINTS_POWER_UP);
			default:
				return AssetManager::getTexture(AssetManager::POINTS_POWER_UP);
			}
		}

		static double getLifetimePerType(PowerUpType powerUpType) {
			switch (powerUpType) {
			case PowerUpType::MULTI_BULLET:
				return MULTI_BULLET_LIFETIME;
			case PowerUpType::SHIELD:
				return MORE_POINTS_LIFETIME;
			case PowerUpType::MORE_POINTS:
				return SHIELD_LIFETIME;
			default:
				return 0;
			}
		}

		static PowerUpType getRandomPowerUpType() {
			return static_cast<PowerUpType>(GetRandomValue(
				static_cast<int>(PowerUpType::MULTI_BULLET),
				static_cast<int>(PowerUpType::MORE_POINTS)
			));
		}

		PowerUp createPowerUp(Vector2 position) {
			PowerUpType powerUpType = getRandomPowerUpType();
			Timer::Timer lifetimeInMapTimer;
			Timer::startTimer(&lifetimeInMapTimer, LIFETIME_IN_MAP);

			return {
				position,
				POWER_UP_RADIUS,
				getLifetimePerType(powerUpType),
				lifetimeInMapTimer,
				powerUpType,
			};
		};

		void drawPowerUp(PowerUp powerUp) {
#ifdef _DEBUG
			DrawCircle(
				static_cast<int>(powerUp.position.x),
				static_cast<int>(powerUp.position.y),
				POWER_UP_RADIUS,
				getColorPerType(powerUp.powerUpType)
			);
#endif

			Texture2D texture = getTexturePerType(powerUp.powerUpType);

			Rectangle srcRectangle = {
				0,
				0,
				static_cast<float>(texture.width),
				static_cast<float>(texture.height)
			};

			Rectangle destRectangle = {
				powerUp.position.x,
				powerUp.position.y,
				powerUp.radius * 2,
				powerUp.radius * 2
			};

			Vector2 origin = {
				static_cast<float>(powerUp.radius),
				static_cast<float>(powerUp.radius)
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

		void pauseTimer(PowerUp& powerUp) {
			Timer::pauseTimer(&powerUp.lifetimeInMapTimer);
		}

		void unpauseTimer(PowerUp& powerUp) {
			Timer::unPauseTimer(&powerUp.lifetimeInMapTimer);
		}
	}
}