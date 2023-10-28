#pragma once

#include "raylib.h"

namespace Asteroids {
	namespace AssetManager {
		enum Assets {
			SHIP = 0,
			PROPULSING_SHIP,
			BIG_ASTEROID,
			MEDIUM_ASTEROID_1,
			MEDIUM_ASTEROID_2,
			SMALL_ASTEROID,
			ASSETS_COUNT
		};

		void init();
		Texture2D getTexture(Assets asset);
	}
}
