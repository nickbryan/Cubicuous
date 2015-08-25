#ifndef CUBICUOUS_GAMESETTINGS_H
#define CUBICUOUS_GAMESETTINGS_H

namespace Cubicuous {
    namespace Core {
        class Scene;

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
        Core::Scene *pauseScene;
        Core::Loops::ILoop *loop;
        Core::MatrixManager::IMatrixManager *matrixManager;

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