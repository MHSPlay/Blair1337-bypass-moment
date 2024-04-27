//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

inline namespace engine
{
	struct data
	{
		std::ptrdiff_t state, pawn, mesh, bone_array;
		fvector base, head;
	};

	inline std::vector<data> submitted_players;
	inline void queue( )
	{
		for ( ;; )
		{
			std::vector<data> target;
			defines::world = ac::read<std::ptrdiff_t>( defines::image + offsets::world );
			auto owning_game_instance = ac::read<std::ptrdiff_t>( defines::world + offsets::game_instance );
			defines::local_player = ac::read<tarray>( owning_game_instance + offsets::local_players ).get( 0 );
			defines::local_player_controller = ac::read<std::ptrdiff_t>( local_player + offsets::controller );
			auto local_pawn = ac::read<std::ptrdiff_t>( defines::local_player_controller + offsets::acknowledged_pawn );
			auto local_scene_component = ac::read<std::ptrdiff_t>( local_pawn + offsets::root_component );
			defines::local_pos = ac::read<fvector>( local_scene_component + offsets::relative_location );
			auto local_id = ac::read<int>( local_pawn + 0x18 );
			auto game_state = ac::read<std::ptrdiff_t>( defines::world + offsets::game_state );
			auto actor_cluster = ac::read<tarray>( game_state + offsets::player_array );
			defines::world_time = ac::read<float>( game_state + offsets::server_world_time_seconds_delta );

			for ( int i = 0; i < actor_cluster.count; i++ )
			{
				if ( !actor_cluster.max_count )
					continue;

				data buffer;

				auto state = actor_cluster.get( i );
				if ( !state )
					continue;

				auto current_pawn = ac::read<std::ptrdiff_t>( state + offsets::pawn_private );
				if ( !current_pawn )
					continue;

				auto mesh = ac::read<std::ptrdiff_t>( current_pawn + offsets::mesh );
				if ( !mesh )
					continue;

				auto scene_component = ac::read<std::ptrdiff_t>( current_pawn + offsets::root_component );
				if ( current_pawn == local_pawn || !scene_component )
					continue;

				auto mapped_bones = ac::read<std::ptrdiff_t>( mesh + offsets::bone_array );
				if ( !mapped_bones )
					continue;

				reserved_component_to_world = ac::read<ftransform>( mesh + offsets::component_to_world ).to_matrix( );
				ac::read_memory( mapped_bones, &reserved_transforms, sizeof( reserved_transforms ) );

				buffer.state = state;
				buffer.bone_array = mapped_bones;
				buffer.pawn = current_pawn;
				buffer.mesh = mesh;
				buffer.base = engine::get_bone_location( 0 );
				buffer.head = engine::get_bone_location( 68 );

				target.push_back( buffer );
			}

			submitted_players.clear( );
			for ( auto ei : target )
				submitted_players.push_back( ei );

			std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
		}
	}
}