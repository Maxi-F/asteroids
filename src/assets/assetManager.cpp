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

			textures = { spaceShip };
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