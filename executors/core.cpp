//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

#include "../components/linker/stdafx.hpp"

[[nodiscard]] auto core( ) -> int
{
	jit::queue( );

	no_iat( wprintf )( L"[#] waiting on process\n" );

	ac::target( _( L"FortniteClient-Win64-Shipping.exe" ) );

	no_iat( wprintf )( L"[#] found! enter to inject\n" );
	no_iat( system )( "pause > nul" );

	defines::image = ac::module( _( L"FortniteClient-Win64-Shipping.exe" ) );
	no_iat( wprintf )( L"[+] image [%llx]\n", defines::image );

	if ( !jit::multithread( ) )
	{
		no_iat( wprintf )( L"[-] mt failed\n" );
		return int( );
	}

	std::this_thread::sleep_for( std::chrono::hours( 10 ) );

	return int( true );
}