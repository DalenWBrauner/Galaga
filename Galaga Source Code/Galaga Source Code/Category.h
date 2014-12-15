#ifndef Category_h
#define Category_h

namespace Category {
	enum Type {
		None				= 0,
		Scene				= 1 << 0,
		PlayerAircraft		= 1 << 1,
		AlliedAircraft		= 1 << 2,
		EnemyAircraft		= 1 << 3,
		//Pickup				= 1 << 4,
		AlliedProjectile	= 1 << 4,
		EnemyProjectile		= 1 << 5,

		Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
		Projectile = AlliedProjectile | EnemyProjectile,
	};
}

#endif