#ifndef Category_h
#define Category_h

namespace Category {
	enum Type {
		None = 0,
		Scene = 1 << 0,
		PlayerAircraft = 1 << 1,
		EnemyAircraft = 1 << 2,
		Collectable = 1 << 3,
	};
}

#endif