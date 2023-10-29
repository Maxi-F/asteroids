#pragma once

#include "raylib.h"

namespace Asteroids {
	namespace AssetManager {
		enum Assets {
			SHIP = 0,
			PROPULSING_SHIP,
			EXPLODED_SHIP,
			SHIELDED_SHIP,
			SHIELDED_PROPULSING_SHIP,
			BIG_ASTEROID,
			MEDIUM_ASTEROID_1,
			MEDIUM_ASTEROID_2,
			SMALL_ASTEROID,
			BULLET,
			BULLETS_POWER_UP,
			POINTS_POWER_UP,
			SHIELD_POWER_UP,
			MULTI_BULLET,
			LIFE,
			ASSETS_COUNT
		};

		void init();
		Texture2D getTexture(Assets asset);
	}
}
