/* Sources:
 * - Jason Gregory's "Game Engine Architecture"
 * - http://en.cppreference.com/w/cpp/utility/hash
*/
#pragma once

#include <string>
#include <algorithm>

#ifdef _DEBUG
#   include <map>
#   include <iostream>
#endif

#include <SymphonyGlobal.h>
#include <Macros/PlatformMacros.h>
#include <Debugging/Debugging.h>

namespace Symphony
{
    class HashString
    {
    public:
        HashString() : hash(0u)
        {
        }

        HashString(uint newHash) : hash(newHash)
        {
        }

        HashString(const char* newValue)
            : HashString(std::string(newValue))
        {
        }

        explicit HashString(const std::string& newString)
        {
            GenerateHash(newString);
        }

        HashString(const HashString& other)
            : hash(other.hash)
        {
        }
        
        ~HashString()
        {
        }
        
        bool IsNull() const;
        bool IsNotNull() const;
        
        //Comparisson operators
        bool operator==(const HashString& other) const;
        
        bool operator!=(const HashString& other) const;

        bool operator==(const std::size_t otherHash) const;
        
        bool operator!=(const std::size_t otherHash) const;
        
        bool operator<(const HashString& other) const;

        //Assignment operators
        HashString& operator=(const HashString& other);

        HashString& operator=(const std::string& newString);

        HashString& operator=(const char* newString);

        HashString& operator=(size_t newHash);
        
        size_t GetHash() const;

        std::string GetString() const;

        const char* GetCString() const;

        //Access operators
        char operator[](std::size_t idx) const;

        static size_t CalculateHash(std::string newString);

        //Public debug functions
#ifdef _DEBUG
        bool HasString() const;

        const std::string& GetStringConstRef() const;
        
        inline friend std::ostream& operator<<(std::ostream& os, const HashString& obj)
        {
            os << obj.GetCString();

            return os;
        }
#endif

    protected:
        std::size_t hash;

        void GenerateHash(std::string newString);

        //Protected static functions
#ifdef _DEBUG
    protected:
        static std::map<std::size_t, std::string> stringDatabase;

        static bool MapHashToString(const std::size_t hash, const std::string& string)
        {
            //Was the mapping already done?
            if (stringDatabase.find(hash) == stringDatabase.end())
            {
                stringDatabase[hash] = string;
                return true;
            }
            
            const bool mappingIsOk = stringDatabase[hash] == string;

            AssertF(mappingIsOk, "HashString error: hash [%zu] maps to both \"%s\" and \"%s\".", hash, stringDatabase[hash].c_str(), string.c_str());

            return mappingIsOk;
        }
#endif

    };



    ///INLINES

    //static
    inline size_t HashString::CalculateHash(std::string newString)
    {
        if (!newString.empty())
        {
            return std::hash<std::string>{}(newString);
        }

        return 0u;
    }

    inline size_t HashString::GetHash() const
    {
        return hash;
    }

    inline bool HashString::IsNull() const
    {
        return hash == 0u;
    }

    inline bool HashString::IsNotNull() const
    {
        return hash != 0u;
    }

    //Comparisson operators
    inline bool HashString::operator==(const HashString& other) const
    {
        return this->hash == other.hash;
    }

    inline bool HashString::operator!=(const HashString& other) const
    {
        return !(this->hash == other.hash);
    }

    inline bool HashString::operator==(const std::size_t otherHash) const
    {
        return hash == otherHash;
    }

    inline bool HashString::operator!=(const std::size_t otherHash) const
    {
        return !(hash == otherHash);
    }

    inline bool HashString::operator<(const HashString& other) const
    {
        return hash < other.hash;
    }

    //Assignment operators
    inline HashString& HashString::operator=(const HashString& other)
    {
        hash = other.hash;

        return *this;
    }
    
    inline HashString& HashString::operator=(const std::string& newString)
    {
        GenerateHash(newString);

        return *this;
    }

    inline HashString& HashString::operator=(const char* newString)
    {
        GenerateHash(newString);

        return *this;
    }

    inline HashString& HashString::operator=(size_t newHash)
    {
        hash = newHash;

        return *this;
    }

    inline void HashString::GenerateHash(std::string newString)
    {
        std::transform(newString.begin(), newString.end(), newString.begin(), ::toupper);

        std::size_t tempHash = CalculateHash(newString);

#       ifdef _DEBUG
            if (!MapHashToString(tempHash, newString))
            {
                tempHash = 0u;
            }
#       endif

        hash = tempHash;
    }
    
    inline std::string HashString::GetString() const
    {
#ifdef _DEBUG
        if (IsNotNull() && stringDatabase.find(hash) != stringDatabase.end())
        {
            return stringDatabase[hash];
        }
#endif

        return IsNotNull() ? std::to_string(hash) : "";
    }
    
    //Access operators
    inline char HashString::operator[](std::size_t idx) const
    {
#ifdef _DEBUG
        if (IsNotNull() && stringDatabase.find(hash) != stringDatabase.end())
        {
            return (stringDatabase[hash])[idx];
        }
#endif

        return '\0';
    }

#ifdef _DEBUG

    inline bool HashString::HasString() const
    {
        return IsNotNull() && stringDatabase.find(hash) != stringDatabase.end();
    }

    inline const char* HashString::GetCString() const
    {
        if (IsNotNull() && stringDatabase.find(hash) != stringDatabase.end())
        {
            return stringDatabase[hash].c_str();
        }

        return "";
    }

    inline const std::string& HashString::GetStringConstRef() const
    {
        AssertF(IsNotNull() && stringDatabase.find(hash) != stringDatabase.end(), "HashString error: No string mapped to hash [%zu]");

        return stringDatabase[hash];
    }
#endif
}