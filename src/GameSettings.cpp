#include "GameSettings.h"
#include "Core/ILoop.h"
#include "Core/Loops/ConstSpeedVarFps.h"

namespace Cubicuous {

    GameSettings::GameSettings() {
        this->loop = new Core::Loops::ConstSpeedVarFps(30);
    }

    GameSettings::GameSettings(Core::ILoop *loop) {
        if (loop == nullptr) {
            this->loop = new Core::Loops::ConstSpeedVarFps(30);
        } else {
            this->loop = loop;
        }
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