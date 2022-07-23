#include "RenderObject.h"

glm::mat4 Transform::getModel() const
{
    glm::mat4 model(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    return model;
}
