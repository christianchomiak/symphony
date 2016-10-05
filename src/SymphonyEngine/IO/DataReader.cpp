#include "DataReader.h"

#include "../Debugging/Debugging.h"

namespace Symphony
{
    bool TestElementAndProperty(tinyxml2::XMLElement* element, const char* property)
    {
        if (element == nullptr)
        {
            Debug::LogError("XML Element cannot be null");
            return false;
        }
        if (property == nullptr)
        {
            Debug::LogError("XML Property name cannot be null");
            return false;
        }
        if (element->FirstChildElement(property) == nullptr)
        {
            Debug::LogErrorF("Property \"%s\" was not found in XML", property);
            return false;
        }
        return true;
    }

    bool ValidateXmlLoading(const char * filename, tinyxml2::XMLError error)
    {
        switch (error)
        {
        case tinyxml2::XML_SUCCESS:
            Debug::LogF("Loaded XML file \"%s\"", filename);
            break;
        case tinyxml2::XML_ERROR_FILE_READ_ERROR:
            Debug::LogErrorF("There was an error trying to read XML file \"%s\"", filename);
            return false;
        case tinyxml2::XML_ERROR_FILE_NOT_FOUND:
            Debug::LogErrorF("Could not find XML file \"%s\"", filename);
            return false;
        case tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
            Debug::LogErrorF("Could not open XML file \"%s\"", filename);
            return false;
        case tinyxml2::XML_ERROR_EMPTY_DOCUMENT:
            Debug::LogErrorF("File \"%s\" is empty", filename);
            return false;
        case tinyxml2::XML_ERROR_PARSING:
            Debug::LogErrorF("Could not parse XML file \"%s\"", filename);
            return false;
        default:
            Debug::LogErrorF("Unkown error trying to load XML file \"%s\"", filename);
            return false;
        }

        return true;
    }
    
    const char* GetTextFromXmlElement(tinyxml2::XMLElement* element, const char* property)
    {
        return TestElementAndProperty(element, property) ? element->FirstChildElement(property)->GetText() : nullptr;
    }
    

#define READ_FROM_XML(TYPE, QUERY) \
    bool ReadFromXmlElement(tinyxml2::XMLElement * element, const char * property, TYPE & out)\
    {\
        if (!TestElementAndProperty(element, property)) return false;\
        if (element->FirstChildElement(property)->QUERY(&out) != tinyxml2::XMLError::XML_SUCCESS)\
        {\
            Debug::LogErrorF("Unkown error trying to read property \"%s\" from element in XML", property);\
            return false;\
        }\
        return true;\
    }

    READ_FROM_XML(unsigned int, QueryUnsignedText)
    READ_FROM_XML(int, QueryIntText)
    READ_FROM_XML(bool, QueryBoolText)
#undef READ_FROM_XML

}