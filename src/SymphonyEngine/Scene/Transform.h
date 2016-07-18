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

        //glm::quat invertedLocalRotation;

        bool localTransformMatrixDeprecated;

    public:
        Transform();
        ~Transform();

        void Scale(float amount);
        void Rotate(float xAmount, float yAmount, float zAmount);
        void Translate(float xAmount, float yAmount, float zAmount);

        void SetPosition(float x, float y, float z);
        void SetPosition(const glm::vec3& newPosition);
        void SetLocalPosition(const glm::vec3& newPosition);
        
        void    SetLocalScale(float x, float y, float z);
        void SetLocalPosition(float x, float y, float z);
        void SetLocalRotation(float x, float y, float z);

        const glm::vec3&    GetLocalScale() const;
        const glm::vec3& GetLocalPosition() const;
        const glm::quat& GetLocalRotation() const;

        glm::vec3 GetPosition() const;

        virtual const glm::vec3& Up() const;
        virtual const glm::vec3& Forward() const;
        virtual const glm::vec3& Right() const;

        const glm::mat4x4& GetWorldTransformMatrix() const;

        void UpdateWorldMatrix();

    protected:
        const glm::mat4x4& GetLocalTransformMatrix();

        void RecomputeLocalTransformMatrix();

    public:

        friend std::ostream& operator<<(std::ostream& os, const Transform& obj)
        {
            glm::vec3 gp = obj.GetPosition();
            os << "Global Position: (" << gp.x << ", " << gp.y << ", " << gp.z << ")" << std::endl;
            os << "Local Position: (" << obj.localPosition.x << ", " << obj.localPosition.y << ", " << obj.localPosition.z << ")" << std::endl;
            os << "Scale: (" << obj.localScale.x << ", " << obj.localScale.y << ", " << obj.localScale.z << ")" << std::endl;

            glm::quat rot = obj.GetLocalRotation();
            //transform quaternion
            //glm::vec3 eulerAngles = obj.GetLocalRotationInEulerDegree();
            os << "Rotation: (" << glm::degrees(glm::pitch(rot)) << ", " << glm::degrees(glm::yaw(rot)) << ", " << glm::degrees(glm::roll(rot)) << ")" << std::endl;

            return os;
        }
    
    protected:
        static glm::vec4 WORLD_UP, WORLD_FORWARD;
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

    inline void Symphony::Transform::SetPosition(float x, float y, float z)
    {
        glm::vec3 delta = glm::vec3(x, y, z);
        delta -= GetPosition();
        Translate(delta.x, delta.y, delta.z);
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
    
    //TO-DO: Can this return `const glm::vec3&` ?
    inline glm::vec3 Symphony::Transform::GetPosition() const
    {
        return glm::vec3(worldTransformMatrix[3]);
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
        
    inline void Symphony::Transform::SetPosition(const glm::vec3& newPosition)
    {
        SetPosition(newPosition.x, newPosition.y, newPosition.z);
    }

    inline void Symphony::Transform::SetLocalPosition(const glm::vec3& newPosition)
    {
        SetLocalPosition(newPosition.x, newPosition.y, newPosition.z);
    }
}