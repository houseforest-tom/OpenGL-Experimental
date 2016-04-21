#include "entity.h"
#include "orientation_component.h"
#include "model_component.h"
#include "deform_component.h"

namespace planet {
	class SphereEntity : public Entity {
	private:
		// Returns a point on the unit sphere.
		vec3 getUnitSpherePoint(float theta, float phi);

		Mesh                 *mesh;
		OrientationComponent *orientation;
		ModelComponent       *model;
		DeformComponent      *deform;

	public:
		// Creates the sphere mesh.
		SphereEntity(OpenGLShaderProgram const *shader, ViewProjComponent const *viewproj);
		virtual void update(float dt) override;
		virtual void render() override;
		~SphereEntity();
	};
}