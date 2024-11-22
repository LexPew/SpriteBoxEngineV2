#pragma once
#include <Utils/json.hpp>
class Entity;
class Renderer;

/**
 * Component class, used to define the base structure of a component
 */
class Component
{
public:
	Entity* owner{ nullptr };
	virtual ~Component() = default;

	/**
	 * Called when the component is initialized, used to set up initial state
	 */	
	virtual void Start() = 0;

	/**
	 * Called every frame, used to update the component and its logic
	 * @param p_deltaTime Time since last frame
	 */
	virtual void Update(float p_deltaTime) = 0;


	/**
	 * Called at the end of each frame, used to render any renderer related logic
	 * @param p_renderer Current renderer
	 */
	virtual void Render(Renderer& p_renderer) = 0;

	//Serialization

	/**
	 * Used to serialize the component and its variables to a json object
	 * @param p_json  Json object to write to
	 */
	virtual void Serialize(nlohmann::json& p_json) = 0;
	/**
	 * Used to deserialize the component and its variables from a json object
	 * @param p_json  Json object to read from
	 */
	virtual void Deserialize(const nlohmann::json& p_json) = 0;
};

