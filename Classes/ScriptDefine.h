#ifndef __SCRIPTDEFINE_H__
#define __SCRIPTDEFINE_H__

//////////////////////////////////////////////////////////////////////////
//include
#include "ScriptBase.h"

#include "Actor.h"
#include "Planet.h"
//////////////////////////////////////////////////////////////////////////
//id
#define ID_FILTER 100

#define ID_EARTH 101
#define ID_MOON 102
//////////////////////////////////////////////////////////////////////////

static ScriptBase* _createScript(int tag)
{
	ScriptBase* pScript = NULL;
	switch (tag / ID_FILTER)
	{
		//////////////////////////////////////////////////////////////////////////
		//create
	case ID_EARTH:
		pScript = new Planet();
		break;
	case ID_MOON:
		pScript = new Planet();
		break;
		//////////////////////////////////////////////////////////////////////////
	}

	return pScript;
}

#endif