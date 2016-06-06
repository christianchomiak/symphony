#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>

#include <ostream>

namespace Symphony
{
    class Transform final
    {
        friend class GameObject;
        
    public:
        GameObject* parent;

    protected:
        glm::vec3 localPosition;
        glm::vec3 localScale;
        glm::quat localRotation;

        glm::vec3 up;
        glm::vec3 forward;
        glm::vec3 right;

        glm::mat4 localTransformMatrix;
        glm::mat4 worldTransformMatrix;

        bool localTransformMatrixDeprecated;

    public:
        Transform();
        ~Transform();
        
        void Translate(float xAmount, float yAmount, float zAmount);
        void Scale(float amount);
        void Rotate(float xAmount, float yAmount, float zAmount);

        void SetLocalPosition(float x, float y, float z);
        void SetLocalScale(float x, float y, float z);
        void SetLocalRotation(float x, float y, float z);

        const glm::vec3& GetLocalPosition() const;
        const glm::vec3& GetLocalScale() const;
        const glm::quat& GetLocalRotation() const;

        virtual const glm::vec3& Forward() const;
        virtual const glm::vec3& Up() const;
        virtual const glm::vec3& Right() const;

        const glm::mat4x4& GetWorldTransformMatrix() const;

        void UpdateWorldMatrix();

    protected:
        const glm::mat4x4& GetLocalTransformMatrix();

        void RecomputeLocalTransformMatrix();

    public:

        friend std::ostream& operator<<(std::ostream& os, const Transform& obj)
        {
            os << "Position: (" << obj.localPosition.x << ", " << obj.localPosition.y << ", " << obj.localPosition.z << ")" << std::endl;
            os << "Scale: (" << obj.localScale.x << ", " << obj.localScale.y << ", " << obj.localScale.z << ")" << std::endl;

            // transform quaternion
            /*glm::vec3 eulerAngles = obj.GetLocalRotationInEulerDegree();
            os << "Rotation: (" << eulerAngles.x << ", " << eulerAngles.y << ", " << eulerAngles.z << ")" << std::endl;*/

            return os;
        }
    };
    
    inline const glm::mat4x4& Symphony::Transform::GetLocalTransformMatrix()
    {
        if (localTransformMatrixDeprecated)
        {
            //Instead of inlining it in this one,
            //let's call it in a separate function to make this as
            //small as possible. Additionally, this saves us from including
            //<glm/gtx/transform.hpp> in this header file.
            RecomputeLocalTransformMatrix();
        }

        return localTransformMatrix;
    }

    inline const glm::mat4x4& Symphony::Transform::GetWorldTransformMatrix() const
    {
        return worldTransformMatrix;
    }
    
    inline const glm::vec3& Symphony::Transform::GetLocalPosition() const
    {
        return localPosition;
    }

    inline const glm::vec3& Symphony::Transform::GetLocalScale() const
    {
        return localScale;
    }

    inline const glm::quat& Symphony::Transform::GetLocalRotation() const
    {
        return localRotation;
    }
    
    inline const glm::vec3& Symphony::Transform::Forward() const {
        return forward;
    }

    inline const glm::vec3& Symphony::Transform::Up() const {
        return up;
    }
    
    inline const glm::vec3& Symphony::Transform::Right() const {
        return right;
    }
}