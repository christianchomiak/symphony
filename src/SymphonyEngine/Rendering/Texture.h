#pragma once

namespace Symphony
{
    struct Texture
    {
        friend class TextureManager;
    public:
        enum WrappingType { REPEAT, MIRRORED_REPEAT, CLAMP, CLAMP_TO_EDGE, CLAMP_TO_BORDER };
        enum FilteringType { NEAREST, LINEAR, TRILINEAR };
        enum Transparency { NONE, SEMI, FULL };

        WrappingType wrapping;

        //TO-DO: Perhaps there should be separate filtering options for MIN & MAG properties
        FilteringType filter;

        
    public:
        Texture(unsigned int newID = 0, WrappingType wrapping = WrappingType::REPEAT, FilteringType filter = FilteringType::NEAREST)
            : id(newID), wrapping(wrapping), filter(filter), transparency(Transparency::NONE)
        {
        }

        void CopyValuesFromTexture(const Texture& original)
        {
            id = original.id;
            wrapping = original.wrapping;
            filter = original.filter;
            transparency = original.transparency;
        }
        
        Transparency GetTransparencyType() const;
        unsigned int ID() const;
        /*bool GetRepeat() const;
        bool GetFiltering() const;
        void SetRepeat(bool willRepeat);
        void SetFiltering(bool willBeFiltered);*/

    protected:
        Transparency transparency;
        unsigned int id;
    };

    inline Texture::Transparency Texture::GetTransparencyType() const
    {
        return transparency;
    }

    inline unsigned int Texture::ID() const
    {
        return id;
    }

    /*inline bool Texture::GetRepeat() const
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