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
        : Text2D(text)
    {
    }

    virtual ~FPSCounterObject()
    {
    }

    virtual void Update()
    {
        sstream.clear();
        sstream.str("FPS: ");
        sstream << "FPS: " << glm::round((1.0 / (double)Time::DeltaTime()));

        text.SetContent(sstream.str());
    }
protected:
    std::stringstream sstream;
};