#ifndef CUBICUOUS_GAMESETTINGS_H
#define CUBICUOUS_GAMESETTINGS_H

#include "Core/Mesher/IMesher.h"
#include "Core/Scene.h"

namespace Cubicuous {
    namespace Core {
        namespace Loops {
            class ILoop;
        }
        namespace MatrixManager {
            class IMatrixManager; //fix incomplete type compile error
        }
    }

    struct GameSettings {
        unsigned int quickQuitKey = 0;
        unsigned int togglePauseKey = 0;

        Core::Loops::ILoop* loop = nullptr;
        Core::Scene* pauseScene = nullptr;
        Core::MatrixManager::IMatrixManager* matrixManager = nullptr;
        Core::Mesher::IMesher* mesher = nullptr;

        inline GameSettings() : GameSettings(60) {};
        GameSettings(int logicFps);
        GameSettings(Core::Loops::ILoop *loop);
        GameSettings(int logicFps, unsigned int quickQuitKey);
        GameSettings(unsigned int togglePauseKey, Core::Scene *pauseScene);
        GameSettings(unsigned int quickQuitKey, unsigned int togglePauseKey, Core::Scene *pauseScene);

        ~GameSettings();
    };
}

#endif