#include "GameSettings.h"
#include "Core/ILoop.h"
#include "Core/Loops/ConstSpeedVarFps.h"

namespace Cubicuous {
    GameSettings::GameSettings(int logicFps) {
        this->loop = new Core::Loops::ConstSpeedVarFps(logicFps);
    }

    GameSettings::GameSettings(Core::ILoop *loop) {
        this->loop = loop;
    }

    GameSettings::GameSettings(unsigned int quickQuitKey)
            : GameSettings()  {
        this->quickQuitKey = quickQuitKey;
    }

    GameSettings::GameSettings(unsigned int quickQuitKey, unsigned int togglePauseKey, Core::Scene *pauseScene)
            : GameSettings(togglePauseKey, pauseScene)  {
        this->quickQuitKey = quickQuitKey;
    }

    GameSettings::GameSettings(unsigned int togglePauseKey, Core::Scene *pauseScene)
            : GameSettings() {
        this->togglePauseKey = togglePauseKey;
        this->pauseScene = pauseScene;
    }

    GameSettings::~GameSettings() {
        if (this->pauseScene != nullptr) {
            delete this->pauseScene;
        }

        delete this->loop;
    }

}