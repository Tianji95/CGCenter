#include "AssetParser.h"
#include "resourceManager.h"
#include <unordered_map>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "config.h"
#include "skybox.h"
namespace Zxen {
	void AssetParser::LoadModelData(const std::string& path)
	{
		Assimp::Importer import;
		const aiScene* assimpScene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenUVCoords);
		if (!assimpScene || assimpScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !assimpScene->mRootNode) {
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
			return;
		}
		ProcessMaterial(path, assimpScene);
		ProcessNode(assimpScene->mRootNode, assimpScene);
	}

	void AssetParser::ProcessMaterial(const std::string& path, const aiScene* scene)
	{
		std::unordered_map<aiTextureType, std::string> mp = {
			{aiTextureType_DIFFUSE, "texture_diffuse"},
			{aiTextureType_SPECULAR, "texture_specular"},
			{aiTextureType_AMBIENT, "texture_ambient"},
			{aiTextureType_EMISSIVE, "texture_emissive"},
			{aiTextureType_HEIGHT, "texture_height"},
			{aiTextureType_NORMALS, "texture_normals"},
			{aiTextureType_SHININESS, "texture_shininess"},
			{aiTextureType_OPACITY, "texture_opacity"},
			{aiTextureType_DISPLACEMENT, "texture_displacement"},
			{aiTextureType_LIGHTMAP, "texture_lightmap"},
			{aiTextureType_REFLECTION, "texture_reflection"},
			{aiTextureType_BASE_COLOR, "texture_basecolor"},
			{aiTextureType_NORMAL_CAMERA, "texture_normal_camera"},
			{aiTextureType_EMISSION_COLOR, "texture_emission_color"},
			{aiTextureType_METALNESS, "texture_metalness"},
			{aiTextureType_DIFFUSE_ROUGHNESS, "texture_diffuse_roughness"},
			{aiTextureType_AMBIENT_OCCLUSION, "texture_ambient_occlusion"}
		};

		unsigned int numMaterials = scene->mNumMaterials;
		for (int i = 0; i < numMaterials; i++) {
			aiMaterial* material = scene->mMaterials[i];
			MaterialPtr mat = rsm->CreateMaterial();
			for (auto iter : mp) {
				std::vector<TexturePtr> maps = loadMaterialTextures(path, material, iter.first, iter.second);
				// todo: 同一个类型的纹理可以有多个么？
				mat->texs.insert(mat->texs.end(), maps.begin(), maps.end());
			}

			aiColor3D color;
			material->Get(AI_MATKEY_COLOR_DIFFUSE, color); mat->colorDiffuse = glm::vec3(color.r, color.g, color.b);
			material->Get(AI_MATKEY_COLOR_SPECULAR, color); mat->colorSpecular = glm::vec3(color.r, color.g, color.b);
			material->Get(AI_MATKEY_COLOR_AMBIENT, color); mat->colorAmbiend = glm::vec3(color.r, color.g, color.b);
			material->Get(AI_MATKEY_COLOR_EMISSIVE, color); mat->colorEmissive = glm::vec3(color.r, color.g, color.b);
			material->Get(AI_MATKEY_COLOR_TRANSPARENT, color); mat->colorTransparent = glm::vec3(color.r, color.g, color.b);
			material->Get(AI_MATKEY_OPACITY, mat->opacity);
			material->Get(AI_MATKEY_SHININESS, mat->shininess);
			material->Get(AI_MATKEY_SHININESS_STRENGTH, mat->shininessStrength);
			material->Get(AI_MATKEY_REFLECTIVITY, mat->reflection);
			material->Get(AI_MATKEY_REFRACTI, mat->refraction);
			material->Get(AI_MATKEY_TRANSPARENCYFACTOR, mat->transparentFactor);
			material->Get(AI_MATKEY_SHADING_MODEL, mat->shadingModel);
			material->Get(AI_MATKEY_BLEND_FUNC, mat->blendFunc);
		}
	}

	void AssetParser::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->ProcessMesh(mesh, scene);
		}
		for (int i = 0; i < node->mNumChildren; i++) {
			this->ProcessNode(node->mChildren[i], scene);
		}
	}

	void AssetParser::ProcessMesh(aiMesh* aimesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		for (int i = 0; i < aimesh->mNumVertices; i++) {
			glm::vec3 pos;
			Vertex vertex;
			pos.x = aimesh->mVertices[i].x;
			pos.y = aimesh->mVertices[i].y;
			pos.z = aimesh->mVertices[i].z;
			vertex.position = pos;
			if (aimesh->mNormals) {
				glm::vec3 normal;
				normal.x = aimesh->mNormals[i].x;
				normal.y = aimesh->mNormals[i].y;
				normal.z = aimesh->mNormals[i].z;
				vertex.normal = normal;
			}
			else {
				vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			}
			vertex.uv0 = glm::vec2(0.0f, 0.0f);
			vertex.uv1 = glm::vec2(0.0f, 0.0f);

			if (aimesh->mTextureCoords[0]) {
				vertex.uv0.x = aimesh->mTextureCoords[0][i].x;
				vertex.uv0.y = aimesh->mTextureCoords[0][i].y;
			}
			if (aimesh->mTextureCoords[1]) {
				vertex.uv1.x = aimesh->mTextureCoords[1][i].x;
				vertex.uv1.y = aimesh->mTextureCoords[1][i].y;
			}
			vertices.push_back(vertex);
		}

		for (int i = 0; i < aimesh->mNumFaces; i++) {
			aiFace face = aimesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}
		MeshPtr mesh = rsm->CreateMesh();

		//scenekit 里面的vertices是怎么做的
		mesh->Setup(vertices, indices, aimesh->mName.C_Str());
		mesh->AddMaterials(RenderPassType::FORWARD, rsm->GetMaterials()[aimesh->mMaterialIndex]);
		mesh->Submit();
	}

	std::vector<TexturePtr> AssetParser::loadMaterialTextures(const std::string& path, aiMaterial* mat, aiTextureType type, std::string& typeName)
	{
		std::vector<TexturePtr> textureIDs;
		std::vector<TexturePtr> textureCached = rsm->GetTextures();
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
			aiString textureName;
			mat->GetTexture(type, i, &textureName);
			bool skip = false;

			for (unsigned int j = 0; j < textureCached.size(); j++) {
				if (textureCached[j]->isSameName(std::string(textureName.C_Str()))) {
					textureIDs.push_back(textureCached[j]);
					skip = true;
					break;
				}
			}
			if (!skip) {
				Texture2DPtr tex = rsm->CreateTexture2D(std::string(textureName.C_Str()));
				std::string texturepath = path.substr(0, path.find_last_of("/") + 1) + textureName.C_Str();
				int width, height, nrComponents;
				unsigned char* data = stbi_load(texturepath.c_str(), &width, &height, &nrComponents, 0);
				GLenum format = channel2Format.find(nrComponents) == channel2Format.end() ? GL_RGBA : channel2Format[nrComponents];
				tex->Setup(typeName, width, height, 0, format, format, GL_UNSIGNED_BYTE, data);
				tex->Submit();
				textureIDs.push_back(tex);
				stbi_image_free(data);
			}
		}
		return textureIDs;
	}

	void AssetParser::LoadStaticLight()
	{
		glm::vec3 pointLightPositions[] = {
			glm::vec3(4708.0f, 2844.0f, 2200.0f), // 书房
			glm::vec3(2880.0f, 2800.0f, 2800.0f), // 玄关
			glm::vec3(1116.0f, 2840.0f, 2487.0f), // 客卫
			glm::vec3(5646.0f, 2855.0f, -310.0f), // 厨房
			glm::vec3(1224.0f, 2889.0f, -888.0f), // 客厅
			glm::vec3(1230.0f, 2962.0f, -3784.0f), // 阳台
			glm::vec3(-3914.0f, 2838.0f, 2814.0f), // 主卧
			glm::vec3(-842.0f, 2829.0f, 2686.0f), // 主卫
			glm::vec3(-4226.0f, 2850.0f, -164.0f), // 中卧
			glm::vec3(-3760.0f,  2855.0f, -3240.0f), // 次卧
			glm::vec3(-5800.0f,  2855.0f, -3130.0f), // 次卧阳台
			glm::vec3(-2190.0f,  2855.0f, -1347.0f), // 走道1
			glm::vec3(-2164.0f,  2855.0f, 536.0f), // 走道2
		};
		for (int i = 0; i < 13; i++) {
			auto newPointLight = rsm->CreatePointLight();
			newPointLight->Setup(pointLightPositions[i],
				glm::vec3(0.05f, 0.05f, 0.05f),
				glm::vec3(0.8f, 0.8f, 0.8f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				1.0f,
				0.000009f,
				0.0000032f,
				i);
		}
		for (int i = 0; i < 13; i++) {
			auto newSpotLight = rsm->CreateSpotLight();
			newSpotLight->Setup(pointLightPositions[i],
				glm::vec3(0.0f, -1.0f, -0.0f),
				glm::vec3(0.05f, 0.05f, 0.05f),
				glm::vec3(0.8f, 0.8f, 0.8f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				100.0f,
				115.0f,
				1.0f,
				0.000009f,
				0.0000032f,
				i);
		}
		MaterialPtr AreaLightMaterial = rsm->CreateMaterial();
		ProgramPtr prog = rsm->CreateProgram(SRC_BASE_PATH + "src/shaders/simple_colored_mesh.vert", SRC_BASE_PATH + "src/shaders/simple_colored_mesh.frag");
		prog->ProduceProgram();
		AreaLightMaterial->program = prog;
		for (int i = 0; i < 13; i++) {
			auto newAreaLight = rsm->CreateAreaLight();
			newAreaLight->Setup(pointLightPositions[i],
				glm::vec3(0.05f, 0.05f, 0.05f),
				glm::vec3(0.8f, 0.8f, 0.8f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				1.0f,
				0.000009f,
				0.0000032f,
				i);
			auto mesh = rsm->CreateAreaLightMesh();
			mesh->Setup("AreaLight");
			mesh->AddMaterials(RenderPassType::FORWARD, AreaLightMaterial);
			mesh->SetCenter(pointLightPositions[i]);
			mesh->SetScaler(glm::vec3(100.0f, 100.0f, 100.0f));
			mesh->Submit();
		}
	}

	void AssetParser::LoadSkybox(const std::string& skyboxpath)
	{
		SkyboxPtr skybox = rsm->CreateSkyBox();
		CubemapPtr cubemap = rsm->CreateCubemap(std::string("skybox"));
		CubeMeshPtr mesh = rsm->CreateBuildInCube();

		std::vector<std::string> faces = { skyboxpath + "right.jpg", skyboxpath + "left.jpg", skyboxpath + "top.jpg", skyboxpath + "bottom.jpg", skyboxpath + "front.jpg", skyboxpath + "back.jpg" };
		int width[6], height[6], nrComponents[6];
		std::vector<void*> buffer(6);
		GLenum format[6];
		for (unsigned int i = 0; i < faces.size(); i++) {
			buffer[i] = stbi_load(faces[i].c_str(), &width[i], &height[i], &nrComponents[i], 0);
			format[i] = channel2Format.find(nrComponents[i]) == channel2Format.end() ? GL_RGBA : channel2Format[nrComponents[i]];
		}

		cubemap->Setup(std::string("skybox"), width, height, 0, format, GL_UNSIGNED_BYTE, buffer);
		cubemap->Submit();

		MaterialPtr skyboxMaterial = rsm->CreateMaterial();
		ProgramPtr prog = rsm->CreateProgram(SRC_BASE_PATH + "src/shaders/skybox.vert", SRC_BASE_PATH + "src/shaders/skybox.frag");
		prog->ProduceProgram();
		skyboxMaterial->program = prog;
		skyboxMaterial->texs.push_back(cubemap);

		mesh->Setup("skybox");
		mesh->AddMaterials(RenderPassType::FORWARD, skyboxMaterial);
		mesh->Submit();
		skybox->Setup(mesh, prog);
	}
}