//
//  PHObjcMessage.h
//  PHFoundation
//
//  Created by Panghu on 3/18/20.
//  Copyright © 2020 Panghu Lee. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT IMP _Nullable PHObjcMessageClassGetImplementation(Class _Nonnull cls, SEL _Nonnull name, bool * _Nullable existsSelf);

FOUNDATION_EXPORT bool PHObjcMessageClassAddMethod(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block);

FOUNDATION_EXPORT IMP _Nullable PHObjcMessageClassReplaceMethod(Class _Nullable cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block);

FOUNDATION_EXPORT IMP _Nullable PHObjcMessageClassOverrideMethod(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block);

#define _PHObjcMessageArguments(arguments...) DEL, ##arguments
#define _PHObjcMessageArgument(argument) argument

#define _PHObjcMessageWrapArguments(arguments...) arguments
#define _PHObjcMessageWrapImplementArguments(a1, a2, arguments...) a2, ##arguments  // (DEL, id self, SEL name) => (id self, SEL name)
#define _PHObjcMessageWrapBlockArguments(a1, a2, a3, arguments...) a2, ##arguments  // (DEL, id self, SEL name) => (id self)

#define _PHObjcMessageWrapGetClass(code) Class __cls = code
#define _PHObjcMessageWrapGetSelector(code) SEL __name = code
#define _PHObjcMessageWrapGetTypes(code) const char * _Nullable __types = code

#define _PHObjcMessageCallOriginal(arguments...) if(__builtin_expect((__ph_original_imp != NULL), 1)) { ((__typeof(__ph_original_impType))__ph_original_imp)(arguments); }
#define _PHObjcMessageCallOverride(arguments...) if(__builtin_expect((__ph_override_imp != NULL), 1)) { ((__typeof(__ph_override_impType))__ph_override_imp)(arguments); }

// Public

/// A macro for wrapping the return type of the swizzled method.
#define PHObjcMessageReturnType(type) type

/// A macro for wrapping arguments of the swizzled method.
#define PHObjcMessageArguments(arguments...) _PHObjcMessageArguments(arguments)

/// A macro for casting and calling original implementation.
/// May be used only in PHObjcMessageReplaceMethod.
#define PHObjcMessageCallOriginal(arguments...) _PHObjcMessageCallOriginal(arguments)

/// A macro for casting and calling override implementation.
/// May be used only in PHObjcMessageOverrideMethod.
#define PHObjcMessageCallOverride(arguments...) _PHObjcMessageCallOverride(arguments)

#define _PHObjcMessageAddMethod(CLS, NAME, TYPES, ReturnType, Arguments, Code)                                              \
            _PHObjcMessageWrapGetClass(CLS);                                                                                \
            _PHObjcMessageWrapGetSelector(NAME);                                                                            \
            _PHObjcMessageWrapGetTypes(TYPES);                                                                              \
            PHObjcMessageClassAddMethod(__cls, __name, __types, ^ReturnType(_PHObjcMessageWrapBlockArguments(Arguments))    \
                Code                                                                                                        \
            );

#define _PHObjcMessageReplaceMethod(CLS, NAME, TYPES, ReturnType, Arguments, Code)                                                  \
            _PHObjcMessageWrapGetClass(CLS);                                                                                        \
            _PHObjcMessageWrapGetSelector(NAME);                                                                                    \
            _PHObjcMessageWrapGetTypes(TYPES);                                                                                      \
            ReturnType (*__ph_original_impType)(_PHObjcMessageWrapImplementArguments(Arguments));                                   \
            __ph_original_impType = NULL;                                                                                           \
            __block IMP __ph_original_imp;                                                                                          \
            __ph_original_imp =                                                                                                     \
                PHObjcMessageClassReplaceMethod(__cls, __name, __types, ^ReturnType(_PHObjcMessageWrapBlockArguments(Arguments))    \
                    Code                                                                                                            \
            );


#define _PHObjcMessageOverrideMethod(CLS, NAME, TYPES, ReturnType, Arguments, Code)                                                 \
            _PHObjcMessageWrapGetClass(CLS);                                                                                        \
            _PHObjcMessageWrapGetSelector(NAME);                                                                                    \
            _PHObjcMessageWrapGetTypes(TYPES);                                                                                      \
            __block IMP __ph_override_imp;                                                                                          \
            ReturnType (*__ph_override_impType)(_PHObjcMessageWrapImplementArguments(Arguments));                                   \
            __ph_override_impType = NULL;                                                                                           \
            __ph_override_imp =                                                                                                     \
                PHObjcMessageClassOverrideMethod(__cls, __name, __types, ^ReturnType(_PHObjcMessageWrapBlockArguments(Arguments))   \
                    Code                                                                                                            \
            );

#define PHObjcMessageAddMethod(cls, name, types, return_type, arguments, code)      \
    do {                                                                            \
        _PHObjcMessageAddMethod(_PHObjcMessageArgument(cls),                        \
                                _PHObjcMessageArgument(name),                       \
                                _PHObjcMessageArgument(types),                      \
                                _PHObjcMessageArgument(return_type),                \
                                _PHObjcMessageWrapArguments(arguments),             \
                                _PHObjcMessageWrapArguments(code))                  \
    } while (false)

#define PHObjcMessageReplaceMethod(cls, name, types, return_type, arguments, code)      \
    do {                                                                                \
        _PHObjcMessageReplaceMethod(_PHObjcMessageArgument(cls),                        \
                                    _PHObjcMessageArgument(name),                       \
                                    _PHObjcMessageArgument(types),                      \
                                    _PHObjcMessageArgument(return_type),                \
                                    _PHObjcMessageWrapArguments(arguments),             \
                                    _PHObjcMessageWrapArguments(code))                  \
    } while (false)

#define PHObjcMessageOverrideMethod(cls, name, types, return_type, arguments, code)     \
do {                                                                                    \
    _PHObjcMessageOverrideMethod(_PHObjcMessageArgument(cls),                           \
                                _PHObjcMessageArgument(name),                           \
                                _PHObjcMessageArgument(types),                          \
                                _PHObjcMessageArgument(return_type),                    \
                                _PHObjcMessageWrapArguments(arguments),                 \
                                _PHObjcMessageWrapArguments(code))                      \
} while (false)

NS_ASSUME_NONNULL_END
