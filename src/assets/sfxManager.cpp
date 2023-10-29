#include "sfxManager.h"

#include <vector>

namespace Asteroids {
	namespace SfxManager {
		struct SfxWithName {
			SfxName name;
			Sound sound;
		};

		static std::vector<SfxWithName> sfxs;

		void init() {
			SfxWithName bulletCollision1 = { BULLET_COLLISION_1, LoadSound("res/sounds/bulletCollision1.wav") };
			SfxWithName bulletCollision2 = { BULLET_COLLISION_2, LoadSound("res/sounds/bulletCollision2.wav") };
			SfxWithName bulletsActivation = { BULLETS_POWER_UP_ACTIVATION, LoadSound("res/sounds/bulletsActivation.wav") };
			SfxWithName bulletsDeactivation = { BULLETS_POWER_UP_DEACTIVATION, LoadSound("res/sounds/bulletsDeactivation.wav") };
			SfxWithName pointsActivation = { POINTS_POWER_UP_ACTIVATION, LoadSound("res/sounds/pointsActivation.wav") };
			SfxWithName pointsDeactivation = { POINTS_POWER_UP_DEACTIVATION, LoadSound("res/sounds/pointsDeactivation.wav") };
			SfxWithName shieldActivation = { SHIELD_POWER_UP_ACTIVATION, LoadSound("res/sounds/shieldActivation.wav") };
			SfxWithName shieldDeactivation = { SHIELD_POWER_UP_DEACTIVATION, LoadSound("res/sounds/shieldDeactivation.wav") };
			SfxWithName points1 = { POINTS_1, LoadSound("res/sounds/points1.wav") };
			SfxWithName points2 = { POINTS_2, LoadSound("res/sounds/points2.wav") };
			SfxWithName points3 = { POINTS_3, LoadSound("res/sounds/points3.wav") };
			SfxWithName shoot1 = { SHOOT_1, LoadSound("res/sounds/shoot1.wav") };
			SfxWithName shoot2 = { SHOOT_2, LoadSound("res/sounds/shoot2.wav") };
			SfxWithName shipCollision = { SHIP_COLLISION, LoadSound("res/sounds/shipCollision.wav") };
			SfxWithName propulsion = { PROPULSION, LoadSound("res/sounds/propulsion.wav") };

			SetSoundVolume(shoot1.sound, 1);
			SetSoundVolume(shoot2.sound, 1);

			sfxs = {
				bulletCollision1,
				bulletCollision2,
				bulletsActivation,
				bulletsDeactivation,
				pointsActivation,
				pointsDeactivation,
				points1,
				points2,
				points3,
				shoot1,
				shoot2,
				shipCollision,
				propulsion
			};
		};

		void stopAllSounds() {
			for (size_t i = 0; i < sfxs.size(); i++) {
				StopSound(sfxs[i].sound);
			}
		}
		
		void playSound(SfxName sfxName, bool shouldOverlap) {
			for (size_t i = 0; i < sfxs.size(); i++) {
				if (sfxName == sfxs[i].name && (shouldOverlap || !IsSoundPlaying(sfxs[i].sound))) {
					PlaySound(sfxs[i].sound);
				}
			}
		};
	}
}