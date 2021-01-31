#include "Core/Base.h"

#include "Graphics/API/GraphicsAPI.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Bit {

    class SimpleRenderer
    {
    public:
        static void Init();
        static void Submit(const glm::mat4& transform, const Ref<Texture2D>& texture);
        
        static void BeginScene(const glm::mat4& camera);
        static void EndScene();

    };

}