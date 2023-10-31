#pragma once

#include "raylib.h"

namespace Asteroids {
	namespace SfxManager {
		enum SfxName {
			BULLET_COLLISION_1 = 0,
			BULLET_COLLISION_2,
			BULLETS_POWER_UP_ACTIVATION,
			BULLETS_POWER_UP_DEACTIVATION,
			POINTS_POWER_UP_ACTIVATION,
			POINTS_POWER_UP_DEACTIVATION,
			SHIELD_POWER_UP_ACTIVATION,
			SHIELD_POWER_UP_DEACTIVATION,
			POINTS_1,
			POINTS_2,
			POINTS_3,
			SHOOT_1,
			SHOOT_2,
			SHIP_COLLISION,
			SHIELD_ASTEROID_COLLISION,
			PROPULSION,
			SFX_COUNT
		};

		enum MusicName {
			GAMEPLAY = 0,
			MENU,
			MUSIC_COUNT
		};

		void init();
		void stopAllSounds();
		void playSound(SfxName name, bool shouldOverlap);
		void stopSound(SfxName sfxName);
		void playMusic(MusicName name);
		void updateMusic(MusicName musicName);
		void stopAllMusic();
	}
}
