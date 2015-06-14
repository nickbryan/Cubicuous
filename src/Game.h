#ifndef CUBICUOUS_GAME_H
#define CUBICUOUS_GAME_H

#include "Window/Window.h"
#include "Core/Scene.h"
#include "Core/ILoop.h"
#include "Core/Loops/ConstSpeedVarFps.h"
#include "Graphics/ShaderProgram.h"

#include <unordered_map>

using Cubicuous::Core::Scene;
using Cubicuous::Core::ILoop;
using Cubicuous::Graphics::ShaderProgram;

namespace Cubicuous {
    class Game {
    public:
        struct GameSettings {
            unsigned int quickQuitKey = 0;
            unsigned int togglePauseKey = 0;
            Scene *pauseScene = nullptr;
            ILoop *loop = nullptr;

            GLuint vertexBufferObject;

            inline GameSettings() {
                this->loop = new Cubicuous::Core::Loops::ConstSpeedVarFps(30);
            }

            inline GameSettings(ILoop *loop) {
                if (loop == nullptr) {
                    this->loop = new Cubicuous::Core::Loops::ConstSpeedVarFps(30);
                }
                else {
                    this->loop = loop;
                }
            }

            inline GameSettings(unsigned int quickQuitKey) : GameSettings() {
                this->quickQuitKey = quickQuitKey;
            }

            inline GameSettings(unsigned int togglePauseKey, Scene *pauseScene) : GameSettings() {
                this->togglePauseKey = togglePauseKey;
                this->pauseScene = pauseScene;
            }

            inline GameSettings(unsigned int quickQuitKey, unsigned int togglePauseKey, Scene *pauseScene)
                    : GameSettings(togglePauseKey, pauseScene) {
                this->quickQuitKey = quickQuitKey;
            }

            inline ~GameSettings() {
                if (this->pauseScene != nullptr) {
                    delete this->pauseScene;
                }

                delete this->loop;
            }
        };

    private:
        std::unordered_map<const char *, Scene *> *_scenes;
        Scene *_activeScene = nullptr;
        Scene *_nextScene = nullptr;
        Scene *_previousScene = nullptr;

        bool _running = false;

        Window::Window *_window;
        GameSettings *_settings;

        ShaderProgram *_shaderProgram;

    public:
        Game(GameSettings *gameSettings, Cubicuous::Window::WindowSettings windowSettings);

        Game(Cubicuous::Window::WindowSettings windowSettings) : Game(new GameSettings(), windowSettings) { };

        ~Game();

        void start();

        inline void stop() { this->_running = false; }

        inline Window::Window *getWindow() const { return this->_window; };

        void cacheScene(const char *name, Scene *scene);

        inline void cacheScene(std::string name, Scene *scene) { this->cacheScene(name.c_str(), scene); }

        Scene* getCachedScene(const char *name) const;

        inline Scene* getCachedScene(std::string name) const { return this->getCachedScene(name.c_str()); }

        inline void setScene(Scene *scene) { this->_nextScene = scene; };

        void setScene(const char *name);

        inline void setScene(std::string name) { this->setScene(name.c_str()); }

        inline void previousScene() { this->setScene(this->_previousScene); }

        inline Scene* getPreviousScene() const { return this->_previousScene; }

        inline Scene* getActiveScene() const { return this->_activeScene; }

        inline Scene* getNextScene() const { return this->_nextScene; }

        inline ShaderProgram* getShaderProgram() { return this->_shaderProgram; }

    };
}
#endif