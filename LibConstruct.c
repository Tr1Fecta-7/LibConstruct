//
//  LibConstruct.c
//  Construct
//
//  Created by Tr1Fecta on 31/03/2020.
//  Copyright © 2020 Tr1Fecta. All rights reserved.
//

#include "LibConstruct.h"
#include <objc/runtime.h>
#include <objc/message.h>

void LCHookMessage(Class class, SEL methodSEL, IMP *origIMP, IMP newIMP) {
	Class origClass = NULL;
	Method origMethod = NULL;
	
	if (class_respondsToSelector(class, methodSEL)) {
		// Get class for Instance Methods
		origClass = objc_getClass(class_getName(class));
		origMethod = class_getInstanceMethod(class, methodSEL);
	}
	else {
		// Get MetaClass for Class Methods
		origClass = objc_getMetaClass(class_getName(class));
		origMethod = class_getClassMethod(origClass, methodSEL);
	}
	
	*origIMP = class_replaceMethod(origClass, methodSEL, newIMP, method_getTypeEncoding(origMethod));
}

void LCHookIvar(id classInstance, const char *name, id value) {
	Ivar ivar = class_getInstanceVariable(object_getClass(classInstance), name);
	if (ivar != NULL) { // Check if the ivar exists
		object_setIvar(classInstance, ivar, value);
	}
}

id LCGetIvar(id classInstance, const char *name) {
	Ivar ivar = class_getInstanceVariable(object_getClass(classInstance), name);
	if (ivar != NULL) {
		return object_getIvar(classInstance, ivar); // Return ivar value
	}
	return NULL;
}

Method LCGetMethodType(Class class, SEL methodSEL) {
	Class origClass = NULL;
	Method origMethod = NULL;
	
	if (class_respondsToSelector(class, methodSEL)) {
		// Get class for Instance Methods and get instance method
		origClass = objc_getClass(class_getName(class));
		origMethod = class_getInstanceMethod(class, methodSEL);
	}
	else {
		// Get MetaClass for Class Methods and get class method
		origClass = objc_getMetaClass(class_getName(class));
		origMethod = class_getClassMethod(origClass, methodSEL);
	}
	
	return origMethod;
}

IMP LCGetImplementation(Class class, SEL methodSEL) {
	Method method = LCGetMethodType(class, methodSEL);
	return method_getImplementation(method);
}
