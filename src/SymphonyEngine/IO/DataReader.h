#pragma once

#include <TinyXML2/tinyxml2.h>

namespace Symphony
{
    bool ValidateXmlLoading(const char* filename, tinyxml2::XMLError error);
    const char* GetTextFromXmlElement(tinyxml2::XMLElement* element, const char* property);
    const char* GetTextFromXmlElementAttribute(tinyxml2::XMLElement* element, const char* attribute);
    
    bool ReadFromXmlElement(tinyxml2::XMLElement* element, const char* property, bool& out);
    bool ReadFromXmlElement(tinyxml2::XMLElement* element, const char* property, unsigned int& out);
    bool ReadFromXmlElement(tinyxml2::XMLElement* element, const char* property, int& out);

    bool ReadAttributeFromXmlElement(tinyxml2::XMLElement* element, const char* attribute, bool& out);
    bool ReadAttributeFromXmlElement(tinyxml2::XMLElement* element, const char* attribute, unsigned int& out);
    bool ReadAttributeFromXmlElement(tinyxml2::XMLElement* element, const char* attribute, int& out);
}