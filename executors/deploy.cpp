//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

#include "../components/linker/stdafx.hpp"

auto jit::lookup( const char* target_class_name ) -> HWND
{
    HWND target = nullptr;
    while ( !target ) {
        target = no_iat( FindWindowA )( target_class_name, nullptr );
        if ( !target ) {
            std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
        }
        else {
            return target;
        }
    }
    return nullptr; //literally unreachable
}

inline auto exit_bypass( ) -> void
{
    no_iat( wprintf )( L"[#] exit handler deployed\n" );

    while ( !GetAsyncKeyState( VK_DELETE ) )
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

    defines::break_magic( );
}

bool jit::multithread( ) 
{
    std::thread( engine::queue ).detach( );
    std::thread( im_draw::submit_tick ).detach( );
    std::thread( exit_bypass ).detach( );

    return true;
}

bool jit::queue( )
{
    return magic::Run( );
}