#pragma once

namespace Symphony
{
    struct Texture
    {
    public:
        enum WrappingType { REPEAT, MIRRORED_REPEAT, CLAMP, CLAMP_TO_EDGE, CLAMP_TO_BORDER };
        enum FilteringType { NEAREST, LINEAR, TRILINEAR };

        WrappingType wrapping;

        //TO-DO: Perhaps there should be separate filtering options for MIN & MAG properties
        FilteringType filter;

        unsigned int id;
        
    public:
        Texture(unsigned int newID = 0, WrappingType wrapping = WrappingType::REPEAT, FilteringType filter = FilteringType::NEAREST)
            : id(newID), wrapping(wrapping), filter(filter)
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