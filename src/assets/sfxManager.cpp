#include "sfxManager.h"

#include <vector>

namespace Asteroids {
	namespace SfxManager {
		struct SfxWithName {
			SfxName name;
			Sound sound;
		};

		struct MusicWithName {
			MusicName name;
			Music music;
			float volume;
		};

		static SfxWithName sfxs[SFX_COUNT];
		static MusicWithName musics[MUSIC_COUNT];


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
			SfxWithName shieldCollision = { SHIELD_ASTEROID_COLLISION, LoadSound("res/sounds/shieldAsteroidCollision.wav") };
			SfxWithName propulsion = { PROPULSION, LoadSound("res/sounds/propulsion.wav") };

			SetSoundVolume(shoot1.sound, 0.5);
			SetSoundVolume(shoot2.sound, 0.5);

			SfxWithName auxSfxs[SFX_COUNT] = {
				bulletCollision1,
				bulletCollision2,
				bulletsActivation,
				bulletsDeactivation,
				pointsActivation,
				pointsDeactivation,
				shieldActivation,
				shieldDeactivation,
				points1,
				points2,
				points3,
				shoot1,
				shoot2,
				shipCollision,
				shieldCollision,
				propulsion
			};

			for (int i = 0; i < SFX_COUNT; i++) {
				sfxs[i] = auxSfxs[i];
			}

			MusicWithName gameplay = { GAMEPLAY, LoadMusicStream("res/sounds/gameplay.mp3"), 0.3f };
			gameplay.music.looping = true;

			MusicWithName auxMusics[MUSIC_COUNT] = { gameplay };

			for (int i = 0; i < MUSIC_COUNT; i++) {
				musics[i] = auxMusics[i];
			}
		};

		void stopAllSounds() {
			for (int i = 0; i < SFX_COUNT; i++) {
				if (IsAudioDeviceReady()) {
					StopSound(sfxs[i].sound);
				}
			}
		}
		
		void playSound(SfxName sfxName, bool shouldOverlap) {
			for (int i = 0; i < SFX_COUNT; i++) {
				if (IsAudioDeviceReady() && sfxName == sfxs[i].name && (shouldOverlap || !IsSoundPlaying(sfxs[i].sound))) {
					PlaySound(sfxs[i].sound);
				}
			}
		};

		void stopSound(SfxName sfxName) {
			for (int i = 0; i < SFX_COUNT; i++) {
				if (IsAudioDeviceReady() && sfxName == sfxs[i].name) {
					StopSound(sfxs[i].sound);
				}
			}
		}

		void playMusic(MusicName musicName) {
			for (int i = 0; i < MUSIC_COUNT; i++) {
				if (IsAudioDeviceReady() && musicName == musics[i].name) {
					PlayMusicStream(musics[i].music);
				}
			}
		};

		void updateMusic(MusicName musicName) {
			for (int i = 0; i < MUSIC_COUNT; i++) {
				if (IsAudioDeviceReady() && musicName == musics[i].name) {
					SetMusicVolume(musics[i].music, musics[i].volume);
					UpdateMusicStream(musics[i].music);
				}
			}
		}

		void stopAllMusic() {
			for (int i = 0; i < MUSIC_COUNT; i++) {
				if (IsAudioDeviceReady()) {
					StopMusicStream(musics[i].music);
				} 
			}
		}
	}
}