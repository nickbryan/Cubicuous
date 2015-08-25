#ifndef CUBICUOUS_MVPMATRIXMANAGER_H
#define CUBICUOUS_MVPMATRIXMANAGER_H

#include "IMatrixManager.h"

namespace Cubicuous {
    namespace Core {
        namespace MatrixManager {
            class MVPMatrixManager : public IMatrixManager {
            private:
                glm::mat4 _model;
                glm::mat4 _projection;
                glm::mat4 _view;

                Graphics::Uniform* _mvpUni;

                void _update();

            public:
                inline MVPMatrixManager(ShaderProgram *shaderProgram, const char* mvpUniformName, bool cached) {
                    if(cached) {
                        this->_mvpUni = shaderProgram->getCachedUniform(mvpUniformName);
                    }
                    else {
                        this->_mvpUni = shaderProgram->cacheUniform(mvpUniformName);
                    }
                };

                inline MVPMatrixManager(ShaderProgram *shaderProgram, const char* mvpUniformName) :
                        MVPMatrixManager(shaderProgram, mvpUniformName, true) { };

                inline MVPMatrixManager(Game *game, const char* mvpUniformName, bool cached) :
                        MVPMatrixManager(game->getShaderProgram(), mvpUniformName, cached) { };

                inline MVPMatrixManager(Game *game, const char* mvpUniformName) :
                        MVPMatrixManager(game->getShaderProgram(), mvpUniformName, true) { };

                inline MVPMatrixManager(Graphics::Uniform *mvpUniform) {
                    this->_mvpUni = mvpUniform;
                }

                virtual void updateModel(glm::mat4 model) override;

                virtual void updateProjection(glm::mat4 projection) override;

                virtual void updateView(glm::mat4 view) override;
            };
        }
    }
}

#endif