#ifndef CUBICUOUS_MVPSEPMATRIXMANAGER_H
#define CUBICUOUS_MVPSEPMATRIXMANAGER_H

#include "IMatrixManager.h"
#include "../../Graphics/Uniform.h"
#include "../../Game.h"

namespace Cubicuous {
    namespace Core {
        namespace MatrixManager {
            class MVPSepMatrixManager : public IMatrixManager {
            private:
                Graphics::Uniform *_modelUni;
                Graphics::Uniform *_projUni;
                Graphics::Uniform *_viewUni;

            public:
                inline MVPSepMatrixManager(Graphics::ShaderProgram *shaderProgram, const char* modelUniName, const char* projUniName,
                                           const char* viewUniName, bool cached) {
                    if(cached) {
                        this->_modelUni = shaderProgram->getCachedUniform(modelUniName);
                    }
                    else {
                        this->_modelUni = shaderProgram->cacheUniform(modelUniName);
                    }

                    if(cached) {
                        this->_viewUni = shaderProgram->getCachedUniform(viewUniName);
                    }
                    else {
                        this->_viewUni = shaderProgram->cacheUniform(viewUniName);
                    }

                    if(cached) {
                        this->_projUni = shaderProgram->getCachedUniform(projUniName);
                    }
                    else {
                        this->_projUni = shaderProgram->cacheUniform(projUniName);
                    }
                };

                inline MVPSepMatrixManager(Graphics::ShaderProgram *shaderProgram, const char* modelUniName, const char* projUniName,
                                           const char* viewUniName) :
                       MVPSepMatrixManager(shaderProgram, modelUniName, projUniName, viewUniName, true) { };

                inline MVPSepMatrixManager(Game *game, const char* modelUniName, const char* projUniName,
                                           const char* viewUniName, bool cached) :
                        MVPSepMatrixManager(game->getShaderProgram(), modelUniName, projUniName, viewUniName, cached) { };

                inline MVPSepMatrixManager(Game *game, const char* modelUniName, const char* projUniName,
                                           const char* viewUniName) :
                        MVPSepMatrixManager(game->getShaderProgram(), modelUniName, projUniName, viewUniName, true) { };

                inline MVPSepMatrixManager(Graphics::Uniform *modelUniform, Graphics::Uniform *projUniform,
                                           Graphics::Uniform *viewUniform) {
                    this->_modelUni = modelUniform;
                    this->_projUni = projUniform;
                    this->_viewUni = viewUniform;
                }

                virtual void updateModel(glm::mat4 model) override;

                virtual void updateProjection(glm::mat4 projection) override;

                virtual void updateView(glm::mat4 view) override;
            };
        }
    }
}

#endif