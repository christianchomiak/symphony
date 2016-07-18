#pragma once

#include <vector>
#include "../Scene/Scene.h"

namespace Symphony
{
    class Renderer
    {
    protected:
        struct OrderableObject
        {
            const GameObject* obj;
            float distanceToCamera;

            OrderableObject(const GameObject* obj, float distanceToCamera) : obj(obj), distanceToCamera(distanceToCamera) {};
            OrderableObject(const OrderableObject& original) : obj(original.obj), distanceToCamera(original.distanceToCamera) {};
            OrderableObject& operator=(OrderableObject& other) // move assignment
            {
                this->obj = other.obj;
                this->distanceToCamera = other.distanceToCamera;
                return *this;
            }
            static bool FarthestObjectFromCamera(OrderableObject& a, OrderableObject& b)
            {
                return a.distanceToCamera > b.distanceToCamera;
            }
            static bool FarthestObjectFromCamera2D(OrderableObject& a, OrderableObject& b)
            {
                //In 2D, bigger numbers (closer to +Z) are near the camera.
                //This means that the approach used in `FarthestObjectFromCamera` would
                //result in the opposite of what we actually want now.
                return a.distanceToCamera < b.distanceToCamera;
            }
        };

    public:
        virtual ~Renderer() {};
        virtual void Render(const Scene* scene) = 0; //, const std::vector<Light*>& lights
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