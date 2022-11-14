#pragma once
#include "VulkanCore.h"
#include "VulkanMemory.h"

#include "glm/glm/glm.hpp"


namespace Spaceng
{

	enum AssetType
	{
		Texture,
		MeshType,
		Simple_Mesh
	};

	class VkGLTFAsset
	{
		friend class VulkanRenderer;
	public:
		VkGLTFAsset(std::string name ,AssetType type);
		~VkGLTFAsset();

		void LoadFromFile(std::string filename);
		inline const std::string getName() { return Name; };
		inline const uint32_t getType() { return Type; };

	private:
		uint32_t Type;
		std::string Name;

		Buffer UniformBuffer;
		VkDescriptorImageInfo TextureDescriptor; // to do : implement inside texture structure like BufferDescriptor;

		VkDescriptorSetLayout DescriptorSetLayout = VK_NULL_HANDLE;
		VkDescriptorPool DescriptorPool = VK_NULL_HANDLE;
		VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;

		struct UBMatrix {
			glm::mat4 projection;
			glm::mat4 model;
			glm::mat4 view;
			glm::vec3 camPos;
		}UBOMatrices;


		
	};
}
