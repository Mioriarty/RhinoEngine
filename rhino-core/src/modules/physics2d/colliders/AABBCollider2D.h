#pragma once

#include "Collider2D.h"

namespace rhino {

	class AABBCollider2D : public Collider2D {

		private:
			float width, height;

		public:
			AABBCollider2D(float width, float height);

			virtual ColliderType getColliderType() const override;

			inline float getWidth() const { return width; }
			inline float getHeight() const { return height; }

	};

}
