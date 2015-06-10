#ifndef CUBICUOUS_CONSTSPEEDVARFPS_H
#define CUBICUOUS_CONSTSPEEDVARFPS_H

#include "../ILoop.h"

namespace Cubicuous {
    namespace Core {
        namespace Loops {
            class ConstSpeedVarFps : public ILoop {
            private:
                static const int MAX_UPDATES = 5;
                double _nextTick;
                double _trackerStart;
                double _trackerEnd;
                int _updates;
                int _skipTicks;

            public:
                ConstSpeedVarFps(int updateRate) : ILoop(updateRate) {
                    this->_nextTick = this->getTicks();
                    this->_skipTicks = 1000 / updateRate;
                };

                ~ConstSpeedVarFps();

                virtual void loop(Scene *activeScene) override;
            };
        }
    }
}
#endif