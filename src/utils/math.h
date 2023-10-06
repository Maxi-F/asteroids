#pragma once
#include "raylib.h"

namespace Asteroids {
	float getDistanceFromMiddle(Rectangle rectangle, Vector2 point);
	float getHalf(float size);
	float getWithFrameTime(float value);
	bool checkRectangleCollision(Rectangle rectangle1, Rectangle rectangle2);
	float clamp(float value, float min, float max);
	float getRandomNegativeOrPositive();
	float moduleOf(float value);
	bool checkPointToRectangleCollision(Rectangle rectangle, Vector2 point);
	int roundUp(int numberToRound, int multiple);

}
