#include "utils/screen.h"

namespace Asteroids {
	namespace ScreenUtils {
		static float screenWidth = 0;
		static float screenHeight = 0;

		float getScreenWidth() {
			if (screenWidth == 0) {
				screenWidth = static_cast<float>(GetScreenWidth());
			}
			return screenWidth;
		}

		float getScreenHeight() {
			if (screenHeight == 0) {
				screenHeight = static_cast<float>(GetScreenHeight());
			}
			return screenHeight;
		}

		void checkPositionByScreenBounds(Entity& entity) {
			Vector2 nextFramePosition = { entity.position.x + entity.velocity.x * GetFrameTime(), entity.position.y + entity.velocity.y * GetFrameTime() };
			
			if (nextFramePosition.x > getScreenWidth()) {
				entity.position.x = 0;
			}
			else if (nextFramePosition.x < 0) {
				entity.position.x = getScreenWidth();
			}
			else if (nextFramePosition.y > getScreenHeight()) {
				entity.position.y = 0;
			}
			else if (nextFramePosition.y < 0) {
				entity.position.y = getScreenHeight();
			}
		}
	}
}
