/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016 Jean-David Gadina - www-xs-labs.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        CFAtomic.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/__private/__CFAtomic.h>
#include <CoreFoundation/__private/__CFRuntime.h>
#include <stdio.h>
#include <stdlib.h>

#if defined( _WIN32 )
#include <SDKDDKVer.h>
#include <Windows.h>
#elif defined( __APPLE__ )
#include <libkern/OSAtomic.h>
#endif

CFIndex CFAtomicIncrement( volatile CFIndex * value )
{
    if( sizeof( CFIndex ) == sizeof( int32_t ) )
    {
        return CFAtomicIncrement32( ( volatile int32_t * )value );
    }
    else if( sizeof( CFIndex ) == sizeof( int64_t ) )
    {
        return CFAtomicIncrement64( ( volatile int64_t * )value );
    }
    
    CFRuntimeAbortWithError( "Invalid size for CFIndex - Unknown platform" );
    
    return 0;
}

int32_t CFAtomicIncrement32( volatile int32_t * value )
{
    #if defined( _WIN32 )
    
    return InterlockedIncrement( ( volatile LONG * )value );
    
    #elif defined( __APPLE__ )
    
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    return OSAtomicIncrement32( value );
    #pragma clang diagnostic pop
    
    #elif defined( __has_builtin ) && __has_builtin( __sync_add_and_fetch )
    
    return __sync_add_and_fetch( value, 1 );
    
    #else
    
    #error "CFAtomicIncrement32 is not implemented for the current platform"
    
    #endif
}

int64_t CFAtomicIncrement64( volatile int64_t * value )
{
    #if defined( _WIN32 )
    
    return InterlockedIncrement64( ( volatile LONGLONG * )value );
    
    #elif defined( __APPLE__ )
    
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    return OSAtomicIncrement64( value );
    #pragma clang diagnostic pop
    
    #elif defined( __has_builtin ) && __has_builtin( __sync_add_and_fetch )
    
    return __sync_add_and_fetch( value, 1 );
    
    #else
    
    #error "CFAtomicIncrement64 is not implemented for the current platform"
    
    #endif
}

CFIndex CFAtomicDecrement( volatile CFIndex * value )
{
    if( sizeof( CFIndex ) == sizeof( int32_t ) )
    {
        return CFAtomicDecrement32( ( volatile int32_t * )value );
    }
    else if( sizeof( CFIndex ) == sizeof( int64_t ) )
    {
        return CFAtomicDecrement64( ( volatile int64_t * )value );
    }
    
    CFRuntimeAbortWithError( "Invalid size for CFIndex - Unknown platform" );
    
    return 0;
}

int32_t CFAtomicDecrement32( volatile int32_t * value )
{
    #if defined( _WIN32 )
    
    return InterlockedDecrement( ( volatile LONG * )value );
    
    #elif defined( __APPLE__ )
    
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    return OSAtomicDecrement32( value );
    #pragma clang diagnostic pop
    
    #elif defined( __has_builtin ) && __has_builtin( __sync_add_and_fetch )
    
    return __sync_add_and_fetch( value, -1 );
    
    #else
    
    #error "CFAtomicDecrement32 is not implemented for the current platform"
    
    #endif
}

int64_t CFAtomicDecrement64( volatile int64_t * value )
{
    #if defined( _WIN32 )
    
    return InterlockedDecrement64( ( volatile LONGLONG * )value );
    
    #elif defined( __APPLE__ )
    
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    return OSAtomicDecrement64( value );
    #pragma clang diagnostic pop
    
    #elif defined( __has_builtin ) && __has_builtin( __sync_add_and_fetch )
    
    return __sync_add_and_fetch( value, -1 );
    
    #else
    
    #error "CFAtomicDecrement64 is not implemented for the current platform"
    
    #endif
}

bool CFAtomicCompareAndSwap( CFIndex oldValue, CFIndex newValue, volatile CFIndex * value )
{
    if( sizeof( CFIndex ) == sizeof( int32_t ) )
    {
        return CFAtomicCompareAndSwap32( ( int32_t )oldValue, ( int32_t )newValue, ( volatile int32_t * )value );
    }
    else if( sizeof( CFIndex ) == sizeof( int64_t ) )
    {
        return CFAtomicCompareAndSwap64( ( int64_t )oldValue, ( int64_t )newValue, ( volatile int64_t * )value );
    }
    
    fprintf( stderr, "Invalid size for CFIndex - Unknown platform\n" );
    abort();
    
    return 0;
}

bool CFAtomicCompareAndSwap32( int32_t oldValue, int32_t newValue, volatile int32_t * value )
{
    #if defined( _WIN32 )
    
    return ( InterlockedCompareExchange( ( volatile LONG * )value, newValue, oldValue ) == oldValue ) ? true : false;
    
    #elif defined( __APPLE__ )
    
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    return ( OSAtomicCompareAndSwap32( oldValue, newValue, value ) ) ? true : false;
    #pragma clang diagnostic pop
    
    #elif defined( __has_builtin ) && __has_builtin( __sync_bool_compare_and_swap )
    
    return __sync_bool_compare_and_swap( value, oldValue, newValue );
    
    #else
    
    #error "CFAtomicCompareAndSwap32 is not implemented for the current platform"
    
    #endif
}

bool CFAtomicCompareAndSwap64( int64_t oldValue, int64_t newValue, volatile int64_t * value )
{
    #if defined( _WIN32 )
    
    return ( InterlockedCompareExchange64( ( volatile LONGLONG * )value, newValue, oldValue ) == oldValue ) ? true : false;
    
    #elif defined( __APPLE__ )
    
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    return ( OSAtomicCompareAndSwap64( oldValue, newValue, value ) ) ? true : false;
    #pragma clang diagnostic pop
    
    #elif defined( __has_builtin ) && __has_builtin( __sync_bool_compare_and_swap )
    
    return __sync_bool_compare_and_swap( value, oldValue, newValue );
    
    #else
    
    #error "CFAtomicCompareAndSwap64 is not implemented for the current platform"
    
    #endif
}

bool CFAtomicCompareAndSwapPointer( void * oldValue, void * newValue, void * volatile * value )
{
    #if defined( _WIN32 )
    
    return ( InterlockedCompareExchangePointer( value, newValue, oldValue ) == oldValue ) ? true : false;
    
    #elif defined( __APPLE__ )
    
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    return ( OSAtomicCompareAndSwapPtr( oldValue, newValue, value ) ) ? true : false;
    #pragma clang diagnostic pop
    
    #elif defined( __has_builtin ) && __has_builtin( __sync_bool_compare_and_swap )
    
    return __sync_bool_compare_and_swap( value, oldValue, newValue );
    
    #else
    
    #error "CFAtomicCompareAndSwapPointer is not implemented for the current platform"
    
    #endif
}
