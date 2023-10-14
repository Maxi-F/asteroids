#pragma once

#include "raylib.h"

namespace Asteroids {
	namespace AssetManager {
		enum Assets {
			SHIP = 0,
			ASSETS_COUNT
		};

		void init();
		Texture2D getTexture(Assets asset);
	}
}
