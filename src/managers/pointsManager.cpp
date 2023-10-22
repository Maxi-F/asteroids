#include "pointsManager.h"

#include <vector>

#include "entities/point.h"
#include "utils/math.h"

namespace Asteroids {
	namespace PointsManager {
		static std::vector<Point::Point> points;

		void init() {
			points.clear();
		};

		void addPoint(Asteroid::Asteroid asteroid, Spaceship::Ship ship) {
			points.push_back(Point::createPointFrom(asteroid.position, ship.position, asteroid.points));
		};

		void updatePoints(Spaceship::Ship ship) {
			for (size_t i = 0; i < points.size(); i++) {
				if (checkCircleCollision({ ship.position, ship.shipRadius }, { points[i].position, points[i].radius })) {
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
