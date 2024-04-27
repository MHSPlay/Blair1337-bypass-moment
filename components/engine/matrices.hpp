//  _ .--.   .--./) _ .--..--.   
// [ '/'`\ \/ /'`\;[ `.-. .-. |       humbly winning,
//  | \__/ |\ \._// | | | | | |     one line at a time.
//  | ;.__/ .',__` [___||__||__]          [risku]
// [__ | ((__))

#include <list>
#include <unordered_map>
#define rectified_pi 3.14159265358979323846264338327950288419716939937510

enum bones : int
{
	HumanBase = 0,
	HumanPelvis = 2,
	HumanLThigh1 = 71,
	HumanLThigh2 = 77,
	HumanLThigh3 = 72,
	HumanLCalf = 74,
	HumanLFoot = 86,
	HumanLToe = 76,
	HumanRThigh1 = 78,
	HumanRThigh2 = 84,
	HumanRThigh3 = 79,
	HumanRCalf = 81,
	HumanRFoot = 87,
	HumanRToe = 83,
	HumanSpine1 = 7,
	HumanSpine2 = 5,
	HumanSpine3 = 2,
	HumanLCollarbone = 9,
	HumanLUpperarm = 35,
	HumanLForearm1 = 36,
	HumanLForearm23 = 10,
	HumanLForearm2 = 34,
	HumanLForearm3 = 33,
	HumanLPalm = 32,
	HumanRCollarbone = 98,
	HumanRUpperarm = 64,
	HumanRForearm1 = 65,
	HumanRForearm23 = 39,
	HumanRForearm2 = 63,
	HumanRForearm3 = 62,
	HumanRPalm = 58,
	HumanNeck = 67,
	HumanHead = 110,
	HumanChest = 66
};

inline namespace engine
{\
	class fvector2d {
	public:
		fvector2d( ) : x( 0.f ), y( 0.f ) {}
		fvector2d( double x, double y ) : x( x ), y( y ) {}

		fvector2d operator + ( const fvector2d& other ) const { return { this->x + other.x, this->y + other.y }; }
		fvector2d operator - ( const fvector2d& other ) const { return { this->x - other.x, this->y - other.y }; }
		fvector2d operator * ( double scalar ) const { return { this->x * scalar, this->y * scalar }; }
		fvector2d operator / ( double divide ) const { return { this->x / divide, this->y / divide }; }

		fvector2d& operator *= ( const double other ) { this->x *= other; this->y *= other; return *this; }
		fvector2d& operator /= ( const double other ) { this->x /= other; this->y /= other; return *this; }

		fvector2d& operator =  ( const fvector2d& other ) { this->x = other.x; this->y = other.y; return *this; }
		fvector2d& operator += ( const fvector2d& other ) { this->x += other.x; this->y += other.y; return *this; }
		fvector2d& operator -= ( const fvector2d& other ) { this->x -= other.x; this->y -= other.y; return *this; }
		fvector2d& operator *= ( const fvector2d& other ) { this->x *= other.x; this->y *= other.y; return *this; }
		fvector2d& operator /= ( const fvector2d& other ) { this->x /= other.x; this->y /= other.y; return *this; }

		operator bool( )
		{
			return bool( this->x && this->y );
		}

		friend bool operator==( const fvector2d& first, const fvector2d& second )
		{
			return first.x == second.x && first.y == second.y;
		}

		friend bool operator!=( const fvector2d& first, const fvector2d& second )
		{
			return !( first == second );
		}

	public:
		double x = 0.f;
		double y = 0.f;
	};

	class fvector {
	public:
		fvector( ) : x( 0.f ), y( 0.f ), z( 0.f ) {}
		fvector( double x, double y, double z ) : x( x ), y( y ), z( z ) {}

		fvector operator + ( const fvector& other ) const { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
		fvector operator - ( const fvector& other ) const { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
		fvector operator * ( double scalar ) const { return { this->x * scalar, this->y * scalar, this->z * scalar }; }
		fvector operator / ( double divide ) const { return { this->x / divide, this->y / divide, this->z / divide }; }

		fvector& operator *= ( const double other ) { this->x *= other; this->y *= other; this->z *= other; return *this; }
		fvector& operator /= ( const double other ) { this->x /= other; this->y /= other; this->z /= other; return *this; }

		fvector& operator =  ( const fvector& other ) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
		fvector& operator += ( const fvector& other ) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
		fvector& operator -= ( const fvector& other ) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
		fvector& operator *= ( const fvector& other ) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
		fvector& operator /= ( const fvector& other ) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

		float dist( const fvector& vector ) const {
			double dx = this->x - vector.x;
			double dy = this->y - vector.y;
			double dz = this->z - vector.z;
			return std::sqrt( dx * dx + dy * dy + dz * dz );
		}
		float dot( const fvector& vector ) { return x * vector.x + y * vector.y + z * vector.z; }
		operator bool( )
		{
			return bool( this->x && this->y && this->z );
		}

		friend bool operator==( const fvector& first, const fvector& second )
		{
			return first.x == second.x && first.y == second.y && first.z == second.z;
		}

		friend bool operator!=( const fvector& first, const fvector& second )
		{
			return !( first == second );
		}

	public:
		double x = 0;
		double y = 0;
		double z = 0;
	};

	struct FQuat
	{
	public:

		/** Holds the quaternion's X-component. */
		float x;

		/** Holds the quaternion's Y-component. */
		float y;

		/** Holds the quaternion's Z-component. */
		float z;

		/** Holds the quaternion's W-component. */
		float w;
	};

	struct
	{
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);
	}monitor;



	struct fplane : fvector
	{
		fplane( ) : fvector( ), w( ) {}
		fplane( double x, double y, double z, double w ) : fvector( x, y, z ), w( w ) {}

		double w;
	};

	struct fmatrix
	{
		fmatrix( ) : xplane( ), yplane( ), zplane( ), wplane( ) {}
		fmatrix( fplane xplane, fplane yplane, fplane zplane, fplane wplane ) : xplane( xplane ), yplane( yplane ), zplane( zplane ), wplane( wplane ) {}

		fplane xplane, yplane, zplane, wplane;

		fmatrix matrix_multiplication( fmatrix other )
		{
			fmatrix multiplicated_matrix = {};

			multiplicated_matrix.wplane.x = this->wplane.x * other.xplane.x + this->wplane.y * other.yplane.x + this->wplane.z * other.zplane.x + this->wplane.w * other.wplane.x;
			multiplicated_matrix.wplane.y = this->wplane.x * other.xplane.y + this->wplane.y * other.yplane.y + this->wplane.z * other.zplane.y + this->wplane.w * other.wplane.y;
			multiplicated_matrix.wplane.z = this->wplane.x * other.xplane.z + this->wplane.y * other.yplane.z + this->wplane.z * other.zplane.z + this->wplane.w * other.wplane.z;
			multiplicated_matrix.wplane.w = this->wplane.x * other.xplane.w + this->wplane.y * other.yplane.w + this->wplane.z * other.zplane.w + this->wplane.w * other.wplane.w;

			return multiplicated_matrix;
		}
	};

	struct ftransform
	{
		ftransform( ) : rotation( ), translation( ), scale3d( ), pad_38( ), pad_58( ) {}
		ftransform( fplane rotation, fvector translation, fvector scale3d ) : rotation( rotation ), translation( translation ), scale3d( scale3d ), pad_38( ), pad_58( ) {}

		fplane rotation;
		fvector translation;
		char pad_38[0x8];
		fvector scale3d;
		char pad_58[0x8];

		fmatrix to_matrix( )
		{
			fmatrix matrix = {};

			double x2 = this->rotation.x * 2;
			double y2 = this->rotation.y * 2;
			double z2 = this->rotation.z * 2;

			double xx2 = this->rotation.x * x2;
			double yy2 = this->rotation.y * y2;
			double zz2 = this->rotation.z * z2;

			double yz2 = this->rotation.y * z2;
			double wx2 = this->rotation.w * x2;

			double xy2 = this->rotation.x * y2;
			double wz2 = this->rotation.w * z2;

			double xz2 = this->rotation.x * z2;
			double wy2 = this->rotation.w * y2;

			matrix.xplane.x = ( 1.0 - ( yy2 + zz2 ) ) * this->scale3d.x;
			matrix.xplane.y = ( xy2 + wz2 ) * this->scale3d.x;
			matrix.xplane.z = ( xz2 - wy2 ) * this->scale3d.x;

			matrix.yplane.x = ( xy2 - wz2 ) * this->scale3d.y;
			matrix.yplane.y = ( 1.0 - ( xx2 + zz2 ) ) * this->scale3d.y;
			matrix.yplane.z = ( yz2 + wx2 ) * this->scale3d.y;

			matrix.zplane.x = ( xz2 + wy2 ) * this->scale3d.z;
			matrix.zplane.y = ( yz2 - wx2 ) * this->scale3d.z;
			matrix.zplane.z = ( 1.0 - ( xx2 + yy2 ) ) * this->scale3d.z;

			matrix.wplane.x = this->translation.x;
			matrix.wplane.y = this->translation.y;
			matrix.wplane.z = this->translation.z;

			matrix.wplane.w = 1.0;

			return matrix;
		}
	};

	class frotator {
	public:
		frotator( ) : pitch( 0.f ), yaw( 0.f ), roll( 0.f ) {}
		frotator( double pitch, double yaw ) : pitch( pitch ), yaw( yaw ), roll( 0.f ) {}
		frotator( double pitch, double yaw, double roll ) : pitch( pitch ), yaw( yaw ), roll( roll ) {}

		frotator operator + ( const frotator& other ) const { return { this->pitch + other.pitch, this->yaw + other.yaw, this->roll + other.roll }; }
		frotator operator - ( const frotator& other ) const { return { this->pitch - other.pitch, this->yaw - other.yaw, this->roll - other.roll }; }
		frotator operator * ( double scalar ) const { return { this->pitch * scalar, this->yaw * scalar, this->roll * scalar }; }
		frotator operator / ( double divide ) const { return { this->pitch / divide, this->yaw / divide, this->roll / divide }; }

		frotator& operator *= ( const double other ) { this->yaw *= other; this->pitch *= other; this->roll *= other; return *this; }
		frotator& operator /= ( const double other ) { this->yaw /= other; this->pitch /= other; this->roll /= other; return *this; }

		frotator& operator =  ( const frotator& other ) { this->pitch = other.pitch; this->yaw = other.yaw; this->roll = other.roll; return *this; }
		frotator& operator += ( const frotator& other ) { this->pitch += other.pitch; this->yaw += other.yaw; this->roll += other.roll; return *this; }
		frotator& operator -= ( const frotator& other ) { this->pitch -= other.pitch; this->yaw -= other.yaw; this->roll -= other.roll; return *this; }
		frotator& operator *= ( const frotator& other ) { this->pitch *= other.pitch; this->yaw *= other.yaw; this->roll *= other.roll; return *this; }
		frotator& operator /= ( const frotator& other ) { this->pitch /= other.pitch; this->yaw /= other.yaw; this->roll /= other.roll; return *this; }

		fmatrix to_matrix( )
		{
			fmatrix matrix = {};

			double _pitch = ( this->pitch * rectified_pi / 180 );
			double _yaw = ( this->yaw * rectified_pi / 180 );
			double _roll = ( this->roll * rectified_pi / 180 );

			double sp = sin( _pitch );
			double cp = cos( _pitch );
			double sy = sin( _yaw );
			double cy = cos( _yaw );
			double sr = sin( _roll );
			double cr = cos( _roll );

			matrix.xplane.x = cp * cy;
			matrix.xplane.y = cp * sy;
			matrix.xplane.z = sp;

			matrix.yplane.x = sr * sp * cy - cr * sy;
			matrix.yplane.y = sr * sp * sy + cr * cy;
			matrix.yplane.z = -sr * cp;

			matrix.zplane.x = -( cr * sp * cy + sr * sy );
			matrix.zplane.y = cy * sr - cr * sp * sy;
			matrix.zplane.z = cr * cp;

			matrix.wplane.w = 1.0;

			return matrix;
		}

		operator bool( )
		{
			return bool( this->pitch && this->yaw && this->roll );
		}

		friend bool operator==( const frotator& first, const frotator& second )
		{
			return first.pitch == second.pitch && first.yaw == second.yaw && first.roll == second.roll;
		}

		friend bool operator!=( const frotator& first, const frotator& second )
		{
			return !( first == second );
		}

	public:
		double pitch = 0.f;
		double yaw = 0.f;
		double roll = 0.f;
	};

	struct fminimalviewinfo
	{
		fminimalviewinfo( ) : loc( ), rot( ), FOV( FOV ) {}
		fminimalviewinfo( fvector Location, fvector Rotation, float FOV ) : loc( Location ), rot( Rotation ), FOV( FOV ) {}

		fvector loc;
		fvector rot;
		float FOV;
	};

	inline fminimalviewinfo get_camera( )
	{
		fminimalviewinfo camera;
		auto location_pointer = ac::read<uintptr_t>( defines::world + 0x110 );
		auto rotation_pointer = ac::read<uintptr_t>( defines::world + 0x120 );

		struct rotation_info
		{
			double pitch;
			char pad_0008[24];
			double yaw;
			char pad_0028[424];
			double roll;
		} rotationInfo;

		rotationInfo.pitch = ac::read<double>( rotation_pointer );
		rotationInfo.yaw = ac::read<double>( rotation_pointer + 0x20 );
		rotationInfo.roll = ac::read<double>( rotation_pointer + 0x1D0 );

		camera.loc = ac::read<fvector>( location_pointer );
		camera.rot.x = asin( rotationInfo.roll ) * ( 180.0 / rectified_pi );
		camera.rot.y = ( ( atan2( rotationInfo.pitch * -1, rotationInfo.yaw ) * ( 180.0 / rectified_pi ) ) * -1 ) * -1;
		camera.FOV = ac::read<float>( defines::local_player + 0x4cc );

		return camera;
	}

	struct FTransform
	{
		FQuat Rotation;
		fvector Translation;
		uint32_t pad0001;
		fvector Scale3D;
		uint32_t pad0002;

		FTransform( ) : Rotation { ( 0.f, 0.f, 0.f, 0.f ) }, Translation( 0.f, 0.f, 0.f ), Scale3D( 0.f, 0.f, 0.f ), pad0001( 0 ), pad0002( 0 ) { }

		FTransform( const FQuat& rot, const fvector& translation, const fvector& scale )
		{

			Rotation = rot;
			Translation = translation;
			Scale3D = scale;

			pad0001 = 0;
			pad0002 = 0;
		}

		inline D3DMATRIX ToMatrixWithScale( )
		{

			D3DMATRIX m;

			m._41 = Translation.x;
			m._42 = Translation.y;
			m._43 = Translation.z;

			float x2 = Rotation.x + Rotation.x;
			float y2 = Rotation.y + Rotation.y;
			float z2 = Rotation.z + Rotation.z;

			float xx2 = Rotation.x * x2;
			float yy2 = Rotation.y * y2;
			float zz2 = Rotation.z * z2;
			m._11 = ( 1.0f - ( yy2 + zz2 ) ) * Scale3D.x;
			m._22 = ( 1.0f - ( xx2 + zz2 ) ) * Scale3D.y;
			m._33 = ( 1.0f - ( xx2 + yy2 ) ) * Scale3D.z;


			float yz2 = Rotation.y * z2;
			float wx2 = Rotation.w * x2;
			m._32 = ( yz2 - wx2 ) * Scale3D.z;
			m._23 = ( yz2 + wx2 ) * Scale3D.y;


			float xy2 = Rotation.x * y2;
			float wz2 = Rotation.w * z2;
			m._21 = ( xy2 - wz2 ) * Scale3D.y;
			m._12 = ( xy2 + wz2 ) * Scale3D.x;


			float xz2 = Rotation.x * z2;
			float wy2 = Rotation.w * y2;
			m._31 = ( xz2 + wy2 ) * Scale3D.z;
			m._13 = ( xz2 - wy2 ) * Scale3D.x;

			m._14 = 0.0f;
			m._24 = 0.0f;
			m._34 = 0.0f;
			m._44 = 1.0f;

			return m;
		}
	};

	inline D3DMATRIX multiply_matrix( D3DMATRIX pM1, D3DMATRIX pM2 )
	{
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

		return pOut;
	}

	inline D3DXMATRIX spot_matrix( fvector rot, fvector origin = fvector( 0, 0, 0 ) )
	{
		float radPitch = ( rot.x * float( rectified_pi ) / 180.f );
		float radYaw = ( rot.y * float( rectified_pi ) / 180.f );
		float radRoll = ( rot.z * float( rectified_pi ) / 180.f );

		float SP = sinf( radPitch );
		float CP = cosf( radPitch );
		float SY = sinf( radYaw );
		float CY = cosf( radYaw );
		float SR = sinf( radRoll );
		float CR = cosf( radRoll );
		D3DMATRIX matrix;
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;
		matrix.m[0][3] = 0.f;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;
		matrix.m[1][3] = 0.f;

		matrix.m[2][0] = -( CR * SP * CY + SR * SY );
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;
		matrix.m[2][3] = 0.f;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}

	inline fminimalviewinfo scheduled_view_point;
	inline bool world_to_screen( fvector world, fvector* screen )
	{
		scheduled_view_point = get_camera( );
		D3DMATRIX tempMatrix = spot_matrix( scheduled_view_point.rot );
		fvector vAxisX = fvector( tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2] );
		fvector vAxisY = fvector( tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2] );
		fvector vAxisZ = fvector( tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2] );
		fvector vDelta = world - scheduled_view_point.loc;
		fvector vTransformed = fvector( vDelta.dot( vAxisY ), vDelta.dot( vAxisZ ), vDelta.dot( vAxisX ) );
		if ( vTransformed.z < 1.f )
			vTransformed.z = 1.f;

		auto buff = fvector2d( ( defines::width / 2.0f ) + vTransformed.x * ( ( ( defines::width / 2.0f ) / tanf( scheduled_view_point.FOV * ( float ) rectified_pi / 360.f ) ) ) / vTransformed.z, ( defines::height / 2.0f ) - vTransformed.y * ( ( ( defines::width / 2.0f ) / tanf( scheduled_view_point.FOV * ( float ) rectified_pi / 360.f ) ) ) / vTransformed.z );
		screen->x = buff.x;
		screen->y = buff.y;

		return true;
	}


	struct tarray
	{
		std::uintptr_t array;
		std::uint32_t count;
		std::uint32_t max_count;

		std::uintptr_t get( std::uint32_t index )
		{
			return ac::read<std::uintptr_t>( array + ( index * 0x8 ) );
		}
	};

	inline std::string player_name_private( __int64 PlayerState )
	{
		auto fstring = ac::read<__int64>( PlayerState + 0xAF0 );
		auto length = ac::read<int>( fstring + 16 );

		auto v6 = ( __int64 ) length;

		if ( !v6 ) return std::string( _( "BOT / AI" ) );

		auto ftext = ( uintptr_t ) ac::read<__int64>( fstring + 8 );

		wchar_t* buffer = new wchar_t[length];
		ac::read_memory( ftext, buffer, length * sizeof( wchar_t ) );

		char v21;
		int v22;
		int i;

		int v25;
		UINT16* v23;

		v21 = v6 - 1;
		if ( !( UINT32 ) v6 )
			v21 = 0;
		v22 = 0;
		v23 = ( UINT16* ) buffer;
		for ( i = ( v21 ) & 3; ; *v23++ += i & 7 )
		{
			v25 = v6 - 1;
			if ( !( UINT32 ) v6 )
				v25 = 0;
			if ( v22 >= v25 )
				break;
			i += 3;
			++v22;
		}

		std::wstring username { buffer };
		delete[] buffer;
		return std::string( username.begin( ), username.end( ) );
	}

	static fmatrix reserved_component_to_world = {};
	static ftransform reserved_transforms[100] = {};
	inline fvector get_bone_location( int bone_id )
	{
		fmatrix matrix = reserved_transforms[bone_id].to_matrix( ).matrix_multiplication( reserved_component_to_world );

		return fvector( matrix.wplane.x, matrix.wplane.y, matrix.wplane.z );
	}


	inline bool skeletons( )
	{
		std::list<int> upper_part = { bones::HumanNeck,bones::HumanHead };
		std::list<int> right_arm = { bones::HumanNeck,bones::HumanChest,bones::HumanRUpperarm,bones::HumanRForearm1,bones::HumanRForearm23,bones::HumanRPalm };
		std::list<int> left_arm = { bones::HumanNeck,bones::HumanChest,bones::HumanLUpperarm,bones::HumanLForearm1,bones::HumanLForearm23,bones::HumanLPalm };
		std::list<int> spine = { bones::HumanChest,bones::HumanSpine1,bones::HumanSpine2,bones::HumanSpine3 };

		std::list<int> lower_right = { bones::HumanPelvis,bones::HumanRThigh1,bones::HumanRThigh2,bones::HumanRThigh3,bones::HumanRCalf,bones::HumanRFoot };
		std::list<int> lower_left = { bones::HumanPelvis,bones::HumanLThigh1,bones::HumanLThigh2,bones::HumanLThigh3,bones::HumanLCalf,bones::HumanLFoot };
		std::list<std::list<int>> skeleton = { upper_part, right_arm, left_arm, spine, lower_right, lower_left };

		fvector previous( 0, 0, 0 );
		fvector current;
		auto p1 = fvector( 0, 0,0 );
		auto c1 = fvector( 0, 0 , 0);
		auto neckpos = get_bone_location( bones::HumanNeck );
		auto pelvispos = get_bone_location( bones::HumanPelvis );

		for ( auto a : skeleton ) {
			previous = fvector( 0, 0, 0 );
			for ( int bone : a ) {
				ImColor Color = { 0,255,255, 255 };

				current = current = bone == bones::HumanNeck ? neckpos : ( bone == bones::HumanPelvis ? pelvispos : get_bone_location( bone ) );
				if ( previous.x == 0.f ) {
					previous = current;
					continue;
				}

				if ( world_to_screen( current, &c1 ) && world_to_screen( previous, &p1 ) ) {
					ImGui::GetBackgroundDrawList( )->AddLine( ImVec2( p1.x, p1.y ), ImVec2( c1.x, c1.y ), Color, 1 );
					previous = current;
				}
			}
		}
	}


	inline std::string get_weapon_name(uintptr_t actor)
	{
		uintptr_t current_weapon = ac::read<uintptr_t>(actor + 0xa20);

		uint64_t weapon_data = ac::read<uint64_t>(current_weapon + 0x4d0);
		if (!weapon_data) return "";
		uint64_t fname_text = ac::read<uint64_t>(weapon_data + 0x38);
		if (!fname_text) return "";
		uint32_t name_length = ac::read<uint32_t>(fname_text + 0x30);
		if (!name_length) return "";
		wchar_t* WeaponName = new wchar_t[uint64_t(name_length) + 1];

		// Pass the pointer directly without casting
		ac::read_memory((uintptr_t(ac::read<uintptr_t>(fname_text + 0x28))), WeaponName, name_length * sizeof(wchar_t));

		std::wstring wWeaponName(WeaponName);
		delete[] WeaponName; // Remember to deallocate memory allocated with new
		return std::string(wWeaponName.begin(), wWeaponName.end());
	}




	inline std::string decrypt_ansi( int key )
	{
		uint32_t chunk = ( uint32_t ) ( ( int ) ( key ) >> 16 );
		uint16_t name = ( uint16_t ) key;
		uint64_t name_pool_chunk = ac::read<uint64_t>( defines::image + offsets::g::names + ( 8 * chunk ) + 16 ) + ( unsigned int ) ( 2 * name );
		uint16_t name_entry = ac::read<uint16_t>( name_pool_chunk );
		int name_len = name_entry >> 6;
		char buff[1024] = {};

		char* v2 = buff; // rdi
		unsigned int v5 = name_len; // eax
		int v4; // ebx
		int16_t result; // ax
		int v6; // edx
		int v7; // ecx
		int v8; // eax
		unsigned int v9; // ecx

		v4 = 9;
		if ( v5 )
		{
			v6 = v5;
			do
			{
				v5 = v4 + ~*v2;
				v4 += 7947;
				*v2++ = v5;
				--v6;
			} while ( v6 );
			return std::string( buff );
		}

		buff[name_len] = '\0';
		return std::string( "" );
	}

	inline std::string get_object_name( int key )
	{
		uint32_t chunk = ( uint32_t ) ( ( int ) ( key ) >> 16 );
		uint16_t name = ( uint16_t ) key;

		uint64_t name_pool_chunk = ac::read<uint64_t>( defines::image + offsets::g::world + ( 8 * chunk ) + 16 ) + ( unsigned int ) ( 2 * name ); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
		if ( ac::read<uint16_t>( name_pool_chunk ) < 64 )
		{
			auto a1 = ac::read<DWORD>( name_pool_chunk + 2 );
			return decrypt_ansi( a1 );
		}
		else
		{
			return decrypt_ansi( key );
		}
	}
}