#pragma once
 
namespace Symphony
{
    class GameTimer
    {
    public:
        //How many milliseconds have passed since the GameTimer was created
        virtual float GetMS() = 0;

        //How many seconds have passed since GetTimedMS was last called
        virtual float GetDeltaTime() = 0;

        virtual void Update() = 0;

        static GameTimer* CreateTimer();

    protected:
        float deltaTime = 0.f;

        GameTimer() {};

        //How many milliseconds have passed since GetTimedMS was last called
        virtual float GetTimedMS() = 0;

    private:
        GameTimer(GameTimer const&) = delete;
        void operator=(GameTimer const&) = delete;
    };
}