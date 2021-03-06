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
 * @header      CFNumber.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION___PRIVATE_CF_NUMBER_H
#define CORE_FOUNDATION___PRIVATE_CF_NUMBER_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/__CFRuntime.h>

CF_EXTERN_C_BEGIN

struct CFNumber
{
    CFRuntimeBase _base;
    CFNumberType  _type;
    
    union
    {
        SInt8       int8;
        SInt16      int16;
        SInt32      int32;
        SInt64      int64;
        Float32     float32;
        Float64     float64;
        char        c;
        short       s;
        int         i;
        long        l;
        long long   ll;
        float       f;
        double      d;
        CFIndex     x;
    }
    _value;
};

CF_EXPORT void CFNumberInitialize( void );

CF_EXPORT CFTypeID       CFNumberTypeID;
CF_EXPORT CFRuntimeClass CFNumberClass;

CF_EXPORT struct CFNumber CFNumberNaN;
CF_EXPORT struct CFNumber CFNumberNegativeInfinity;
CF_EXPORT struct CFNumber CFNumberPositiveInfinity;

CF_EXPORT CFHashCode  CFNumberHash( CFNumberRef n );
CF_EXPORT bool        CFNumberEquals( CFNumberRef n1, CFNumberRef n2 );
CF_EXPORT CFStringRef CFNumberCopyDescription( CFNumberRef n );
CF_EXPORT SInt64      CFNumberGetSInt64Value( CFNumberRef n );
CF_EXPORT Float64     CFNumberGetFloat64Value( CFNumberRef n );
CF_EXPORT bool        CFNumberIsPositiveInfinity( CFNumberRef n );
CF_EXPORT bool        CFNumberIsNegativeInfinity( CFNumberRef n );
CF_EXPORT bool        CFNumberIsNAN( CFNumberRef n );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION___PRIVATE_CF_NUMBER_H */
