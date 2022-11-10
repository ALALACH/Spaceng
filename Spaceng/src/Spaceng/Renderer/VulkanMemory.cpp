#include"PCH.h"
#include"VulkanMemory.h"




namespace Spaceng
{

	VkResult VulkanBufferMemory::AllocateBufferMemory(
		VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size,
		VkBuffer* buffer, VkDeviceMemory* memory, VkDescriptorBufferInfo BufferDescriptor, void* mapped , VkDevice Device,
		VkPhysicalDeviceMemoryProperties DeviceMemoryProperties,void* data, bool DescriptorAccess ,bool mapAccess)
	{
		VkBufferCreateInfo BufferCreateCI{};
		BufferCreateCI.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		BufferCreateCI.usage = usageFlags;
		BufferCreateCI.size = size;
		BufferCreateCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		VK_CHECK_RESULT(vkCreateBuffer(Device, &BufferCreateCI, nullptr, buffer));

		VkMemoryRequirements memReq;
		vkGetBufferMemoryRequirements(Device, *buffer, &memReq);

		VkBool32* memTypeFound = nullptr;
		VkMemoryAllocateInfo memAlloc{};
		memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memAlloc.allocationSize = memReq.size;
		memAlloc.memoryTypeIndex = getMemoryType(DeviceMemoryProperties, memoryPropertyFlags, memReq, memTypeFound);

		VkMemoryAllocateFlagsInfoKHR allocFlagsInfo{};
		if (usageFlags & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
			allocFlagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR;
			allocFlagsInfo.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;
			memAlloc.pNext = &allocFlagsInfo;
		}

		VK_CHECK_RESULT(vkAllocateMemory(Device, &memAlloc, nullptr, memory));

		if (data != nullptr)
		{
			VK_CHECK_RESULT(vkMapMemory(Device, *memory, 0, size, 0, &mapped));
			memcpy(mapped, data, size);
			// If host coherency hasn't been requested, do a manual flush to make writes visible
			if ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0)
			{
				VkMappedMemoryRange mappedRange{};
				mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
				mappedRange.memory = *memory;
				mappedRange.offset = 0;
				mappedRange.size = size;
				VK_CHECK_RESULT(vkFlushMappedMemoryRanges(Device, 1, &mappedRange));
			}
			vkUnmapMemory(Device, *memory);
		}
		if (!data && mapAccess) //UniformBuffers Specefic
		{
			VK_CHECK_RESULT(vkMapMemory(Device, *memory, 0, size, 0, &mapped));
		}
		if (DescriptorAccess)
		{
			BufferDescriptor.buffer = *buffer;
			BufferDescriptor.offset = 0;
			BufferDescriptor.range = VK_WHOLE_SIZE;
		}
		// Attach the memory to the buffer object
		VK_CHECK_RESULT(vkBindBufferMemory(Device, *buffer, *memory, 0));

		return VK_SUCCESS;
	}


	void VulkanBufferMemory::DeallocateBufferMemory(VkDevice Device ,VkBuffer* buffer , VkDeviceMemory* memory)
	{
		vkDestroyBuffer(Device, *buffer, nullptr);
		vkFreeMemory(Device, *memory, nullptr);
		//VK_SPEC : If a memory object is mapped at the time it is freed, it is implicitly unmapped.
	}


	uint32_t VulkanBufferMemory::getMemoryType(VkPhysicalDeviceMemoryProperties DeviceMemoryProperties, VkMemoryPropertyFlags memoryPropertyFlags,
		VkMemoryRequirements memReq, VkBool32* memTypeFound)
	{
		for (uint32_t i = 0; i < DeviceMemoryProperties.memoryTypeCount; i++)
		{
			if ((memReq.memoryTypeBits & 1) == 1)
			{
				if ((DeviceMemoryProperties.memoryTypes[i].propertyFlags & memoryPropertyFlags) == memoryPropertyFlags)
				{
					if (memTypeFound){
						*memTypeFound = true;
					}
					return i;
				}
			}
			memReq.memoryTypeBits >>= 1;
		}

		if (memTypeFound)
		{
			*memTypeFound = false;
			return 0;
		}
		else
		{
			SE_LOG_ERROR("Could not find a matching memory type");
			__debugbreak();
			return 0;
		}
	}

}