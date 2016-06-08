#include "Transform.h"

//#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "GameObject.h"

namespace Symphony
{
    glm::vec4 Transform::WORLD_UP       = glm::vec4(0.f, 1.f, 0.f, 0.f),
              Transform::WORLD_FORWARD  = glm::vec4(0.f, 0.f, 1.f, 0.f);

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
        glm::mat4 RotationMatrix = glm::toMat4(localRotation);

        localTransformMatrix = glm::translate(localPosition)
                             * RotationMatrix                   //glm::toMat4(localRotation)
                             * glm::scale(localScale);

        up      = glm::vec3(RotationMatrix * WORLD_UP);
        forward = glm::vec3(RotationMatrix * WORLD_FORWARD);
        right   = glm::cross(up, forward);
        
        //invertedLocalRotation = glm::inverse(localRotation);

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
        /*glm::mat3 worldMat3 = glm::inverse( glm::mat3(worldTransformMatrix));
        //glm::mat3 worldMat3 = glm::toMat3(localRotation); // glm::mat3(worldTransformMatrix);

        up      = worldMat3 * glm::vec3(0.f, 1.f, 0.f);
        forward = worldMat3 * glm::vec3(0.f, 0.f, 1.f);
        //right   = glm::cross(up, forward);
        right   = worldMat3 * glm::vec3(1.f, 0.f, 0.f);*/
        
        /*up      = glm::vec3(invertedLocalRotation * WORLD_UP);
        forward = glm::vec3(invertedLocalRotation * WORLD_FORWARD);
        right   = glm::cross(up, forward);*/

        /*glm::mat4 RotationMatrix = glm::toMat4(localRotation);
        up = glm::vec3(RotationMatrix * WORLD_UP);
        forward = glm::vec3(RotationMatrix * WORLD_FORWARD);
        right = glm::cross(up, forward);*/
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
        localRotation = glm::quat(glm::radians(glm::vec3(xAmount, yAmount, zAmount))) * localRotation;
        
        /*localScale.x = x;
        localScale.y = y;
        localScale.z = z;*/
        localTransformMatrixDeprecated = true;
    }
}