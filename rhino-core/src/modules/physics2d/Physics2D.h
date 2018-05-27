#pragma once

#include <list>

#include "core\Module.h"

#include "RigidBody2D.h"

namespace rhino {


	class Physics2D {

		friend class rhino::RigidBody2D;

		public:
			static const Module module;

		private:
			static Vector2 gravity;

			static std::list<RigidBody2D*> bodies;

			static void computePhysics();

			
			static void collide(RigidBody2D* b1, RigidBody2D* b2);

			static void collideCircleCircle(RigidBody2D* b1, RigidBody2D* b2);
			static void collideCircleAABB(RigidBody2D* b1, RigidBody2D* b2);
			static void collideAABBAABB(RigidBody2D* b1, RigidBody2D* b2);

			static void resolveCollision(RigidBody2D* b1, RigidBody2D* b2, const Vector2& normal);
		
	};



	



}
