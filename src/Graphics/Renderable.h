#ifndef CUBICUOUS_RENDERABLE_H
#define CUBICUOUS_RENDERABLE_H

namespace Cubicuous {
    namespace Graphics {
        class Renderable {
        public:
            virtual void render(double deltaTime) = 0;
        };
    }
}
#endif