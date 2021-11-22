#pragma once
#ifndef PROGRAM_H
#define PROGRAM_H
#include "shaderBase.h"
#include <unordered_map>
#include <memory>
#include "config.h"

enum class ProgramType {
	Test = 0,
	Main = 1,
	SkyBox = 2,
	SimpleColored = 3,
	SimpleDepthMapGenerate = 4,
	VSMGenerate = 5,
};

class Program {
public:
	std::shared_ptr<ShaderBase> GetProgram(ProgramType type)
	{
		if (mp.find(type) == mp.end()) {
			return nullptr;
		}
		return mp[type];
	}
	static Program& GetInstance()
	{
		static Program instance;
		return instance;
	}
private:
	Program(){
		mp[ProgramType::Test] = std::make_shared<ShaderBase>(SRC_BASE_PATH + "src/shaders/test_textured.vert", SRC_BASE_PATH + "src/shaders/test_textured.frag");
		mp[ProgramType::Test]->ProduceProgram();

		mp[ProgramType::Main] = std::make_shared<ShaderBase>(SRC_BASE_PATH + "src/shaders/main.vert", SRC_BASE_PATH + "src/shaders/main.frag");
		mp[ProgramType::Main]->ProduceProgram();

		mp[ProgramType::SkyBox] = std::make_shared<ShaderBase>(SRC_BASE_PATH + "src/shaders/skybox.vert", SRC_BASE_PATH + "src/shaders/skybox.frag");
		mp[ProgramType::SkyBox]->ProduceProgram();

		mp[ProgramType::SimpleColored] = std::make_shared<ShaderBase>(SRC_BASE_PATH + "src/shaders/simple_colored_mesh.vert", SRC_BASE_PATH + "src/shaders/simple_colored_mesh.frag");
		mp[ProgramType::SimpleColored]->ProduceProgram();

		mp[ProgramType::SimpleDepthMapGenerate] = std::make_shared<ShaderBase>(SRC_BASE_PATH + "src/shaders/simple_depth_map_generate.vert", SRC_BASE_PATH + "src/shaders/simple_depth_map_generate.frag");
		mp[ProgramType::SimpleDepthMapGenerate]->ProduceProgram();

		mp[ProgramType::VSMGenerate] = std::make_shared<ShaderBase>(SRC_BASE_PATH + "src/shaders/vsm_generate.vert", SRC_BASE_PATH + "src/shaders/vsm_generate.frag");
		mp[ProgramType::VSMGenerate]->ProduceProgram();
	}
	~Program() {	 }
	Program(const Program&);
	Program& operator=(const Program&);
	std::unordered_map<ProgramType, std::shared_ptr<ShaderBase>> mp;
};

#endif // !PROGRAM_H
