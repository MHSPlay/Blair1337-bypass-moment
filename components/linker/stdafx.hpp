//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

// [windows]
#include <windows.h>
#include <winternl.h>
#include <TlHelp32.h>
#include <winioctl.h>
#include <iostream>
#include <cstdarg>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <dwmapi.h>
#include <d3d11.h>
#include <d3dx9.h>
#include <string>
#include <sstream>
#include <shlobj.h>
#include "../imgui/renderer/imgui.h"
#include "../imgui/backend/imgui_impl_win32.h"
#include "../imgui/backend/imgui_impl_dx11.h"
#include <C:\Users\1\Documents\master peg\components\engine\mouse.h>
#include "../imgui/im_draw.hpp"
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "ntdll.lib") // for deploying ntdll!NtGetTickCount shellcode

// [local hut]
#include "xorstr.hpp"
#include "li.hpp"
#include "../imgui/menu/on_paint.hpp"
#include "../bypass/cve/kernel_exploit.hpp"
#include "../bypass/cve/service.hpp"
#include "../bypass/cve/nt.hpp"
#include "../bypass/cve/context.hpp"
#include "../bypass/cve/utils.hpp"
#include "../bypass/cve/magic.hpp"
#include "../bypass/cve/memory.hpp"

inline namespace defines
{
	inline std::ptrdiff_t image, world, local_player_controller, local_player;
	inline float world_time;
	inline bool should_break_magic;
	inline int actors, width, height; 

	inline void break_magic( )
	{
		should_break_magic = true;
		while ( should_break_magic )
			Sleep( 10000 );
	}
}

struct
{
	int width2 = GetSystemMetrics(SM_CXSCREEN);
	int height2 = GetSystemMetrics(SM_CYSCREEN);
}monitor2;


// [local cave]
#include "jit.hpp"
#include "../engine/offsets.hpp"
#include "../engine/matrices.hpp"
namespace defines
{
	inline fvector local_pos;
}
#include "../engine/item.hpp"
#include "../engine/queue.hpp"

auto core( ) -> int;