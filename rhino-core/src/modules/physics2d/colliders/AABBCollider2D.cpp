#include "AABBCollider2D.h"

#include <cmath>

namespace rhino {

	AABBCollider2D::AABBCollider2D(float width, float height)
		:Collider2D(sqrtf((width * width + height * height) * 0.25f)), width(width), height(height) {
	}


	Collider2D::ColliderType AABBCollider2D::getColliderType() const {
		return Collider2D::ColliderType::AABB;
	}

}