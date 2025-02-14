#include <Bit.h>

struct OrbitingComponent
{
    //Some variables needed for the orbit sim;
    float OrbitingMass; // * 10^23 kg
    float SolarMass = 1.989f; // * 10^30 kg
    float Ecc; // between 0 and 1 (ellipse shape)
    float Period;

    float Degrees = 0.0f; //theta --incremented over time (governs the x y of the transform)

    float SemiMajor = 1.0f;
    float SemiMinor = 0.0f;

    OrbitingComponent() = default;
    OrbitingComponent(const OrbitingComponent&) = default;
    OrbitingComponent(const float& mass, const float& ecc, const float& period)
        : OrbitingMass(mass), Ecc(ecc), Period(period) {}
};

class OrbitingController : public Bit::ScriptableEntity
{
public:

    void OnCreate()
    {
        auto& transform = GetComponent<Bit::TransformComponent>();
        auto& orbiting = GetComponent<OrbitingComponent>();

        orbiting.SemiMinor = glm::sqrt(orbiting.SemiMajor * orbiting.SemiMajor * (1 - orbiting.Ecc * orbiting.Ecc));
        transform.Scale = glm::vec3(0.05f);
    }

    void OnUpdate(Bit::Timestep ts)
    {
        auto& orbiting = GetComponent<OrbitingComponent>();
        auto& transform = GetComponent<Bit::TransformComponent>();

        orbiting.Degrees += (120.0f * ts); //TO BE CHANGED
        orbiting.Degrees = (orbiting.Degrees > 360.0f) ? (orbiting.Degrees - 360.0f) : orbiting.Degrees;

        transform.Position = {
            orbiting.SemiMajor * orbiting.Ecc + orbiting.SemiMajor * (float)glm::cos(glm::radians(orbiting.Degrees)),
            orbiting.SemiMinor * (float)glm::sin(glm::radians(orbiting.Degrees)),
            0.0f
        };
    }

};
