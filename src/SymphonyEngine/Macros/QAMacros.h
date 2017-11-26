#pragma once

/* These macros should be handy for those cases where it might be useful to
 * execute code that will only be used for QA/Testing purposes and that will
 * not be needed in Release mode.
 */

#ifdef _DEBUG

#   include <Debugging/Debugging.h>

#   define CHECK_NULL_POINTER(pointer, DEBUG_FUNCTION, FAILURE_INSTRUCTION) \
        if (pointer == nullptr) \
        { \
            DEBUG_FUNCTION("Null pointer found in: "#pointer); \
            _WATCHPOINT \
            FAILURE_INSTRUCTION; \
        }

//#   define NULL_POINTER_ERROR(pointer, FAILURE_INSTRUCTION)   CHECK_NULL_POINTER(pointer, Symphony::Debug::DoLogError,   FAILURE_INSTRUCTION)
//#   define NULL_POINTER_WARNING(pointer, FAILURE_INSTRUCTION) CHECK_NULL_POINTER(pointer, Symphony::Debug::DoLogWarning, FAILURE_INSTRUCTION)

#else

#   define CHECK_NULL_POINTER(pointer, DEBUG_FUNCTION, FAILURE_INSTRUCTION)

//#   define NULL_POINTER_ERROR(pointer, FAILURE_INSTRUCTION)
//#   define NULL_POINTER_WARNING(pointer, FAILURE_INSTRUCTION)

#endif