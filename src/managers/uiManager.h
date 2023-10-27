#pragma once

namespace Asteroids {
	namespace UiManager {
		void initUI();
		void drawUI(int totalPoints, int lives, bool isPaused);
		void updateUI(bool& isPaused);
	}
}
