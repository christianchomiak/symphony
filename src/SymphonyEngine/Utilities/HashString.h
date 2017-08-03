/* Sources:
 * - Jason Gregory's "Game Engine Architecture"
 * - http://en.cppreference.com/w/cpp/utility/hash
*/
#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "../Macros/PlatformMacros.h"

namespace Symphony
{
    class HashString
    {
    public:
        HashString() : hash(0)
        {
        }

        HashString(const char* newValue)
            : HashString(std::string(newValue))
        {
        }

        HashString(const std::string& newValue)
        {
            std::string newVal = newValue;
            std::transform(newVal.begin(), newVal.end(), newVal.begin(), ::toupper);
            DEBUG_ONLY(value = newVal);
            hash = std::hash<std::string>{}(newVal);
        }
        
        ~HashString()
        {
        }

        //Comparisson operators
        inline bool operator==(const HashString& other) const
        {
            return this->hash == other.hash;
        }
        
        inline bool operator!=(const HashString& other) const
        {
            return !(this->hash == other.hash);
        }

        inline bool operator==(const std::size_t& otherHash) const
        {
            return hash == otherHash;
        }
        
        inline bool operator!=(const std::size_t& otherHash) const
        {
            return !(hash == otherHash);
        }
        

        inline bool operator<(const HashString& other) const
        {
            return hash < other.hash;
        }

        //Assignment operators
        inline HashString& operator=(const std::string& other)
        {
            DEBUG_ONLY(value = other;)
            
            hash = std::hash<std::string>{}(other);

            return *this;
        }

        inline HashString& operator=(const char* other)
        {
            std::string otherString(other);
            DEBUG_ONLY(value = otherString;)

            hash = std::hash<std::string>{}(otherString);

            return *this;
        }

#ifdef _DEBUG

        inline const std::string& GetStringConstRef() const
        {
            return value;
        }

        inline std::string GetString()
        {
            return value;
        }

        //Access operators
        inline char operator[](std::size_t idx) const
        {
            return value[idx];
        }

        inline friend std::ostream& operator<<(std::ostream& os, const HashString& obj)
        {
            os << obj.value;

            return os;
        }
#endif

    protected:
        std::size_t hash;

        DEBUG_ONLY(std::string value;)
    };
}