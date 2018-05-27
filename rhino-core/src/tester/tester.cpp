#define PLATFORM_DESCTOP

#include <iostream>

#include "modules\rendering\rendering.h"
#include "modules\physics2d\Physics2D.h"

#include "maths\maths.h"
#include "utility\Time.h"
#include "core\Application.h"
#include "modules/rendering\Camera.h"
#include "utility\Input.h"

#include "MoveBehavoir.h"


#define LOG(s) std::cout << s << std::endl


rhino::ShaderProgram* cubeShader;
rhino::ShaderProgram* texShader;
rhino::GameObject* objMesh;
rhino::GameObject* objCam;

rhino::GameObject* objPhy;

bool loadFunc() {
	using namespace rhino;

	std::vector<Mesh::Vertex> v = {
		{ { -0.5f, -0.5f, 0.0f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f } },
		{ { -0.5f,  0.5f, 0.0f },{ 0.0f, 1.0f },{ 0.0f, 0.0f, 0.0f } },
		{ { 0.5f,  0.5f, 0.0f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, 0.0f } },
		{ { 0.5f, -0.5f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 0.0f, 0.0f } }
	};

	std::vector<unsigned int> indeces = {
		0, 1, 2,
		0, 2, 3
	};

	glEnable(GL_DEPTH_TEST);

	cubeShader = ShaderProgram::compileProgram("res/shader/cube.shader");
	texShader = ShaderProgram::compileProgram("res/shader/simpleTexture.shader");

	GameObject Cam("Cam");
	Cam.getTransform().setPosition({0.0f, 0.0f, -3.0f});
	ProjectiveCamera trueCam(70.0f, 0.0001f, 100000.0f);
	trueCam.setClearColor(Color(0.1f, 0.4f, 1.0f, 1.0f));
	Cam.addComponent(trueCam);

	MoveBehavoir moveBehavior;
	moveBehavior.movementSpeed = 10.0f;
	moveBehavior.rotationSpeed = 100.0f;
	Cam.addComponent(moveBehavior);


	objCam = GameObject::instantiate(Cam);

	GameObject meshPrefab("Rotating Mesh");
	meshPrefab.getTransform().translate({ 0.0f, -0.3f, -4.0f });
	meshPrefab.getTransform().setRotation(Quaternion::axisAngle({ 1.0f, -2.0f, 0.0f }, 45.0f));
	const Mesh& mesh = Mesh::createStandartMesh<Mesh::StandartMesh::CUBE>();
	RenderableData trueData = mesh.createRenderableData();
	Material mat(cubeShader);
	mat.setProperty("brightness", 1.0f);
	Texture* tex = new Texture("res/textures/grass.jpg");
	Texture* stancil = new Texture("res/textures/test.png");
	mat.setProperty("tex", *tex);
	mat.setProperty("stancil", *stancil);

	Renderer renderer(mat, trueData);
	meshPrefab.addComponent(&renderer);
	objMesh = GameObject::instantiate(meshPrefab);

	meshPrefab.setName("MEsh2");

	GameObject::instantiate(meshPrefab)->getTransform().setPosition({ 0.0f, -0.3f, 4.0f });

	GameObject objPlane;
	objPlane.getTransform().setPosition({ -5.0f, -1.0f, -5.0f });
	objPlane.getTransform().setScale({ 10.0f, 1.0f, 10.0f });

	RenderableData plane = Mesh::createStandartMesh<Mesh::StandartMesh::PLANE>().createRenderableData();
	Material texMat(texShader);
	texMat.setProperty("image", *tex);

	Renderer texRenderer(texMat, plane);
	objPlane.addComponent(texRenderer);

	GameObject::instantiate(objPlane);


	GameObject phy1("Physic1");
	RigidBody2D rb((Collider2D*)new CircleCollider2D(1.0f), 1.0f, 0.0001f);
	phy1.getTransform().translate({ 0.01f, 5.0f, 0.0f });
	phy1.addComponent(rb);
	objPhy = GameObject::instantiate(phy1);

	GameObject phy2("Physic2");
	RigidBody2D rb2((Collider2D*)new CircleCollider2D(1.5f), 0.0f, 0.0f);
	phy2.addComponent(rb2);
	GameObject::instantiate(phy2);

	return true;
}

float rotation = 0.0f;

void update() {
	//objMesh->getTransform().translate({ 0.0f, 0.0f, 0.0001f });
	objMesh->getTransform().setRotation(rhino::Quaternion::eulerAngles({ rotation += 0.05f, rotation, rotation }));

	LOG(objPhy->getTransform().getPosition());
	
}


int main() {

	using namespace rhino;

	Application::loadModule(Graphics::module);
	Application::loadModule(Physics2D::module);

	rhino::Application::AppProperties properties = { "HOPE", 500, 500, "1.0" };

	rhino::Application::start(properties, loadFunc, update);


	return 0;
}