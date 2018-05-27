#pragma once

#include "core/Component.h"
#include "Mesh.h"
#include "data/shader/Material.h"
#include "data/shader/ShaderProgram.h"
#include <unordered_map>
#include <vector>

namespace rhino {

	class Renderer : public Component {

		SIMPLE_GETCOPY_OVERLOAD(Renderer)

		protected:
			static std::unordered_map<ShaderProgram*, std::unordered_map<Material*, std::vector<Renderer*>>> renderers;
			static void addRendererToList(Renderer* r);

		public:
			static const std::unordered_map<ShaderProgram*, std::unordered_map<Material*, std::vector<Renderer*>>>& getAllRenderers() { return renderers; };

		protected:
			Material material;
			RenderableData data;


			void awake();
			void remove();

		public:
			Renderer(const Material& mat, const RenderableData& data);
			void render() const;

			inline const Material& getMaterial() const { return material; };
			

	};

}