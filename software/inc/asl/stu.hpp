/*
 * stu.hpp
 *
 * Scheduling and Timing Utilities
 * This module allows registering of delayed callbacks, including repeating callbacks.
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#pragma once
#include <hal/generics.hpp>

namespace ASL
{
namespace STU
{

typedef uint32_t taskRef_t;
typedef uint32_t (*taskCallbackFn)(taskRef_t ref);

taskRef_t registerTask(taskCallbackFn function, uint16_t ticksUntilCall);
void cancelTask(taskRef_t ref);

void cancelAllTasks();

}
}
