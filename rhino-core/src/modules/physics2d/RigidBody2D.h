#pragma once

#include "core\Component.h"

#include "colliders\colliders.h"

namespace rhino {

	class Physics2D;

	class RigidBody2D : Component {
		SIMPLE_GETCOPY_OVERLOAD(RigidBody2D)

		friend class rhino::Physics2D;

		private:
			Collider2D* collider;
			Vector2* pos;
			float invMass;
			float gravityScale;

			Vector2 velocity;
			Vector2 force;

			void finishFrame();

		public:
			RigidBody2D(Collider2D* collider, float mass, float gravityScale = 1.0f);

			virtual void awake() override;

			inline Collider2D* getCollider() const { return collider; }
			inline Vector2* getPosRef() const { return pos; }
	};

}