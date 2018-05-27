#include "CircleCollider2D.h"

namespace rhino {

	CircleCollider2D::CircleCollider2D(float radius)
		: Collider2D(radius + PHY_2D_EPS), radius(radius){
	}


	Collider2D::ColliderType CircleCollider2D::getColliderType() const {
		return Collider2D::ColliderType::CIRCLE;
	}

}