#include "gameManager.h"

namespace Asteroids {
	namespace GameManager {
		static int highScore = 0;
		static int lastScore = 0;

		int getLastScore() {
			return lastScore;
		}

		void setLastScore(int newLastScore) {
			lastScore = newLastScore;
		}

		int getHighScore() {
			return highScore;
		};

		void setNewHighScore(int probablyNewHighScore) {
			if (probablyNewHighScore > highScore) {
				highScore = probablyNewHighScore;
			}
		};
	}
}

