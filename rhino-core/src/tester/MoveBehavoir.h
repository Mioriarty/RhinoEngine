#pragma once

#include "core\Component.h"

using namespace rhino;

class MoveBehavoir : public Component {

	SIMPLE_GETCOPY_OVERLOAD(MoveBehavoir)

	public:

		float movementSpeed, rotationSpeed;

		void awake() override;

		void update() override;

};