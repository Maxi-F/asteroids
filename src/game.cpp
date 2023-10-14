#include "game.h"

#include "raylib.h"
#include "screens/screenManager.h"
#include "assets/assetManager.h"
#include "constants/dimensions.h"

namespace Asteroids {
    static void close() {
        CloseWindow();
    }

    static void init() {
        InitWindow(static_cast<int>(SCREEN_DIMENSIONS.x), static_cast<int>(SCREEN_DIMENSIONS.y), "LePong");

        AssetManager::init();
        ScreensManager::initManager();
        
    }

    static void update(bool& shouldClose) {
        ScreensManager::updateScreen(shouldClose);
    }

    static void draw() {
        BeginDrawing();
            GetFontDefault();
            ClearBackground(BLACK);

            ScreensManager::drawScreen();

        EndDrawing();
    }

    void startGame() {
        init();
        bool shouldClose = false;

        SetExitKey(0);

        while (!shouldClose)
        {
            update(shouldClose);

            draw();
        }

        close();
    }

}
