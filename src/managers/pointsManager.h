#pragma once

#include "entities/asteroid.h"
#include "entities/spaceship.h"

namespace Asteroids {
	namespace PointsManager {
		void init();
		void addPoint(Asteroid::Asteroid asteroid, Spaceship::Ship ship);
		void updatePoints(Spaceship::Ship ship, int &points);
		void drawPoints();
	}
}
