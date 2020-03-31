//
//  LibConstruct.h
//  Construct
//
//  Created by Tr1Fecta on 31/03/2020.
//  Copyright © 2020 Tr1Fecta. All rights reserved.
//

#include <stdio.h>
#include <objc/runtime.h>
#include <objc/message.h>


void LCHookMessage(Class class, SEL methodSEL, IMP *origIMP, IMP newIMP);
void LCHookIvar(id classInstance, const char *name, id value);
id LCGetIvar(id classInstance, const char *name);
Method LCGetMethodType(Class class, SEL methodSEL);
IMP LCGetImplementation(Class class, SEL methodSEL);
