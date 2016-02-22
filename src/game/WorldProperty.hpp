//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_WorldProperties_H
#define JUMPER_WorldProperties_H

#include "Vector.hpp"

namespace jumper
{

/**
 * @brief	A class that holds properties about the physical characteristics
 * 			of a level.
 */
class WorldProperty
{
public:

    WorldProperty();

    /**
     * Constructor.
     *
     * @param damping		Damping force on tiles
     */
    WorldProperty(const Vector2f& damping);

    /**
     * Returns the damping force
     */
    const Vector2f &damping() const;

    /**
     * Sets the damping force
     */
    void setDamping(const Vector2f &damping);

private:

    /// Damping force. Currently for the whole level
    Vector2f m_damping;
};

}
#endif //JUMPER_WorldProperties_H
