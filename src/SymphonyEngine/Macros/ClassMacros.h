#pragma once

#define NO_EMPTY_CONSTRUCTOR(Class) Class##() = delete;
#define NO_COPY_CONSTRUCTOR(Class) Class##(Class const&) = delete;
#define NO_ASSIGNMENT_OPERATOR(Class) void operator=(Class const&) = delete;
#define NO_DESTRUCTOR(Class) ~##Class() = delete;

#define NO_DEFAULT_CONSTRUCTORS(Class) \
        NO_EMPTY_CONSTRUCTOR(Class)\
        NO_COPY_CONSTRUCTOR(Class)\
        NO_ASSIGNMENT_OPERATOR(Class)

//This should be accompanied by SINGLETON_INSTANCE_INIT() in the .cpp
#define SINGLETON(T) \
        protected:\
            static T* instance;\
            static void Release() { delete instance; instance = nullptr; }\
        private:\
            T();\
            ~T();\
        public:\
            NO_COPY_CONSTRUCTOR(T)\
            NO_ASSIGNMENT_OPERATOR(T)\
            static T* Instance()\
            {\
                if (!instance) instance = new T();\
                return instance;\
            }

#define SINGLETON_INSTANCE_INIT(T) T* T::instance = nullptr;