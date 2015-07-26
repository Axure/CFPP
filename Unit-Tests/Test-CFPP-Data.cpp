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
 * @file        Test-CFPP-Data.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    Unit tests for CF::Data
 */

#include <CF++.hpp>
#include <GoogleMock/GoogleMock.h>

using namespace testing;

static CF::Data::Byte __bytes[] = { 0xDE, 0xAD, 0xBE, 0xEF };

TEST( CFPP_Data, CTOR )
{
    CF::Data d;
    
    ASSERT_TRUE( d.IsValid() );
    ASSERT_EQ( d.GetLength(), 0 );
}

TEST( CFPP_Data, CTOR_CFIndex )
{
    CF::Data d( 100 );
    
    ASSERT_TRUE( d.IsValid() );
    ASSERT_EQ( d.GetLength(), 0 );
}

TEST( CFPP_Data, CTOR_AutoPointer )
{
    CF::Data d1( CF::AutoPointer( CFDataCreateMutable( NULL, 10 ) ) );
    CF::Data d2( CF::AutoPointer( CFUUIDCreate( NULL ) ) );
    CF::Data d3( CF::AutoPointer( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Data, CTOR_CFType )
{
    CF::Data d1( static_cast< CFTypeRef >( CF::Data().GetCFObject() ) );
    CF::Data d2( static_cast< CFTypeRef >( NULL ) );
    CF::Data d3( static_cast< CFTypeRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Data, CTOR_CFData )
{
    CF::Data d1( static_cast< CFDataRef >( CF::Data().GetCFObject() ) );
    CF::Data d2( static_cast< CFDataRef >( NULL ) );
    CF::Data d3( static_cast< CFDataRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Data, CTOR_CFString )
{
    CF::Data d1( static_cast< CFStringRef >( CFSTR( "hello, world" ) ) );
    CF::Data d2( static_cast< CFStringRef >( NULL ) );
    CF::Data d3( static_cast< CFStringRef >( CF::Boolean().GetCFObject() ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Data, CTOR_STDString )
{
    CF::Data d1( std::string( "hello, world" ) );
    CF::Data d2( std::string( "" ) );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
}

TEST( CFPP_Data, CTOR_BytePtr )
{
    CF::Data d1( __bytes, sizeof( __bytes ) );
    CF::Data d2( NULL,    sizeof( __bytes ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
}

#ifdef CFPP_HAS_CPP11
TEST( CFPP_Data, CTOR_STDInitializerList )
{
    CF::Data d( { 0xDE, 0xAD, 0xBE, 0xEF } );
    
    ASSERT_TRUE( d.IsValid() );
    ASSERT_TRUE( d.GetLength() == 4 );
    
    ASSERT_TRUE( d[ 0 ] == 0xDE );
    ASSERT_TRUE( d[ 1 ] == 0xAD );
    ASSERT_TRUE( d[ 2 ] == 0xBE );
    ASSERT_TRUE( d[ 3 ] == 0xEF );
}
#endif

TEST( CFPP_Data, CCTOR )
{
    CF::Data d1;
    CF::Data d2( static_cast< CFDataRef >( NULL ) );
    CF::Data d3( d1 );
    CF::Data d4( d2 );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
}

#ifdef CFPP_HAS_CPP11
TEST( CFPP_Data, MCTOR )
{
    CF::Data d1;
    CF::Data d2( static_cast< CFDataRef >( nullptr ) );
    CF::Data d3( std::move( d1 ) );
    CF::Data d4( std::move( d2 ) );
    
    ASSERT_FALSE( d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
}
#endif

TEST( CFPP_Data, OperatorAssignData )
{
    CF::Data d1( __bytes, sizeof( __bytes ) );
    CF::Data d2( static_cast< CFDataRef >( NULL ) );
    CF::Data d3;
    CF::Data d4;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_TRUE(  d4.IsValid() );
    
    ASSERT_TRUE( d1.GetLength() == sizeof( __bytes ) );
    
    d3 = d1;
    d4 = d2;
    
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE( d3.GetLength() == sizeof( __bytes ) );
}

TEST( CFPP_Data, OperatorAssignAutoPointer )
{
    CF::Data d1( static_cast< CFTypeRef >( NULL ) );
    CF::Data d2;
    CF::Data d3;
    
    ASSERT_FALSE( d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    
    d1 = CF::AutoPointer( CFDataCreateMutable( NULL, 10 ) );
    d2 = CF::AutoPointer( CFUUIDCreate( NULL ) );
    d3 = CF::AutoPointer( NULL );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
}

TEST( CFPP_Data, OperatorAssignCFType )
{
    CF::Data d1( __bytes, sizeof( __bytes ) );
    CF::Data d2( static_cast< CFDataRef >( NULL ) );
    CF::Data d3;
    CF::Data d4;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_TRUE(  d4.IsValid() );
    
    ASSERT_TRUE( d1.GetLength() == sizeof( __bytes ) );
    
    d3 = static_cast< CFTypeRef >( d1.GetCFObject() );
    d4 = static_cast< CFTypeRef >( d2.GetCFObject() );
    
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE( d3.GetLength() == sizeof( __bytes ) );
}

TEST( CFPP_Data, OperatorAssignCFData )
{
    CF::Data d1( __bytes, sizeof( __bytes ) );
    CF::Data d2( static_cast< CFDataRef >( NULL ) );
    CF::Data d3;
    CF::Data d4;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_TRUE(  d4.IsValid() );
    
    ASSERT_TRUE( d1.GetLength() == sizeof( __bytes ) );
    
    d3 = static_cast< CFDataRef >( d1.GetCFObject() );
    d4 = static_cast< CFDataRef >( d2.GetCFObject() );
    
    ASSERT_TRUE(  d3.IsValid() );
    ASSERT_FALSE( d4.IsValid() );
    
    ASSERT_TRUE( d3.GetLength() == sizeof( __bytes ) );
}

TEST( CFPP_Data, OperatorAssignCFString )
{
    CF::Data d1;
    CF::Data d2;
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    d1 = static_cast< CFStringRef >( CFSTR( "hello, world" ) );
    d2 = static_cast< CFStringRef >( NULL );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    ASSERT_TRUE( d1.GetLength() > 0 );
}

TEST( CFPP_Data, OperatorAssignSTDString )
{
    CF::Data d1;
    CF::Data d2;
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    d1 = std::string( "hello, world" );
    d2 = std::string( "" );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( d2.IsValid() );
    
    ASSERT_TRUE( d1.GetLength() >  0 );
    ASSERT_TRUE( d2.GetLength() == 0 );
}

TEST( CFPP_Data, CastToBytePtr )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( static_cast< const CF::Data::Byte * >( d1 ) != NULL );
    ASSERT_TRUE( static_cast< const CF::Data::Byte * >( d2 ) != NULL );
    ASSERT_TRUE( static_cast< const CF::Data::Byte * >( d3 ) == NULL );
    
    ASSERT_TRUE( static_cast< const CF::Data::Byte * >( d2 )[ 0 ] == 0xDE );
    ASSERT_TRUE( static_cast< const CF::Data::Byte * >( d2 )[ 1 ] == 0xAD );
    ASSERT_TRUE( static_cast< const CF::Data::Byte * >( d2 )[ 2 ] == 0xBE );
    ASSERT_TRUE( static_cast< const CF::Data::Byte * >( d2 )[ 3 ] == 0xEF );
}

TEST( CFPP_Data, CastToSTDString )
{
    CF::Data d1;
    CF::Data d2( std::string( "hello, world" ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( static_cast< std::string >( d1 ) == "" );
    ASSERT_TRUE( static_cast< std::string >( d2 ) == "hello, world" );
    ASSERT_TRUE( static_cast< std::string >( d3 ) == "" );
}

TEST( CFPP_Data, OperatorSubscript )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1[  0 ] == 0x00 );
    ASSERT_TRUE( d1[ -1 ] == 0x00 );
    ASSERT_TRUE( d1[  1 ] == 0x00 );
    
    ASSERT_TRUE( d2[  0 ] == 0xDE );
    ASSERT_TRUE( d2[ -1 ] == 0x00 );
    ASSERT_TRUE( d2[  1 ] == 0xAD );
    
    ASSERT_TRUE( d3[  0 ] == 0x00 );
    ASSERT_TRUE( d3[ -1 ] == 0x00 );
    ASSERT_TRUE( d3[  1 ] == 0x00 );
}

TEST( CFPP_Data, OperatorPlusEqualByte )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    d1 += 0xFF;
    d2 += 0xFF;
    d3 += 0xFF;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1[ 0 ] == 0xFF );
    ASSERT_TRUE( d2[ 4 ] == 0xFF );
}

TEST( CFPP_Data, OperatorPlusEqualCFString )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    d1 += CFSTR( "hello, world" );
    d2 += CFSTR( "hello, world" );
    d3 += CFSTR( "hello, world" );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1[ 0 ] == 'h' );
    ASSERT_TRUE( d2[ 4 ] == 'h' );
}

TEST( CFPP_Data, OperatorPlusEqualCFData )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    d1 += static_cast< CFDataRef >( d2 );
    d2 += static_cast< CFDataRef >( d2 );
    d3 += static_cast< CFDataRef >( d2 );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1[ 0 ] == 0xDE );
    ASSERT_TRUE( d2[ 4 ] == 0xDE );
}

TEST( CFPP_Data, OperatorPlusEqualData )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    d1 += d2;
    d2 += d2;
    d3 += d2;
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1[ 0 ] == 0xDE );
    ASSERT_TRUE( d2[ 4 ] == 0xDE );
}

TEST( CFPP_Data, OperatorPlusEqualSTDString )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    d1 += std::string( "hello, world" );
    d2 += std::string( "hello, world" );
    d3 += std::string( "hello, world" );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1[ 0 ] == 'h' );
    ASSERT_TRUE( d2[ 4 ] == 'h' );
}

TEST( CFPP_Data, GetTypeID )
{
    CF::Data d;
    
    ASSERT_EQ( d.GetTypeID(), CFDataGetTypeID() );
}

TEST( CFPP_Data, GetCFObject )
{
    CF::Data d1;
    CF::Data d2( static_cast< CFStringRef >( NULL ) );
    
    ASSERT_TRUE( d1.GetCFObject() != NULL );
    ASSERT_TRUE( d2.GetCFObject() == NULL );
    
    ASSERT_EQ( CFGetTypeID( d1.GetCFObject() ), CFDataGetTypeID() );
}

TEST( CFPP_Data, GetLength )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1.GetLength() == 0 );
    ASSERT_TRUE( d2.GetLength() == sizeof( __bytes ) );
    ASSERT_TRUE( d3.GetLength() == 0 );
}

TEST( CFPP_Data, SetLength )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1.GetLength() == 0 );
    ASSERT_TRUE( d2.GetLength() == sizeof( __bytes ) );
    ASSERT_TRUE( d3.GetLength() == 0 );
    
    d1.SetLength( 10 );
    d2.SetLength( 10 );
    d3.SetLength( 10 );
    
    ASSERT_TRUE( d1.GetLength() == 10 );
    ASSERT_TRUE( d2.GetLength() == 10 );
    ASSERT_TRUE( d3.GetLength() ==  0 );
}

TEST( CFPP_Data, IncreaseLength )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1.GetLength() == 0 );
    ASSERT_TRUE( d2.GetLength() == sizeof( __bytes ) );
    ASSERT_TRUE( d3.GetLength() == 0 );
    
    d1.IncreaseLength( 10 );
    d2.IncreaseLength( 10 );
    d3.IncreaseLength( 10 );
    
    ASSERT_TRUE( d1.GetLength() == 10 );
    ASSERT_TRUE( d2.GetLength() == sizeof( __bytes ) + 10 );
    ASSERT_TRUE( d3.GetLength() ==  0 );
}

TEST( CFPP_Data, GetBytePtr )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1.GetBytePtr() != NULL );
    ASSERT_TRUE( d2.GetBytePtr() != NULL );
    ASSERT_TRUE( d3.GetBytePtr() == NULL );
    
    ASSERT_TRUE( d2.GetBytePtr()[ 0 ] == 0xDE );
    ASSERT_TRUE( d2.GetBytePtr()[ 1 ] == 0xAD );
    ASSERT_TRUE( d2.GetBytePtr()[ 2 ] == 0xBE );
    ASSERT_TRUE( d2.GetBytePtr()[ 3 ] == 0xEF );
}

TEST( CFPP_Data, GetMutableBytePtr )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1.GetMutableBytePtr() != NULL );
    ASSERT_TRUE( d2.GetMutableBytePtr() != NULL );
    ASSERT_TRUE( d3.GetMutableBytePtr() == NULL );
    
    ASSERT_TRUE( d2.GetMutableBytePtr()[ 0 ] == 0xDE );
    ASSERT_TRUE( d2.GetMutableBytePtr()[ 1 ] == 0xAD );
    ASSERT_TRUE( d2.GetMutableBytePtr()[ 2 ] == 0xBE );
    ASSERT_TRUE( d2.GetMutableBytePtr()[ 3 ] == 0xEF );
}

TEST( CFPP_Data, GetBytes )
{
    CF::Data       d1( __bytes, sizeof( __bytes ) );
    CF::Data       d2( static_cast< CFDataRef >( NULL ) );
    CF::Data::Byte bytes[ 2 ];
    
    memset( bytes, 0x00, sizeof( bytes ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    d2.GetBytes( CFRangeMake( 0, 2 ), bytes );
    
    ASSERT_FALSE( d2.IsValid() );
    ASSERT_TRUE( bytes[ 0 ] == 0x00 );
    ASSERT_TRUE( bytes[ 1 ] == 0x00 );
    
    d1.GetBytes( CFRangeMake( 0, 2 ), bytes );
    
    ASSERT_TRUE( d1.IsValid() );
    ASSERT_TRUE( bytes[ 0 ] == 0xDE );
    ASSERT_TRUE( bytes[ 1 ] == 0xAD );
}

TEST( CFPP_Data, AppendBytes )
{
    CF::Data d1;
    CF::Data d2( __bytes, sizeof( __bytes ) );
    CF::Data d3( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    d1.AppendBytes( __bytes, sizeof( __bytes ) );
    d2.AppendBytes( __bytes, sizeof( __bytes ) );
    d3.AppendBytes( __bytes, sizeof( __bytes ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1.GetBytePtr() != NULL );
    ASSERT_TRUE( d2.GetBytePtr() != NULL );
    ASSERT_TRUE( d3.GetBytePtr() == NULL );
    
    ASSERT_TRUE( d1.GetBytePtr()[ 0 ] == 0xDE );
    ASSERT_TRUE( d1.GetBytePtr()[ 1 ] == 0xAD );
    ASSERT_TRUE( d1.GetBytePtr()[ 2 ] == 0xBE );
    ASSERT_TRUE( d2.GetBytePtr()[ 3 ] == 0xEF );
    
    ASSERT_TRUE( d2.GetBytePtr()[ 0 ] == 0xDE );
    ASSERT_TRUE( d2.GetBytePtr()[ 1 ] == 0xAD );
    ASSERT_TRUE( d2.GetBytePtr()[ 2 ] == 0xBE );
    ASSERT_TRUE( d2.GetBytePtr()[ 3 ] == 0xEF );
    ASSERT_TRUE( d2.GetBytePtr()[ 4 ] == 0xDE );
    ASSERT_TRUE( d2.GetBytePtr()[ 5 ] == 0xAD );
    ASSERT_TRUE( d2.GetBytePtr()[ 6 ] == 0xBE );
    ASSERT_TRUE( d2.GetBytePtr()[ 7 ] == 0xEF );
}

TEST( CFPP_Data, ReplaceBytes )
{
    CF::Data       d1;
    CF::Data       d2( __bytes, sizeof( __bytes ) );
    CF::Data       d3( static_cast< CFDataRef >( NULL ) );
    CF::Data::Byte bytes[ 3 ];
    
    memset( bytes, 0xFF, sizeof( bytes ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    d1.ReplaceBytes( CFRangeMake( 0, 2 ), bytes, 2 );
    d2.ReplaceBytes( CFRangeMake( 0, 2 ), bytes, 2 );
    d3.ReplaceBytes( CFRangeMake( 0, 2 ), bytes, 2 );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
    ASSERT_FALSE( d3.IsValid() );
    
    ASSERT_TRUE( d1.GetBytePtr() != NULL );
    ASSERT_TRUE( d2.GetBytePtr() != NULL );
    ASSERT_TRUE( d3.GetBytePtr() == NULL );
    
    ASSERT_TRUE( d1.GetBytePtr()[ 0 ] == 0xFF );
    ASSERT_TRUE( d1.GetBytePtr()[ 1 ] == 0xFF );
    
    ASSERT_TRUE( d2.GetBytePtr()[ 0 ] == 0xFF );
    ASSERT_TRUE( d2.GetBytePtr()[ 1 ] == 0xFF );
    ASSERT_TRUE( d2.GetBytePtr()[ 2 ] == 0xBE );
    ASSERT_TRUE( d2.GetBytePtr()[ 3 ] == 0xEF );
    
    d2.ReplaceBytes( CFRangeMake( 0, 2 ), bytes, 3 );
    
    ASSERT_TRUE( d2.GetBytePtr()[ 0 ] == 0xFF );
    ASSERT_TRUE( d2.GetBytePtr()[ 1 ] == 0xFF );
    ASSERT_TRUE( d2.GetBytePtr()[ 2 ] == 0xFF );
    ASSERT_TRUE( d2.GetBytePtr()[ 3 ] == 0xBE );
    ASSERT_TRUE( d2.GetBytePtr()[ 4 ] == 0xEF );
    
    d2.ReplaceBytes( CFRangeMake( 0, 3 ), bytes, 1 );
    
    ASSERT_TRUE( d2.GetBytePtr()[ 0 ] == 0xFF );
    ASSERT_TRUE( d2.GetBytePtr()[ 1 ] == 0xBE );
    ASSERT_TRUE( d2.GetBytePtr()[ 2 ] == 0xEF );
}

TEST( CFPP_Data, DeleteBytes )
{
    CF::Data d1( __bytes, sizeof( __bytes ) );
    CF::Data d2( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    d1.DeleteBytes( CFRangeMake( 1, 2 ) );
    d2.DeleteBytes( CFRangeMake( 1, 2 ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    ASSERT_TRUE( d1.GetBytePtr()[ 0 ] == 0xDE );
    ASSERT_TRUE( d1.GetBytePtr()[ 1 ] == 0xEF );
}

TEST( CFPP_Data, Swap )
{
    CF::Data d1;
    CF::Data d2( static_cast< CFDataRef >( NULL ) );
    
    ASSERT_TRUE(  d1.IsValid() );
    ASSERT_FALSE( d2.IsValid() );
    
    swap( d1, d2 );
    
    ASSERT_FALSE( d1.IsValid() );
    ASSERT_TRUE(  d2.IsValid() );
}
