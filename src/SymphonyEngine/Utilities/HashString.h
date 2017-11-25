/* Sources:
 * - Jason Gregory's "Game Engine Architecture"
 * - http://en.cppreference.com/w/cpp/utility/hash
*/
#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#include "../global.h"
#include "../Macros/PlatformMacros.h"
#include "../Debugging/Debugging.h"

namespace Symphony
{
    class HashString
    {
#ifdef _DEBUG
    protected:
        static std::map<std::size_t, std::string> stringDatabase;

        static bool MapHashToString(const std::size_t hash, const std::string& string)
        {
            if (stringDatabase.find(hash) == stringDatabase.end())
            {
                stringDatabase[hash] = string;
            }

            const bool mappingIsOk = stringDatabase[hash] == string;

            AssertF(mappingIsOk, "HashString error: hash %zu maps to both \"%s\" and \"%s\".", stringDatabase[hash], string);

            return mappingIsOk;
        }
#endif

    protected:
        std::size_t hash;

        inline void AssignString(const std::string& newString)
        {
            std::size_t tempHash;

            if (!newString.empty())
            {
                std::string processedString = newString;
                std::transform(processedString.begin(), processedString.end(), processedString.begin(), ::toupper);

                tempHash = std::hash<std::string>{}(processedString);

#ifdef _DEBUG
                if (!MapHashToString(tempHash, processedString))
                {
                    tempHash = 0u;
                }
#endif
            }
            else
            {
                tempHash = 0u;
            }

            hash = tempHash;
        }

    public:
        HashString() : hash(0u)
        {
        }

        HashString(const char* newValue)
            : HashString(std::string(newValue))
        {
        }

        HashString(const std::string& newString)
        {
            AssignString(newString);
        }
        
        ~HashString()
        {
        }

        inline bool IsValid() const
        {
            return hash != 0u;
        }

        inline operator bool() const
        {
            return IsValid();
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

        inline bool operator==(const std::size_t otherHash) const
        {
            return hash == otherHash;
        }
        
        inline bool operator!=(const std::size_t otherHash) const
        {
            return !(hash == otherHash);
        }
        
        inline bool operator<(const HashString& other) const
        {
            return hash < other.hash;
        }

        //Assignment operators
        inline HashString& operator=(const std::string& newString)
        {
            AssignString(newString);

            return *this;
        }

        inline HashString& operator=(const char* newString)
        {
            AssignString(newString);

            return *this;
        }

#ifdef _DEBUG

        inline const std::string& GetStringConstRef() const
        {
            AssertF(stringDatabase.find(hash) != stringDatabase.end(), "HashString error: No string mapped to hash [%zu]");

            return stringDatabase[hash];
        }

        inline std::string GetString() const
        {
            if (stringDatabase.find(hash) != stringDatabase.end())
            {
                return stringDatabase[hash];
            }

            return "";
        }

        inline const char* GetCString() const
        {
            if (stringDatabase.find(hash) != stringDatabase.end())
            {
                return stringDatabase[hash].c_str();
            }

            return "";
        }

        //Access operators
        inline char operator[](std::size_t idx) const
        {
            if (stringDatabase.find(hash) != stringDatabase.end())
            {
                return (stringDatabase[hash])[idx];
            }

            return '\0';
        }

        inline friend std::ostream& operator<<(std::ostream& os, const HashString& obj)
        {
            os << obj.GetString();

            return os;
        }
#endif
    };
}