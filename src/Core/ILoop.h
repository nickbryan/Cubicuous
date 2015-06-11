#ifndef CUBICUOUS_ILOOP_H
#define CUBICUOUS_ILOOP_H

#include <time.h>
#include <ctime>
#include "Scene.h"

namespace Cubicuous {
    namespace Core {
        class ILoop {
        protected:
            //desired fps
            int _updateRate;


            int _frps = 0; //frames rendered previous second
            int _frts = 0; //frames rendered this second

            int _fups = 0; //updates ran previous second
            int _futs = 0; //updates ran this second

            double _renderTime;
            double _updateTime;

        private:
            int _nextTime = 0;

        public:
            inline ILoop(int updateRate) { this->_updateRate = updateRate; }

            virtual void loop(Scene *activeScene) { };

            inline virtual int getFps() const { return this->_frps; }

            inline virtual int getUps() const { return this->_fups; }

            inline virtual double getRenderTime() const { return this->_renderTime; };

            inline virtual double getUpdateTime() const { return this->_updateTime; };

            inline double getTicks() const { return static_cast<double>(clock()) / CLOCKS_PER_SEC; }

            inline virtual void _checkSecondElapsed() {
                if (std::time(nullptr) > this->_nextTime) { //been more than 1000ms
                    this->_fups = this->_futs;
                    this->_frps = this->_frts;
                    this->_nextTime++; //in another 1000ms
                }
            }
        };
    }
}

#endif