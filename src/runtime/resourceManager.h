#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <memory>
#include "assetParser.h"
#include "texture.h"
#include "material.h"
#include "PointLight.h"
#include "arealight.h"
#include "spotlight.h"
#include "rectanglemesh.h"
#include "skybox.h"
#include "cubemesh.h"
#include "Framebuffer.h"
namespace Zxen {
	class Scene;
	class ZXEngine;
	class ResourceManager {
	public:
		ResourceManager()
		{
			parser = std::make_unique<AssetParser>(this);
		}
		~ResourceManager() = default;
		void LoadDataToScene(Scene* scene, const std::string& path, const std::string& skyboxpath);

		Texture2DPtr CreateTexture2D(std::string& name);
		CubemapPtr CreateCubemap(std::string& name);
		SkyboxPtr CreateSkyBox();
		MaterialPtr CreateMaterial();
		MeshPtr CreateMesh();
		PointLightPtr CreatePointLight();
		AreaLightPtr CreateAreaLight();
		SpotLightPtr CreateSpotLight();
		RectangleMeshPtr CreateAreaLightMesh();
		CubeMeshPtr CreateBuildInCube();
		ProgramPtr CreateProgram(const std::string& vertexPath, const std::string& fragmentPath);
		FrameBufferPtr CreateFrameBuffer();

		std::vector<TexturePtr>& GetTextures();
		std::vector<PointLightPtr>& GetPointLights();
		std::vector<AreaLightPtr>& GetAreaLights();
		std::vector<SpotLightPtr>& GetSpotLights();
		std::vector<MaterialPtr>& GetMaterials();
		std::vector<MeshPtr>& GetRenderableMeshes();
		std::vector<RectangleMeshPtr>& GetAreaLightMeshes();
		SkyboxPtr GetSkyBox();

	private:
		std::unique_ptr<AssetParser> parser;
		std::vector<TexturePtr> textures;
		std::vector<MaterialPtr> materials;
		std::vector<MeshPtr> meshes;
		std::vector<PointLightPtr> pointLights;
		std::vector<AreaLightPtr> areaLights;
		std::vector<SpotLightPtr> spotLights;
		std::vector<RectangleMeshPtr> areaLightMesh;
		std::vector<ProgramPtr> programs;
		std::vector<CubemapPtr> cubemaps;
		SkyboxPtr skybox;
	};
}
#endif // !RESOURCE_MANAGER_H
