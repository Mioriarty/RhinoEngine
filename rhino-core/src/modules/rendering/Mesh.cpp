#include "Mesh.h"
#include <iostream>

namespace rhino {

	void RenderableData::bind() const {
		vao.bind();
		ibo.bind();
	}

	void RenderableData::unbind() const {
		ibo.unbind();
		vao.unbind();
	}

	
	Mesh			Mesh::standartMeshes[3];
	unsigned int	Mesh::createdStandartMeshes = 0;

	Mesh::Mesh(const std::vector<Mesh::Vertex>& vertecies, const std::vector<unsigned int>& indecies)
		: vertecies(vertecies), indecies(indecies) {
	}

	RenderableData Mesh::createRenderableData() const {
		const void* data = (const void*)&vertecies[0];

		Vbo vbo = Vbo::createVbo(data, vertecies.size() * sizeof(Mesh::Vertex));
		
		VboLayout layout;
		layout.pushFloat(3);
		layout.pushFloat(2);
		layout.pushFloat(3);


		RenderableData stm = { Vao::createVao(), Ibo::createIbo(&indecies[0], indecies.size()) };

		stm.vao.addBuffer(vbo, layout);

		return stm;
	}



}