#pragma once

#include <sstream>
#include "../SymphonyEngine/Scene/Text/Text2D.h"
#include "../SymphonyEngine/Rendering/UI/Font.h"
#include "../SymphonyEngine/Time/Time.h"

using namespace Symphony;

class FPSCounterObject : public Text2D
{
public:
    FPSCounterObject() = delete;
    
    explicit FPSCounterObject(const Text& text)
        : Text2D(text, "FPS_COUNTER")
    {
    }

    virtual ~FPSCounterObject()
    {
    }

    virtual void Update()
    {
        if (!Time::IsPaused())
        {
            sstream.clear();
            sstream.str("FPS: ");
            sstream << "FPS: " << glm::round((1.0 / (double)Time::TrueDeltaTime()));

            text.SetContent(sstream.str());
        }
    }
protected:
    std::stringstream sstream;
};