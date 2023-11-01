#include "assetManager.h"

#include <vector>

namespace Asteroids {
	namespace AssetManager {
		struct AssetWithTexture {
			Assets asset;
			Texture2D texture;
		};

		static AssetWithTexture textures[ASSETS_COUNT];

		void init() {
			AssetWithTexture background = { Assets::BACKGROUND, LoadTexture("res/images/background.png") };
			AssetWithTexture rules = { Assets::RULES, LoadTexture("res/images/rules.png") };
			AssetWithTexture credits = { Assets::CREDITS, LoadTexture("res/images/credits.png") };

			AssetWithTexture spaceShip = { Assets::SHIP, LoadTexture("res/images/spaceship.png") };
			AssetWithTexture propulsingSpaceship = { Assets::PROPULSING_SHIP, LoadTexture("res/images/propulsingShip.png") };
			AssetWithTexture explodedShip = { Assets::EXPLODED_SHIP, LoadTexture("res/images/explodedShip.png") };
			AssetWithTexture shieldedShip = { Assets::SHIELDED_SHIP, LoadTexture("res/images/notPropulsingShieldedShip.png") };
			AssetWithTexture shieldedPropulsingShip = { Assets::SHIELDED_PROPULSING_SHIP, LoadTexture("res/images/shieldedShip.png") };

			AssetWithTexture bigAsteroid = { Assets::BIG_ASTEROID, LoadTexture("res/images/bigAsteroid.png") };
			AssetWithTexture mediumAsteroid1 = { Assets::MEDIUM_ASTEROID_1, LoadTexture("res/images/mediumAsteroid.png") };
			AssetWithTexture mediumAsteroid2 = { Assets::MEDIUM_ASTEROID_2, LoadTexture("res/images/mediumAsteroid2.png") };
			AssetWithTexture smallAsteroid = { Assets::SMALL_ASTEROID, LoadTexture("res/images/smallAsteroid.png") };
			
			AssetWithTexture bullet = { Assets::BULLET, LoadTexture("res/images/bullet.png") };
			AssetWithTexture multiBullet = { Assets::MULTI_BULLET, LoadTexture("res/images/multiBullet.png") };
			
			AssetWithTexture bulletsPowerUp = { Assets::BULLETS_POWER_UP, LoadTexture("res/images/bulletsPowerup.png") };
			AssetWithTexture pointsPowerUp = { Assets::POINTS_POWER_UP, LoadTexture("res/images/pointsPowerup.png") };
			AssetWithTexture shieldPowerUp = { Assets::SHIELD_POWER_UP, LoadTexture("res/images/shieldPowerup.png") };
			AssetWithTexture emptyPowerUp = { Assets::EMPTY_POWER_UP, LoadTexture("res/images/emptyPowerUp.png") };

			AssetWithTexture life = { Assets::LIFE, LoadTexture("res/images/life.png") };
			AssetWithTexture point = { Assets::POINT, LoadTexture("res/images/point.png") };
			AssetWithTexture pause = { Assets::PAUSE, LoadTexture("res/images/pause.png") };

			AssetWithTexture auxTextures[ASSETS_COUNT] = {
				background,
				rules,
				credits,
				spaceShip,
				propulsingSpaceship,
				explodedShip,
				shieldedShip,
				shieldedPropulsingShip,
				bigAsteroid,
				mediumAsteroid1,
				mediumAsteroid2,
				smallAsteroid,
				bullet,
				multiBullet,
				bulletsPowerUp,
				pointsPowerUp,
				shieldPowerUp,
				emptyPowerUp,
				life,
				point,
				pause
			};

			for (int i = 0; i < ASSETS_COUNT; i++) {
				textures[i] = auxTextures[i];
			}
		}

		Texture2D getTexture(Assets asset) {
			for (int i = 0; i < ASSETS_COUNT; i++) {
				if (asset == textures[i].asset) {
					return textures[i].texture;
				}
			}
			return {};
		}
	}
}