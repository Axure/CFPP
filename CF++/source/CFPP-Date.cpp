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
 * @file        CFPP-Date.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFDateRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    Date Date::CurrentDate( void )
    {
        Date date;
        
        return date;
    }
    
    Date::Date( void ): _cfObject( NULL )
    {
        this->SetValue( CFAbsoluteTimeGetCurrent() );
    }
    
    Date::Date( const Date & value ): _cfObject( NULL )
    {
        if( value._cfObject != NULL )
        {
            this->_cfObject = static_cast< CFDateRef >( CFRetain( value._cfObject ) );
        }
    }
    
    Date::Date( const AutoPointer & value ): _cfObject( NULL )
    {
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFDateRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    Date::Date( CFTypeRef value ): _cfObject( NULL )
    {
        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFDateRef >( CFRetain( value ) );
        }
    }
    
    Date::Date( CFDateRef value ): _cfObject( NULL )
    {
        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFDateRef >( CFRetain( value ) );
        }
    }
    
    Date::Date( CFAbsoluteTime value ): _cfObject( NULL )
    {
        this->SetValue( value );
    }
    
    #ifdef CFPP_HAS_CPP11
    Date::Date( Date && value )
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    #endif
    
    Date::~Date( void )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = NULL;
        }
    }
    
    Date & Date::operator = ( Date value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    Date & Date::operator = ( const AutoPointer & value )
    {
        return operator =( Date( value ) );
    }
    
    Date & Date::operator = ( CFTypeRef value )
    {
        return operator =( Date( value ) );
    }
    
    Date & Date::operator = ( CFDateRef value )
    {
        return operator =( Date( value ) );
    }
    
    Date & Date::operator = ( CFAbsoluteTime value )
    {
        return operator =( Date( value ) );
    }
    
    bool Date::operator == ( const Date & value ) const
    {
        if( this->_cfObject == NULL || value._cfObject == NULL )
        {
            return false;
        }
        
        return CFDateCompare( this->_cfObject, value._cfObject, NULL ) == kCFCompareEqualTo;
    }
    
    bool Date::operator == ( CFTypeRef value ) const
    {
        return operator ==( Date( value ) );
    }
    
    bool Date::operator == ( CFDateRef value ) const
    {
        return operator ==( Date( value ) );
    }
    
    bool Date::operator == ( CFAbsoluteTime value ) const
    {
        return operator ==( Date( value ) );
    }
    
    bool Date::operator != ( const Date & value ) const
    {
        return !operator ==( value );
    }
    
    bool Date::operator != ( CFTypeRef value ) const
    {
        return !operator ==( value );
    }
    
    bool Date::operator != ( CFDateRef value ) const
    {
        return !operator ==( value );
    }
    
    bool Date::operator != ( CFAbsoluteTime value ) const
    {
        return !operator ==( value );
    }
    
    bool Date::operator >= ( const Date & value ) const
    {
        CFComparisonResult r;
        
        if( this->_cfObject == NULL || value._cfObject == NULL )
        {
            return false;
        }
        
        r = CFDateCompare( this->_cfObject, value._cfObject, NULL );
        
        return r == kCFCompareGreaterThan || r == kCFCompareEqualTo;
    }
    
    bool Date::operator >= ( CFDateRef value ) const
    {
        return operator >=( Date( value ) );
    }
    
    bool Date::operator >= ( CFAbsoluteTime value ) const
    {
        return operator >=( Date( value ) );
    }
    
    bool Date::operator <= ( const Date & value ) const
    {
        CFComparisonResult r;
        
        if( this->_cfObject == NULL || value._cfObject == NULL )
        {
            return false;
        }
        
        r = CFDateCompare( this->_cfObject, value._cfObject, NULL );
        
        return r == kCFCompareLessThan || r == kCFCompareEqualTo;
    }
    
    bool Date::operator <= ( CFDateRef value ) const
    {
        return operator <=( Date( value ) );
    }
    
    bool Date::operator <= ( CFAbsoluteTime value ) const
    {
        return operator <=( Date( value ) );
    }
    
    bool Date::operator > ( const Date & value ) const
    {
        if( this->_cfObject == NULL || value._cfObject == NULL )
        {
            return false;
        }
        
        return CFDateCompare( this->_cfObject, value._cfObject, NULL ) == kCFCompareGreaterThan;
    }
    
    bool Date::operator > ( CFDateRef value ) const
    {
        return operator >( Date( value ) );
    }
    
    bool Date::operator > ( CFAbsoluteTime value ) const
    {
        return operator >( Date( value ) );
    }
    
    bool Date::operator < ( const Date & value ) const
    {
        if( this->_cfObject == NULL || value._cfObject == NULL )
        {
            return false;
        }
        
        return CFDateCompare( this->_cfObject, value._cfObject, NULL ) == kCFCompareLessThan;
    }
    
    bool Date::operator < ( CFDateRef value ) const
    {
        return operator <( Date( value ) );
    }
    
    bool Date::operator < ( CFAbsoluteTime value ) const
    {
        return operator <( Date( value ) );
    }
    
    Date & Date::operator += ( const Date & value )
    {
        this->SetValue( this->GetValue() + value.GetValue() );
        
        return *( this );
    }
    
    Date & Date::operator += ( CFDateRef value )
    {
        return operator +=( Date( value ) );
    }
    
    Date & Date::operator += ( CFAbsoluteTime value )
    {
        return operator +=( Date( value ) );
    }
    
    Date & Date::operator -= ( const Date & value )
    {
        this->SetValue( this->GetValue() - value.GetValue() );
        
        return *( this );
    }
    
    Date & Date::operator -= ( CFDateRef value )
    {
        return operator -=( Date( value ) );
    }
    
    Date & Date::operator -= ( CFAbsoluteTime value )
    {
        return operator -=( Date( value ) );
    }
    
    Date Date::operator + ( const Date & value )
    {
        return Date( *( this ) ) += value;
    }
    
    Date Date::operator + ( CFDateRef value )
    {
        return operator +( Date( value ) );
    }
    
    Date Date::operator + ( CFAbsoluteTime value )
    {
        return operator +( Date( value ) );
    }
    
    Date Date::operator - ( const Date & value )
    {
        return Date( *( this ) ) -= value;
    }
    
    Date Date::operator - ( CFDateRef value )
    {
        return operator -( Date( value ) );
    }
    
    Date Date::operator - ( CFAbsoluteTime value )
    {
        return operator -( Date( value ) );
    }
    
    Date & Date::operator ++ ( void )
    {
        this->SetValue( this->GetValue() + 1 );
        
        return *( this );
    }
    
    Date Date::operator ++ ( int )
    {
        Date n;
        
        n = *( this );
        
        operator++();
        
        return n;
    }
    
    Date & Date::operator -- ( void )
    {
        this->SetValue( this->GetValue() - 1 );
        
        return *( this );
    }
    
    Date Date::operator -- ( int )
    {
        Date n;
        
        n = *( this );
        
        operator--();
        
        return n;
    }
    
    Date::operator CFAbsoluteTime () const
    {
        return this->GetValue();
    }
    
    CFTypeID Date::GetTypeID( void ) const
    {
        return CFDateGetTypeID();
    }
    
    CFTypeRef Date::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    CFAbsoluteTime Date::GetValue( void ) const
    {
        if( this->_cfObject == NULL )
        {
            return static_cast< CFAbsoluteTime >( 0 );
        }
        
        return CFDateGetAbsoluteTime( this->_cfObject );
    }
    
    void Date::SetValue( CFAbsoluteTime value )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
        }
        
        this->_cfObject = CFDateCreate( static_cast< CFAllocatorRef >( NULL ), value );
    }
    
    void swap( Date & v1, Date & v2 )
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
