//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

inline namespace engine
{
	inline namespace loot
	{
		enum class EFortItemTier : std::uint8_t
		{
			No_Tier = 0,
			I = 1,
			II = 2,
			III = 3,
			IV = 4,
			V = 5,
			VI = 6,
			VII = 7,
			VIII = 8,
			IX = 9,
			X = 10,
			NumItemTierValues = 11,
			EFortItemTier_MAX = 12
		};

		inline ImColor get_item_color( EFortItemTier tier )
		{
			switch ( tier )
			{
			case EFortItemTier::I: // common
				return ImColor( 123, 123, 123 );
			case EFortItemTier::II: // uncommon
				return ImColor( 58, 121, 19 );
			case EFortItemTier::III: // rare
				return ImColor( 18, 88, 162 );
			case EFortItemTier::IV: // epic
				return ImColor( 189, 63, 250 );
			case EFortItemTier::V: // legendary
				return ImColor( 255, 118, 5 );
			case EFortItemTier::VI: // mythic
				return ImColor( 220, 160, 30 );
			case EFortItemTier::VII: // exotic
				return ImColor( 0, 225, 252 );
			default:
				return ImColor( 123, 123, 123 );
			}
		}
	}
}