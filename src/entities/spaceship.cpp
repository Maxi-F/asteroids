#include "spaceship.h"

#include "raymath.h"

#include "assets/assetManager.h"
#include "utils/math.h"
#include "utils/screen.h"
#include "entities/bulletManager.h"

#include <iostream>

namespace Asteroids {
	namespace Spaceship {
		static float SHIP_RADIUS = 20.0f;
		static Vector2 MAX_VELOCITY = { 300.0f, 300.0f };

		static void updatePosition(Ship& spaceShip) {
			spaceShip.position = Vector2Add(spaceShip.position, Vector2Scale(spaceShip.velocity, GetFrameTime()));
		}

		static void updateVelocity(Ship& spaceShip) {
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
				spaceShip.velocity = Vector2Clamp(
					Vector2Add(spaceShip.velocity, Vector2Scale(spaceShip.direction, spaceShip.acceleration * GetFrameTime())),
					Vector2Scale(MAX_VELOCITY, -1.0f),
					MAX_VELOCITY
				);
			}
		}

		static float getAngleByDirection(Ship spaceShip) {
			return static_cast<float>(atan2(spaceShip.direction.y, spaceShip.direction.x)) * RAD2DEG + 90.0f;
		}

		static void updatePositionByScreenCollitions(Ship& spaceShip) {
			ScreenUtils::Entity shipEntity = { spaceShip.position, spaceShip.velocity };
			ScreenUtils::checkPositionByScreenBounds(shipEntity);

			spaceShip.position = shipEntity.position;
		}

		static void shootFrom(Ship spaceShip) {
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
				BulletManager::addBullet(Bullets::createBullet(spaceShip.position, spaceShip.direction));
			}
		}

		Ship createSpaceship() {
			Texture2D shipTexture = AssetManager::getTexture(AssetManager::Assets::SHIP);
			Vector2 screenDimensions = { ScreenUtils::getScreenWidth(), ScreenUtils::getScreenHeight() };

			return {
				SHIP_RADIUS,
				0.0f,
				400.0f,
				{ getHalf(screenDimensions.x), getHalf(screenDimensions.y) },
				{ 0.0f, 0.0f },
				{ 0.0f, 0.0f },
				shipTexture
			};
		}

		void restartSpaceship(Ship& spaceShip) {
			Vector2 screenDimensions = { ScreenUtils::getScreenWidth(), ScreenUtils::getScreenHeight() };

			spaceShip.velocity = { 0.0f, 0.0f };
			spaceShip.position = { getHalf(screenDimensions.x), getHalf(screenDimensions.y) };
		};

		void updateSpaceship(Ship &spaceShip) {
			Vector2 mousePosition = GetMousePosition();

			spaceShip.direction = Vector2Normalize(Vector2Subtract(mousePosition, spaceShip.position));

			spaceShip.rotation = getAngleByDirection(spaceShip);

			updatePosition(spaceShip);
			updateVelocity(spaceShip);

			updatePositionByScreenCollitions(spaceShip);

			shootFrom(spaceShip);
		}

		void drawSpaceship(Ship spaceShip) {
			Rectangle srcRectangle = {
				0,
				0,
				static_cast<float>(spaceShip.texture.width),
				static_cast<float>(spaceShip.texture.height)
			};

			Rectangle destRectangle = { 
				spaceShip.position.x,
				spaceShip.position.y,
				spaceShip.shipRadius * 2,
				spaceShip.shipRadius * 2
			};		

			Vector2 origin = {
				static_cast<float>(spaceShip.shipRadius),
				static_cast<float>(spaceShip.shipRadius)
			};

#ifdef _DEBUG
			DrawCircle(static_cast<int>(spaceShip.position.x), static_cast<int>(spaceShip.position.y), spaceShip.shipRadius, YELLOW);
#endif 

			DrawTexturePro(
				spaceShip.texture,
				srcRectangle,
				destRectangle,
				origin,
				spaceShip.rotation,
				WHITE
			);
		}
	}
}