#include "assetManager.h"

#include <vector>

namespace Asteroids {
	namespace AssetManager {
		struct AssetWithTexture {
			Assets asset;
			Texture2D texture;
		};

		static std::vector<AssetWithTexture> textures;

		void init() {
			AssetWithTexture spaceShip = { Assets::SHIP, LoadTexture("assets/spaceship.png") };
			AssetWithTexture propulsingSpaceship = { Assets::PROPULSING_SHIP, LoadTexture("assets/propulsingShip.png") };
			AssetWithTexture explodedShip = { Assets::EXPLODED_SHIP, LoadTexture("assets/explodedShip.png") };
			AssetWithTexture shieldedShip = { Assets::SHIELDED_SHIP, LoadTexture("assets/shieldedShip.png") };
			AssetWithTexture shieldedPropulsingShip = { Assets::SHIELDED_PROPULSING_SHIP, LoadTexture("assets/shieldedShip.png") };

			AssetWithTexture bigAsteroid = { Assets::BIG_ASTEROID, LoadTexture("assets/bigAsteroid.png") };
			AssetWithTexture mediumAsteroid1 = { Assets::MEDIUM_ASTEROID_1, LoadTexture("assets/mediumAsteroid.png") };
			AssetWithTexture mediumAsteroid2 = { Assets::MEDIUM_ASTEROID_2, LoadTexture("assets/mediumAsteroid2.png") };
			AssetWithTexture smallAsteroid = { Assets::SMALL_ASTEROID, LoadTexture("assets/smallAsteroid.png") };
			
			AssetWithTexture bullet = { Assets::BULLET, LoadTexture("assets/bullet.png") };
			AssetWithTexture multiBullet = { Assets::MULTI_BULLET, LoadTexture("assets/multiBullet.png") };
			
			AssetWithTexture bulletsPowerUp = { Assets::BULLETS_POWER_UP, LoadTexture("assets/bulletsPowerup.png") };
			AssetWithTexture pointsPowerUp = { Assets::POINTS_POWER_UP, LoadTexture("assets/pointsPowerup.png") };
			AssetWithTexture shieldPowerUp = { Assets::SHIELD_POWER_UP, LoadTexture("assets/shieldPowerup.png") };

			AssetWithTexture life = { Assets::LIFE, LoadTexture("assets/life.png") };

			textures = { 
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
				life
			};
		}

		Texture2D getTexture(Assets asset) {
			for (size_t i = 0; i < textures.size(); i++) {
				if (asset == textures[i].asset) {
					return textures[i].texture;
				}
			}
			return {};
		}
	}
}