#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>

#ifndef FMOD_ERROR_H
#define FMOD_ERROR_H

void FMODErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

#endif