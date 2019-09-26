#ifndef PROCESS_HPP
#define PROCESS_HPP

namespace BEETLE {namespace PROCESS
{
	enum class STATUS
	{
		RUNNING, SUSPENDED
	};

	struct Process
	{
		const unsigned int pid;
		STATUS status;
		Process* parent;
		void* elfExecutable;
	};

	//TODO::
	// * only return the PID and use it to identify the process image
	// * automatically get the caller PID
	Process& createNewProcess (const Process& parentProcess);
	void launchProcess (Process& processToLaunche);
}}

#endif