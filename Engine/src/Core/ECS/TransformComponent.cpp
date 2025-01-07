#include "Core/ECS/TransformComponent.h"

#include <iostream>



void TransformComponent::Start()
{
	//Broadcast the position and scale on start
	onPositionChanged(position);
	onScaledChanged(scale);

}


