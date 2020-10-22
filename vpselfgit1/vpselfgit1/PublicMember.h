
#include "vpModule.h"
#include "vpKernel.h"
#include "vpPagingMgr.h"
#include "vpSearchPath.h"
#include "vpPipeline.h"
#include "vpWindow.h"
#include "vpChannel.h"
#include "vpObserver.h"
#include "vpScene.h"
#include "vpTransform.h"
#include "vpObject.h"
#include "vpIsectorBump.h"
#include "vpIsectorTripod.h"
#include "vpIsectorServiceInline.h"
#include "vpGroundClamp.h"
#include "vpRecyclingService.h"
#include "vpEnvGlobals.h"
#include "vpEnv.h"
#include "vpEnvSun.h"
#include "vpEnvMoon.h"
#include "vpEnvSkyDome.h"
#include "vpEnvCloudLayer2D.h"
#include "vpEnvStars.h"
#include "vpEnvWind.h"
#include "vpMotionDrive.h"
#include "vpFxDebris.h"
#include "vpApp.h"

typedef vuVector< vuField< vuBase* > > InstancesList;

#pragma once

class PublicMember
{
public:
	PublicMember(void);
	~PublicMember(void);

	static void CTS_Define(void);

	static UINT CTS_RunBasicThread(LPVOID);

	static HWND CTS_RunningWindow; //ok

	static bool CTS_continueRunVP; //ok

	static CWinThread* CTS_vegaThread; //ok

	static InstancesList* CTS_s_pInstancesToUnref;

	static vpSearchPath* CTS_pSearchPath_mySearchPath;

	static vpScene* CTS_pScene_myScene;

	};

