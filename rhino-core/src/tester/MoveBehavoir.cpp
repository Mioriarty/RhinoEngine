#include "MoveBehavoir.h"

#include "modules\rendering\Camera.h"
#include "utility\Input.h"
#include "core\GameObject.h"
#include "utility\Time.h"

void MoveBehavoir::awake() {
	std::cout << "AWAKE" << std::endl;
}

void MoveBehavoir::update() {

	float move = movementSpeed * Time::getDeltaTime();
	float rotation = rotationSpeed * Time::getDeltaTime();

	if (Input::isKeyPressed(Input::Key::SPACE)) {
		getTransform().translate({ 0.0f, move, 0.0f });
	}

	if (Input::isKeyPressed(Input::Key::LEFT_SHIFT)) {
		getTransform().translate({ 0.0f, -move, 0.0f });
	}

	if (Input::isKeyPressed(Input::Key::A)) {
		getTransform().rotate(Quaternion::axisAngle({ 0.0f, 1.0f, 0.0f }, rotation));
	}

	if (Input::isKeyPressed(Input::Key::D)) {
		getTransform().rotate(Quaternion::axisAngle({ 0.0f, 1.0f, 0.0f }, -rotation));
	}

	if (Input::isKeyPressed(Input::Key::W)) {
		getTransform().translate({ 0.0f, 0.0f, -move }, TransformScope::LOCAL);
	}

	
	if (Input::isKeyPressed(Input::Key::S)) {
		getTransform().translate({ 0.0f, 0.0f, move }, TransformScope::LOCAL);
		Camera* c = gameObject->getComponent<ProjectiveCamera>();
		c->setClearColor(Color::BLUE);
	}

	getTransform().rotate(Quaternion::axisAngle({ 1.0f, 0.0f, 0.0f }, Input::getScroll()[1] * 2.0f));

	
	
}