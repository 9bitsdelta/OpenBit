#pragma once

/*
 * FOR USE WITH OPENBIT APPLICATIONS
 */

//CORE
#include "Core/Base.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/Event.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"

//GRAPHICS
#include "Graphics/API/GraphicsAPI.h"
#include "Graphics/Camera.h"
#include "Graphics/SimpleRenderer.h"
#include "Graphics/SpriteRenderer.h"
#include "Graphics/PrimitivesRenderer.h"

//ECS
#include "ECS/Scene.h"
#include "ECS/Entity.h"
#include "ECS/Components.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*
 * ENTRY POINT
 */

#include "Core/EntryPoint.h"