#include "ConstSpeedVarFps.h"

namespace Cubicuous {
    namespace Core {
        namespace Loops {

            ConstSpeedVarFps::ConstSpeedVarFps(int updateRate) : ILoop(updateRate) {
                this->_nextTick = this->getTicks();
                this->_skipTicks = 1000 / updateRate;
            };

            ConstSpeedVarFps::~ConstSpeedVarFps() {

            }

            void ConstSpeedVarFps::loop(Game *game) {
                this->_updates = 0;
                this->_checkSecondElapsed();

                while ((this->_trackerStart = this->getTicks()) > this->_nextTick &&
                       this->_updates < ConstSpeedVarFps::MAX_UPDATES) {
                    game->getWindow()->update();
                    game->getActiveScene()->getInput()->processEvents();
                    game->getActiveScene()->update();
                    this->_trackerEnd = this->getTicks();
                    this->_updateTime = this->_trackerEnd - this->_trackerStart;
                    this->_futs++;
                    this->_nextTick += this->_skipTicks;
                    this->_updates++;
                }

                this->_trackerStart = this->getTicks();

                //update camera to save lines
                if(game->getActiveScene()->getCamera() != nullptr) {
                    game->getActiveScene()->getCamera()->updateMVP();
                }

                game->getActiveScene()->render((this->_trackerStart + this->_skipTicks - this->_nextTick) / this->_skipTicks);
                this->_trackerEnd = this->getTicks();
                this->_frts++;
                this->_renderTime = this->_trackerEnd - this->_trackerStart;
            }
        }
    }
}