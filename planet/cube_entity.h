#include "entity.h"
#include "model_component.h"

namespace planet {
	class CubeEntity : public Entity {
	private:
		Mesh* mesh;

	public:
		CubeEntity();
		~CubeEntity();
	};
}