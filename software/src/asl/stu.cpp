/*
 * stu.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#include <asl/stu.hpp>

#include <hal/mcu.hpp>

#include <vector>

namespace ASL {
namespace STU {

struct TaskData_t
{
	taskRef_t reference;
	uint32_t nextInvocationUs;
	taskCallbackFn callback;
};

static taskRef_t maxAllocated = 0U;
static std::vector<taskRef_t> toAllocate;
static std::vector<TaskData_t> activeTasks;

static void allocateMoreIDs()
{
	for (uint32_t i = maxAllocated; i < maxAllocated + 100; ++i)
	{
		toAllocate.push_back(i);
	}
}

taskRef_t registerTask (taskCallbackFn function, uint32_t delayMicroseconds)
{
	if (toAllocate.empty())
	{
		allocateMoreIDs();
	}

	TaskData_t data;
	data.reference = toAllocate.back();
	toAllocate.pop_back();

	data.nextInvocationUs = HAL::MCU::getMicroseconds() + delayMicroseconds;
	data.callback = function;

	activeTasks.push_back(std::move(data));

	return data.reference;
}

void cancelTask (taskRef_t ref)
{
	bool found = false;
	std::vector<TaskData_t>::iterator value;

	for (auto it = activeTasks.begin(); it != activeTasks.end(); ++it)
	{
		if (it->reference == ref)
		{
			found = true;
			value = it;
		}
	}

	if (true == found)
	{
		activeTasks.erase(value);
	}
}

void cancelAllTasks()
{

}

}
}
