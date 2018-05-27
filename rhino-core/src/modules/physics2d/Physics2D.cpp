#include "Physics2D.h"


namespace rhino {

	Vector2 Physics2D::gravity = { 0.0f, -9.81f };

	const Module Physics2D::module = { "Physics2D", nullptr, nullptr, Physics2D::computePhysics, nullptr, nullptr };

	std::list<RigidBody2D*> Physics2D::bodies;

	void Physics2D::computePhysics() {
		for (auto body1 = bodies.begin(); body1 != bodies.end(); body1 = ++body1) {
			Vector2* pos1 = (*body1)->getPosRef();

			for (auto body2 = std::next(body1); body2 != bodies.end(); body2 = ++body2) {
				Vector2* pos2 = (*body2)->getPosRef();

				float maxColDist = (*body1)->getCollider()->getMaxCollisionDistance() + (*body2)->getCollider()->getMaxCollisionDistance();
				maxColDist *= maxColDist;

				float bodyDist = (*pos2 - *pos1).magnitudeSqr();

				if (maxColDist > bodyDist){
					std::cout << "Colliding: " << *body1 << " with " << *body2 << std::endl;
					collide(*body1, *body2);
				}
				
			}
		}

		for(auto body : bodies)
			body->finishFrame();
	}

	void Physics2D::collide(RigidBody2D* b1, RigidBody2D* b2) {
		Collider2D::ColliderType c1 = b1->getCollider()->getColliderType();
		Collider2D::ColliderType c2 = b2->getCollider()->getColliderType();

		if (c1 == Collider2D::ColliderType::CIRCLE) {

			if (c2 == Collider2D::ColliderType::CIRCLE)
				collideCircleCircle(b1, b2);
			else if (c2 == Collider2D::ColliderType::AABB)
				collideCircleAABB(b1, b2);

		} else if (c1 == Collider2D::ColliderType::AABB) {

			if (c2 == Collider2D::ColliderType::CIRCLE)
				collideCircleAABB(b2, b1);
			else if (c2 == Collider2D::ColliderType::AABB)
				collideAABBAABB(b1, b2);
		}
	}

	void Physics2D::collideCircleCircle(RigidBody2D* b1, RigidBody2D* b2) {
		float distSqr = (*b2->getPosRef() - *b1->getPosRef()).magnitudeSqr();
		float radii = ((CircleCollider2D*)b1->getCollider())->getRadius() + ((CircleCollider2D*)b2->getCollider())->getRadius();

		if (radii * radii < distSqr)
			return;

		Vector2 normal = (*b2->getPosRef() - *b1->getPosRef()).normalized();

		resolveCollision(b1, b2, normal);
	}

	void Physics2D::collideCircleAABB(RigidBody2D* b1, RigidBody2D* b2) {
	}

	void Physics2D::collideAABBAABB(RigidBody2D* b1, RigidBody2D* b2) {
		Vector2 normal;

		Vector2& pos1 = *b1->getPosRef();
		Vector2& pos2 = *b2->getPosRef();

		AABBCollider2D& c1 = *(AABBCollider2D*)b1->getCollider();
		AABBCollider2D& c2 = *(AABBCollider2D*)b2->getCollider();

		if (!(doRangesOverlap(pos1[0] - c1.getWidth() * 0.5f, pos1[0] + c1.getWidth() * 0.5f, pos2[0] - c2.getWidth() * 0.5f, pos2[0] + c2.getWidth() * 0.5f))
			&& doRangesOverlap(pos1[1] - c1.getHeight() * 0.5f, pos1[1] + c1.getHeight() * 0.5f, pos2[1] - c2.getHeight() * 0.5f, pos2[1] + c2.getHeight() * 0.5f))
			return;

		resolveCollision(b1, b2, normal);
	}


	void Physics2D::resolveCollision(RigidBody2D* b1, RigidBody2D* b2, const Vector2& normal) {
		Vector2 relVelocity = b2->velocity - b1->velocity;

		float velAlongNormal = relVelocity.dot(normal);

		if (velAlongNormal > 0.0f)
			return; // Objects are seperating

		float restitution = 1.0f; // bouncyness

		float j = -(1 + restitution) * velAlongNormal * (b1->invMass + b2->invMass);

		Vector2 force = normal * j;

		b1->force -= force;
		b2->force += force;
	}

}