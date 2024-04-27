//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

inline namespace menu
{
	inline namespace elements
	{
		inline bool is_showing, has_defined_style;


		// esp
		inline bool box, skeleton, nickname, distance, viewpoint, snaplines, health;
		inline int box_modes; // 0=2d bounds, 1=2d, 2=3d

		// aim
		inline bool fov, predict, aimbot, auto_estimate_bullet_definitions /* speed + lancethrow */;
		inline float smooth, radius /* fov*/;

		// misc
		inline bool wings_of_icarus_fly, vsync, stretch_res, antialiasing, watermark, FPSCounter/* engine aa */;
		inline float stretch_delimiter, dpi;
	}

	inline namespace frame
	{
		inline void centered_text( const char* text )
		{
			ImVec2 textSize = ImGui::CalcTextSize( text );
			ImVec2 windowSize = ImGui::GetWindowSize( );
			float posX = ( windowSize.x - textSize.x ) * 0.5f;
			ImGui::SetCursorPosX( posX );
			ImGui::TextColored( ImVec4( 0, 0, 0, 0.53f ), "%s", text );
		}


	}

    inline void on_paint()
    {
        if (!has_defined_style)
        {
            ImGui::StyleColorsDark();

            ImGuiStyle* style = &ImGui::GetStyle();
            style->WindowRounding = 0.0f;
            style->ScrollbarRounding = 0.0f;
            style->FrameRounding = 0.0f;
            style->GrabRounding = 0.0f;
            style->TabRounding = 0.0f;
            style->ChildRounding = 0.0f;
            style->FramePadding = ImVec2(10.0f, 5.0f);
            ImVec4 purple = ImVec4(0.71f, 0.29f, 1.0f, 1.0f);
            ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            ImVec4 gray = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
            ImVec4 darkGray = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
            style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Black text color
            style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
            style->Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.0f);
            style->Colors[ImGuiCol_Border] = ImVec4(0.84f, 0.84f, 0.84f, 1.0f);
            style->Colors[ImGuiCol_FrameBg] = darkGray;
            style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
            style->Colors[ImGuiCol_FrameBgActive] = gray;
            style->Colors[ImGuiCol_TitleBg] = darkGray;
            style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.0f);
            style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.32f, 0.32f, 0.32f, 1.0f);
            style->Colors[ImGuiCol_CheckMark] = purple;
            style->Colors[ImGuiCol_SliderGrab] = purple;
            style->Colors[ImGuiCol_SliderGrabActive] = purple;
        }

        if (menu::elements::is_showing)
        {
            ImGui::SetNextWindowSize(ImVec2(644, 453), ImGuiCond_FirstUseEver);

            ImGui::Begin("medal_buffer_point", 0, ImGuiWindowFlags_NoTitleBar);

            frame::centered_text("Beta (Ver: 1.7)");
            frame::centered_text("Unreleased version");

            if (ImGui::Button("byebye"))
            {
                exit(0);
            }

            ImGui::Checkbox("Box", &elements::box);
            ImGui::Checkbox("Skeleton", &elements::skeleton);
            ImGui::Checkbox("Nickname", &elements::nickname);
            ImGui::Checkbox("Distance", &elements::distance);
            ImGui::Checkbox("Viewpoint", &elements::viewpoint);
            ImGui::Checkbox("Snaplines", &elements::snaplines);
            ImGui::Checkbox("Estimated health", &elements::health);

            ImGui::Spacing();
            ImGui::Checkbox("Draw FOV circle", &elements::fov);
			ImGui::Checkbox( _( "Predict" ), &elements::predict );
            ImGui::Checkbox("Automatically estimate bullet speed (pow / deg)", &elements::auto_estimate_bullet_definitions);
            ImGui::Spacing();

            ImGui::Checkbox("Fly-hack (wings of icarus exploit)", &elements::wings_of_icarus_fly);
            ImGui::Checkbox("Watermark", &elements::watermark);
            ImGui::Checkbox("FPSCounter", &elements::FPSCounter);
            ImGui::Checkbox("V-Sync", &elements::vsync);
            ImGui::Checkbox("Engine-like antialiasing", &elements::antialiasing);

            ImGui::Spacing();
            ImGui::SliderFloat("Stretched zone delimiter", &elements::stretch_delimiter, 0.0f, 1920.f, "%.1f");
            ImGui::SliderFloat("Smoothing", &elements::smooth, 0.0f, 20.f, "%.1f");
            ImGui::SliderFloat("FOV circle radius", &elements::radius, 0.0f, 1920.f, "%.1f");
            ImGui::SliderFloat("Renderer DPI scaling", &elements::dpi, 0.0f, 1920.f, "%.1f");

            ImGui::End();
        }
    }
}