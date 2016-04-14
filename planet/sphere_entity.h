#include "entity.h"
#include "model_component.h"

namespace planet {
	class SphereEntity : public Entity {
	private:
		// Spherical mesh.
		Mesh* mesh = nullptr;

		// Returns a point on a sphere.
		vec3 getUnitSpherePoint(float theta, float phi);

	public:
		// Create the mesh for the sphere.
		SphereEntity(OpenGLShaderProgram* shader, ViewProjComponent const* viewproj);

		// Delete the sphere mesh.
		~SphereEntity();
	};
}