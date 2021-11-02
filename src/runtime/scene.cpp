#include "scene.h"
#include "PointLight.h"
#include "spotlight.h"
#include "arealight.h"
#include "config.h"
#include "program.h"
#include "trianglemesh.h"
#include "rectanglemesh.h"
void Scene::LoadScene()
{
	cubemap = std::make_shared<CubeMap>();
	CubeMap::TextureDirectory directory;
	directory.right = SRC_BASE_PATH + "3dmodels/skybox/right.jpg";
	directory.left = SRC_BASE_PATH + "3dmodels/skybox/left.jpg";
	directory.top = SRC_BASE_PATH + "3dmodels/skybox/top.jpg";
	directory.bottom = SRC_BASE_PATH + "3dmodels/skybox/bottom.jpg";
	directory.front = SRC_BASE_PATH + "3dmodels/skybox/front.jpg";
	directory.back = SRC_BASE_PATH + "3dmodels/skybox/back.jpg";
	cubemap->GenResources(directory);

	auto newmodel = std::make_shared<Model>();
	std::shared_ptr<ShaderBase> mainProgram = Program::GetInstance().GetProgram(ProgramType::Main);
	// newmodel->LoadModel(std::string("F:/GitHub/CGCenter/3dmodels/backpack/backpack.obj"));
	newmodel->LoadModel(std::string(SRC_BASE_PATH + "3dmodels/home/home.obj"));
	models.push_back(newmodel);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(4708.0f, 2844.0f, 2200.0f), // 书房
		glm::vec3(2880.0f, 2800.0f, 2800.0f), // 玄关
		glm::vec3(1116.0f, 2840.0f, 2487.0f), // 客卫
		glm::vec3(5646.0f, 2855.0f, -310.0f), // 厨房
		glm::vec3(1224.0f, 2889.0f, -888.0f), // 客厅
		glm::vec3(1230.0f, 2962.0f, -3784.0f), // 阳台
		glm::vec3(-3914.0f, 2838.0f, 2814.0f), // 主卧
		glm::vec3(-842.0f, 2829.0f, 2686.0f), // 主卫
		glm::vec3(-4226.0f, 2900.0f, -164.0f), // 中卧
		glm::vec3(-3760.0f,  2955.0f, -3240.0f), // 次卧
		glm::vec3(-5800.0f,  2955.0f, -3130.0f), // 次卧阳台
		glm::vec3(-2190.0f,  2955.0f, -1347.0f), // 走道1
		glm::vec3(-2164.0f,  2955.0f, 536.0f), // 走道2
	};
	for (int i = 0; i < 13; i++) {
		auto newPointLight = std::make_shared<PointLight>(pointLightPositions[i],
			glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.8f, 0.8f, 0.8f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			1.0f,
			0.000009f,
			0.0000032f,
			i,
			mainProgram);
		lights.push_back(newPointLight);
	}
	for (int i = 0; i < 13; i++) {
		auto newSpotLight = std::make_shared<SpotLight>(pointLightPositions[i],
			glm::vec3(0.0f, -1.0f, -0.0f),
			glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.8f, 0.8f, 0.8f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			100.0f,
			115.0f,
			1.0f,
			0.000009f,
			0.0000032f,
			i,
			mainProgram);
		lights.push_back(newSpotLight);
	}

	for (int i = 0; i < 13; i++) {
		auto newAreaLight = std::make_shared<AreaLight>(pointLightPositions[i],
			glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.8f, 0.8f, 0.8f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			1.0f,
			0.000009f,
			0.0000032f,
			i,
			mainProgram);
		lights.push_back(newAreaLight);

		auto mesh = std::make_shared<RectangleMesh>();
		mesh->LoadMesh();
		mesh->SetCenter(pointLightPositions[i]);
		mesh->SetScaler(glm::vec3(100.0f, 100.0f, 100.0f));
		rectMeshes.push_back(mesh);
	}
	

	// directional light
	//mainProgram->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	//mainProgram->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	//mainProgram->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	//mainProgram->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
}

void Scene::Draw()
{
	for (auto light : lights) {
		light->SetUniforms();
	}
	for (auto model : models) {
		model->Draw();
	}
	std::shared_ptr<ShaderBase> prog = Program::GetInstance().GetProgram(ProgramType::SimpleColored);
	prog->use();
	for (auto mesh : rectMeshes) {
		mesh->Draw();
	}
	cubemap->Draw();
}

void Scene::DeleteScene()
{
	models.clear();
	lights.clear();
}