#include "bullet.h"

#include "raymath.h"

#include "utils/screen.h"

namespace Asteroids {
	namespace Bullets {
		static const float BULLET_VELOCITY = 1000.0f;
		static const float BULLET_RADIUS = 5.0f;
		static const double BULLET_LIFETIME = 1.0;

		Bullet createBullet(Vector2 position, Vector2 direction) {
			Timer::Timer timer;
			Timer::startTimer(&timer, BULLET_LIFETIME);

			return {
				position,
				direction,
				BULLET_VELOCITY,
				BULLET_RADIUS,
				timer
			};
		}

		void updateBullet(Bullet& bullet) {
			bullet.position = Vector2Add(bullet.position, Vector2Scale(bullet.direction, bullet.velocity * GetFrameTime()));

			if (Timer::timerDone(bullet.lifetimeTimer)) {
				bullet.shouldRemove = true;
			}
		}

		void drawBullet(Bullet bullet) {
			DrawCircle(
				static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.radius, WHITE
			);
		}

		Bullet copyBulletByAngle(Bullet bullet, float angle) {
			return {
				bullet.position,
				Vector2Rotate(bullet.direction, angle),
				bullet.velocity,
				bullet.radius,
				bullet.lifetimeTimer
			};
		}

		void pauseTimer(Bullet& bullet) {
			Timer::pauseTimer(&bullet.lifetimeTimer);
		}

		void unpauseTimer(Bullet& bullet) {
			Timer::unPauseTimer(&bullet.lifetimeTimer);
		}
	}
}
