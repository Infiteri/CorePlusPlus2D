#pragma once

#include "Base.h"

#include "Core/Application.h"
#include "Core/Logger.h"
#include "Core/Input.h"
#include "Core/Engine.h"
#include "Core/Layer/Layer.h"
#include "Core/Layer/LayerStack.h"
#include "Core/Memory/CeMemory.h"
#include "Core/Window.h"
#include "Platform/Platform.h"

#include "Renderer/Camera/OrthographicCamera.h"
#include "Renderer/Camera/CameraSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Geometry/Geometry.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Shader/ShaderSystem.h"
#include "Renderer/Texture/TextureManager.h"
#include "Renderer/Objects/Mesh.h"
#include "Resource/Loaders/MaterialLoader.h"

#include "Scene/Scene.h"
#include "Scene/Actor.h"
#include "Scene/World.h"
#include "Scene/SceneSerializer.h"