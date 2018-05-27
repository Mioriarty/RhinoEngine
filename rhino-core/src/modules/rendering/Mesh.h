#pragma once

#include "data/Vao.h"
#include "data/Ibo.h"
#include <cmath>

namespace rhino {

	struct RenderableData {
		Vao vao;
		Ibo ibo;

		void bind() const;
		void unbind() const;

		RenderableData() = default;
	};

	class Mesh {

		public:
			struct Vertex {
				float position[3];
				float textureCoord[2];
				float normal[3];
			};

			enum class StandartMesh {
				QUAD, CUBE, PLANE
			};
		
		private:
			std::vector<Vertex> vertecies;
			std::vector<unsigned int> indecies;

			static Mesh standartMeshes[];
			static unsigned int createdStandartMeshes;

		public:
			Mesh() = default;
			Mesh(const std::vector<Vertex>& vertecies, const std::vector<unsigned int>& indecies);

			RenderableData createRenderableData() const;


			template<StandartMesh T>
			static const Mesh& createStandartMesh();
	};

	template<Mesh::StandartMesh T>
	inline const Mesh& Mesh::createStandartMesh() {
		static_assert(false, "Unknown standart mesh type");
	}

	template<>
	inline const Mesh& Mesh::createStandartMesh<Mesh::StandartMesh::QUAD>() {
		if ((1u & createdStandartMeshes) == 0) {
			createdStandartMeshes |= 1u;

			std::vector<Mesh::Vertex> verts = {
				{ { -0.5f, -0.5f, 0.0f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f } },
				{ { -0.5f,  0.5f, 0.0f },{ 0.0f, 1.0f },{ 0.0f, 0.0f, 0.0f } },
				{ { 0.5f,  0.5f, 0.0f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, 0.0f } },
				{ { 0.5f, -0.5f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 0.0f, 0.0f } }
			};

			std::vector<unsigned int> inds = {
				0, 1, 2,
				0, 2, 3
			};

			standartMeshes[0] = Mesh(verts, inds);

		}
		return standartMeshes[0];
	}

	template<>
	inline const Mesh& Mesh::createStandartMesh<Mesh::StandartMesh::CUBE>() {
		if ((2u & createdStandartMeshes) == 0) {
			createdStandartMeshes |= 2u;

			#define l 0.5f
			#define i 1.0f

			std::vector<Mesh::Vertex> verts = {
				{ { -l, -l, -l },{ 0, 0 },{ 0, -i, 0 } }, // buttom
				{ { -l, -l, -l },{ 0, 0 },{ 0, 0, -i } }, // front
				{ { -l, -l, -l },{ i, 0 },{ -i, 0, 0 } }, // left
														  //
				{ {  l, -l, -l },{ i, 0 },{ 0, -i, 0 } }, // buttom
				{ {  l, -l, -l },{ 0, 0 },{ i, 0, 0 } },  // right
				{ {  l, -l, -l },{ i, 0 },{ 0, 0, -i } }, // front
														  //
				{ {  l, -l,  l },{ i, i },{ 0, -i, 0 } }, // buttom
				{ {  l, -l,  l },{ 0, 0 },{ 0, 0, i } },  // back
				{ {  l, -l,  l },{ i, 0 },{ i, 0, 0 } },  // right
														  //
				{ { -l, -l,  l },{ 0, i },{ 0, -i, 0 } }, // buttom
				{ { -l, -l,  l },{ 0, 0 },{ -i, 0, 0 } }, // left
				{ { -l, -l,  l },{ i, 0 },{ 0, 0, i } },  // back
														  //
														  //
				{ { -l,  l, -l },{ 0, 0 },{ 0, i, 0 } },  // top
				{ { -l,  l, -l },{ 0, i },{ 0, 0, -i } }, // front
				{ { -l,  l, -l },{ i, i },{ -i, 0, 0 } }, // left
														  //
				{ { l,  l, -l },{ i, 0 },{ 0, i, 0 } },   // top
				{ { l,  l, -l },{ 0, i },{ i, 0, 0 } },   // right
				{ { l,  l, -l },{ i, i },{ 0, 0, -i } },  // front
														  //
				{ { l,  l,  l },{ i, i },{ 0, i, 0 } },   // top
				{ { l,  l,  l },{ 0, i },{ 0, 0, i } },   // back
				{ { l,  l,  l },{ i, i },{ i, 0, 0 } },   // right
														  //
				{ { -l,  l,  l },{ 0, i },{ 0, i, 0 } },  // top
				{ { -l,  l,  l },{ 0, i },{ -i, 0, 0 } }, // left
				{ { -l,  l,  l },{ i, i },{ 0, 0, i } },  // back

			};

			#undef l
			#undef i

			std::vector<unsigned int> inds = {
				0,  3,  6,    0,  9,  6,  // buttom
				12, 15, 18,   12, 21, 18, // top
				1,  5,  17,   1,  13, 17, // front
				7,  11, 23,   7,  19, 23, // back
				2,  10, 22,   2,  14, 22, // left
				4,  8,  20,   4,  16, 20  // right
			};

			standartMeshes[1] = Mesh(verts, inds);
		}
		return standartMeshes[1];
	}

	template<>
	inline const Mesh& Mesh::createStandartMesh<Mesh::StandartMesh::PLANE>() {
		if ((4u & createdStandartMeshes) == 0) {
			createdStandartMeshes |= 4u;

			std::vector<Mesh::Vertex> verts;
			//verts.reserve(10 * 10);
			std::vector<unsigned int> inds;
			inds.reserve(9 * 9 * 2 * 3);

			for (int z = 0; z < 10; z++) {
				for (int x = 0; x < 10; x++) {
					verts.push_back({ { (float)x, 0.0f, (float)z }, { ((float) x) / 9.0f, ((float) z) / 9.0f }, { 0.0f, 1.0f, 0.0f } });

					if (x < 9 && z < 9) {
						inds.emplace_back(x + z * 10);
						inds.emplace_back((x + 1) + z * 10);
						inds.emplace_back((x + 1) + (z + 1) * 10);

						inds.emplace_back(x + z * 10);
						inds.emplace_back(x + (z + 1) * 10);
						inds.emplace_back((x + 1) + (z + 1) * 10);
					}
				}
			}

			standartMeshes[2] = Mesh(verts, inds);

		}
		return standartMeshes[2];
	}


}