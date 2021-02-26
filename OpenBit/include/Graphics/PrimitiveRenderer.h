#pragma once
#include "Core/Base.h"

#include "Graphics/API/GraphicsAPI.h"

#include "Graphics/Camera.h"

namespace Bit {

    class PrimitiveRenderer
    {
    public:

        static void Init();
        static void Shutdown();

        static void BeginScene(const glm::mat4& cam);
        static void EndScene();

        static void SetShader(const Ref<Shader>& shader);
        static Ref<Shader>& GetShader();

        static void Draw(const DrawMethod& type, std::vector<float> points, std::vector<uint32_t> indices, const glm::vec4& color);

    };

}