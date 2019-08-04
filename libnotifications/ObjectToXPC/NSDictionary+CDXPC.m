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

#import "NSDictionary+CDXPC.h"

#import "NSArray+CDXPC.h"
#import "NSData+CDXPC.h"
#import "NSDate+CDXPC.h"
#import "NSNumber+CDXPC.h"
#import "NSString+CDXPC.h"

#import "ObjectToXPC-Private.h"

//CD_FIX_CATEGORY_BUG(NSDictionary_CDXPC)
@implementation NSDictionary (CDXPC)

+ (id)dictionaryWithXPCObject:(xpc_object_t)xpcObject
{
	return [[[self class] alloc] initWithXPCObject:xpcObject];
}

- (id)initWithXPCObject:(xpc_object_t)xpcObject
{
	NSAssert(xpc_get_type(xpcObject) == XPC_TYPE_DICTIONARY, @"xpcObject must be of type XPC_TYPE_DICTIONARY");
	
	NSUInteger capacity = xpc_dictionary_get_count(xpcObject);
	NSMutableDictionary *newSelf = [[NSMutableDictionary alloc] initWithCapacity:capacity];
	
	if (newSelf) {
		xpc_dictionary_apply(xpcObject, ^_Bool(const char *keyStr, xpc_object_t value) {
			NSString *key = [[NSString alloc] initWithUTF8String:keyStr];
			xpc_type_t valueType = xpc_get_type(value);
			id object = nil;
			
			if (valueType == XPC_TYPE_ARRAY) {
				object = [[NSArray alloc] initWithXPCObject:value];
				
			}
			else if (valueType == XPC_TYPE_BOOL ||
					 valueType == XPC_TYPE_DOUBLE ||
					 valueType == XPC_TYPE_INT64 ||
					 valueType == XPC_TYPE_UINT64) {
				object = [[NSNumber alloc] initWithXPCObject:value];
			}
			else if (valueType == XPC_TYPE_DATA) {
				object = [[NSData alloc] initWithXPCObject:value];
			}
			else if (valueType == XPC_TYPE_DATE) {
				object = [[NSDate alloc] initWithXPCObject:value];
			}
			else if (valueType == XPC_TYPE_DICTIONARY) {
				object = [[NSDictionary alloc] initWithXPCObject:value];
			}
			else if (valueType == XPC_TYPE_NULL) {
				object = [NSNull null];
			}
			else if (valueType == XPC_TYPE_STRING) {
				object = [[NSString alloc] initWithXPCObject:value];
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
			
			if (object == nil) {
				object = [NSNull null];
			}
			[newSelf setValue:object forKey:key];
			
			return true;
		});
	}
	
	self = newSelf;
	return self;
}

- (xpc_object_t)XPCObject
{
	xpc_object_t resXpcDictionary = xpc_dictionary_create(NULL, NULL, 0);
	
	[self enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
		xpc_object_t xpcObj = NULL;
		
		if ([obj respondsToSelector:@selector(XPCObject)]) {
			xpcObj = [obj XPCObject];
		}
		else if ([obj isKindOfClass:[NSNull class]]) {
			xpcObj = xpc_null_create();
		}
		else {
			NSString *assertionString = [[NSString alloc] initWithFormat:@"Could not create XPC version of object '%@' of type %@.", obj, [obj class]];
#if DEBUG
			NSAssert(NO, assertionString);
#else
			NSLog(@"%@", assertionString);
#endif
		}
		
		if (xpcObj != NULL) {
			// Make sure the key is a string!
			if (![key isKindOfClass:[NSString class]]) {
				key = [key description];
			}
			const char *xpcKey = [key UTF8String];
			
			xpc_dictionary_set_value(resXpcDictionary, xpcKey, xpcObj);
			
			xpc_release(xpcObj);
		}
	}];
	
	return resXpcDictionary;
}

@end
