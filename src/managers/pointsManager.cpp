#include "pointsManager.h"

#include <vector>

#include "entities/point.h"
#include "utils/math.h"
#include "assets/sfxManager.h"
#include "managers/powerupsManager.h"

namespace Asteroids {
	namespace PointsManager {
		static std::vector<Point::Point> points;

		static SfxManager::SfxName getRandomPointSound() {
			const int POINTS_SOUNDS_COUNT = 3;
			int collisionSound = GetRandomValue(1, POINTS_SOUNDS_COUNT);

			switch (collisionSound) {
			case 1:
				return SfxManager::POINTS_1;
			case 2:
				return SfxManager::POINTS_2;
			case 3:
				return SfxManager::POINTS_3;
			default:
				return SfxManager::POINTS_1;
			}
		}

		void init() {
			points.clear();
		};

		void addPoint(Asteroid::Asteroid asteroid, Spaceship::Ship ship) {
			points.push_back(Point::createPointFrom(asteroid.position, ship.position, asteroid.points));
		};

		void updatePoints(Spaceship::Ship ship, int &totalPoints) {
			for (size_t i = 0; i < points.size(); i++) {
				if (checkCircleCollision({ ship.position, ship.shipRadius }, { points[i].position, points[i].radius })) {
					SfxManager::playSound(getRandomPointSound(), true);

					if (PowerupsManager::isPowerUpActive(PowerUp::MORE_POINTS)) {
						totalPoints += points[i].points * 2;
					}
					else {
						totalPoints += points[i].points;
					}
					points.erase(points.begin() + i);
				}
				else {
					Point::updatePoint(points[i], ship.position);
				}
			};
		};

		void drawPoints() {
			for (size_t i = 0; i < points.size(); i++) {
				Point::drawPoint(points[i]);
			};
		};
	}
}
