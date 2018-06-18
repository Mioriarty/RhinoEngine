#include "ECS.h"

namespace rhino { namespace ecs {

	ECS::~ECS() {

		for (std::map<unsigned int, std::vector<char>>::iterator it = components.begin(); it != components.end(); ++it) {
			size_t typeSize = BaseComponent::getTypeSize(it->first);
			ComponentFreeFunction freeFun = BaseComponent::getTypeFreeFunction(it->first);

			for (unsigned int i = 0; i < it->second.size(); i += typeSize)
				freeFun((BaseComponent*)&(it->second[i]));
	
		}


		for (auto entity : entities)
			delete entity;

	}

	// Entity methods
	EntityHandle ECS::makeEntity(BaseComponent* entityComponents, const unsigned int* componentIds, unsigned int numConponents) {
		std::pair<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>>* entity = new std::pair<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>>();
		EntityHandle handle = (EntityHandle)entity;

		for (unsigned int i = 0; i < numConponents; i++) {

			if (!BaseComponent::isTypeValid(componentIds[i])) {
				delete entity;
				return nullptr;
			}

			ComponentCreateFunction createFun = BaseComponent::getTypeCreateFunction(componentIds[i]);
			std::pair<unsigned int, unsigned int> pair;
			pair.first = componentIds[i];
			pair.second = createFun(components[componentIds[i]], handle, &entityComponents[i]);
			entity->second.push_back(pair);
		}

		entity->first = entities.size();
		entities.emplace_back(entity);

		return handle;
	}

	void ECS::removeEntity(EntityHandle handle) {
		std::vector<std::pair<unsigned int, unsigned int>> entity = handleToEntity(handle);

		for (unsigned int i = 0; i < entity.size(); i++) {
			removeComponentInternal(entity[i].first, entity[i].second);
		}

		unsigned int destIndex = handleToEntityIndex(handle);
		unsigned int srcIndex = entities.size() - 1;
		delete entities[destIndex];
		entities[destIndex] = entities[srcIndex];
		entities.pop_back();
	}

	void ECS::addSystem(BaseSystem* system) {
		systems.push_back(system);
	}


} }