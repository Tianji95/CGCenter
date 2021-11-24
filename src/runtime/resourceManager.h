#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

class ResourceManager {
public:
	static ResourceManager& GetInstance()
	{
		static ResourceManager inst;
		return inst;
	}
	
private:
	ResourceManager()
	{

	}
	~ResourceManager()
	{

	}
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
};
#endif // !RESOURCE_MANAGER_H
