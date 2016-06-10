#pragma once

#include <vector>
#include "../Scene/Scene.h"

namespace Symphony
{
    class Renderer
    {
    protected:
        struct PossibleObject
        {
            const GameObject* obj;
            float distanceToCamera;

            PossibleObject(const GameObject* obj, float distanceToCamera) : obj(obj), distanceToCamera(distanceToCamera) {};
            PossibleObject(const PossibleObject& original) : obj(original.obj), distanceToCamera(original.distanceToCamera) {};
            PossibleObject& operator=(PossibleObject& other) // move assignment
            {
                this->obj = other.obj;
                this->distanceToCamera = other.distanceToCamera;
                return *this;
            }
            static bool ClosestObjectToCamera(PossibleObject& a, PossibleObject& b)
            {
                return a.distanceToCamera > b.distanceToCamera;
            }
        };

    public:
        virtual ~Renderer() {};
        virtual void Render(const GameObject* sceneRoot, const std::vector<Camera*>& cameras, const std::vector<Light*>& lights) = 0;
        void ProcessTexture(const Texture& t) const;

    protected:
        /*static bool ClosestObjectToCamera(const GameObject* a, const GameObject* b)
        {
            return a->GetRenderObject()->distanceToCamera > b->GetRenderObject()->distanceToCamera;
            /*if (currentCamera)
            {
                glm::vec3 camPosition = currentCamera->transform.GetPosition();
                float distanceA = glm::distance2(a->transform.GetPosition(), camPosition);
                float distanceB = glm::distance2(b->transform.GetPosition(), camPosition);
                return distanceA > distanceB;
            }
            return false;*/
        //}
    };
}