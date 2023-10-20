#include "bullet.h"

#include "raymath.h"

#include "utils/screen.h"

namespace Asteroids {
	namespace Bullets {
		static const float BULLET_VELOCITY = 1000.0f;
		static const float BULLET_RADIUS = 5.0f;
		static const double BULLET_LIFETIME = 1.0;

		static void updateBulletByScreenCollision(Bullet& bullet) {
			ScreenUtils::Entity bulletEntity = { bullet.position, Vector2Scale(bullet.direction, bullet.velocity) };
			ScreenUtils::checkPositionByScreenBounds(bulletEntity);

			bullet.position = bulletEntity.position;
		}

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

			updateBulletByScreenCollision(bullet);

			if (Timer::timerDone(bullet.lifetimeTimer)) {
				bullet.shouldRemove = true;
			}
		}

		void drawBullet(Bullet bullet) {
			DrawCircle(
				static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.radius, WHITE
			);
		}
	}
}