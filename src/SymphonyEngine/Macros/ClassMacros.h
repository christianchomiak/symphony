#pragma once

#define NO_EMPTY_CONSTRUCTOR(Class) Class##() = delete;
#define NO_COPY_CONSTRUCTOR(Class) Class##(Class const&) = delete;
#define NO_ASSIGNMENT_OPERATOR(Class) void operator=(Class const&) = delete;
#define NO_DESTRUCTOR(Class) ~##Class() = delete;

#define NO_DEFAULT_CONSTRUCTORS(Class) \
        NO_EMPTY_CONSTRUCTOR(Class)\
        NO_COPY_CONSTRUCTOR(Class)\
        NO_ASSIGNMENT_OPERATOR(Class)