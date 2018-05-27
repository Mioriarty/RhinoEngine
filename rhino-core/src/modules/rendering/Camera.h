#pragma once

#include <vector>
#include "core/Component.h"
#include "Renderer.h"
#include "maths\maths.h"

namespace rhino {

	class Camera : public Component {

		private:
			static std::vector<Camera*> cameras;
			static unsigned int mainCamera;

		public:
			static void renderAll();
			static const Camera& getMainCamera() { return *(cameras[mainCamera]); };

		private:
			Color clearColor;

			void render() const;

		protected:

			void awake();
			void remove();

		public:
			Camera(/*float fovOrOrthographicSize, float nearPlane = 0.0001f, float farPlane = 10000.0f*/);

			Matrix4 getViewMatrix() const;
			virtual Matrix4 getProjectionMatrix() const = 0;
			Matrix4 toMatrix() const;

			inline const Color& getClearColor() const { return clearColor; }
			inline void setClearColor(const Color& color) { clearColor = color; };
	};

	class PassiveCamera : public Camera {
		SIMPLE_GETCOPY_OVERLOAD(PassiveCamera)

		public:
			PassiveCamera() = default;

			virtual Matrix4 getProjectionMatrix() const override;
	};

	class OrthographicCamera : public Camera {

		SIMPLE_GETCOPY_OVERLOAD(OrthographicCamera)

		private:
			float orthographgicSize, nearPlane, farPlane;

		public:
			OrthographicCamera(float orthographgicSize, float nearPlane, float farPlane);

			virtual Matrix4 getProjectionMatrix() const override;

	};

	class ProjectiveCamera : public Camera {

		SIMPLE_GETCOPY_OVERLOAD(ProjectiveCamera)

		private:
			float fov, nearPlane, farPlane;

		public:
			ProjectiveCamera(float fov, float nearPlane, float farPlane);

			virtual Matrix4 getProjectionMatrix() const override;

	};

}