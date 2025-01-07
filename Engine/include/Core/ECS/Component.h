#pragma once

#include <cereal/types/polymorphic.hpp>
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
	 * Called when the component is created, used to set up initial state
	 */
    virtual void Awake() {};
    /**
     * Called after awake used for starting logic
     */
    virtual void Start() {};

    /**
     * Called every frame, used to update the component and its logic
     * @param p_deltaTime Time since last frame
     */
    virtual void Update(float p_deltaTime) {};

    /**
     * Called at the end of each frame, used to render any renderer related logic
     * @param p_renderer Current renderer
     */
    virtual void Render(Renderer& p_renderer) {};

	//------------------Serialization------------------

    template <class Archive>
    void save(Archive& archive) const {
        // Serialize base class data if any
    }

    template <class Archive>
    void load(Archive& archive) {
        // Serialize base class data if any
    }
};
CEREAL_REGISTER_TYPE(Component)
