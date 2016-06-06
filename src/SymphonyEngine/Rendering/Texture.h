#pragma once

namespace Symphony
{
    struct Texture
    {
    public:
        enum WrappingType { REPEAT, MIRRORED_REPEAT, CLAMP, CLAMP_TO_EDGE, CLAMP_TO_BORDER };

        WrappingType typeOfWrapping;
        bool filter;
        unsigned int id;
        
    public:
        Texture(unsigned int newID = 0, WrappingType wrapping = WrappingType::REPEAT, bool filter = false)
            : id(newID), typeOfWrapping(wrapping), filter(filter)
        {
        }
        
        /*unsigned int ID() const;
        bool GetRepeat() const;
        bool GetFiltering() const;
        void SetRepeat(bool willRepeat);
        void SetFiltering(bool willBeFiltered);*/
    };

    /*inline unsigned int Texture::ID() const
    {
        return id;
    }

    inline bool Texture::GetRepeat() const
    {
        return repeat;
    }

    inline bool Texture::GetFiltering() const
    {
        return filter;
    }

    void SetRepeat(bool willRepeat)
    {

    }

    void SetFiltering(bool willBeFiltered)
    {

    }*/
}