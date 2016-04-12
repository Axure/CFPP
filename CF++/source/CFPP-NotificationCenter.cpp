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
 * @file        CFPP-NotificationCenter.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFNotificationCenterRef wrapper
 */

#include <CF++.hpp>

namespace CF
{
    NotificationCenter NotificationCenter::GetDarwinNotifyCenter( void )
    {
        return CFNotificationCenterGetDarwinNotifyCenter();
    }
    
    NotificationCenter NotificationCenter::GetDistributedCenter( void )
    {
        return CFNotificationCenterGetDistributedCenter();
    }
    
    NotificationCenter NotificationCenter::GetLocalCenter( void )
    {
        return CFNotificationCenterGetLocalCenter();
    }
    
    NotificationCenter::NotificationCenter( void ): _cfObject( NULL )
    {}
    
    NotificationCenter::NotificationCenter( const NotificationCenter & value ): _cfObject( NULL )
    {
        if( value._cfObject != NULL )
        {
            this->_cfObject = reinterpret_cast< CFNotificationCenterRef >( const_cast< void * >( CFRetain( value._cfObject ) ) );
        }
    }
    
    NotificationCenter::NotificationCenter( const AutoPointer & value ): _cfObject( NULL )
    {
        if( value.IsValid() && value.GetTypeID() == this->GetTypeID() )
        {
            this->_cfObject = static_cast< CFNotificationCenterRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    NotificationCenter::NotificationCenter( CFTypeRef value ): _cfObject( NULL )
    {
        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = reinterpret_cast< CFNotificationCenterRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    NotificationCenter::NotificationCenter( CFNotificationCenterRef value ): _cfObject( NULL )
    {
        if( value != NULL && CFGetTypeID( value ) == this->GetTypeID() )
        {
            this->_cfObject = reinterpret_cast< CFNotificationCenterRef >( const_cast< void * >( CFRetain( value ) ) );
        }
    }
    
    #ifdef CFPP_HAS_CPP11
    NotificationCenter::NotificationCenter( NotificationCenter && value )
    {
        this->_cfObject = value._cfObject;
        value._cfObject = nullptr;
    }
    #endif
    
    NotificationCenter::~NotificationCenter( void )
    {
        if( this->_cfObject != NULL )
        {
            CFRelease( this->_cfObject );
            
            this->_cfObject = NULL;
        }
    }
    
    NotificationCenter & NotificationCenter::operator = ( NotificationCenter value )
    {
        swap( *( this ), value );
        
        return *( this );
    }
    
    NotificationCenter & NotificationCenter::operator = ( const AutoPointer & value )
    {
        return operator =( NotificationCenter( value ) );
    }
    
    NotificationCenter & NotificationCenter::operator = ( CFTypeRef value )
    {
        return operator =( NotificationCenter( value ) );
    }
    
    NotificationCenter & NotificationCenter::operator = ( CFNotificationCenterRef value )
    {
        return operator =( NotificationCenter( value ) );
    }
    
    CFTypeID NotificationCenter::GetTypeID( void ) const
    {
        return CFNotificationCenterGetTypeID();
    }
    
    CFTypeRef NotificationCenter::GetCFObject( void ) const
    {
        return this->_cfObject;
    }
    
    void NotificationCenter::PostNotification( const String & name, const void * object, const Dictionary & userInfo, bool deliverImmediately ) const
    {
        if( this->_cfObject == NULL )
        {
            return;
        }
        
        CFNotificationCenterPostNotification( this->_cfObject, name, object, userInfo, deliverImmediately );
    }
    
    void NotificationCenter::PostNotificationWithOptions( const String & name, const void * object, const Dictionary & userInfo, CFOptionFlags options ) const
    {
        if( this->_cfObject == NULL )
        {
            return;
        }
        
        CFNotificationCenterPostNotificationWithOptions( this->_cfObject, name, object, userInfo, options );
    }
    
    void NotificationCenter::AddObserver( const void * observer, CFNotificationCallback callback, const String & name, const void * object, CFNotificationSuspensionBehavior suspensionBehavior )
    {
        if( this->_cfObject == NULL )
        {
            return;
        }
        
        CFNotificationCenterAddObserver( this->_cfObject, observer, callback, name, object, suspensionBehavior );
    }
    
    void NotificationCenter::RemoveEveryObserver( const void * observer )
    {
        if( this->_cfObject == NULL )
        {
            return;
        }
        
        CFNotificationCenterRemoveEveryObserver( this->_cfObject, observer );
    }
    
    void NotificationCenter::RemoveObserver( const void * observer, const String & name, const void * object )
    {
        if( this->_cfObject == NULL )
        {
            return;
        }
        
        CFNotificationCenterRemoveObserver( this->_cfObject, observer, name, object );
    }
    
    void swap( NotificationCenter & v1, NotificationCenter & v2 )
    {
        using std::swap;
        
        swap( v1._cfObject, v2._cfObject );
    }
}
