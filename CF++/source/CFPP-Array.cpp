/*******************************************************************************
 * Copyright (c) 2014, Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        CFPP-Array.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFArrayRef wrapper
 */

#include <CF++.hpp>

static bool __hasCallBacks = false;

static CFArrayCallBacks __callbacks;

#ifdef _WIN32

static const void *	__CFArrayRetainCallBack( CFAllocatorRef allocator, const void * value );
static const void *	__CFArrayRetainCallBack( CFAllocatorRef allocator, const void * value )
{
    ( void )allocator;
    
    if( value != NULL )
    {
        value = CFRetain( value );
    }
    
    return value;
}

static void __CFArrayReleaseCallBack( CFAllocatorRef allocator, const void * value );
static void __CFArrayReleaseCallBack( CFAllocatorRef allocator, const void * value )
{
    ( void )allocator;
    
    if( value != NULL )
    {
        CFRelease( value );
    }
}

static CFStringRef __CFArrayCopyDescriptionCallBack( const void * value );
static CFStringRef __CFArrayCopyDescriptionCallBack( const void * value )
{
    if( value == NULL )
    {
        return CFStringCreateWithCString( ( CFAllocatorRef )NULL, "(null)", kCFStringEncodingUTF8 );
    }
    
    return CFCopyDescription( value );
}

static Boolean __CFArrayEqualCallBack( const void * value1, const void * value2 );
static Boolean __CFArrayEqualCallBack( const void * value1, const void * value2 )
{
    if( value1 == value2 )
    {
        return true;
    }
    
    if( value1 == NULL || value2 == NULL )
    {
        return false;
    }
    
    return CFEqual( value1, value2 );
}

static void __createCallbacks( void )
{
    if( __hasCallBacks == true  )
    {
        return;
    }
    
    __hasCallBacks = true;
    
    __callbacks.version         = 0;
    __callbacks.retain          = __CFArrayRetainCallBack;
    __callbacks.release         = __CFArrayReleaseCallBack;
    __callbacks.copyDescription = __CFArrayCopyDescriptionCallBack;
    __callbacks.equal           = __CFArrayEqualCallBack;
}

#else

static void __createCallbacks( void )
{
    if( __hasCallBacks == true  )
    {
        return;
    }
    
    __hasCallBacks = true;
    __callbacks    = kCFTypeArrayCallBacks;
}

#endif

namespace CF
{
    Array::Array( void ): _cfObject( NULL )
    {
        __createCallbacks();
        
        this->_cfObject = CFArrayCreateMutable
        (
            static_cast< CFAllocatorRef >( NULL ),
            0,
            &__callbacks
        );
    }
    
    Array::Array( const Array & value ): _cfObject( NULL )
    {
        __createCallbacks();
        
        if( value._cfObject != NULL )
        {
            this->_cfObject = CFArrayCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( NULL ),
                CFArrayGetCount( value._cfObject ),
                value._cfObject
            );
        }
    }
    
    Array::Array( const AutoPointer & value ): _cfObject( NULL )
    {
        __createCallbacks();
        
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = CFArrayCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( NULL ),
                CFArrayGetCount( value ),
                value
            );
        }
    }
    
    Array::Array( CFTypeRef value ): _cfObject( NULL )
    {
        __createCallbacks();
        
        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = CFArrayCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( NULL ),
                CFArrayGetCount( static_cast< CFArrayRef >( value ) ),
                static_cast< CFArrayRef >( value )
            );
        }
    }
    
    Array::Array( CFArrayRef value ): _cfObject( NULL )
    {
        __createCallbacks();
        
        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = CFArrayCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( NULL ),
                CFArrayGetCount( value ),
                value
            );
        }
    }
    
    #ifdef CFPP_HAS_CPP11
    Array::Array( Array && value )
    {
        this->_cfObject = value._cfObject;
        value._cfObject = NULL;
    }
    #endif
    
    Array::~Array( void )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = NULL;
        }
    }
    
    Array & Array::operator = ( Array value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Array & Array::operator = ( const AutoPointer & value )
    {
        return operator =( value.GetCFObject() );
    }
    
    Array & Array::operator = ( CFTypeRef value )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
        }
        
        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = CFArrayCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( NULL ),
                CFArrayGetCount( static_cast< CFArrayRef >( value ) ),
                static_cast< CFArrayRef >( value )
            );
        }
        else
        {
            this->_cfObject = NULL;
        }
        
        return *( this );
    }
    
    Array & Array::operator = ( CFArrayRef value )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
        }
        
        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = CFArrayCreateMutableCopy
            (
                static_cast< CFAllocatorRef >( NULL ),
                CFArrayGetCount( value ),
                value
            );
        }
        else
        {
            this->_cfObject = NULL;
        }
        
        return *( this );
    }
    
    Array & Array::operator += ( const Array & value )
    {
        this->AppendArray( value._cfObject );
        
        return *( this );
    }
    
    Array & Array::operator += ( CFTypeRef value )
    {
        this->AppendArray( static_cast< CFArrayRef >( value ) );
        
        return *( this );
    }
    
    Array & Array::operator += ( CFArrayRef value )
    {
        this->AppendArray( value );
        
        return *( this );
    }
    
    Array & Array::operator << ( CFTypeRef value )
    {
        this->AppendValue( value );
        
        return *( this );
    }
    
    Array & Array::operator << ( const char * value )
    {
        String s;
        
        s = value;
        
        this->AppendValue( s );
        
        return *( this );
    }
    
    Array & Array::operator << ( String value )
    {
        this->AppendValue( value );
        
        return *( this );
    }
    
    Array & Array::operator << ( Number value )
    {
        this->AppendValue( value );
        
        return *( this );
    }
            
    CFTypeRef Array::operator [] ( int index ) const
    {
        return this->GetValueAtIndex( static_cast< CFIndex >( index ) );
    }
    
    CFTypeID Array::GetTypeID( void ) const
    {
        return CFArrayGetTypeID();
    }
    
    CFTypeRef Array::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    CFIndex Array::GetCount( void ) const
    {
        return ( this->_cfObject == NULL ) ? 0 : CFArrayGetCount( this->_cfObject );
    }
    
    bool Array::ContainsValue( CFTypeRef value ) const
    {
        if( this->_cfObject == NULL || value == NULL )
        {
            return false;
        }
        
        return ( CFArrayContainsValue
        (
            this->_cfObject,
            CFRangeMake( 0, this->GetCount() ),
            value
        ) ) ? true : false;
    }
    
    void Array::RemoveAllValues( void ) const
    {
        if( this->_cfObject != NULL )
        {
            CFArrayRemoveAllValues( this->_cfObject );
        }
    }
    
    CFTypeRef Array::GetValueAtIndex( CFIndex index ) const
    {
        if( this->_cfObject == NULL || index >= this->GetCount() )
        {
            return NULL;
        }
        
        return CFArrayGetValueAtIndex( this->_cfObject, index );
    }
    
    void Array::SetValueAtIndex( CFTypeRef value, CFIndex index ) const
    {
        if( this->_cfObject == NULL || index >= this->GetCount() || value == NULL )
        {
            return;
        }
        
        CFArraySetValueAtIndex( this->_cfObject, index, value );
    }
    
    void Array::InsertValueAtIndex( CFTypeRef value, CFIndex index ) const
    {
        if( this->_cfObject == NULL || index >= this->GetCount() || value == NULL )
        {
            return;
        }
        
        CFArrayInsertValueAtIndex( this->_cfObject, index, value );
    }
    
    void Array::AppendValue( CFTypeRef value ) const
    {
        if( this->_cfObject == NULL || value == NULL )
        {
            return;
        }
        
        CFArrayAppendValue( this->_cfObject, value );
    }
    
    void Array::RemoveValueAtIndex( CFIndex index ) const
    {
        if( this->_cfObject == NULL || index >= this->GetCount() )
        {
            return;
        }
        
        CFArrayRemoveValueAtIndex( this->_cfObject, index );
    }
    
    void Array::AppendArray( CFArrayRef array ) const
    {
        if( array == NULL || CFGetTypeID( array ) != this->GetTypeID() )
        {
            return;
        }
        
        if( this->_cfObject != NULL )
        {
            CFArrayAppendArray
            (
                this->_cfObject,
                array,
                CFRangeMake( 0, CFArrayGetCount( array ) )
            );
        }
    }
    
    void Array::ExchangeValuesAtIndices( CFIndex index1, CFIndex index2 ) const
    {
        if( this->_cfObject == NULL || index1 >= this->GetCount() || index2 >= this->GetCount() )
        {
            return;
        }
        
        CFArrayExchangeValuesAtIndices( this->_cfObject, index1, index2 );
    }
    
    Array::Iterator Array::begin( void ) const
    {
        return Iterator( this->_cfObject, this->GetCount() );
    }
    
    Array::Iterator Array::end( void ) const
    {
        return Iterator( this->_cfObject, this->GetCount(), this->GetCount() );
    }
        
    void swap( Array & v1, Array & v2 )
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
