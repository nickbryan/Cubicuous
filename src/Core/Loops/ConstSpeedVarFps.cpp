#include "ConstSpeedVarFps.h"

namespace Cubicuous {
	namespace Core {
		namespace Loops {
			void ConstSpeedVarFps::loop(Scene *activeScene) {
				this->_checkSecondElapsed();
				this->_updates = 0;

				while ((this->_trackerStart = this->getTicks()) > this->_nextTick &&
					   this->_updates < ConstSpeedVarFps::MAX_UPDATES) {
					activeScene->update();
					this->_trackerEnd = this->getTicks();
					this->_updateTime = this->_trackerEnd - this->_trackerStart;
					this->_futs++;
					this->_nextTick += this->_skipTicks;
					this->_updates++;
				}

				this->_trackerStart = this->getTicks();
				activeScene->render((this->_trackerStart + this->_skipTicks - this->_nextTick) / this->_skipTicks);
				this->_trackerEnd = this->getTicks();
				this->_frts++;
				this->_renderTime = this->_trackerEnd - this->_trackerStart;
			}

			ConstSpeedVarFps::~ConstSpeedVarFps() {
				delete(&this->_nextTick);
				delete(&this->_skipTicks);
				delete(&this->_updates);
				delete(&this->_trackerStart);
				delete(&this->_trackerEnd);
			}
		}
	}
}