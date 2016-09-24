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
            Debug::LogError("Property name cannot be null");
            return false;
        }
        if (element->FirstChildElement(property) == nullptr)
        {
            Debug::LogError("Property was not found");
            return false;
        }
        return true;
    }

    bool ValidateXmlLoading(const char * filename, tinyxml2::XMLError error)
    {
        switch (error)
        {
        case tinyxml2::XML_SUCCESS:
            Debug::Log("Loaded window properties file");
            break;
        case tinyxml2::XML_ERROR_FILE_READ_ERROR:
            Debug::LogError("There was an error trying to read the window properties file");
            return false;
        case tinyxml2::XML_ERROR_FILE_NOT_FOUND:
            Debug::LogError("Could not find the window properties file");
            return false;
        case tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
            Debug::LogError("Could not open the window properties file");
            return false;
        case tinyxml2::XML_ERROR_EMPTY_DOCUMENT:
            Debug::LogError("The window properties file is empty");
            return false;
        case tinyxml2::XML_ERROR_PARSING:
            Debug::LogError("Could not parse the window properties file");
            return false;
        default:
            Debug::LogError("Unkown error trying to load the window properties file");
            return false;
        }

        return true;
    }

    const char* GetTextFromXmlElement(tinyxml2::XMLElement* element, const char* property)
    {
        return TestElementAndProperty(element, property) ? element->FirstChildElement(property)->GetText() : nullptr;
    }

    bool ReadFromXmlElement(tinyxml2::XMLElement* element, const char* property, bool & out)
    {
        if (!TestElementAndProperty(element, property)) return false;
        
        if (element->FirstChildElement(property)->QueryBoolText(&out) != tinyxml2::XMLError::XML_SUCCESS)
        {
            Debug::LogError("Unkown error trying to read property from element");
            return false;
        }

        return true;
    }

    bool ReadFromXmlElement(tinyxml2::XMLElement * element, const char * property, unsigned int & out)
    {
        if (!TestElementAndProperty(element, property)) return false;

        if (element->FirstChildElement(property)->QueryUnsignedText(&out) != tinyxml2::XMLError::XML_SUCCESS)
        {
            Debug::LogError("Unkown error trying to read property from element");
            return false;
        }

        return true;
    }

    bool ReadFromXmlElement(tinyxml2::XMLElement * element, const char * property, int & out)
    {
        if (!TestElementAndProperty(element, property)) return false;

        if (element->FirstChildElement(property)->QueryIntText(&out) != tinyxml2::XMLError::XML_SUCCESS)
        {
            Debug::LogError("Unkown error trying to read property from element");
            return false;
        }

        return true;
    }

}