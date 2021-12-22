#include "resourceManager.h"
#include "scene.h"
#include "zxEngine.h"
namespace Zxen {
	void ResourceManager::LoadDataToScene(Scene* scene, const std::string& path, const std::string& skyboxpath)
	{
		parser->LoadModelData(path);
		parser->LoadStaticLight();
		parser->LoadSkybox(skyboxpath);
	}

	//--------------- Create Method---------------
	Texture2DPtr ResourceManager::CreateTexture2D(std::string& name)
	{
		Texture2DPtr temp = std::make_shared<Texture2D>(name, textures.size() + 1);
		textures.push_back(temp);
		return temp;
	}

	MaterialPtr ResourceManager::CreateMaterial()
	{
		MaterialPtr temp = std::make_shared<Material>(materials.size() + 1);
		materials.push_back(temp);
		return temp;
	}

	MeshPtr ResourceManager::CreateMesh()
	{
		MeshPtr tmp = std::make_shared<Mesh>(meshes.size() + 1);
		meshes.push_back(tmp);
		return tmp;
	}

	PointLightPtr ResourceManager::CreatePointLight()
	{
		PointLightPtr tmp = std::make_shared<PointLight>();
		pointLights.push_back(tmp);
		return tmp;
	}
	AreaLightPtr ResourceManager::CreateAreaLight()
	{
		AreaLightPtr tmp = std::make_shared<AreaLight>();
		areaLights.push_back(tmp);
		return tmp;
	}

	SpotLightPtr ResourceManager::CreateSpotLight()
	{
		SpotLightPtr tmp = std::make_shared<SpotLight>();
		spotLights.push_back(tmp);
		return tmp;
	}

	RectangleMeshPtr ResourceManager::CreateAreaLightMesh()
	{
		RectangleMeshPtr tmp = std::make_shared<RectangleMesh>();
		areaLightMesh.push_back(tmp);
		return tmp;
	}

	ProgramPtr ResourceManager::CreateProgram(const std::string& vertexPath, const std::string& fragmentPath)
	{
		ProgramPtr tmp = std::make_shared<Program>(vertexPath, fragmentPath);
		programs.push_back(tmp);
		return tmp;
	}

	CubemapPtr ResourceManager::CreateCubemap(std::string& name)
	{
		CubemapPtr cubemap = std::make_shared<Cubemap>(name, textures.size() + 1);
		cubemaps.push_back(cubemap);
		return cubemap;
	}

	SkyboxPtr ResourceManager::CreateSkyBox()
	{
		skybox = std::make_shared<Skybox>();
		return skybox;
	}

	CubeMeshPtr ResourceManager::CreateBuildInCube()
	{
		CubeMeshPtr tmp = std::make_shared<CubeMesh>();
		return tmp;
	}

	FrameBufferPtr ResourceManager::CreateFrameBuffer()
	{
		return std::make_shared<FrameBuffer>();
	}

	//--------------- Get Method---------------
	std::vector<TexturePtr>& ResourceManager::GetTextures()
	{
		return textures;
	}
	std::vector<PointLightPtr>& ResourceManager::GetPointLights()
	{
		return pointLights;
	}

	std::vector<AreaLightPtr>& ResourceManager::GetAreaLights()
	{
		return areaLights;
	}

	std::vector<SpotLightPtr>& ResourceManager::GetSpotLights()
	{
		return spotLights;
	}

	std::vector<MaterialPtr>& ResourceManager::GetMaterials()
	{
		return materials;
	}

	SkyboxPtr ResourceManager::GetSkyBox()
	{
		return skybox;
	}

	std::vector<MeshPtr>& ResourceManager::GetRenderableMeshes()
	{
		return meshes;
	}

	std::vector<RectangleMeshPtr>& ResourceManager::GetAreaLightMeshes()
	{
		return areaLightMesh;
	}
}