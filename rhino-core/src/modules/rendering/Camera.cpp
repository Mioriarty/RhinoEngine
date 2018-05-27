#include "Camera.h"

#include "core/GameObject.h"
#include "core/Graphics.h"

namespace rhino {

	std::vector<Camera*> Camera::cameras;
	unsigned int Camera::mainCamera = 0;

	void Camera::renderAll() {
		if (cameras.size() == 0) {
			std::cout << "No Cameras in this scene" << std::endl;
			return;
		}
		for (unsigned int i = 0; i < cameras.size(); i++) {
			if (i == mainCamera)
				continue;
			cameras[i]->render();
		}

		cameras[mainCamera]->render();
	}

	void Camera::render() const {
		glClearColor(clearColor.getR(), clearColor.getG(), clearColor.getB(), clearColor.getA());
		for (auto& entry1 : Renderer::getAllRenderers()) {
			entry1.first->start();
			entry1.first->loadMat4("viewMatrix", toMatrix());
			for (auto& entry2 : entry1.second) {
				entry2.first->loadAll();
				for (Renderer* renderer : entry2.second) {
					entry1.first->loadMat4("modelMatrix", renderer->getGameObject()->getTransform().toMatrix());
					renderer->render();
				}
			}
			entry1.first->stop();
		}
	}

	Camera::Camera()
		:clearColor(Color::BLACK) {
	}


	void Camera::awake() {
		cameras.push_back(this);
	}

	void Camera::remove() {

		for(unsigned int i = 0; i < cameras.size(); i++)
			if (cameras[i] == this) {
				cameras.erase(cameras.begin() + i);

				return;
			}
	}

	Matrix4 Camera::getViewMatrix() const {
		return MatrixFactory::viewMatrix(gameObject->getTransform().getPosition(), gameObject->getTransform().getRotation());
	}

	Matrix4 Camera::toMatrix() const {
		return getProjectionMatrix() * getViewMatrix();
	}


	Matrix4 PassiveCamera::getProjectionMatrix() const {
		return Matrix4::identity();
	}


	OrthographicCamera::OrthographicCamera(float orthographgicSize, float nearPlane, float farPlane)
		: orthographgicSize(orthographgicSize), nearPlane(nearPlane), farPlane(farPlane) {
	}

	Matrix4 OrthographicCamera::getProjectionMatrix() const {
		return Matrix4::identity();
	}


	ProjectiveCamera::ProjectiveCamera(float fov, float nearPlane, float farPlane)
		: fov(fov), nearPlane(nearPlane), farPlane(farPlane) {
	}

	Matrix4 ProjectiveCamera::getProjectionMatrix() const {
		return MatrixFactory::perspectiveProjectionMatrix(fov, nearPlane, farPlane, (float)Graphics::getWidth() / (float)Graphics::getHeight());
	}
}