#pragma once

#include "raylib.h"

#include "utils/timer.h"

namespace Asteroids {
	namespace Bullets {
		struct Bullet {
			Vector2 position;
			Vector2 direction;
			float velocity;
			float radius;
			Timer::Timer lifetimeTimer;
			bool shouldRemove = false;
		};

		Bullet createBullet(Vector2 position, Vector2 direction);
		void updateBullet(Bullet& bullet);
		void drawBullet(Bullet bullet);
		Bullet copyBulletByAngle(Bullet bullet, float angle);
		void pauseTimer(Bullet& bullet);
		void unpauseTimer(Bullet& bullet);
	}
}
