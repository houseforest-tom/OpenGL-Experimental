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

		const u16 latitudeTesselation;
		const u16 longitudeTesselation;
		float *heightmap;

		float getHeightmapEntry(u16 latitude, u16 longitude);
		void  setHeightmapEntry(u16 latitude, u16 longitude, float value);
		float getTheta(u16 latitude);
		float getPhi(u16 longitude);
		float random(float min = 0.0f, float max = 1.0f);
		vec3  randomColor();

	public:
		// Creates the sphere mesh.
		SphereEntity(
			u16 latitudeTesselation, 
			u16 longitudeTesselation, 
			float radius, 
			float maxDistortion, 
			OpenGLShaderProgram const *shader, 
			ViewProjComponent const *viewproj);

		virtual void update(float dt) override;
		virtual void render() override;
		~SphereEntity();
	};
}