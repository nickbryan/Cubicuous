#ifndef CUBICUOUS_GAME_H
#define CUBICUOUS_GAME_H

#include "Core/Exception.h"
#include "Window/Window.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/VertexBuffer.h"
#include "GameSettings.h"
#include "Core/Loops/ILoop.h"
#include "Core/MatrixManager/IMatrixManager.h"
#include "Core/GeometryManager.h"
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
        std::unordered_map<std::string, Scene*> _scenes;
        Scene *_activeScene = nullptr;
        Scene *_nextScene = nullptr;
        Scene *_previousScene = nullptr;

        bool _running = false;

        Window::Window* _window = nullptr;
        GameSettings* _settings = nullptr;

        ShaderProgram* _shaderProgram = nullptr;
        std::unordered_map<std::string, VertexBuffer*> _vertexBuffers;
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
        inline Core::GeometryManager* getGeometryManager() const { return this->getSettings()->geometryManager; }
        inline Core::Mesher::IMesher* getMesher() const { return this->getSettings()->mesher; }

        /* Scene catching */
        void cacheScene(std::string name, Scene *scene);
        inline void cacheScene(const char* name, Scene *scene) { this->cacheScene(std::string(name), scene); }

        Scene* getCachedScene(std::string name) const;
        inline Scene* getCachedScene(const char* name) const { return this->getCachedScene(std::string(name)); }

        /* Scene management */
        inline void setScene(Scene *scene) { this->_nextScene = scene; };
        void setScene(std::string name);
        inline void setScene(const char *name) { this->setScene(std::string(name)); };

        inline void previousScene() { this->setScene(this->_previousScene); }

        inline Scene* getPreviousScene() const { return this->_previousScene; }

        inline Scene* getActiveScene() const { return this->_activeScene; }

        inline Scene* getNextScene() const { return this->_nextScene; }

        /* Core graphics management */
        inline ShaderProgram* getShaderProgram() const { return this->_shaderProgram; }

        /* Vertex buffer management */
        VertexBuffer* createVertexBuffer(std::string, GLenum type);
        inline VertexBuffer* createVertexBuffer(const char* name, GLenum type) { return this->createVertexBuffer(std::string(name), type); };
        inline VertexBuffer* createVertexBuffer(std::string name) { return this->createVertexBuffer(name, GL_STATIC_DRAW); };
        inline VertexBuffer* createVertexBuffer(const char* name) { return this->createVertexBuffer(std::string(name)); };

        void createVertexBuffer(std::string name, GLuint id, GLenum storageMode, GLenum type);
        inline void attachVertexBuffer(std::string name, GLuint id, GLenum type) { this->createVertexBuffer(name, id, type, type); };

        void attachVertexBuffer(std::string name, VertexBuffer* buffer);
        inline void attachVertexBuffer(std::string name, GLuint id) { this->attachVertexBuffer(name, id, GL_STATIC_DRAW); };

        VertexBuffer* getVertexBuffer(std::string name) const;
        inline VertexBuffer* getVertexBuffer(const char* name) const { return this->getVertexBuffer(std::string(name)); };
    };
}
#endif