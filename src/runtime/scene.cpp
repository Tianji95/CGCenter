#include "scene.h"
#include "PointLight.h"
void Scene::LoadScene()
{
	testProgram = std::make_shared<ShaderBase>(SRC_BASE_PATH + "src/shaders/test.vert", SRC_BASE_PATH + "src/shaders/test.frag");
	testProgram->ProduceProgram();

	mainProgram = std::make_shared<ShaderBase>(SRC_BASE_PATH + "src/shaders/main.vert", SRC_BASE_PATH + "src/shaders/main.frag");
	mainProgram->ProduceProgram();

	skyBoxProgram = std::make_shared<ShaderBase>(SRC_BASE_PATH + "src/shaders/skybox.vert", SRC_BASE_PATH + "src/shaders/skybox.frag");
	skyBoxProgram->ProduceProgram();
	
	cubemap = std::make_shared<CubeMap>(skyBoxProgram);
	CubeMap::TextureDirectory directory;
	directory.right = SRC_BASE_PATH + "3dmodels/skybox/right.jpg";
	directory.left = SRC_BASE_PATH + "3dmodels/skybox/left.jpg";
	directory.top = SRC_BASE_PATH + "3dmodels/skybox/top.jpg";
	directory.bottom = SRC_BASE_PATH + "3dmodels/skybox/bottom.jpg";
	directory.front = SRC_BASE_PATH + "3dmodels/skybox/front.jpg";
	directory.back = SRC_BASE_PATH + "3dmodels/skybox/back.jpg";
	cubemap->GenResources(directory);

	auto newmodel = std::make_shared<Model>(mainProgram);
	// newmodel->LoadModel(std::string("F:/GitHub/CGCenter/3dmodels/backpack/backpack.obj"));
	newmodel->LoadModel(std::string(SRC_BASE_PATH + "3dmodels/home/home.obj"));
	models.push_back(newmodel);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(4708.0f, 2844.0f, 2200.0f), // �鷿
		glm::vec3(2880.0f, 2800.0f, 2800.0f), // ����
		glm::vec3(1116.0f, 2840.0f, 2487.0f), // ����
		glm::vec3(5646.0f, 2855.0f, -310.0f), // ����
		glm::vec3(1224.0f, 2889.0f, -888.0f), // ����
		glm::vec3(1230.0f, 2962.0f, -3784.0f), // ��̨
		glm::vec3(-3914.0f, 2838.0f, 2814.0f), // ����
		glm::vec3(-842.0f, 2829.0f, 2686.0f), // ����
		glm::vec3(-4226.0f, 2900.0f, -164.0f), // ����
		glm::vec3(-3760.0f,  2955.0f, -3240.0f), // ����
		glm::vec3(-5800.0f,  2955.0f, -3130.0f), // ������̨
		glm::vec3(-2190.0f,  2955.0f, -1347.0f), // �ߵ�1
		glm::vec3(-2164.0f,  2955.0f, 536.0f), // �ߵ�2
	};
	for (int i = 0; i < 1; i++) {
		auto newPointLight = std::make_shared<PointLight>(pointLightPositions[i],
			glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.8f, 0.8f, 0.8f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			1.0f,
			0.00000009f,
			0.000000032f,
			i,
			mainProgram);
		lights.push_back(newPointLight);
	}
	// directional light
	//mainProgram->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	//mainProgram->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	//mainProgram->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	//mainProgram->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	// spotLight
	//mainProgram->setVec3("spotLight.position", 4708.0f, 2844.0f, 2200.0f);
	//mainProgram->setVec3("spotLight.direction", 0.0f, -1.0f, -0.0f);
	//mainProgram->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	//mainProgram->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	//mainProgram->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	//mainProgram->setFloat("spotLight.constant", 0.6f);
	//mainProgram->setFloat("spotLight.linear", 0.00009);
	//mainProgram->setFloat("spotLight.quadratic", 0.000032);
	//mainProgram->setFloat("spotLight.cutOff", glm::cos(glm::radians(100.0f)));
	//mainProgram->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(115.0f)));
}

void Scene::Draw()
{
	for (auto light : lights) {
		light->SetUniforms();
	}
	for (auto model : models) {
		model->Draw();
	}
	cubemap->Draw();
}

void Scene::DeleteScene()
{
	models.clear();
	lights.clear();
}