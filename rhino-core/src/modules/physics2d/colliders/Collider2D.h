#pragma once

#define PHY_2D_EPS 0.00001f

namespace rhino {

	class Collider2D {

		protected:

			Collider2D(float maxCollisionDistance)
				:maxCollisionDistance(maxCollisionDistance + PHY_2D_EPS) {
			}

			float maxCollisionDistance;

		public:

			enum class ColliderType {
				CIRCLE, AABB
			};
			
			virtual ColliderType getColliderType() const = 0;

			inline float getMaxCollisionDistance() const { return maxCollisionDistance; }
	};


}
