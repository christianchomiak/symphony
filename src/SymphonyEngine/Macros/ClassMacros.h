#pragma once

#define DELETE_ALL_CONSTRUCTORS(Class) \
    Class##() = delete;\
    Class##(Class const&) = delete;\
    void operator=(Class const&) = delete;

#define DELETE_DESTRUCTOR(Class) ~##Class() = delete;