#pragma once
#include "raylib.h"

namespace Asteroids {
	namespace MathUtils {
		struct Circle {
			Vector2 position;
			float radius;
		};

		float clamp(float value, float min, float max);
		float moduleOf(float value);
		int roundUp(int numberToRound, int multiple);
		bool checkRectangleCollision(Rectangle rectangle1, Rectangle rectangle2);
		bool checkCircleCollision(Circle circle1, Circle circle2);
		bool checkPointToRectangleCollision(Rectangle rectangle, Vector2 point);
		float getHalf(float size);
		float getWithFrameTime(float value);
		float getDistanceFromMiddle(Rectangle rectangle, Vector2 point);
		float getRandomNegativeOrPositive();
	}
}
