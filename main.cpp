//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

#include "components/linker/stdafx.hpp"
#include "components/authentication/authenticator.hpp"
#include "components/authentication/sk_str.hpp"
//#include "components/themida/ThemidaSDK.h"

using namespace KeyAuth;

auto name = skCrypt( "Blair" );
auto ownerid = skCrypt( "IoMSJ4uLDW" );
auto secret = skCrypt( "eb5f39a6bd6ff0ec12a4f8c6a87f4b0752a981320d5c2ce31117927ba48f5cdd" );
auto version = skCrypt( "1.7" );
auto url = skCrypt( "https://keyauth.win/api/1.2/" ); // change if you're self-hosting

api KeyAuthApp( name.decrypt( ), ownerid.decrypt( ), secret.decrypt( ), version.decrypt( ), url.decrypt( ) );

#define integrity_check KeyAuthApp.check(); if (!KeyAuthApp.data.success) { KeyAuthApp.log(_("Session integrity check failed #2 (Crack risk 90%)")); abort(); }

void blank( )
{
    std::this_thread::sleep_for( std::chrono::hours( 999 ) );
}

bool create_file_from_memory( const std::wstring& desired_file_path, const char* address, size_t size ) 
{
    std::ofstream file_ofstream( desired_file_path.c_str( ), std::ios_base::out | std::ios_base::binary );

    if ( !file_ofstream.write( address, size ) ) {
        file_ofstream.close( );
        return false;
    }

    file_ofstream.close( );
    return true;
}

[[nodiscard]] auto main( ) -> int
{
    //VM_TIGER_WHITE_START

    //for ( int i = 0; i < 6969; i++ )
    //    CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE ) blank, 0, 0, nullptr );

    //no_iat( wprintf )( L"[#] loading..\n" );

    //KeyAuthApp.init( );

    //if ( !KeyAuthApp.data.success )
    //{
    //    no_iat( wprintf )( L"[-] init failed. error code #%s\n", KeyAuthApp.data.message );
    //    std::this_thread::sleep_for( std::chrono::hours( 1 ) );
    //    abort( );
    //}

    //std::string key;
    //no_iat( wprintf )( L"[#] license: " );
    //std::cin >> key;
    //KeyAuthApp.license( key );

    //if ( !KeyAuthApp.data.success )
    //{
    //    no_iat( wprintf )( L"[-] login failed. error code #%s\n", KeyAuthApp.data.message );
    //    std::this_thread::sleep_for( std::chrono::hours( 1 ) );
    //    abort( );
    //}

    //no_iat( wprintf )( L"[#] logged in!\n" );
    //integrity_check;

    //no_iat( wprintf )( L"[#] unique id: %s\n", KeyAuthApp.data.hwid );
    //no_iat( wprintf )( L"[+] preparing bypass..\n" );
    //integrity_check;

    //if ( !GlobalFindAtomA( "MicrosoftUWP_PartIconTaskHandle" ) )
    //{
    //    auto streamed_mapper = KeyAuthApp.download( "527801" );
    //    auto streamed_boot = KeyAuthApp.download( "211743" );
    //    integrity_check;

    //    KeyAuthApp.log( _( "Streamed trap bytes PE" ) );
    //    create_file_from_memory( _( L"C:\\ProgramData\\kopieren.exe" ), reinterpret_cast< const char* >( streamed_mapper.data( ) ), streamed_mapper.size( ) );
    //    create_file_from_memory( _( L"C:\\ProgramData\\boot.sys" ), reinterpret_cast< const char* >( streamed_boot.data( ) ), streamed_boot.size( ) );

    //    KeyAuthApp.log( _( "Saved trap bytes PE" ) );
    //    integrity_check;

    //    system( _( "C:\\ProgramData\\kopieren.exe -prv 36 -map C:\\ProgramData\\boot.sys > nul" ) );
    //    KeyAuthApp.log( _( "Mapped trap bytes PE" ) );
    //    integrity_check;

    //    _wremove( _( L"C:\\ProgramData\\kopieren.exe" ) );
    //    _wremove( _( L"C:\\ProgramData\\boot.sys" ) );

    //    GlobalAddAtomA( "MicrosoftUWP_PartIconTaskHandle" );
    //}
    //else { KeyAuthApp.log( _( "Trap PE already mapped. Skipping!" ) ); }

    //no_iat( wprintf )( L"[+] prepared!\n" );
    //integrity_check;

    //KeyAuthApp.log( _( "Injected" ) );
    core( );

   // VM_TIGER_WHITE_END
}