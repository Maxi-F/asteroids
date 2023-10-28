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
			AssetWithTexture bigAsteroid = { Assets::BIG_ASTEROID, LoadTexture("assets/bigAsteroid.png") };
			AssetWithTexture mediumAsteroid1 = { Assets::MEDIUM_ASTEROID_1, LoadTexture("assets/mediumAsteroid.png") };
			AssetWithTexture mediumAsteroid2 = { Assets::MEDIUM_ASTEROID_2, LoadTexture("assets/mediumAsteroid2.png") };
			AssetWithTexture smallAsteroid = { Assets::SMALL_ASTEROID, LoadTexture("assets/smallAsteroid.png") };

			textures = { 
				spaceShip,
				propulsingSpaceship,
				bigAsteroid,
				mediumAsteroid1,
				mediumAsteroid2,
				smallAsteroid
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