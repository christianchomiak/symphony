#include "Transform.h"

//#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "GameObject.h"

namespace Symphony
{
    Transform::Transform()
        : localScale(1.f), localTransformMatrixDeprecated(true)
    {
        parent = nullptr;
    }

    Transform::~Transform()
    {
    }

    void Transform::RecomputeLocalTransformMatrix()
    {
        localTransformMatrix = glm::translate(localPosition)
                             * glm::toMat4(localRotation)
                             * glm::scale(localScale);

        localTransformMatrixDeprecated = false;
    }

    void Transform::UpdateWorldMatrix()
    {
        if (parent == nullptr)
        {
            worldTransformMatrix = GetLocalTransformMatrix();
        }
        else
        {
            worldTransformMatrix = parent->transform.GetWorldTransformMatrix() * GetLocalTransformMatrix();
        }
        
        //We only need to compute two of the directions as the third one
        //can be computed as the cross product of the previous ones
        glm::mat3 worldMat3 = glm::mat3(worldTransformMatrix);
        up      = worldMat3 * glm::vec3(0.f, 1.f, 0.f);
        forward = worldMat3 * glm::vec3(0.f, 0.f, 1.f);
        right   = glm::cross(up, forward);
        //right   = worldMat3 * glm::vec3(1.f, 0.f, 0.f);
    }

    void Transform::SetLocalPosition(float x, float y, float z)
    {
        localPosition.x = x;
        localPosition.y = y;
        localPosition.z = z;
        localTransformMatrixDeprecated = true;
    }

    void Transform::SetLocalScale(float x, float y, float z)
    {
        localScale.x = x;
        localScale.y = y;
        localScale.z = z;
        localTransformMatrixDeprecated = true;
    }

    void Transform::SetLocalRotation(float x, float y, float z)
    {
        localRotation = glm::quat(glm::radians(glm::vec3(x, y, z)));

        /*localScale.x = x;
        localScale.y = y;
        localScale.z = z;*/
        localTransformMatrixDeprecated = true;
    }

    void Transform::Translate(float xAmount, float yAmount, float zAmount)
    {
        localPosition.x += xAmount;
        localPosition.y += yAmount;
        localPosition.z += zAmount;
        localTransformMatrixDeprecated = true;
    }
    
    void Transform::Scale(float amount)
    {
        localScale *= amount;
        localTransformMatrixDeprecated = true;
    }
    
    void Transform::Rotate(float xAmount, float yAmount, float zAmount)
    {
        localRotation *= glm::quat(glm::radians(glm::vec3(xAmount, yAmount, zAmount)));

        /*localScale.x = x;
        localScale.y = y;
        localScale.z = z;*/
        localTransformMatrixDeprecated = true;
    }
}