#pragma once
#ifndef ASSET_PARSER_H
#define ASSET_PARSER_H
#include <string>
#include <vector>
#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <unordered_map>
#include <GL/glew.h>
#include "texture.h"
namespace Zxen {
	class ResourceManager;
	class AssetParser {
	public:
		AssetParser(ResourceManager* rsm) : rsm(rsm)
		{
		}
		~AssetParser() = default;
		void LoadModelData(const std::string& path);
		void LoadStaticLight();
		void LoadSkybox(const std::string& skyboxpath);
	private:
		std::unordered_map<int, GLenum> channel2Format = {
			{1,GL_RED},
			{3, GL_RGB},
			{4, GL_RGBA}
		};
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);
		void ProcessMaterial(const std::string& path, const aiScene* scene);
		std::vector<TexturePtr> loadMaterialTextures(const std::string& path, aiMaterial* mat, aiTextureType type, std::string& typeName);
		ResourceManager* rsm;
	};
}
#endif // !ASSET_PARSER_H
