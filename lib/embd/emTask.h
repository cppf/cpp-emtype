/*
----------------------------------------------------------------------------------------
	emTask: Coroutine-based multi-tasking support library for emdb library (C/C++)
	File: emTask.h

    This file is part of embd. For more details, go through
	Readme.txt. For copyright information, go through copyright.txt.

    embd is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    embd is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with embd.  If not, see <http://www.gnu.org/licenses/>.
----------------------------------------------------------------------------------------
*/



/*
	emTask is a coroutine-based multi-tasking support library for emdb library. It has been developed for
	for being used in the development of the internet of things for AVR processors. For information,
	on its usage, please visit: https://github.com/wolfram77/embd.
*/



#ifndef	_emTask_h_
#define	_emTask_h_



// Requisite headers
#include "embd/emType.h"
#include "embd/emList.h"



// Select shorthand level
// 
// The default shorthand level is 2 i.e., members of this
// library can be accessed as tsk<function_name>. The
// shorthand level can be selected in the main header
// file of embd library
#ifndef	emTask_Shorthand
#define	emTask_Shorthand	2
#endif



// Individual Task Mold format
// 
// Each task needs to have an object of an individual task mold. It is used to store
// continuation line, task status, and state buffer. Depending on the size a state
// buffer required, an appropriate task mold needs to be chosen. State buffer is used
// to store state variables (non-global) which need to restored after the task has
// regained the CPU. The range is from 8 to 256 bytes (by default, provided in powers
// of 2). For any different size mold, MoldMake() can be used make a mold of desired
// size.
// 
#if	emTask_Shorthand == 0
#define	emTask_MoldMake(size)	\
typedef	struct _emTask_Mold##size	\
{	\
	int		Line;	\
	byte	Status;	\
	byte	State[size];	\
}emTask_Mold##size
#elif emTask_Shorthand == 1
#define	emTask_MoldMake(size)	\
typedef	struct _emTask_Mold##size	\
{	\
	int		Line;	\
	byte	Status;	\
	byte	State[size];	\
}emTask_Mold##size, task_Mold##size
#elif emTask_Shorthand == 2
#define	emTask_MoldMake(size)	\
typedef	struct _emTask_Mold##size	\
{	\
	int		Line;	\
	byte	Status;	\
	byte	State[size];	\
}emTask_Mold##size, task_Mold##size, tskMold##size
#endif

emTask_MoldMake(2);

emTask_MoldMake(4);

emTask_MoldMake(8);

emTask_MoldMake(16);

emTask_MoldMake(32);

emTask_MoldMake(64);

emTask_MoldMake(128);

emTask_MoldMake(256);

typedef byte (*emTask_FnPtr)(emTask_Mold256*);

typedef int emTask_Semaphore;

#if emTask_Shorthand >= 1
#define	task_MoldMake			emTask_MoldMake
#define	task_FnPtr				emTask_FnPtr
#define	task_Semaphore			emTask_Semaphore
#endif

#if	emTask_Shorthand >= 2
#define	tskMoldMake				emTask_MoldMake
#define	tskFnPtr				emTask_FnPtr
#define	tskSemaphore			emTask_Semaphore
#endif



// Task List Mold
// 
// An internal Task list is used to store pointers to task functions and pointers to
// their task object. This list is used to perform task switching. This list object is
// required while initializing emTask library. The list must be pre-iniltialized. To make
// a task list, first a task list mold of desired size can be made using TaskListMoldMake(),
// and then, an object needs to be created from the mold and initilized using emList library.
// 
#define	emList_TaskListMoldMake(size)	\
	emList_MoldMake(TaskList, emTask_Mold256*, emTask_FnPtr, size)

#if emTask_Shorthand >= 1
#define	list_TaskListMoldMake	emList_TaskListMoldMake
#endif

#if	emTask_Shorthand >= 2
#define	lstTaskListMoldMake		emList_TaskListMoldMake
#endif

emList_TaskListMoldMake(8);

emList_TaskListMoldMake(16);

emList_TaskListMoldMake(32);

emList_TaskListMoldMake(64);

emList_TaskListMoldMake(128);

emList_TaskListMoldMake(256);

#define	emList_TaskListMold		emList_TaskListMold256

#if emTask_Shorthand >= 1
#define	list_TaskListMold		emList_TaskListMold
#endif

#if	emTask_Shorthand >= 2
#define	lstTaskListMold			emList_TaskListMold
#endif

emList_TaskListMold*	emTask;
byte					emTask_RunIndex;	
byte					emTask_ExitStatus;

#if emTask_Shorthand >= 1
#define	task_RunIndex			emTask_RunIndex
#define	task_ExitStatus			emTask_ExitStatus
#endif

#if	emTask_Shorthand >= 2
#define	tskRunIndex				emTask_RunIndex
#define	tskExitStatus			emTask_ExitStatus
#endif



// Exit Status constants
#define	emTask_StatusRan			0
#define	emTask_StatusSwitched		1
#define	emTask_StatusSwitchedOut	2
#define	emTask_StatusWaiting		3
#define	emTask_ExitStatusOk			0
#define	emTask_ExitStatusError		0xFF

#if emTask_Shorthand >= 1
#define	task_StatusRan			emTask_StatusRan
#define	task_StatusSwitched		emTask_StatusSwitched
#define	task_StatusSwitchedOut	emTask_StatusSwitchedOut
#define	task_StatusWaiting		emTask_StatusWaiting
#define	task_StatusExited		emTask_StatusExited
#define	task_ExitStatusOk		emTask_ExitStatusOk
#define	task_ExitStatusError	emTask_ExitStatusError
#endif

#if	emTask_Shorthand >= 2
#define	tskStatusRan			emTask_StatusRan
#define	tskStatusSwitched		emTask_StatusSwitched
#define	tskStatusSwitchedOut	emTask_StatusSwitchedOut
#define	tskStatusWaiting		emTask_StatusWaiting
#define	tskStatusExited			emTask_StatusExited
#define	tskExitStatusOk			emTask_ExitStatusOk
#define	tskExitStatusError		emTask_ExitStatusError
#endif



// Function:
// InitMain(*task_list)
// 
// Initializes Task Management System before use. This is required before
// anything else. 
// 
// Parameters:
// task_list:	pre-initalized task list object for use internally by the emTask library
//				the size of task list defines the maximum number of concurrently running
//				tasks.
// 
// Returns:
// nothing
//
void emTask_InitMain(void* task_list)
{
	emTask = (emList_TaskListMold*)task_list;
	emTask_RunIndex = 0;
}

#if emTask_Shorthand >= 1
#define	task_InitMain			emTask_InitMain
#endif

#if	emTask_Shorthand >= 2
#define	tskInitMain				emTask_InitMain
#endif



// Function:
// Init(*task)
// 
// Initializes a task object (task) before use.
// 
// Parameters:
// task:	the task object to initialize
// 
// Returns:
// nothing
//
#define	emTask_Init(task)	\
	do{	\
		(*(task)).Line = 0;	\
		(*(task)).Status = 0;	\
	}while(0)

#if emTask_Shorthand >= 1
#define	task_Init				emTask_Init
#endif

#if	emTask_Shorthand >= 2
#define	tskInit					emTask_Init
#endif



// Function:
// GetNumTasks()
// GetNumTasks()
// 
// Gives the number of task running (added to the running list).
// 
// Parameters:
// none
// 
// Returns:
// num_tasks:	number of running tasks
//
#define	emTask_GetNumTasks()	\
	((*emTask).Count)

#if emTask_Shorthand >= 1
#define	task_GetNumTasks		emTask_GetNumTasks
#endif

#if	emTask_Shorthand >= 2
#define	tskGetNumTasks			emTask_GetNumTasks
#endif



// Function:
// GetFree()
// 
// Gives the number of free cells (space to add a task) available in task list.
// 
// Parameters:
// none
// 
// Returns:
// cells_free:	number of free cells in task list
//
#define	emTask_GetFree()	\
	(1 + (*emTask).Max - (*emTask).Count)

#if emTask_Shorthand >= 1
#define	task_GetFree			emTask_GetFree
#endif

#if	emTask_Shorthand >= 2
#define	tskGetFree				emTask_GetFree
#endif



// Function:
// Add(*task, *taskfn)
// 
// Adds a new task to the list of tasks to be executed. 
// 
// Parameters:
// task:	the task object for the task
// taskfn:	pointer to the task function (that is executed)
// 
// Returns:
// status:	0 for success, 0xFF for failed to add
// 
byte emTask_AddFn(void* task, emTask_FnPtr taskfn)
{
	return emList_Add(emTask, task, taskfn);
}

#define	emTask_Add(task, taskfn)	\
	emTask_AddFn(task, (emTask_FnPtr)(taskfn))

#if emTask_Shorthand >= 1
#define	task_Add				emTask_Add
#endif

#if	emTask_Shorthand >= 2
#define	tskAdd					emTask_Add
#endif



// Function:
// Remove(*task)
// 
// Removes an existing task from the list of tasks to be executed. 
// 
// Parameters:
// task:	the task object for the task to be removed
// 
// Returns:
// status:	0 for success, 0xFF for failed to add
// 
byte emTask_Remove(void* task)
{
	return emList_Remove(emTask, task);
}

#if emTask_Shorthand >= 1
#define	task_Remove				emTask_Remove
#endif

#if	emTask_Shorthand >= 2
#define	tskRemove				emTask_Remove
#endif



// Function:
// RemoveAll(exit_status)
// 
// Removes all running tasks, and thus the Run() returns with a exit status
// 
// Parameters:
// exit_status:	the exit status of removal of all tasks
// 
// Returns:
// nothing
//
void emTask_RemoveAll(byte exit_status)
{
	emList_Clear(emTask);
	emTask_RunIndex = 0;
	emTask_ExitStatus = exit_status;
}

#if emTask_Shorthand >= 1
#define	task_RemoveAll			emTask_RemoveAll
#endif

#if	emTask_Shorthand >= 2
#define	tskRemoveAll			emTask_RemoveAll
#endif



// Function:
// Run()
// 
// Executes all tasks and returns only when all tasks have been removed.
// 
// Parameters:
// none
// 
// Returns:
// status:	0 for success, 0xFF for failed
// 
byte emTask_Run()
{
	while(emTask_GetNumTasks())
	{
		if(emTask_RunIndex >= emTask_GetNumTasks()) emTask_RunIndex -= emTask_GetNumTasks();
		(*emTask).Key[emTask_RunIndex]->Status = (*(*emTask).Value[emTask_RunIndex])((*emTask).Key[emTask_RunIndex]);
		emTask_RunIndex++;
	}
	return emTask_ExitStatus;
}

#if emTask_Shorthand >= 1
#define	task_Run				emTask_Run
#endif

#if	emTask_Shorthand >= 2
#define	tskRun					emTask_Run
#endif



// Macro:
// TaskFn(taskname, taskmold)
// 
// A macro that is to be used to create a task function
// 
// Parameters:
// taskname:	name of the task function
// taskmold:	mold to be used with this task
// 
#define	emTask_TaskFn(taskname, taskmold)	\
	byte taskname(taskmold* emTask_Obj)

#if emTask_Shorthand >= 1
#define	task_TaskFn				emTask_TaskFn
#endif

#if	emTask_Shorthand >= 2
#define	tskTaskFn				emTask_TaskFn
#endif



// Function:
// Begin()
// 
// Used to begin a task. Must be used in the first line of a
// task function
// 
// Parameters:
// none
// 
// Returns:
// nothing
// 
#define	emTask_Begin()	\
	switch((*emTask_Obj).Line)	\
	{	\
		case 0:

#if emTask_Shorthand >= 1
#define	task_Begin				emTask_Begin
#endif

#if	emTask_Shorthand >= 2
#define	tskBegin				emTask_Begin
#endif



// Function:
// End()
// 
// Used to end a task. Must be used in the last line of a
// task function
// 
// Parameters:
// none
// 
// Returns:
// nothing
// 
#define	emTask_End()	\
		}	\
	(*emTask_Obj).Line = 0;	\
	return emTask_StatusRan

#if emTask_Shorthand >= 1
#define	task_End				emTask_End
#endif

#if	emTask_Shorthand >= 2
#define	tskEnd					emTask_End
#endif



// Function:
// SaveState(<state variables list>)
// 
// Save state variables to the state buffer of task object
// 
// Parameters:
// <state variables list>:	a list of state variables (as type1, state1, type2, state2, ...) to store separated with commas
// 
// Returns:
// nothing
// 
#define	emTask_EmptyFn()

#define	emTask_SaveState1(type1, state1)	\
	(*((type1*)(*emTask_Obj).State) = state1)

#define	emTask_SaveState2(type1, state1, type2, state2)	\
	do{	\
	*((type1*)(*emTask_Obj).State) = state1;	\
	*((type2*)((*emTask_Obj).State + sizeof(type1))) = state2;	\
	}while(0)

#define	emTask_SaveState3(type1, state1, type2, state2, type3, state3)	\
	do{	\
	*((type1*)(*emTask_Obj).State) = state1;	\
	*((type2*)((*emTask_Obj).State + sizeof(type1))) = state2;	\
	*((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2))) = state3;	\
	}while(0)

#define	emTask_SaveState4(type1, state1, type2, state2, type3, state3, type4, state4)	\
	do{	\
	*((type1*)(*emTask_Obj).State) = state1;	\
	*((type2*)((*emTask_Obj).State + sizeof(type1))) = state2;	\
	*((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2))) = state3;	\
	*((type4*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3))) = state4;	\
	}while(0)

#define	emTask_SaveState5(type1, state1, type2, state2, type3, state3, type4, state4, type5, state5)	\
	do{	\
	*((type1*)(*emTask_Obj).State) = state1;	\
	*((type2*)((*emTask_Obj).State + sizeof(type1))) = state2;	\
	*((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2))) = state3;	\
	*((type4*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3))) = state4;	\
	*((type5*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4))) = state5;	\
	}while(0)

#define	emTask_SaveState6(type1, state1, type2, state2, type3, state3, type4, state4, type5, state5, type6, state6)	\
	do{	\
	*((type1*)(*emTask_Obj).State) = state1;	\
	*((type2*)((*emTask_Obj).State + sizeof(type1))) = state2;	\
	*((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2))) = state3;	\
	*((type4*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3))) = state4;	\
	*((type5*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4))) = state5;	\
	*((type6*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5))) = state6;	\
	}while(0)

#define	emTask_SaveState7(type1, state1, type2, state2, type3, state3, type4, state4, type5, state5, type6, state6, type7, state7)	\
	do{	\
	*((type1*)(*emTask_Obj).State) = state1;	\
	*((type2*)((*emTask_Obj).State + sizeof(type1))) = state2;	\
	*((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2))) = state3;	\
	*((type4*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3))) = state4;	\
	*((type5*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4))) = state5;	\
	*((type6*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5))) = state6;	\
	*((type7*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5) + sizeof(type6))) = state7;	\
	}while(0)

#define	emTask_SaveState8(type1, state1, type2, state2, type3, state3, type4, state4, type5, state5, type6, state6, type7, state7, type8, state8)	\
	do{	\
	*((type1*)(*emTask_Obj).State) = state1;	\
	*((type2*)((*emTask_Obj).State + sizeof(type1))) = state2;	\
	*((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2))) = state3;	\
	*((type4*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3))) = state4;	\
	*((type5*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4))) = state5;	\
	*((type6*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5))) = state6;	\
	*((type7*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5) + sizeof(type6))) = state7;	\
	*((type8*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5) + sizeof(type6) + sizeof(type7))) = state8;	\
	}while(0)

#define	emTask_SaveState(...)	\
	Macro(Macro17(_0, __VA_ARGS__, emTask_SaveState8, _15, emTask_SaveState7, _13, emTask_SaveState6, _11, emTask_SaveState5, _9, emTask_SaveState4, _7, emTask_SaveState3, _5, emTask_SaveState2, _3, emTask_SaveState1, emTask_EmptyFn, emTask_EmptyFn)(__VA_ARGS__))

#if emTask_Shorthand >= 1
#define	task_SaveState			emTask_SaveState
#endif

#if	emTask_Shorthand >= 2
#define	tskSaveState			emTask_SaveState
#endif



// Function:
// LoadState(<state variables list>)
// 
// Load state variables from the state buffer of task object
// 
// Parameters:
// <state variables list>:	a list of state variables (as type1, state1, type2, state2, ...) to load separated with commas
// 
// Returns:
// nothing
// 
#define	emTask_LoadState1(type1, state1)	\
	(state1 = *((type1*)(*emTask_Obj).State))

#define	emTask_LoadState2(type1, state1, type2, state2)	\
	do{	\
	state1 = *((type1*)(*emTask_Obj).State);	\
	state2 = *((type2*)((*emTask_Obj).State + sizeof(type1)));	\
	}while(0)

#define	emTask_LoadState3(type1, state1, type2, state2, type3, state3)	\
	do{	\
	state1 = *((type1*)(*emTask_Obj).State);	\
	state2 = *((type2*)((*emTask_Obj).State + sizeof(type1)));	\
	state3 = *((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2)));	\
	}while(0)

#define	emTask_LoadState4(type1, state1, type2, state2, type3, state3, type4, state4)	\
	do{	\
	state1 = *((type1*)(*emTask_Obj).State);	\
	state2 = *((type2*)((*emTask_Obj).State + sizeof(type1)));	\
	state3 = *((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2)));	\
	state4 = *((type4*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3)));	\
	}while(0)

#define	emTask_LoadState5(type1, state1, type2, state2, type3, state3, type4, state4, type5, state5)	\
	do{	\
	state1 = *((type1*)(*emTask_Obj).State);	\
	state2 = *((type2*)((*emTask_Obj).State + sizeof(type1)));	\
	state3 = *((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2)));	\
	state4 = *((type4*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3)));	\
	state5 = *((type5*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4)));	\
	}while(0)

#define	emTask_LoadState6(type1, state1, type2, state2, type3, state3, type4, state4, type5, state5, type6, state6)	\
	do{	\
	state1 = *((type1*)(*emTask_Obj).State);	\
	state2 = *((type2*)((*emTask_Obj).State + sizeof(type1)));	\
	state3 = *((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2)));	\
	state4 = *((type4*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3)));	\
	state5 = *((type5*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4)));	\
	state6 = *((type6*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5)));	\
	}while(0)

#define	emTask_LoadState7(type1, state1, type2, state2, type3, state3, type4, state4, type5, state5, type6, state6, type7, state7)	\
	do{	\
	state1 = *((type1*)(*emTask_Obj).State);	\
	state2 = *((type2*)((*emTask_Obj).State + sizeof(type1)));	\
	state3 = *((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2)));	\
	state4 = *((type4*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3)));	\
	state5 = *((type5*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4)));	\
	state6 = *((type6*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5)));	\
	state7 = *((type7*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5) + sizeof(type6)));	\
	}while(0)

#define	emTask_LoadState8(type1, state1, type2, state2, type3, state3, type4, state4, type5, state5, type6, state6, type7, state7, type8, state8)	\
	do{	\
	state1 = *((type1*)(*emTask_Obj).State);	\
	state2 = *((type2*)((*emTask_Obj).State + sizeof(type1)));	\
	state3 = *((type3*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2)));	\
	state4 = *((type4*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3)));	\
	state5 = *((type5*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4)));	\
	state6 = *((type6*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5)));	\
	state7 = *((type7*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5) + sizeof(type6)));	\
	state8 = *((type8*)((*emTask_Obj).State + sizeof(type1) + sizeof(type2) + sizeof(type3) + sizeof(type4) + sizeof(type5) + sizeof(type6) + sizeof(type7)));	\
	}while(0)

#define	emTask_LoadState(...)	\
	Macro(Macro17(_0, __VA_ARGS__, emTask_LoadState8, _15, emTask_LoadState7, _13, emTask_LoadState6, _11, emTask_LoadState5, _9, emTask_LoadState4, _7, emTask_LoadState3, _5, emTask_LoadState2, _3, emTask_LoadState1, emTask_EmptyFn, emTask_EmptyFn)(__VA_ARGS__))

#if emTask_Shorthand >= 1
#define	task_LoadState			emTask_LoadState
#endif

#if	emTask_Shorthand >= 2
#define	tskLoadState			emTask_LoadState
#endif



// Function:
// SwitchOut()
// 
// Used to switch out a task. Next time, the task will start from begining.
// 
// Parameters:
// none
// 
// Returns:
// nothing
// 
#define	emTask_SwitchOut()	\
	do{	\
	(*emTask_Obj).Line = 0;	\
	return emTask_StatusSwitchedOut;	\
	}while(0)

#if emTask_Shorthand >= 1
#define	task_SwitchOut			emTask_SwitchOut
#endif

#if	emTask_Shorthand >= 2
#define	tskSwitchOut			emTask_SwitchOut
#endif



// Function:
// Switch(<state variables list>)
// 
// Used to switch from task. If no state variables are present in task, use Switch(), else if state variables are presNext time, the task will continue.
// 
// Parameters:
// <state variables list>:	a list of state variables (as type1, state1, type2, state2, ...) to store separated with commas
// 
// Returns:
// nothing
// 
#define	emTask_Switch(...)	\
	do{	\
	(*emTask_Obj).Line = __LINE__;	\
	emTask_SaveState(__VA_ARGS__);	\
	return emTask_StatusSwitched;	\
	case __LINE__:	\
	emTask_LoadState(__VA_ARGS__);	\
	}while(0)

#if emTask_Shorthand >= 1
#define	task_Switch				emTask_Switch
#endif

#if	emTask_Shorthand >= 2
#define	tskSwitch				emTask_Switch
#endif



// Function:
// WaitWhile(waitcond, <state variables list>)
// 
// Used to wait while a condition is satisfied.
// 
// Parameters:
// waitcond:	wait condition (will wait as long as this condition is true)
// <state variables list>:	a list of state variables (as type1, state1, type2, state2, ...) to store separated with commas
// 
// Returns:
// nothing
// 
#define	emTask_WaitWhile(waitcond, ...)	\
	do{	\
	(*emTask_Obj).Line = __LINE__;	\
	emTask_SaveState(__VA_ARGS__);	\
	case __LINE__:	\
	if(waitcond) return emTask_StatusWaiting;	\
	emTask_LoadState(__VA_ARGS__);	\
	}while(0)

#if emTask_Shorthand >= 1
#define	task_WaitWhile			emTask_WaitWhile
#endif

#if	emTask_Shorthand >= 2
#define	tskWaitWhile			emTask_WaitWhile
#endif



// Function:
// WaitUntil(waitcond, <state variables list>)
// 
// Used to wait until a condition is satisfied.
// 
// Parameters:
// waitcond:	wait condition (will wait until this condition is true)
// <state variables list>:	a list of state variables (as type1, state1, type2, state2, ...) to store separated with commas
// 
// Returns:
// nothing
// 
#define	emTask_WaitUntil(waitcond, ...)	\
	emTask_WaitWhile(!(waitcond), __VA_ARGS__)

#if emTask_Shorthand >= 1
#define	task_WaitUntil			emTask_WaitUntil
#endif

#if	emTask_Shorthand >= 2
#define	tskWaitUntil			emTask_WaitUntil
#endif



// Function:
// Exit(exitstatus)
// 
// Used to exit from task. The task is removed from execution.
// 
// Parameters:
// exitstatus:	exit status of the task
// 
// Returns:
// nothing
// 
#define	emTask_Exit(exitstatus)	\
	do{	\
	emTask_Remove(emTask_Obj);	\
	return exitstatus;	\
	}while(0)

#if emTask_Shorthand >= 1
#define	task_Exit				emTask_Exit
#endif

#if	emTask_Shorthand >= 2
#define	tskExit					emTask_Exit
#endif



// Function:
// SemWait(sem, <state variables list>)
// 
// Used to wait for a semaphore. Can be used to write a critical section.
// 
// Parameters:
// sem:			semaphore used
// <state variables list>:	a list of state variables (as type1, state1, type2, state2, ...) to store separated with commas
// 
// Returns:
// nothing
// 
#define	emTask_SemWait(sem, ...)	\
	do{	\
	emTask_WaitUntil(sem > 0, __VA_ARGS__);	\
	sem--;	\
	}while(0)

#if emTask_Shorthand >= 1
#define	task_SemWait			emTask_SemWait
#endif

#if	emTask_Shorthand >= 2
#define	tskSemWait				emTask_SemWait
#endif



// Function:
// SemSignal(sem)
// 
// Used to signal with a semaphore. Can be used to write a critical section.
// 
// Parameters:
// sem:			semaphore used
// 
// Returns:
// nothing
// 
#define	emTask_SemSignal(sem)	\
	sem++

#if emTask_Shorthand >= 1
#define	task_SemSignal			emTask_SemSignal
#endif

#if	emTask_Shorthand >= 2
#define	tskSemSignal			emTask_SemSignal
#endif



#endif
