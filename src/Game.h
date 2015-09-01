#ifndef CUBICUOUS_GAME_H
#define CUBICUOUS_GAME_H

#include "Window/Window.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/VertexBuffer.h"
#include "GameSettings.h"
#include "Core/Loops/ILoop.h"
#include "Core/MatrixManager/IMatrixManager.h"
#include <unordered_map>

namespace Cubicuous {
    namespace Core {
        namespace Loops {
            class ConstSpeedVarFps;
        }

        namespace Loops {
            class ILoop;
        }

        class Scene;
    }
}

using Cubicuous::Core::Scene;
using Cubicuous::Core::Loops::ILoop;
using Cubicuous::Graphics::ShaderProgram;
using Cubicuous::Graphics::VertexBuffer;
using Cubicuous::Core::MatrixManager::IMatrixManager;

namespace Cubicuous {
    class Game {
    private:
        std::unordered_map<const char*, Scene*>* _scenes = nullptr;
        Scene *_activeScene = nullptr;
        Scene *_nextScene = nullptr;
        Scene *_previousScene = nullptr;

        bool _running = false;

        Window::Window* _window = nullptr;
        GameSettings* _settings = nullptr;

        ShaderProgram* _shaderProgram = nullptr;
        std::unordered_map<const char*, VertexBuffer*> _vertexBuffers;
        GLuint _vertexArrayID;

    public:
        Game(GameSettings *gameSettings, Cubicuous::Window::WindowSettings windowSettings);

        Game(Cubicuous::Window::WindowSettings windowSettings) : Game(new GameSettings(), windowSettings) { };

        ~Game();

        /* Core methods */
        void start();

        inline bool isRunning() const { return this->_running; }

        inline void stop() { this->_running = false; }

        inline Window::Window *getWindow() const { return this->_window; };

        inline GameSettings* getSettings() const { return this->_settings; };

        /* Get functions for integral esettings */
        inline IMatrixManager* getMatrixManager() const { return this->getSettings()->matrixManager; }
        inline Core::Mesher::IMesher* getMesher() const { return this->getSettings()->mesher; }

        /* Scene catching */
        void cacheScene(const char *name, Scene *scene);
        inline void cacheScene(std::string name, Scene *scene) { this->cacheScene(name.c_str(), scene); }

        Scene* getCachedScene(const char *name) const;
        inline Scene* getCachedScene(std::string name) const { return this->getCachedScene(name.c_str()); }

        /* Scene management */
        inline void setScene(Scene *scene) { this->_nextScene = scene; };
        void setScene(const char *name);
        inline void setScene(std::string name) { this->setScene(name.c_str()); }

        inline void previousScene() { this->setScene(this->_previousScene); }

        inline Scene* getPreviousScene() const { return this->_previousScene; }

        inline Scene* getActiveScene() const { return this->_activeScene; }

        inline Scene* getNextScene() const { return this->_nextScene; }

        /* Core graphics management */
        inline ShaderProgram* getShaderProgram() const { return this->_shaderProgram; }

        /* Vertex buffer management */
        VertexBuffer* createVertexBuffer(const char* name, GLenum type);
        inline VertexBuffer* createVertexBuffer(const char* name) { return this->createVertexBuffer(name, GL_STATIC_DRAW); };

        void createVertexBuffer(const char* name, GLuint id, GLenum storageMode, GLenum type);
        inline void attachVertexBuffer(const char* name, GLuint id, GLenum type) { this->createVertexBuffer(name, id, type, type); };
        void attachVertexBuffer(const char* name, VertexBuffer* buffer);
        inline void attachVertexBuffer(const char* name, GLuint id) { this->attachVertexBuffer(name, id, GL_STATIC_DRAW); };

        VertexBuffer* getVertexBuffer(const char* name);
    };
}
#endif