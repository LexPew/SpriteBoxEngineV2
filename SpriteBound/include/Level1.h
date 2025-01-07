#pragma once
#include "Core/Scene.h"
#include "PlayerActor.h"
#include "cereal/types/polymorphic.hpp"
#include "cereal/types/memory.hpp"


class Level1 : public Scene
{
private:
    bool reloadScene{ false };
    void OnFinishTrigger(Actor& p_actor);
    void ResetLevel();
public:
    Level1();

    void CreateLevel();
    void Update(float deltaTime) override;


};
CEREAL_REGISTER_TYPE(Level1)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Scene, Level1)
