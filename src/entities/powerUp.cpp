#include "powerUp.h"

namespace Asteroids {
	namespace PowerUp {
		static const float POWER_UP_RADIUS = 10.0f;
		static const double MULTI_BULLET_LIFETIME = 15.0;
		static const double MORE_POINTS_LIFETIME = 15.0;
		static const double SHIELD_LIFETIME = 10.0;

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

			return {
				position,
				POWER_UP_RADIUS,
				getLifetimePerType(powerUpType),
				powerUpType
			};
		};
		
		void drawPowerUp(PowerUp powerUp) {
			DrawCircle(
				static_cast<int>(powerUp.position.x),
				static_cast<int>(powerUp.position.y),
				POWER_UP_RADIUS,
				getColorPerType(powerUp.powerUpType)
			);
		};
	}
}