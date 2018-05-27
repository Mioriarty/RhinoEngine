#include "RigidBody2D.h"

#include "Physics2D.h"

#include "utility\Time.h"

namespace rhino {
	
	RigidBody2D::RigidBody2D(Collider2D* collider, float mass, float gravityScale)
		:collider(collider), invMass(mass > 0.0f ? 1.0f / mass : 0.0f), gravityScale(gravityScale) {
	}

	void RigidBody2D::awake() {
		pos = (Vector2*)&getTransform().getPosition();
		Physics2D::bodies.emplace_back(this);
	}

	void RigidBody2D::finishFrame() {
		velocity += force * invMass;
		*pos += velocity * Time::getDeltaTime();

		force = Physics2D::gravity * gravityScale;
	}
}


