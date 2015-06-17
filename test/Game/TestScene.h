#ifndef CUBICUOUS_TESTSCENE_H
#define CUBICUOUS_TESTSCENE_H

#include "../../src/core/Scene.h"
#include "../../src/core/Entity.h"
#include "../../src/Game.h"

class TestScene : public Cubicuous::Core::Scene {
public:
    inline TestScene(Cubicuous::Game* game) : Scene(game) {};
    inline ~TestScene() {};
    void render(double deltaTime) override;

    void update() override;
};


#endif
