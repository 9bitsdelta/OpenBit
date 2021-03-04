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

#include "Core/EntryPoint.h"

//GRAPHICS
#include "Graphics/API/GraphicsAPI.h"
#include "Graphics/Camera.h"
#include "Graphics/SimpleRenderer.h"
#include "Graphics/SpriteRenderer.h"
#include "Graphics/PrimitiveRenderer.h"

//ECS
#include "ECS/Scene.h"
#include "ECS/Entity.h"
#include "ECS/Components.h"

//SCRIPTING
#include "Scripting/Lua.h"

//External
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
