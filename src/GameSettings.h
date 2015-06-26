#ifndef CUBICUOUS_GAMESETTINGS_H
#define CUBICUOUS_GAMESETTINGS_H



namespace Cubicuous {
    namespace Core {
        class Scene;
        class ILoop;
    }

    struct GameSettings {
        unsigned int quickQuitKey = 0;
        unsigned int togglePauseKey = 0;
        Core::Scene *pauseScene = nullptr;
        Core::ILoop *loop = nullptr;

        inline GameSettings() : GameSettings(60) {};
        GameSettings(int logicFps);
        GameSettings(Core::ILoop *loop);
        GameSettings(unsigned int quickQuitKey);
        GameSettings(unsigned int togglePauseKey, Core::Scene *pauseScene);
        GameSettings(unsigned int quickQuitKey, unsigned int togglePauseKey, Core::Scene *pauseScene);

        ~GameSettings();
    };
}

#endif
