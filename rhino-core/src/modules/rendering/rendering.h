#pragma once

#include "core\Module.h"
#include "Camera.h"

namespace rhino { namespace Graphics {

	const Module module = {"graphics", nullptr, nullptr, nullptr, Camera::renderAll};

} }
