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
 * @file        CFPP-Pair.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ pair of CFTypeRef
 */


#include <CF++.hpp>

namespace CF
{    
    Pair::Pair( CFTypeRef key, CFTypeRef value ): _key( NULL ), _value( NULL )
    {
        this->SetKey( key );
        this->SetValue( value );
    }
    
    Pair::Pair( const Pair & value ): _key( NULL ), _value( NULL )
    {
        this->SetKey( value._key );
        this->SetValue( value._value );
    }
    
    Pair::Pair( const char * key, CFTypeRef value ): _key( NULL ), _value( NULL )
    {
        String s;
        
        s = key;
        
        this->SetKey( s );
        this->SetValue( value );
    }
    
    Pair::Pair( String key, CFTypeRef value ): _key( NULL ), _value( NULL )
    {
        this->SetKey( key );
        this->SetValue( value );
    }
    
    Pair::Pair( String key, String value ): _key( NULL ), _value( NULL )
    {
        this->SetKey( key );
        this->SetValue( value );
    }
    
    Pair::Pair( const char * key, String value ): _key( NULL ), _value( NULL )
    {
        String s;
        
        s = key;
        
        this->SetKey( s );
        this->SetValue( value );
    }
    
    Pair::Pair( String key, const char * value ): _key( NULL ), _value( NULL )
    {
        String s;
        
        s = value;
        
        this->SetKey( key );
        this->SetValue( s );
    }
    
    Pair::Pair( const char * key, const char * value ): _key( NULL ), _value( NULL )
    {
        String s1;
        String s2;
        
        s1 = key;
        s2 = value;
        
        this->SetKey( s1 );
        this->SetValue( s2 );
    }
    
    Pair::Pair( String key, Number value ): _key( NULL ), _value( NULL )
    {
        this->SetKey( key );
        this->SetValue( value );
    }
    
    Pair::Pair( const char * key, Number value ): _key( NULL ), _value( NULL )
    {
        String s;
        
        s = key;
        
        this->SetKey( s );
        this->SetValue( value );
    }
    
    #ifdef CFPP_HAS_CPP11
    Pair::Pair( Pair && value )
    {
        this->_key   = value._key;
        value._key   = NULL;
        this->_value = value._value;
        value._value = NULL;
    }
    #endif
    
    Pair::~Pair( void )
    {
        if( this->_key != NULL )
        {
            CFRelease( this->_key );
        }
        
        if( this->_value != NULL )
        {
            CFRelease( this->_value );
        }
    }
    
    Pair & Pair::operator = ( Pair value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    CFTypeRef Pair::GetKey( void ) const
    {
        return this->_key;
    }
    
    CFTypeRef Pair::GetValue( void ) const
    {
        return this->_value;
    }
            
    void Pair::SetKey( CFTypeRef key )
    {
        if( this->_key != NULL )
        {
            CFRelease( this->_key );
        }
        
        if( key != NULL )
        {
            this->_key = CFRetain( key );
        }
        else
        {
            this->_key = NULL;
        }
    }
    
    void Pair::SetValue( CFTypeRef value )
    {
        if( this->_value != NULL )
        {
            CFRelease( this->_value );
        }
        
        if( value != NULL )
        {
            this->_value = CFRetain( value );
        }
        else
        {
            this->_value = NULL;
        }
    }
    
    void swap( Pair & v1, Pair & v2 )
    {
        using std::swap;
        
        swap( v1._key, v2._key );
        swap( v1._value, v2._value );
    }
}
