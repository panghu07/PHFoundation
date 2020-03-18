//
//  PHObjcMessage.m
//  PHFoundation
//
//  Created by Panghu on 3/18/20.
//  Copyright © 2020 Panghu Lee. All rights reserved.
//

#import "PHObjcMessage.h"

#import <objc/runtime.h>
#import <objc/message.h>

IMP _Nullable PHObjcMessageClassGetImplementation(Class _Nonnull cls, SEL _Nonnull name, bool * _Nullable existsSelf) {
    
    if (object_isClass(cls) == false) {
        *existsSelf = false;
        return NULL;
    }
    
    Method method = class_isMetaClass(cls) ? class_getClassMethod(cls, name) : class_getInstanceMethod(cls, name);
    if (method == NULL) {
        *existsSelf = false;
        return NULL;
    }
    
    *existsSelf = false;
    unsigned int count;
    Method *methods = class_copyMethodList(cls, &count);
    for (unsigned int index = 0; index < count; index ++) {
        SEL sel = method_getName(methods[index]);
        if (sel_isEqual(sel, name)) {
            *existsSelf = true;
            break;
        }
    }
    
    if (methods != NULL) {
        free(methods);
    }
    
    return method != NULL ? method_getImplementation(method) : NULL;
}

bool PHObjcMessageClassAddMethod(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block) {
    bool existsSelf;
    IMP imp = PHObjcMessageClassGetImplementation(cls, name, &existsSelf);
    if (imp == NULL && existsSelf == false) {
        return class_addMethod(cls, name, imp_implementationWithBlock(block), types);
    } else {
        return false;
    }
}

IMP _Nullable PHObjcMessageClassReplaceMethod(Class _Nullable cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block) {
    bool existsSelf;
    IMP imp = PHObjcMessageClassGetImplementation(cls, name, &existsSelf);
    if (imp != NULL && existsSelf == true) {
        return class_replaceMethod(cls, name, imp_implementationWithBlock(block), types);
    } else {
        return NULL;
    }
}

IMP _Nullable PHObjcMessageClassOverrideMethod(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block) {
    bool existsSelf;
    IMP imp = PHObjcMessageClassGetImplementation(cls, name, &existsSelf);
    if (imp != NULL && existsSelf == false) {
        bool success = class_addMethod(cls, name, imp_implementationWithBlock(block), types);
        return success ? imp : NULL;
    } else {
        return NULL;
    }
}
