#include "gameplay.h"

#include "entities/spaceship.h"

namespace Asteroids {
	namespace Gameplay {
		struct GameplayEntities {
			Spaceship::Ship spaceship;
		};

		static GameplayEntities gameplayEntities;

		void initGameplay() {
			gameplayEntities = {
				Spaceship::createSpaceship()
			};
		}

		void updateGameplay() {
			Spaceship::updateSpaceship(gameplayEntities.spaceship);
		}

		void drawGameplay() {
			Spaceship::drawSpaceship(gameplayEntities.spaceship);
		}
	}
}
