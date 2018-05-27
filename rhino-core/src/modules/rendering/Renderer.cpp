#include "Renderer.h"


namespace rhino {

	std::unordered_map<ShaderProgram*, std::unordered_map<Material*, std::vector<Renderer*>>> Renderer::renderers;

	void Renderer::addRendererToList(Renderer* r) {
		auto it1 = renderers.find((ShaderProgram* const)(r->getMaterial().getReferceShader()));
		
		if (it1 != renderers.end()) {
			auto it2 = it1->second.find((Material* const)&(r->getMaterial()));

			if (it2 != it1->second.end()) {
				it2->second.push_back(r);
			} else {
				it1->second.insert({ (Material* const)&(r->getMaterial()), {r} });
			}
		} else {
			std::unordered_map<Material*, std::vector<Renderer*>> map;
			map.insert({ (Material* const)&(r->getMaterial()), {r} });
			renderers.insert({ (ShaderProgram* const)(r->getMaterial().getReferceShader()), map });
		}

	}


	Renderer::Renderer(const Material& mat, const RenderableData& data)
		:material(mat), data(data){
	}

	void Renderer::awake() {
		addRendererToList(this);
	}

	void Renderer::remove() {
		auto itShader = renderers.find((ShaderProgram* const)material.getReferceShader());
		auto itMaterial = itShader->second.find((Material* const)&material);

		if (itMaterial->second.size() > 1) {
			for(unsigned int i = 0; i < itMaterial->second.size(); i++)
				if (itMaterial->second[i] == this) {
					itMaterial->second.erase(itMaterial->second.begin() + i);
					return;
				}
		} else {
			itShader->second.erase(itMaterial->first);
			if (itShader->second.size() == 0) {
				renderers.erase(itShader->first);
			}
		}

	}

	void Renderer::render() const {
		data.bind();
		glDrawElements(GL_TRIANGLES, (int) data.ibo.getCount(), GL_UNSIGNED_INT, nullptr);
		data.unbind();
	}

}