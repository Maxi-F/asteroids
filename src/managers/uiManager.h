#pragma once

namespace Asteroids {
	namespace UiManager {
		void initUI();
		void drawUI(int totalPoints, int lives);
		void updateUI(bool& isPaused);
	}
}
