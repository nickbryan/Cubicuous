#ifndef CUBICUOUS_ILOOP_H
#define CUBICUOUS_ILOOP_H

#include <time.h>
#include <ctime>
#include "../Scene.h"
#include "../../Game.h"

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <sys/time.h>
#endif

namespace Cubicuous {
    namespace Core {
        namespace Loops {
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
                time_t _nextTime = 0;

            public:
                inline ILoop(int updateRate) {
                    this->_updateRate = updateRate;
                    this->_nextTime = std::time(nullptr);
                }

                inline virtual ~ILoop() {};

                virtual void loop(Game* game) = 0;

                inline virtual int getFps() const { return this->_frps; }

                inline virtual int getUps() const { return this->_fups; }

                inline virtual double getRenderTime() const { return this->_renderTime; };

                inline virtual double getUpdateTime() const { return this->_updateTime; };

                inline unsigned getTicks() const {
                #ifdef _WIN32
                    return GetTickCount();
                #else
                    struct timeval tv;
                    gettimeofday(&tv, 0);
                    return unsigned((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
                #endif
                }

                inline virtual void _checkSecondElapsed() {
                    if (std::time(nullptr) > this->_nextTime) { //been more than 1000ms
                        this->_fups = this->_futs;
                        this->_frps = this->_frts;
                        this->_futs = 0;
                        this->_frts = 0;
                        this->_nextTime++; //in another second
                    }
                }
            };
        }
    }
}

#endif