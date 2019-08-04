/**
 * ObjectToXPC
 *
 * Copyright 2011 Aron Cedercrantz. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 * 
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY ARON CEDERCRANTZ ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ARON CEDERCRANTZ OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Aron Cedercrantz.
 */
#import "NSArray+CDXPC.h"

#import "NSData+CDXPC.h"
#import "NSDate+CDXPC.h"
#import "NSDictionary+CDXPC.h"
#import "NSNumber+CDXPC.h"
#import "NSString+CDXPC.h"

#import "ObjectToXPC-Private.h"

//CD_FIX_CATEGORY_BUG(NSArray_CDXPC);
@implementation NSArray (CDXPC)

+ (id)arrayWithXPCObject:(xpc_object_t)xpcObject
{
	return [[[self class] alloc] initWithXPCObject:xpcObject];
}

- (id)initWithXPCObject:(xpc_object_t)xpcObject
{
	NSAssert(xpc_get_type(xpcObject) == XPC_TYPE_ARRAY, @"xpcObject must be of type XPC_TYPE_ARRAY.");
	
	NSUInteger capacity = xpc_array_get_count(xpcObject);
	NSMutableArray *newSelf = [[NSMutableArray alloc] initWithCapacity:capacity];
	
	if (newSelf) {
		xpc_array_apply(xpcObject, ^_Bool(size_t index, xpc_object_t value) {
			xpc_type_t valueType = xpc_get_type(value);
			
			if (valueType == XPC_TYPE_ARRAY) {
				NSArray *array = [[NSArray alloc] initWithXPCObject:value];
				[newSelf addObject:array];
			}
			else if (valueType == XPC_TYPE_BOOL ||
					 valueType == XPC_TYPE_DOUBLE ||
					 valueType == XPC_TYPE_INT64 ||
					 valueType == XPC_TYPE_UINT64) {
				NSNumber *boolNumber = [[NSNumber alloc] initWithXPCObject:value];
				[newSelf addObject:boolNumber];
			}
			else if (valueType == XPC_TYPE_DATA) {
				NSData *data = [[NSData alloc] initWithXPCObject:value];
				[newSelf addObject:data];
			}
			else if (valueType == XPC_TYPE_DATE) {
				NSDate *date = [[NSDate alloc] initWithXPCObject:value];
				[newSelf addObject:date];
			}
			else if (valueType == XPC_TYPE_DICTIONARY) {
				NSDictionary *dictionary = [[NSDictionary alloc] initWithXPCObject:value];
				[newSelf addObject:dictionary];
			}
			else if (valueType == XPC_TYPE_NULL) {
				[newSelf addObject:[NSNull null]];
			}
			else if (valueType == XPC_TYPE_STRING) {
				NSString *string = [[NSString alloc] initWithXPCObject:value];
				[newSelf addObject:string];
			}
			else {
				char *valueDescription = xpc_copy_description(value);
				NSString *assertionString = [[NSString alloc] initWithFormat:@"Unsupported XPC object '%s'.", valueDescription];
				free(valueDescription);
#if DEBUG
				NSAssert(NO, assertionString);
#else
				NSLog(@"%@", assertionString);
#endif
			}
			
			return true;
		});
	}
	
	self = newSelf;
	return self;
}

- (xpc_object_t)XPCObject
{
	xpc_object_t resXpcArray = xpc_array_create(NULL, 0);
	
	for (id obj in self) {
		if ([obj respondsToSelector:@selector(XPCObject)]) {
			xpc_object_t xpcObj = [obj XPCObject];
			xpc_array_append_value(resXpcArray, xpcObj);
			xpc_release(xpcObj);
		}
		else if ([obj isKindOfClass:[NSNull class]]) {
			xpc_object_t nullObject = xpc_null_create();
			xpc_array_set_value(resXpcArray, XPC_ARRAY_APPEND, nullObject);
			xpc_release(nullObject);
		}
		else {
			NSString *assertionString = [[NSString alloc] initWithFormat:@"Could not create XPC version of object '%@' of type %@.", obj, [obj class]];
#if DEBUG
			NSAssert(NO, assertionString);
#else
			NSLog(@"%@", assertionString);
#endif
		}
	}
	
	return resXpcArray;
}

@end
