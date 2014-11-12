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
 
/* $Id$ */

/*!
 * @header      CFPP-Dictionary.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    CoreFoundation++ CFDictionaryRef wrapper
 */

#ifndef __CFPP_DICTIONARY_H__
#define __CFPP_DICTIONARY_H__

#include <CF++/CFPP-PropertyListType.h>
#include <CF++/CFPP-Pair.h>
#include <CF++/CFPP-String.h>
#include <map>

namespace CF
{
    class Dictionary: public PropertyListType< Dictionary >
    {
        public:
            
            Dictionary( void );
            Dictionary( const Dictionary & value );
            Dictionary( CFTypeRef cfObject );
            Dictionary( CFDictionaryRef cfObject );
            
            virtual ~Dictionary( void );
            
            Dictionary & operator = ( Dictionary value );
            Dictionary & operator = ( CFTypeRef value );
            Dictionary & operator = ( CFDictionaryRef value );
            
            Dictionary & operator += ( Pair pair );
            Dictionary & operator << ( Pair pair );
            
            CFTypeRef operator [] ( CFTypeRef key );
            CFTypeRef operator [] ( const char * key );
            CFTypeRef operator [] ( String key );
            
            virtual CFTypeID  GetTypeID( void ) const;
            virtual CFTypeRef GetCFObject( void ) const;
            
            bool      ContainsKey( CFTypeRef key );
            bool      ContainsValue( CFTypeRef value );
            void      RemoveAllValues( void );
            CFIndex   GetCount( void );
            CFTypeRef GetValue( CFTypeRef key );
            void      AddValue( CFTypeRef key, CFTypeRef value );
            void      RemoveValue( CFTypeRef key );
            void      ReplaceValue( CFTypeRef key, CFTypeRef value );
            void      SetValue( CFTypeRef key, CFTypeRef value );
            
            std::map< CFTypeRef, CFTypeRef > GetKeysAndValues( void );
            
            friend void swap( Dictionary & v1, Dictionary & v2 );
            
        private:
            
            CFMutableDictionaryRef _cfObject;
    };
}

#endif /* __CFPP_DICTIONARY_H__ */
