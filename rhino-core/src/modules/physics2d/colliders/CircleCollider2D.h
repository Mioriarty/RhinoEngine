#pragma once

#include "Collider2D.h"

namespace rhino {

	class CircleCollider2D : Collider2D {

		private:
			float radius;
		
		public:
			CircleCollider2D(float radius);

			virtual ColliderType getColliderType() const override;

			inline float getRadius() const { return radius; }

	};

}
