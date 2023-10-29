#include "bullet.h"

#include "raymath.h"

#include "utils/screen.h"
#include "assets/assetManager.h"

namespace Asteroids {
	namespace Bullets {
		static const float BULLET_VELOCITY = 1000.0f;
		static const float BULLET_RADIUS = 5.0f;
		static const double BULLET_LIFETIME = 1.0;

		Bullet createBullet(Vector2 position, Vector2 direction, float angle) {
			Timer::Timer timer;
			Timer::startTimer(&timer, BULLET_LIFETIME);

			return {
				position,
				direction,
				BULLET_VELOCITY,
				BULLET_RADIUS,
				timer,
				angle,
				AssetManager::getTexture(AssetManager::BULLET),
			};
		}

		void updateBullet(Bullet& bullet) {
			bullet.position = Vector2Add(bullet.position, Vector2Scale(bullet.direction, bullet.velocity * GetFrameTime()));

			if (Timer::timerDone(bullet.lifetimeTimer)) {
				bullet.shouldRemove = true;
			}
		}

		void drawBullet(Bullet bullet) {
#ifdef _DEBUG
			DrawCircle(
				static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.radius, WHITE
			);
#endif
			Rectangle srcRectangle = {
				0,
				0,
				static_cast<float>(bullet.texture.width),
				static_cast<float>(bullet.texture.height)
			};

			Rectangle destRectangle = {
				bullet.position.x,
				bullet.position.y,
				bullet.radius * 2,
				bullet.radius * 2
			};

			Vector2 origin = {
				static_cast<float>(bullet.radius),
				static_cast<float>(bullet.radius)
			};

			DrawTexturePro(
				bullet.texture,
				srcRectangle,
				destRectangle,
				origin,
				bullet.angle,
				WHITE
			);
		}

		Bullet copyBulletByAngle(Bullet bullet, float angle) {
			return {
				bullet.position,
				Vector2Rotate(bullet.direction, angle),
				bullet.velocity,
				bullet.radius,
				bullet.lifetimeTimer,
				bullet.angle,
				bullet.texture
			};
		}

		void changeTextureToMulti(Bullet& bullet) {
			bullet.texture = AssetManager::getTexture(AssetManager::MULTI_BULLET);
		}

		void pauseTimer(Bullet& bullet) {
			Timer::pauseTimer(&bullet.lifetimeTimer);
		}

		void unpauseTimer(Bullet& bullet) {
			Timer::unPauseTimer(&bullet.lifetimeTimer);
		}
	}
}
