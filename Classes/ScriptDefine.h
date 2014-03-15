#ifndef __SCRIPTDEFINE_H__
#define __SCRIPTDEFINE_H__

//////////////////////////////////////////////////////////////////////////
//include
#include "GlobalDefine.h"
#include "ScriptBase.h"
#include "Actor.h"
#include "CameraActor.h"
#include "Comet.h"
#include "Meteorolite.h"
#include "FixedStar.h"
#include "Planet.h"
#include "BlackHole.h"
//////////////////////////////////////////////////////////////////////////

static ScriptBase* _createScript(int tag)
{
	ScriptBase* pScript = NULL;
	switch (tag / ID_MASK)
	{
		//////////////////////////////////////////////////////////////////////////
		//create
	case ID_CAMERA:
		pScript = new CameraActor();
		break;
	case ID_COMET:
		pScript = new Comet();
		break;
	case ID_METEOROLITE:
		pScript = new Meteorolite();
		break;
	case ID_FIXEDSTAR:
		pScript = new FixedStar();
		break;
	case ID_PLANET:
		pScript = new Planet();
		break;
	case ID_BLACKHOLE:
		pScript = new BlackHole();
		break;
		//////////////////////////////////////////////////////////////////////////
	}

	return pScript;
}

#endif