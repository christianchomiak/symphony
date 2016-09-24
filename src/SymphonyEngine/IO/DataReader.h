#pragma once

#include <TinyXML2/tinyxml2.h>

namespace Symphony
{
    bool ValidateXmlLoading(const char* filename, tinyxml2::XMLError error);
    const char* GetTextFromXmlElement(tinyxml2::XMLElement* element, const char* property);
    bool ReadFromXmlElement(tinyxml2::XMLElement* element, const char* property, bool& out);
    bool ReadFromXmlElement(tinyxml2::XMLElement* element, const char* property, unsigned int& out);
    bool ReadFromXmlElement(tinyxml2::XMLElement* element, const char* property, int& out);
}