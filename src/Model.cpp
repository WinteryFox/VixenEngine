#include "Model.h"

namespace graphics::model {
	Model::Model(vector<Mesh*> &meshes, bool visible) : meshes(meshes), visible(visible) {
	
	}
	
	bool Model::isVisible() const {
		return visible;
	}
	
	void Model::setVisible(bool visible) {
		this->visible = visible;
	}
	
	vector<Mesh*> Model::getMeshes() {
		return meshes;
	}
}