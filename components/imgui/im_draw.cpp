//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

#include "../linker/stdafx.hpp"
#include "glyphs/pragma_font.hpp"
using Clock = std::chrono::steady_clock;


// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

void FancyBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    // Draw shadow
    drawList->AddRectFilled(ImVec2(X + 1, Y + 1), ImVec2(X + W + 1, Y + H + 1), IM_COL32_BLACK_TRANS);

    // Draw main box border
    drawList->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), IM_COL32_WHITE, 0.0f, 0, thickness);
}

void outlined_text(ImDrawList* drawlist, int x, int y, ImColor Color, const char* text)
{
    ImVec2 offsets[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (const auto& offset : offsets)
    {
        drawlist->AddText(ImVec2(x + offset.x, y + offset.y), ImColor(0, 0, 0, 255), text);
    }

    drawlist->AddText(ImVec2(x, y), Color, text);
}


inline namespace im_draw
{
    static ID3D11Device* g_pd3dDevice = nullptr;
    static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
    static IDXGISwapChain* g_pSwapChain = nullptr;
    static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
    static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

    inline void CreateRenderTarget( )
    {
        ID3D11Texture2D* pBackBuffer;
        g_pSwapChain->GetBuffer( 0, IID_PPV_ARGS( &pBackBuffer ) );
        g_pd3dDevice->CreateRenderTargetView( pBackBuffer, nullptr, &g_mainRenderTargetView );
        pBackBuffer->Release( );
    }

    inline void CleanupRenderTarget( )
    {
        if ( g_mainRenderTargetView ) { g_mainRenderTargetView->Release( ); g_mainRenderTargetView = nullptr; }
    }

    inline  bool CreateDeviceD3D( HWND hWnd )
    {
        // Setup swap chain
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory( &sd, sizeof( sd ) );
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        HRESULT res = D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext );
        if ( res == DXGI_ERROR_UNSUPPORTED ) // Try high-performance WARP software driver if hardware is not available.
            res = D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext );
        if ( res != S_OK )
            return false;

        CreateRenderTarget( );
        return true;
    }

    inline void CleanupDeviceD3D( )
    {
        CleanupRenderTarget( );
        if ( g_pSwapChain ) { g_pSwapChain->Release( ); g_pSwapChain = nullptr; }
        if ( g_pd3dDeviceContext ) { g_pd3dDeviceContext->Release( ); g_pd3dDeviceContext = nullptr; }
        if ( g_pd3dDevice ) { g_pd3dDevice->Release( ); g_pd3dDevice = nullptr; }
    }

    // Win32 message handler
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    WNDPROC previous_window_procedure;
    inline LRESULT WINAPI hooked_window_procedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
    {
        if ( ImGui_ImplWin32_WndProcHandler( hWnd, msg, wParam, lParam ) )
            return true;

        switch ( msg )
        {
        case WM_KEYUP:
            if ( wParam == VK_INSERT )
                menu::elements::is_showing = !menu::elements::is_showing;
            break;
        case WM_SIZE:
            if ( wParam == SIZE_MINIMIZED )
                return 0;
            g_ResizeWidth = ( UINT ) LOWORD( lParam ); // Queue resize
            g_ResizeHeight = ( UINT ) HIWORD( lParam );
            return 0;
        case WM_SYSCOMMAND:
            if ( ( wParam & 0xfff0 ) == SC_KEYMENU ) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage( 0 );
            return 0;
        }
        return CallWindowProc( previous_window_procedure, hWnd, msg, wParam, lParam );
    }

    int distance;
    double scaling_factor_per_unit_distance = 0.01;
    auto submit_tick( ) -> void
    {
        HWND hwnd = no_iat( FindWindowA )( "MedalOverlayClass", "MedalOverlay" );
        if ( !hwnd )
        {
            no_iat( wprintf )( L"[-] medal not found. is it installed? is it opened?\n" );
            defines::break_magic( );
            return;
        }

        previous_window_procedure = ( WNDPROC ) SetWindowLongPtr( hwnd, ( -4 ), ( LONG_PTR ) &hooked_window_procedure );
        if ( !CreateDeviceD3D( hwnd ) )
        {
            CleanupDeviceD3D( );
            no_iat( wprintf )( L"[-] d3d error #7\n" );
            defines::break_magic( );
            return;
        }

        MARGINS margins = { -1 };
        RECT rect;
        auto result = no_iat( GetWindowRect )( no_iat( FindWindowA ) ( "UnrealWindow", "Fortnite  " ), &rect );
        if ( !result ) {
            no_iat( wprintf )( L"[-] d3d error #9\n" );
            defines::break_magic( );
            return;
        }

        defines::width = rect.right - rect.left;
        defines::height = rect.bottom - rect.top;

        DwmExtendFrameIntoClientArea( hwnd, &margins );
        SetWindowPos( hwnd, 0, 0, 0, defines::width, defines::height, SWP_SHOWWINDOW );

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION( );
        ImGui::CreateContext( );
        ImGuiIO& io = ImGui::GetIO( ); ( void ) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark( );
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init( hwnd );
        ImGui_ImplDX11_Init( g_pd3dDevice, g_pd3dDeviceContext );

        io.Fonts->AddFontFromMemoryTTF( glyph::pgm, sizeof( glyph::pgm ), 17 );

        // Main loop
        bool done = false;
        int active_tick = 0, has_passed = 0;

        while ( !done )
        {
            // Poll and handle messages (inputs, window resize, etc.)
            // See the WndProc() function below for our to dispatch events to the Win32 backend.
            MSG msg;
            while ( ::PeekMessage( &msg, nullptr, 0U, 0U, PM_REMOVE ) )
            {
                ::TranslateMessage( &msg );
                ::DispatchMessage( &msg );
                if ( msg.message == WM_QUIT )
                    done = true;
            }
            if ( done )
                break;

            if ( GetAsyncKeyState( VK_INSERT ) & 1 )
                menu::elements::is_showing = !menu::elements::is_showing;

            // Handle window resize (we don't resize directly in the WM_SIZE handler)
            if ( g_ResizeWidth != 0 && g_ResizeHeight != 0 )
            {
                CleanupRenderTarget( );
                g_pSwapChain->ResizeBuffers( 0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0 );
                g_ResizeWidth = g_ResizeHeight = 0;
                CreateRenderTarget( );
            }


            POINT mousePos;
            ImDrawList* draw_list = ImGui::GetForegroundDrawList();
            GetCursorPos( &mousePos );
            ScreenToClient( hwnd, &mousePos );
            bool leftMouseButtonPressed = ( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 ) != 0;
            ImGui_ImplDX11_NewFrame( );
            ImGuiIO& io = ImGui::GetIO( );
            io.MousePos = ImVec2( static_cast< float >( mousePos.x ), static_cast< float >( mousePos.y ) );
            io.MouseDown[0] = leftMouseButtonPressed;

            // Start the Dear ImGui frame
            ImGui_ImplDX11_NewFrame( );
            ImGui_ImplWin32_NewFrame( );
            ImGui::NewFrame( );
            {
                static float f = 0.0f;
                static int counter = 0;

                if ( !has_passed )
                {
                    if ( !active_tick )
                        active_tick = GetTickCount64( );

                    if ( GetTickCount64( ) < active_tick + 5000 )
                    {
                        ImGui::GetBackgroundDrawList( )->AddRectFilled( { 0,0 }, { 221,30 }, ImColor( 68, 68, 68 ) );
                        ImGui::GetBackgroundDrawList( )->AddRectFilled( { 0,0 }, { 4,30 }, ImColor( 75, 255, 0 ) );
                        ImGui::GetBackgroundDrawList( )->AddText( { 18,15 }, ImColor( 255, 255, 255 ), _( "Linked with medal texture buffer" ) );
                    }
                    else
                    {
                        has_passed = 1;
                    }
                }

                if ( defines::world && engine::submitted_players.size( ) )
                {
                    for ( auto player : engine::submitted_players )
                    {
                        auto state = player.state, pawn = player.pawn, mesh = player.mesh;
                        if ( !state || !pawn || !mesh )
                            continue;

                        auto base = player.base;
                        if ( !base.x || !base.y )
                            continue;

                        auto head = player.head;
                        if ( !head.x || !head.y )
                            continue;

                        fvector base_point;
                        if ( !engine::world_to_screen( base, &base_point ) )
                            continue;

                        fvector head_point;
                        if ( !engine::world_to_screen( head, &head_point ) )
                            continue;

                        head_point.z + 15;

                        distance = static_cast< int >( local_pos.dist( player.base ) ) / 100;
                        if ( distance == 1254 )
                            distance = 0;

                        float distance_modifier = engine::scheduled_view_point.loc.dist( head ) * 0.001F;


                        ImVec2 bg_position;
                        ImVec2 bg_size;



                        //black background
                        //if (menu::elements::nickname)
                        //{
                        //    std::string text = engine::player_name_private(player.state);
                        //    if (menu::elements::distance)
                        //        text += " [" + std::to_string(distance) + "m]";

                        //    auto target_point = ImVec2(head_point.x, base_point.y + 15);
                        //    double target_scaling_factor = 1.0 - (distance * scaling_factor_per_unit_distance);
                        //    if (distance <= 15)
                        //        target_point.y += 20;
                        //    else
                        //        target_point.y += 25 * target_scaling_factor;

                        //    ImVec2 text_size = ImGui::CalcTextSize(text.c_str());
                        //    bg_size = ImVec2(6 + text_size.x, 4 + text_size.y);

                        //    bg_position = ImVec2(target_point.x - bg_size.x * 0.5f, target_point.y - bg_size.y - 2);

                        //    ImVec2 text_position(bg_position.x + (bg_size.x - text_size.x) * 0.5f, bg_position.y + (bg_size.y - text_size.y) * 0.5f);

                        //    ImGui::GetBackgroundDrawList()->AddRectFilled(bg_position, ImVec2(bg_position.x + bg_size.x, bg_position.y + bg_size.y), IM_COL32(0, 0, 0, 255), 5.f);
                        //    ImGui::GetBackgroundDrawList()->AddText(text_position, ImColor(255, 255, 255), text.c_str());
                        //}


                        if (menu::elements::nickname)
                        {
                            std::string text = engine::player_name_private(player.state);
                            if (menu::elements::distance)
                                text += " [" + std::to_string(distance) + "m]";

                            auto target_point = ImVec2(head_point.x, base_point.y + 15);
                            double target_scaling_factor = 1.0 - (distance * scaling_factor_per_unit_distance);
                            if (distance <= 15)
                                target_point.y += 20;
                            else
                                target_point.y += 25 * target_scaling_factor;

                            ImVec2 text_size = ImGui::CalcTextSize(text.c_str());
                            bg_size = ImVec2(6 + text_size.x, 4 + text_size.y);

                            bg_position = ImVec2(target_point.x - bg_size.x * 0.5f, target_point.y - bg_size.y - 2);

                            ImVec2 text_position(bg_position.x + (bg_size.x - text_size.x) * 0.5f, bg_position.y + (bg_size.y - text_size.y) * 0.5f);

                            // Draw text with outline
                            outlined_text(ImGui::GetBackgroundDrawList(), text_position.x, text_position.y, ImColor(255, 255, 255), text.c_str());
                        }


                        if (menu::elements::box)
                        {
                            float BoxHeight = abs(head_point.y - base_point.y); // Box Dimensions
                            float BoxWidth = BoxHeight * 0.60;

                            FancyBox(head_point.x - (BoxWidth / 2), head_point.y, BoxWidth, BoxHeight, IM_COL32(255, 0, 0, 255), 1.5);
                            draw_list->AddLine(ImVec2(base_point.x, base_point.y), ImVec2(base_point.x, base_point.y), IM_COL32(255, 255, 255, 255), 2);
                           // ImGui::GetBackgroundDrawList()->AddRect(box_min, box_max, IM_COL32(255, 0, 0, 255)); 
                        }

                        if (menu::skeleton)
                        {
                            //skeletons();
                        }


                        if (menu::elements::snaplines)
                        {
                            //draw_list->AddLine(ImVec2(base_point.x, base_point.y), ImVec2(head_point.x, head_point.y), IM_COL32(255, 255, 255, 255), 2);
                        }
                        

                        if (menu::watermark) {
                            char Watermark[64];
                            sprintf_s(Watermark, 64, "Nigger");
                            float fontSize = 18;
                            ImVec2 textPosition(15, 10);
                            ImColor color = ImColor(255, 255, 255);

                            outlined_text(ImGui::GetBackgroundDrawList(), textPosition.x, textPosition.y, color, Watermark);

                            // Add the "cc" text in purple
                            sprintf_s(Watermark, 64, ".pro");
                            fontSize = 18;
                            textPosition.x += ImGui::CalcTextSize("Nigger").x;
                            color = ImColor(160, 32, 240, 255);
                            outlined_text(ImGui::GetBackgroundDrawList(), textPosition.x, textPosition.y, color, Watermark);
                        }

                        if (menu::FPSCounter) {
                            char FPSCounter[64];
                            sprintf_s(FPSCounter, 64, "[%.1f FPS]", ImGui::GetIO().Framerate);
                            float fontSize = 18;
                            ImVec2 textPosition(15, 30); // Adjust y-coordinate for the FPS counter
                            ImColor color = ImColor(255, 255, 255);
                            outlined_text(ImGui::GetBackgroundDrawList(), textPosition.x, textPosition.y, color, FPSCounter);
                        }


                        //if (menu::elements::box)
                        //{
                        //    float BoxHeight = abs(head_point.y - base_point.y); // Box Dimensions
                        //    float BoxWidth = BoxHeight * 0.60f;

                        //    Normalbox(head_point.x - (BoxWidth / 2), head_point.y, BoxWidth, BoxHeight, IM_COL32(255, 0, 0, 255), 1.5f, 0);
                        //}

                    }
                }

                if ( has_passed )
                {
                    menu::on_paint( );
                   /* ImGui::GetBackgroundDrawList( )->AddText( { 18,18 }, ImColor( 255, 255, 255 ), std::string( "Queued for next tick: " + std::to_string( engine::submitted_players.size( ) ) ).c_str( ) );
                    ImGui::GetBackgroundDrawList( )->AddText( { 18,32 }, ImColor( 255, 255, 255 ), std::string( "Viewport layout: " + std::to_string( defines::width ) + " x " + std::to_string( defines::height ) ).c_str( ) );*/

                    /*if ( defines::world_time < 1.f ) ImGui::GetBackgroundDrawList( )->AddText( { 18,46 }, ImColor( 255, 255, 255 ), std::string( "World time: " + std::to_string( defines::world_time ) ).c_str( ) );
                    else  ImGui::GetBackgroundDrawList( )->AddText( { 18,46 }, ImColor( 255, 255, 255 ), std::string( "World time: " + std::to_string( defines::world_time ) + " (active for " + std::to_string( defines::world_time / 60.f ) + " minutes)" ).c_str( ) );*/
                }
            }

            // Rendering
            const float color[] { 0, 0, 0, 0 };
            ImGui::Render( );
            ImGui::EndFrame( );
            g_pd3dDeviceContext->OMSetRenderTargets( 1, &g_mainRenderTargetView, nullptr );
            g_pd3dDeviceContext->ClearRenderTargetView( g_mainRenderTargetView, color );
            ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );

            g_pSwapChain->Present( 0, 0 ); // Present without vsync

            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
        }
    }
}