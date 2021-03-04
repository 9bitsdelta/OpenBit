#include <Bit.h>

#include "Extras.h"

#define QUICK_ADD_PLANET(x, y, z)  {m_Planets.push_back(m_Scene.CreateEntity(x));\
                                   auto& planet = m_Planets.back(); \
                                   auto& prim = planet.AddComponent<Bit::PrimitiveComponent>(Bit::DrawMethod::Triangle_Fan, planetVert, planetIndex, y);\
                                   prim.IsVisible = false;\
                                   planet.AddComponent<Bit::NativeScriptComponent>().Bind<OrbitingController>();\
                                   planet.AddComponent<OrbitingComponent>(z);}

class Sandbox : public Bit::Application
{
public:
    Sandbox()
        :Bit::Application("Kepler")
    {
        m_Checkerboard = Bit::Texture2D::Create("assets/textures/checkerboard.png");

        m_Camera->SetOrthographicProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
        m_Scene.SetCamera(m_Camera);

        std::vector<float> planetVert = {
            0.0f, 0.0f, 0.0f,
            (float)glm::cos(glm::radians(0.0f)), (float)glm::sin(glm::radians(0.0f)), 0.0f,
            (float)glm::cos(glm::radians(30.0f)), (float)glm::sin(glm::radians(30.0f)), 0.0f,
            (float)glm::cos(glm::radians(60.0f)), (float)glm::sin(glm::radians(60.0f)), 0.0f,
            (float)glm::cos(glm::radians(90.0f)), (float)glm::sin(glm::radians(90.0f)), 0.0f,
            (float)glm::cos(glm::radians(120.0f)), (float)glm::sin(glm::radians(120.0f)), 0.0f,
            (float)glm::cos(glm::radians(150.0f)), (float)glm::sin(glm::radians(150.0f)), 0.0f,
            (float)glm::cos(glm::radians(180.0f)), (float)glm::sin(glm::radians(180.0f)), 0.0f,
            (float)glm::cos(glm::radians(210.0f)), (float)glm::sin(glm::radians(210.0f)), 0.0f,
            (float)glm::cos(glm::radians(240.0f)), (float)glm::sin(glm::radians(240.0f)), 0.0f,
            (float)glm::cos(glm::radians(270.0f)), (float)glm::sin(glm::radians(270.0f)), 0.0f,
            (float)glm::cos(glm::radians(300.0f)), (float)glm::sin(glm::radians(300.0f)), 0.0f,
            (float)glm::cos(glm::radians(330.0f)), (float)glm::sin(glm::radians(330.0f)), 0.0f,
        };

        std::vector<uint32_t> planetIndex = { 0, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 1 };

        {
            m_Sun = m_Scene.CreateEntity("Sun");
            auto& transform = m_Sun.GetComponent<Bit::TransformComponent>();
            transform.Scale = glm::vec3(2.0f * m_Zoom / 25.0f);
            m_Sun.AddComponent<Bit::PrimitiveComponent>(Bit::DrawMethod::Triangle_Fan, planetVert, planetIndex, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
        }

        m_Planets.reserve(8);
        QUICK_ADD_PLANET("Mercury", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), OrbitingComponent(3.301f, 0.205f, 87.97f));
        QUICK_ADD_PLANET("Venus", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), OrbitingComponent(48.675f, 0.006f, 224.701f));
        QUICK_ADD_PLANET("Earth", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), OrbitingComponent(59.72f, 0.016f, 365.0f));
        QUICK_ADD_PLANET("Mars", glm::vec4(1.0f, 0.2f, 0.2f, 1.0f), OrbitingComponent(6.417f, 0.0934f, 686.971f));
        QUICK_ADD_PLANET("Jupiter", glm::vec4(0.8f, 0.8f, 0.2f, 1.0f), OrbitingComponent(18982.0f, 0.0489f, 4332.59f));
        QUICK_ADD_PLANET("Saturn", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), OrbitingComponent(5683.4f, 0.0565f, 10759.22f));
        QUICK_ADD_PLANET("Uranus", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), OrbitingComponent(868.1f, 0.0463f, 30688.5f));
        QUICK_ADD_PLANET("Pluto", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), OrbitingComponent(0.1303f, 0.2488f, 90560.0f));

        for (int i = 0; i<m_Planets.size(); i++)
        {
            std::string& name = m_Planets[i].GetComponent<Bit::TagComponent>();
            m_NameToIndex[name] = i;
        }

    }

    ~Sandbox()
    {
        
    }

    void OnUpdate(Bit::Timestep& ts) override
    {
        Bit::SpriteRenderer::BeginScene(m_Camera->Get());
        Bit::SpriteRenderer::DrawQuad(glm::vec3(0.0f, 0.0f, 0.0f),glm::vec2(20.0f), m_Checkerboard, 20.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.2f));
        Bit::SpriteRenderer::EndScene();
        m_Scene.OnUpdate(ts);
    }

    void OnImGuiRender() override
    {
        //bool show = true;
        //ImGui::ShowDemoWindow(&show);

        static std::string active = "Earth";

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos, ImGuiCond_Once);
        ImGui::SetNextWindowSize({viewport->Size.x * 0.2f, viewport->Size.y}, ImGuiCond_Once);

        ImGui::Begin("Settings", NULL, 
            ImGuiWindowFlags_MenuBar  
            | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoTitleBar
        );
        
        ImGui::BeginMenuBar();
        if (ImGui::BeginMenu(" > Select Planet"))
        {
            for (auto planet : m_Planets)
            {
                bool selected = false;
                std::string& name = planet.GetComponent<Bit::TagComponent>();
                ImGui::MenuItem(name.c_str(), NULL, &selected);
                if (selected)
                {
                    active = name;
                }
                else
                {
                    m_Planets[m_NameToIndex[name]].GetComponent<Bit::PrimitiveComponent>().IsVisible = false;
                }
                selected = false;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
        
        if (!active.empty())
        {
            m_Planets[m_NameToIndex[active]].GetComponent<Bit::PrimitiveComponent>().IsVisible = true;
            auto& planet = m_Planets[m_NameToIndex[active]];

            auto& orbiting = planet.GetComponent<OrbitingComponent>();
            ImGui::PushID(active.c_str());
            ImGui::Text("%s", active.c_str());
            ImGui::Separator();
            ImGui::Text("Current Angle: %g", orbiting.Degrees);
            ImGui::PopID();
        }
        
        ImGui::End();

    }

    void OnEvent(Bit::Event& event) override
    {
        //Other Events

        //Sandbox events
        Bit::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Bit::WindowResizeEvent>(BIT_BIND_EVENT_FN(Sandbox::OnWindowResize));
        dispatcher.Dispatch<Bit::MouseScrolledEvent>(BIT_BIND_EVENT_FN(Sandbox::OnMouseScrolled));
    }

    bool OnWindowResize(Bit::WindowResizeEvent& event)
    {
        m_AspectRatio = (float)event.GetWidth()/(float)event.GetHeight();
        m_Camera->SetOrthographicProjection(-m_AspectRatio*m_Zoom, m_AspectRatio*m_Zoom, -m_Zoom, m_Zoom);
        return true;
    }

    bool OnMouseScrolled(Bit::MouseScrolledEvent& event)
    {
        m_Zoom -= 0.1f * event.GetYOffset();

        m_Zoom = std::max(1.2f, m_Zoom);
        m_Zoom = std::min(m_Zoom, 2.2f);
        m_Camera->SetOrthographicProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);

        return true;
    }


private:
    Bit::Ref<Bit::Camera> m_Camera = Bit::Camera::Create(Bit::Projection::Orthographic);

    Bit::Scene m_Scene;
    
    Bit::Entity m_Sun;
    std::vector<Bit::Entity> m_Planets;

    std::unordered_map<std::string, int> m_NameToIndex;

    Bit::Ref<Bit::Texture2D> m_Checkerboard;

    float m_AspectRatio = 16.0f/9.0f;
    float m_Zoom = 1.2f;
};

Bit::Application* Bit::CreateApp()
{
    return new Sandbox;
}

int main(int argc, char** argv)
{
    return BitMain(argc, argv);
}
