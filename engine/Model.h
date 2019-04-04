#pragma once

#include "Mesh.h"
#include "Camera.h"

namespace graphics::model {
	class Model {
	private:
		const vector<Mesh*> meshes;
		bool visible;
		
	public:
		explicit Model(vector<Mesh*> &meshes, bool visible = true);
		
		bool isVisible() const;
		
		void setVisible(bool visible);
		
		vector<Mesh*> getMeshes();
	};
}