#pragma once

template<typename T>
class Singleton
{
public:
    static T* Instance();
    static void Release();

private:
    Singleton(Singleton const&) {};
    Singleton& operator=(Singleton const&) {};
    
protected:
    static T* instance;

    Singleton() {};
    //Singleton() { instance = static_cast <T*> (this); };
    virtual ~Singleton() {  };
};

template<typename T>
typename T* Singleton<T>::instance = nullptr;

template<typename T>
T* Singleton<T>::Instance()
{
    if (!instance)
    {
        Singleton<T>::instance = new T();
    }

    return instance;
}

template<typename T>
void Singleton<T>::Release()
{
    delete Singleton<T>::instance;
    Singleton<T>::instance = nullptr;
}
