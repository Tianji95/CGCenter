#include "model.h"
#include <iostream>
#include <unordered_map>
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "uiframework.h"

void Model::LoadModel(std::string& path)
{
	testProgram = std::make_shared<ShaderBase>("F:/GitHub/CGCenter/src/shaders/test.vert", "F:/GitHub/CGCenter/src/shaders/test.frag");
	testProgram->ProduceProgram();

	mainProgram = std::make_shared<ShaderBase>("F:/GitHub/CGCenter/src/shaders/main.vert", "F:/GitHub/CGCenter/src/shaders/main.frag");
	mainProgram->ProduceProgram();

	Assimp::Importer import;
	const aiScene* assimpScene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenUVCoords);
	if (!assimpScene || assimpScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !assimpScene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	ProcessNode(assimpScene->mRootNode, assimpScene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// 添加当前节点中的所有Mesh  
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->ProcessMesh(mesh, scene);
	}
	// 递归处理该节点的子孙节点  
	for (int i = 0; i < node->mNumChildren; i++) {
		this->ProcessNode(node->mChildren[i], scene);
	}
} 

void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	for (int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 pos;
		Vertex vertex;
		pos.x = mesh->mVertices[i].x;
		pos.y = mesh->mVertices[i].y;
		pos.z = mesh->mVertices[i].z;
		vertex.position = pos;
		if (mesh->mNormals) {
			glm::vec3 normal;
			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;
			vertex.normal = normal;
		}
		else {
			vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		}

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else {
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
	Material mat;
	if (mesh->mMaterialIndex >= 0) {
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

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		for (auto iter : mp) {
			std::vector<Texture> maps = loadMaterialTextures(material,
				iter.first, iter.second);
			mat.texs.insert(mat.texs.end(), maps.begin(), maps.end());
		}
		aiColor3D color;
		material->Get(AI_MATKEY_COLOR_DIFFUSE, color); mat.colorDiffuse = glm::vec3(color.r, color.g, color.b);
		material->Get(AI_MATKEY_COLOR_SPECULAR, color); mat.colorSpecular = glm::vec3(color.r, color.g, color.b);
		material->Get(AI_MATKEY_COLOR_AMBIENT, color); mat.colorAmbiend = glm::vec3(color.r, color.g, color.b);
		material->Get(AI_MATKEY_COLOR_EMISSIVE, color); mat.colorEmissive = glm::vec3(color.r, color.g, color.b);
		material->Get(AI_MATKEY_COLOR_TRANSPARENT, color); mat.colorTransparent = glm::vec3(color.r, color.g, color.b);
		material->Get(AI_MATKEY_OPACITY, mat.opacity);
		material->Get(AI_MATKEY_SHININESS, mat.shininess);
		material->Get(AI_MATKEY_SHININESS_STRENGTH, mat.shininessStrength);
		material->Get(AI_MATKEY_REFLECTIVITY, mat.reflection);
		material->Get(AI_MATKEY_REFRACTI, mat.refraction);
		material->Get(AI_MATKEY_TRANSPARENCYFACTOR, mat.transparentFactor);
		material->Get(AI_MATKEY_SHADING_MODEL, mat.shadingModel);
		material->Get(AI_MATKEY_BLEND_FUNC, mat.blendFunc);
	}
	meshes.push_back(std::make_shared<Mesh*>(new Mesh(vertices, indices, mat, mesh->mName.C_Str(), mainProgram)));
	return;
}

void Model::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glm::mat4 modelMatrix = glm::mat4(1.0);
	mainProgram->SetMVP(modelMatrix, UIFramework::Instance().camera->GetViewMatirx(), UIFramework::Instance().camera->GetProjectionMatrix());
	mainProgram->use();
	for (auto mesh : meshes) {
		(*mesh)->Draw();
	}
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;

		mat->GetTexture(type, i, &str);
		std::cout << str.C_Str() << std::endl;   // ---> emtyp string
		std::cout << std::string(str.C_Str()) << std::endl;   // ---> emtyp string
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++) {
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip) {   // if texture hasn't been loaded already, load it
			Texture texture;
			//texture.id = TextureFromFile(str.C_Str(), "F:/GitHub/CGCenter/3dmodels/Kitchen/Kitchen/");
			texture.id = TextureFromFile(str.C_Str(), "F:/GitHub/CGCenter/3dmodels/home_v001/");

			texture.type = typeName;
			texture.path = str.C_Str();   // ---> emtyp string
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}


unsigned int Model::TextureFromFile(const char* path, const std::string& directory)
{
	std::string filename = std::string(path);  // ---> emtyp string
	filename = directory + filename;
	std::cout << filename << std::endl;   // ---> only show directory path
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	if (data) {
		GLenum format=3;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // read texture use 1 Byte alighment, avoid crash using 4 Byte alighment
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void Model::DeleteModel()
{
	for (auto mesh : meshes) {
		(*mesh)->DeleteMesh();
	}
	for (auto texture : textures_loaded) {
		glDeleteTextures(1, &texture.id);
	}
	meshes.clear();
}
