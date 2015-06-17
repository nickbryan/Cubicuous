#ifndef CUBICUOUS_TESTSCENE_H
#define CUBICUOUS_TESTSCENE_H

#include "../../src/core/Scene.h"
#include "../../src/core/Entity.h"
#include "../../src/Game.h"

class TestScene : public Cubicuous::Core::Scene {
public:
    inline TestScene() : Scene(){};
    inline ~TestScene(){};
    void render(Cubicuous::Game *game, double deltaTime) override;

    void update(Cubicuous::Game *game) override;
};


#endif
