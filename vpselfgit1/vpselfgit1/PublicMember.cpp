#include "stdafx.h"
#include "PublicMember.h"

HWND PublicMember::CTS_RunningWindow = NULL;

bool PublicMember::CTS_continueRunVP = NULL;

CWinThread* PublicMember::CTS_vegaThread = NULL;

InstancesList* PublicMember::CTS_s_pInstancesToUnref = NULL;

vpSearchPath* PublicMember::CTS_pSearchPath_mySearchPath = NULL;

vpScene* PublicMember::CTS_pScene_myScene = NULL;



PublicMember::PublicMember()
{
}


PublicMember::~PublicMember()
{
}

void PublicMember::CTS_Define(void)
{
	PublicMember::CTS_s_pInstancesToUnref = new InstancesList;

	vpModule::initializeModule("vpEnv");
	vpModule::initializeModule("vpMotion");
	vpModule::initializeModule("vpFx");

	//建立路径搜索实例
	vpKernel* pKernel_myKernel = vpKernel::instance();
	pKernel_myKernel->setNotifyLevel(vuNotify::LEVEL_WARN);
	pKernel_myKernel->setNotifyColorEnable(false);
	pKernel_myKernel->setPriority(vuThread::PRIORITY_NORMAL);
	pKernel_myKernel->setProcessor(-1);
	pKernel_myKernel->setFrameRateLimiterEnable(true);
	pKernel_myKernel->setDesiredFrameRate(0);
	pKernel_myKernel->setNotifyClassTypeMode(vuNotify::CLASS_TYPE_MODE_INCLUSIVE);

	//vpPagingMgr* pPagingMgr_myPagingMgr = vpPagingMgr::instance();
	//pPagingMgr_myPagingMgr->setAsynchronousPagingQueueEnable(true);
	//pPagingMgr_myPagingMgr->setAsynchronousFileIOEnable(false);
	//pPagingMgr_myPagingMgr->setDefaultQueuePriority(vuThread::PRIORITY_NORMAL);
	//pPagingMgr_myPagingMgr->setDefaultQueueProcessor(0);
	//pPagingMgr_myPagingMgr->setMaxNumPageablesToBeCompletedPerFrame(-1);



	PublicMember::CTS_pSearchPath_mySearchPath = vpSearchPath::instance();
	PublicMember::CTS_pSearchPath_mySearchPath->append("$(PRESAGIS_VEGA_PRIME_RESOURCE_6)/resources/data/databases/camp_pendleton/");
	PublicMember::CTS_pSearchPath_mySearchPath->append("D:/Vega prime resources/resources/tutorials/vegaprime/desktop_tutor/data/eggbertwonky");
	PublicMember::CTS_pSearchPath_mySearchPath->append("D:/Vega prime resources/resources/tutorials/vegaprime/desktop_tutor/data/humv-dirty");
	PublicMember::CTS_pSearchPath_mySearchPath->append("D:/Vega prime resources/resources/tutorials/vegaprime/round_earth_marine_tutor/data/ds15_land-geo-land-only-geo");
	PublicMember::CTS_pSearchPath_mySearchPath->append("D:/Vega prime 2013/Suite13/Vega_Prime/resources/data/databases/camp_pendleton");
	PublicMember::CTS_pSearchPath_mySearchPath->append("D:/Vega prime 2013/Suite13/Vega_Prime/resources/data/models/hotel");
	PublicMember::CTS_pSearchPath_mySearchPath->append("D:/Vega prime 2013/Suite13/Vega_Prime/resources/data/databases/paloalto");
	PublicMember::CTS_pSearchPath_mySearchPath->append("D:/Vega prime 2013/Suite13/Vega_Prime/resources/data/databases/oceanside/externals");
	PublicMember::CTS_pSearchPath_mySearchPath->append("D:/Vega prime 2013/Suite13/Vega_Prime/resources/data/databases/ladbm_one_level/data");
	PublicMember::CTS_pSearchPath_mySearchPath->append("D:/Vega prime 2013/Suite13/Vega_Prime/resources/data/models/cargo");

	vpPipeline* pPipeline_myPipeline = new vpPipeline();
	pPipeline_myPipeline->setName("myPipeline");
	pPipeline_myPipeline->setMultiThread(vsPipeline::MULTITHREAD_INLINE);
	pPipeline_myPipeline->setId(0);
	pPipeline_myPipeline->setNumCullThreads(0);
	pPipeline_myPipeline->setCullThreadPriority(vuThread::PRIORITY_NORMAL);
	pPipeline_myPipeline->setCullThreadProcessor(-1);
	pPipeline_myPipeline->setDrawThreadPriority(vuThread::PRIORITY_NORMAL);
	pPipeline_myPipeline->setDrawThreadProcessor(-1);
	pPipeline_myPipeline->setBeginFrameOnVsyncEnable(false);
	pPipeline_myPipeline->setDesiredTextureSubloadTime(-1);
	pPipeline_myPipeline->setDesiredBufferObjectSubloadTime(-1);
	pPipeline_myPipeline->setDesiredShaderApplyTime(-1);
	pPipeline_myPipeline->setTextureSubloadByteAmount(-1);
	pPipeline_myPipeline->setBufferObjectSubloadByteAmount(-1);
	pPipeline_myPipeline->setTextureSubloadingGain(1);
	pPipeline_myPipeline->setBufferObjectSubloadingGain(1);
	pPipeline_myPipeline->setGraphicsResourceApplyThreadMode(vsPipeline::APPLY_ASYNCHRONOUS_GRAPHICS, false);
	pPipeline_myPipeline->setGraphicsResourceApplyThreadMode(vsPipeline::APPLY_ASYNCHRONOUS_TEXTURE_SUBLOAD, false);
	pPipeline_myPipeline->setGraphicsResourceApplyThreadMode(vsPipeline::APPLY_ASYNCHRONOUS_BUFFER_OBJECT_SUBLOAD, false);
	pPipeline_myPipeline->setGraphicsResourceThreadPriority(vuThread::PRIORITY_ABOVE_NORMAL);
	pPipeline_myPipeline->setGraphicsResourceThreadProcessor(-1);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pPipeline_myPipeline);

	vpWindow* pWindow_myWindow = new vpWindow();
	pWindow_myWindow->setName("myWindow");
	pWindow_myWindow->setLabel("Vega Prime Window");
	pWindow_myWindow->setOrigin(0, 0);
	pWindow_myWindow->setSize(450, 300);
	pWindow_myWindow->setFullScreenEnable(false);
	pWindow_myWindow->setBorderEnable(true);
	pWindow_myWindow->setInputEnable(true);
	pWindow_myWindow->setCursorEnable(true);
	pWindow_myWindow->setStereoEnable(false);
	pWindow_myWindow->setNumColorBits(8);
	pWindow_myWindow->setNumAlphaBits(8);
	pWindow_myWindow->setNumDepthBits(24);
	pWindow_myWindow->setNumStencilBits(0);
	pWindow_myWindow->setNumAccumColorBits(0);
	pWindow_myWindow->setNumAccumAlphaBits(0);
	pWindow_myWindow->setNumMultiSampleBits(4);
	pWindow_myWindow->setSwapInterval(1);
	pWindow_myWindow->setSwapSyncEnable(false);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pWindow_myWindow);

	vpChannel* pChannel_myChannel = new vpChannel();
	pChannel_myChannel->setName("myChannel");
	pChannel_myChannel->setOffsetTranslate(0, 0, 0);
	pChannel_myChannel->setOffsetRotate(0, 0, 0);
	pChannel_myChannel->setCullMask(0x0FFFFFFFF);
	pChannel_myChannel->setRenderMask(0x0FFFFFFFF);
	pChannel_myChannel->setClearColor(0.000000f, 0.500000f, 1.000000f, 0.000000f);
	pChannel_myChannel->setClearBuffers(0x03);
	pChannel_myChannel->setDrawArea(0, 1, 0, 1);
	pChannel_myChannel->setFOVSymmetric(45.000000f, -1.000000f);
	pChannel_myChannel->setNearFar(1.000000f, 110000.000000f);
	pChannel_myChannel->setLODVisibilityRangeScale(1);
	pChannel_myChannel->setLODTransitionRangeScale(1);
	pChannel_myChannel->setFOVScale(-1);
	pChannel_myChannel->setCullThreadPriority(vuThread::PRIORITY_NORMAL);
	pChannel_myChannel->setCullThreadProcessor(-1);
	pChannel_myChannel->setGraphicsModeEnable(vpChannel::GRAPHICS_MODE_WIREFRAME, false);
	pChannel_myChannel->setGraphicsModeEnable(vpChannel::GRAPHICS_MODE_TRANSPARENCY, true);
	pChannel_myChannel->setGraphicsModeEnable(vpChannel::GRAPHICS_MODE_TEXTURE, true);
	pChannel_myChannel->setGraphicsModeEnable(vpChannel::GRAPHICS_MODE_LIGHT, true);
	pChannel_myChannel->setGraphicsModeEnable(vpChannel::GRAPHICS_MODE_FOG, true);
	pChannel_myChannel->setGraphicsModeEnable(vpChannel::GRAPHICS_MODE_SHADERS, true);
	pChannel_myChannel->setMultiSample(vpChannel::MULTISAMPLE_ANTIALIAS);
	pChannel_myChannel->setStatisticsPage(vpChannel::PAGE_OFF);
	pChannel_myChannel->setCullBoundingBoxTestEnable(false);
	pChannel_myChannel->setOpaqueSort(vpChannel::OPAQUE_SORT_TEXTURE, vpChannel::OPAQUE_SORT_MATERIAL);
	pChannel_myChannel->setTransparentSort(vpChannel::TRANSPARENT_SORT_DEPTH);
	pChannel_myChannel->setDrawBuffer(vpChannel::DRAW_BUFFER_DEFAULT);
	pChannel_myChannel->setStressEnable(false);
	pChannel_myChannel->setStressParameters(1, 20, 0.75, 0.5, 2);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pChannel_myChannel);

	vpObserver* pObserver_myObserver = new vpObserver();
	pObserver_myObserver->setName("myObserver");
	pObserver_myObserver->setStrategyEnable(false);
	pObserver_myObserver->setTranslate(0, 0, 343.347);
	pObserver_myObserver->setRotate(0, -7, 0);
	pObserver_myObserver->setLatencyCriticalEnable(false);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pObserver_myObserver);

	vpScene* pScene_myScene = new vpScene();
	pScene_myScene->setName("myScene");

	PublicMember::CTS_s_pInstancesToUnref->push_back(PublicMember::CTS_pScene_myScene);

	vpTransform* pTransform_hummerTransform = new vpTransform();
	pTransform_hummerTransform->setName("hummerTransform");
	pTransform_hummerTransform->setCullMask(0x0FFFFFFFF);
	pTransform_hummerTransform->setRenderMask(0x0FFFFFFFF);
	pTransform_hummerTransform->setIsectMask(0x0FFFFFFFF);
	pTransform_hummerTransform->setStrategyEnable(true);
	pTransform_hummerTransform->setTranslate(0, -30, 5);
	pTransform_hummerTransform->setRotate(0, 0, 0);
	pTransform_hummerTransform->setScale(1, 1, 1);
	pTransform_hummerTransform->setStaticEnable(false);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pTransform_hummerTransform);

	vpObject* pObject_terrain = new vpObject();
	pObject_terrain->setName("terrain");
	pObject_terrain->setCullMask(0x0FFFFFFFF);
	pObject_terrain->setRenderMask(0x0FFFFFFFF);
	pObject_terrain->setIsectMask(0x0FFFFFFFF);
	pObject_terrain->setStrategyEnable(false);
	pObject_terrain->setTranslate(2500, 2500, 0);
	pObject_terrain->setRotate(0, 0, 0);
	pObject_terrain->setScale(1, 1, 1);
	pObject_terrain->setStaticEnable(false);
	pObject_terrain->setFileName("c002-r002.flt");
	pObject_terrain->setAutoPage(vpObject::AUTO_PAGE_SYNCHRONOUS);
	pObject_terrain->setManualLODChild(-1);
	pObject_terrain->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_PRESERVE_LIGHT_SOURCES, false);
	pObject_terrain->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SIGNIFICANT_SIZE, false);
	pObject_terrain->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_CONTROLS, true);
	pObject_terrain->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_ANIMATIONS, true);
	pObject_terrain->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_APPEARANCES, true);
	pObject_terrain->setLoaderDetailMultiTextureStage(-1);
	pObject_terrain->setLoaderBlendTolerance(0.050000f);
	pObject_terrain->setLoaderUnits(vsNodeLoader::Data::LOADER_UNITS_METERS);
	pObject_terrain->setBuilderNormalMode(vsNodeLoader::Data::BUILDER_NORMAL_MODE_PRESERVE);
	pObject_terrain->setBuilderTangentMode(vsNodeLoader::Data::BUILDER_TANGENT_MODE_GENERATE_PER_VERTEX_PER_PRIMITIVE_AND_ANGLE_WEIGHTED);
	pObject_terrain->setBuilderTangentGenerationMode(vsNodeLoader::Data::BUILDER_TANGENT_GENERATION_MODE_GENERATE_AS_NEEDED);
	pObject_terrain->setBuilderColorTolerance(0.001000f);
	pObject_terrain->setBuilderNormalTolerance(0.860000f);
	pObject_terrain->setGeometryOption(vsNodeLoader::Data::GEOMETRY_OPTION_GENERATE_DISPLAY_LISTS, false);
	pObject_terrain->setGeometryFormat(vrGeometryBase::FORMAT_VERTEX_BUFFER_OBJECT, 0x01FFFF);
	pObject_terrain->setPostLoadOption(vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_BINDINGS, true);
	pObject_terrain->setPostLoadOption(vpGeometryPageable::POST_LOAD_OPTION_COLLAPSE_TRIANGLE_STRIPS, true);
	pObject_terrain->setTextureSubloadEnable(true);
	pObject_terrain->setBufferObjectSubloadEnable(true);
	pObject_terrain->setTextureSubloadRender(vpGeometry::TEXTURE_SUBLOAD_RENDER_DEFERRED);
	pObject_terrain->setTexturePreserveImageLevelsEnable(true);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pObject_terrain);

	vpObject* pObject_farmhouse = new vpObject();
	pObject_farmhouse->setName("farmhouse");
	pObject_farmhouse->setCullMask(0x0FFFFFFFF);
	pObject_farmhouse->setRenderMask(0x0FFFFFFFF);
	pObject_farmhouse->setIsectMask(0x0FFFFFFFF);
	pObject_farmhouse->setStrategyEnable(true);
	pObject_farmhouse->setTranslate(2450, 2460, 0);
	pObject_farmhouse->setRotate(0, 0, 0);
	pObject_farmhouse->setScale(1, 1, 1);
	pObject_farmhouse->setStaticEnable(false);
	pObject_farmhouse->setFileName("house01.flt");
	pObject_farmhouse->setAutoPage(vpObject::AUTO_PAGE_SYNCHRONOUS);
	pObject_farmhouse->setManualLODChild(-1);
	pObject_farmhouse->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_PRESERVE_LIGHT_SOURCES, false);
	pObject_farmhouse->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SIGNIFICANT_SIZE, false);
	pObject_farmhouse->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_CONTROLS, true);
	pObject_farmhouse->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_ANIMATIONS, true);
	pObject_farmhouse->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_APPEARANCES, true);
	pObject_farmhouse->setLoaderDetailMultiTextureStage(-1);
	pObject_farmhouse->setLoaderBlendTolerance(0.050000f);
	pObject_farmhouse->setLoaderUnits(vsNodeLoader::Data::LOADER_UNITS_METERS);
	pObject_farmhouse->setBuilderNormalMode(vsNodeLoader::Data::BUILDER_NORMAL_MODE_PRESERVE);
	pObject_farmhouse->setBuilderTangentMode(vsNodeLoader::Data::BUILDER_TANGENT_MODE_GENERATE_PER_VERTEX_PER_PRIMITIVE_AND_ANGLE_WEIGHTED);
	pObject_farmhouse->setBuilderTangentGenerationMode(vsNodeLoader::Data::BUILDER_TANGENT_GENERATION_MODE_GENERATE_AS_NEEDED);
	pObject_farmhouse->setBuilderColorTolerance(0.001000f);
	pObject_farmhouse->setBuilderNormalTolerance(0.860000f);
	pObject_farmhouse->setGeometryFormat(vrGeometryBase::FORMAT_VERTEX_BUFFER_OBJECT, 0x01FFFF);
	pObject_farmhouse->setTextureSubloadEnable(true);
	pObject_farmhouse->setBufferObjectSubloadEnable(true);
	pObject_farmhouse->setTextureSubloadRender(vpGeometry::TEXTURE_SUBLOAD_RENDER_DEFERRED);
	pObject_farmhouse->setTexturePreserveImageLevelsEnable(false);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pObject_farmhouse);

	vpObject* pObject_hummer = new vpObject();
	pObject_hummer->setName("hummer");
	pObject_hummer->setCullMask(0x0FFFFFFFF);
	pObject_hummer->setRenderMask(0x0FFFFFFFF);
	pObject_hummer->setIsectMask(0x0FFFFFFFF);
	pObject_hummer->setStrategyEnable(true);
	pObject_hummer->setTranslate(2360, 2490, 0);
	pObject_hummer->setRotate(-90, 0, 0);
	pObject_hummer->setScale(1, 1, 1);
	pObject_hummer->setStaticEnable(false);
	pObject_hummer->setFileName("humv-dirty.flt");
	pObject_hummer->setAutoPage(vpObject::AUTO_PAGE_SYNCHRONOUS);
	pObject_hummer->setManualLODChild(-1);
	pObject_hummer->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_PRESERVE_LIGHT_SOURCES, false);
	pObject_hummer->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SIGNIFICANT_SIZE, false);
	pObject_hummer->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_CONTROLS, true);
	pObject_hummer->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_ANIMATIONS, true);
	pObject_hummer->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_APPEARANCES, true);
	pObject_hummer->setLoaderDetailMultiTextureStage(-1);
	pObject_hummer->setLoaderBlendTolerance(0.050000f);
	pObject_hummer->setLoaderUnits(vsNodeLoader::Data::LOADER_UNITS_METERS);
	pObject_hummer->setBuilderNormalMode(vsNodeLoader::Data::BUILDER_NORMAL_MODE_PRESERVE);
	pObject_hummer->setBuilderTangentMode(vsNodeLoader::Data::BUILDER_TANGENT_MODE_GENERATE_PER_VERTEX_PER_PRIMITIVE_AND_ANGLE_WEIGHTED);
	pObject_hummer->setBuilderTangentGenerationMode(vsNodeLoader::Data::BUILDER_TANGENT_GENERATION_MODE_GENERATE_AS_NEEDED);
	pObject_hummer->setBuilderColorTolerance(0.001000f);
	pObject_hummer->setBuilderNormalTolerance(0.860000f);
	pObject_hummer->setGeometryFormat(vrGeometryBase::FORMAT_VERTEX_BUFFER_OBJECT, 0x01FFFF);
	pObject_hummer->setTextureSubloadEnable(true);
	pObject_hummer->setBufferObjectSubloadEnable(true);
	pObject_hummer->setTextureSubloadRender(vpGeometry::TEXTURE_SUBLOAD_RENDER_DEFERRED);
	pObject_hummer->setTexturePreserveImageLevelsEnable(false);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pObject_hummer);

	vpObject* pObject_grainstorage = new vpObject();
	pObject_grainstorage->setName("grainstorage");
	pObject_grainstorage->setCullMask(0x0FFFFFFFF);
	pObject_grainstorage->setRenderMask(0x0FFFFFFFF);
	pObject_grainstorage->setIsectMask(0x0FFFFFFFF);
	pObject_grainstorage->setStrategyEnable(true);
	pObject_grainstorage->setTranslate(2450, 2530, 0);
	pObject_grainstorage->setRotate(90, 0, 0);
	pObject_grainstorage->setScale(1, 1, 1);
	pObject_grainstorage->setStaticEnable(false);
	pObject_grainstorage->setFileName("house04.flt");
	pObject_grainstorage->setAutoPage(vpObject::AUTO_PAGE_SYNCHRONOUS);
	pObject_grainstorage->setManualLODChild(-1);
	pObject_grainstorage->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_PRESERVE_LIGHT_SOURCES, false);
	pObject_grainstorage->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_PRESERVE_SIGNIFICANT_SIZE, false);
	pObject_grainstorage->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_CONTROLS, true);
	pObject_grainstorage->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_ANIMATIONS, true);
	pObject_grainstorage->setLoaderOption(vsNodeLoader::Data::LOADER_OPTION_SHARE_LIGHT_POINT_APPEARANCES, true);
	pObject_grainstorage->setLoaderDetailMultiTextureStage(-1);
	pObject_grainstorage->setLoaderBlendTolerance(0.050000f);
	pObject_grainstorage->setLoaderUnits(vsNodeLoader::Data::LOADER_UNITS_METERS);
	pObject_grainstorage->setBuilderNormalMode(vsNodeLoader::Data::BUILDER_NORMAL_MODE_PRESERVE);
	pObject_grainstorage->setBuilderTangentMode(vsNodeLoader::Data::BUILDER_TANGENT_MODE_GENERATE_PER_VERTEX_PER_PRIMITIVE_AND_ANGLE_WEIGHTED);
	pObject_grainstorage->setBuilderTangentGenerationMode(vsNodeLoader::Data::BUILDER_TANGENT_GENERATION_MODE_GENERATE_AS_NEEDED);
	pObject_grainstorage->setBuilderColorTolerance(0.001000f);
	pObject_grainstorage->setBuilderNormalTolerance(0.860000f);
	pObject_grainstorage->setGeometryFormat(vrGeometryBase::FORMAT_VERTEX_BUFFER_OBJECT, 0x01FFFF);
	pObject_grainstorage->setTextureSubloadEnable(true);
	pObject_grainstorage->setBufferObjectSubloadEnable(true);
	pObject_grainstorage->setTextureSubloadRender(vpGeometry::TEXTURE_SUBLOAD_RENDER_DEFERRED);
	pObject_grainstorage->setTexturePreserveImageLevelsEnable(false);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pObject_grainstorage);

	vpIsectorBump* pIsectorBump_bumpIsector = new vpIsectorBump();
	pIsectorBump_bumpIsector->setName("bumpIsector");
	pIsectorBump_bumpIsector->setEnable(true);
	pIsectorBump_bumpIsector->setRenderEnable(true);
	pIsectorBump_bumpIsector->setTranslate(0, 0, 0);
	pIsectorBump_bumpIsector->setRotate(0, 0, 0);
	pIsectorBump_bumpIsector->setMode(0x02);
	pIsectorBump_bumpIsector->setIsectMask(0x01);
	pIsectorBump_bumpIsector->setMaterialMask(0x0FFFF);
	pIsectorBump_bumpIsector->setStrategyEnable(true);
	pIsectorBump_bumpIsector->setDimensions(3.000000f, 3.000000f, 3.000000f);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pIsectorBump_bumpIsector);

	vpIsectorTripod* pIsectorTripod_tripodIsector = new vpIsectorTripod();
	pIsectorTripod_tripodIsector->setName("tripodIsector");
	pIsectorTripod_tripodIsector->setEnable(true);
	pIsectorTripod_tripodIsector->setRenderEnable(true);
	pIsectorTripod_tripodIsector->setTranslate(0, 0, 0);
	pIsectorTripod_tripodIsector->setRotate(0, 0, 0);
	pIsectorTripod_tripodIsector->setMode(0x02A);
	pIsectorTripod_tripodIsector->setIsectMask(0x0FFFFFFFF);
	pIsectorTripod_tripodIsector->setMaterialMask(0x0FFFF);
	pIsectorTripod_tripodIsector->setStrategyEnable(true);
	pIsectorTripod_tripodIsector->setSegmentZExtent(-5000.000000f, 5000.000000f);
	pIsectorTripod_tripodIsector->setDimensions(1.000000f, 1.000000f);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pIsectorTripod_tripodIsector);

	vpIsectorServiceInline* pIsectorServiceInline_myIsectorService = new vpIsectorServiceInline();
	pIsectorServiceInline_myIsectorService->setName("myIsectorService");

	PublicMember::CTS_s_pInstancesToUnref->push_back(pIsectorServiceInline_myIsectorService);

	vpGroundClamp* pGroundClamp_myGroundClamp = new vpGroundClamp();
	pGroundClamp_myGroundClamp->setName("myGroundClamp");
	pGroundClamp_myGroundClamp->setOffsetFromGround(0.000000f);
	pGroundClamp_myGroundClamp->setFallingVelocity(-1.000000f);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pGroundClamp_myGroundClamp);

	vpRecyclingService* pRecyclingService_myRecyclingService = vpRecyclingService::instance();
	pRecyclingService_myRecyclingService->setMultiThread(vpRecyclingService::MULTITHREAD_INLINE);
	pRecyclingService_myRecyclingService->setThreadPriority(vuThread::PRIORITY_NORMAL);
	pRecyclingService_myRecyclingService->setThreadProcessor(-1);
	pRecyclingService_myRecyclingService->setRecycleTime(-1);

	vpEnvGlobals* pEnvGlobals_myEnvGlobals = vpEnvGlobals::instance();
	pEnvGlobals_myEnvGlobals->setSkyLightEnable(true);
	pEnvGlobals_myEnvGlobals->setDominantCelestialLightingEnable(true);
	pEnvGlobals_myEnvGlobals->setLocalViewerEnable(false);
	pEnvGlobals_myEnvGlobals->setTwoSidedLightingEnable(false);
	pEnvGlobals_myEnvGlobals->addFogMaximumAltitude(0.100000f, 300.000000f);
	pEnvGlobals_myEnvGlobals->addFogMaximumAltitude(0.250000f, 2000.000000f);
	pEnvGlobals_myEnvGlobals->addFogMaximumAltitude(0.400000f, 1200.000000f);
	pEnvGlobals_myEnvGlobals->setEnvironmentMapGenerationEnable(false);

	vpEnv* pEnv_myEnv = new vpEnv();
	pEnv_myEnv->setName("myEnv");
	pEnv_myEnv->setDate(1, 9, 2006);
	pEnv_myEnv->setTimeOfDay(9.250000f);
	pEnv_myEnv->setTimeMultiplier(1.000000f);
	pEnv_myEnv->setEphemerisUpdateInterval(0.000000f);
	pEnv_myEnv->setReferencePosition(-117.355103f, 33.301300f);
	pEnv_myEnv->setEphemerisTimeZoneOffset(-10000);
	pEnv_myEnv->setSkyColor(0.513725f, 0.701961f, 0.941176f, 1.000000f);
	pEnv_myEnv->setVisibilityType(vpEnvFx::VISIBILITY_TYPE_VERTEX_EXP2);
	pEnv_myEnv->setVisibilityRangeOnset(0.000000f);
	pEnv_myEnv->setVisibilityRangeOpaque(60000.000000f);
	pEnv_myEnv->setVisibilityColor(0.764706f, 0.858824f, 1.000000f, 1.000000f);
	pEnv_myEnv->setHazeColor(0.772549f, 0.772549f, 0.772549f, 0.445397f);
	pEnv_myEnv->setManageVisibilityColorsEnable(true);
	pEnv_myEnv->setAmbientLightingColor(0.000000f, 0.000000f, 0.000000f, 1.000000f);
	pEnv_myEnv->setLightBrightnessScale(vpEnv::COLOR_AMBIENT, 0.500000f);
	pEnv_myEnv->setLightBrightnessScale(vpEnv::COLOR_DIFFUSE, 0.500000f);
	pEnv_myEnv->setLightBrightnessScale(vpEnv::COLOR_SPECULAR, 1.000000f);
	pEnv_myEnv->setLightColorScale(vpEnv::COLOR_AMBIENT, 1.000000f, 1.000000f, 1.000000f);
	pEnv_myEnv->setLightColorScale(vpEnv::COLOR_DIFFUSE, 1.000000f, 1.000000f, 1.000000f);
	pEnv_myEnv->setLightColorScale(vpEnv::COLOR_SPECULAR, 1.000000f, 1.000000f, 1.000000f);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pEnv_myEnv);

	vpEnvSun* pEnvSun_myEnvSun = new vpEnvSun();
	pEnvSun_myEnvSun->setName("myEnvSun");
	pEnvSun_myEnvSun->setEnable(true);
	pEnvSun_myEnvSun->setTwilightDip(-18.000000f);
	pEnvSun_myEnvSun->setGeometryEnable(true);
	pEnvSun_myEnvSun->setTextureFile("sun.inta");
	pEnvSun_myEnvSun->setTextureBlendColor(1.000000f, 1.000000f, 1.000000f, 1.000000f);
	pEnvSun_myEnvSun->setTextureBlendMode(vpEnvSun::TEXTURE_BLEND_MODE_MODULATE);
	pEnvSun_myEnvSun->setColor(0.992156f, 1.000000f, 0.949019f, 1.000000f);
	pEnvSun_myEnvSun->setVisibilityRangeRatio(0.050000f);
	pEnvSun_myEnvSun->setAngularSize(5.500000f);
	pEnvSun_myEnvSun->setHorizonAngle(40.000000f);
	pEnvSun_myEnvSun->setHorizonColor(1.000000f, 0.545098f, 0.239216f, 1.000000f);
	pEnvSun_myEnvSun->setHorizonSizeScale(2.000000f);
	pEnvSun_myEnvSun->setHorizonLightColorScale(0.250000f);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pEnvSun_myEnvSun);

	vpEnvMoon* pEnvMoon_myEnvMoon = new vpEnvMoon();
	pEnvMoon_myEnvMoon->setName("myEnvMoon");
	pEnvMoon_myEnvMoon->setEnable(true);
	pEnvMoon_myEnvMoon->setBrightness(0.250000f);
	pEnvMoon_myEnvMoon->setGeometryEnable(true);
	pEnvMoon_myEnvMoon->setTextureFile("moon.inta");
	pEnvMoon_myEnvMoon->setTextureBlendColor(1.000000f, 1.000000f, 1.000000f, 1.000000f);
	pEnvMoon_myEnvMoon->setTextureBlendMode(vpEnvMoon::TEXTURE_BLEND_MODE_MODULATE);
	pEnvMoon_myEnvMoon->setColor(0.811765f, 0.886275f, 0.937255f, 1.000000f);
	pEnvMoon_myEnvMoon->setVisibilityRangeRatio(0.100000f);
	pEnvMoon_myEnvMoon->setAngularSize(1.500000f);
	pEnvMoon_myEnvMoon->setHorizonAngle(30.000000f);
	pEnvMoon_myEnvMoon->setHorizonColor(0.811765f, 0.886275f, 0.937255f, 1.000000f);
	pEnvMoon_myEnvMoon->setHorizonSizeScale(1.700000f);
	pEnvMoon_myEnvMoon->setHorizonLightColorScale(0.000000f);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pEnvMoon_myEnvMoon);

	vpEnvSkyDome* pEnvSkyDome_myEnvSkyDome = new vpEnvSkyDome();
	pEnvSkyDome_myEnvSkyDome->setName("myEnvSkyDome");
	pEnvSkyDome_myEnvSkyDome->setEnable(true);
	pEnvSkyDome_myEnvSkyDome->setGroundColor(0.211765f, 0.286275f, 0.149020f, 1.000000f);
	pEnvSkyDome_myEnvSkyDome->setGroundEnable(true);
	pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio(0, 0.100000f);
	pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio(1, 0.300000f);
	pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio(2, 0.750000f);
	pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio(3, 0.900000f);
	pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio(4, 1.000000f);
	pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio(5, 1.000000f);
	pEnvSkyDome_myEnvSkyDome->setVisibilityRangeRatio(6, 1.000000f);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pEnvSkyDome_myEnvSkyDome);

	vpEnvCloudLayer2D* pEnvCloudLayer2D_myEnvCloudLayer = new vpEnvCloudLayer2D();
	pEnvCloudLayer2D_myEnvCloudLayer->setName("myEnvCloudLayer");
	pEnvCloudLayer2D_myEnvCloudLayer->setEnable(true);
	pEnvCloudLayer2D_myEnvCloudLayer->setColor(0.300000f, 0.300000f, 0.300000f, 1.000000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setElevation(5000.000000f, 6000.000000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setCoverageScale(0.250000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setGeometryEnable(true);
	pEnvCloudLayer2D_myEnvCloudLayer->setEnvHazeColorScale(0.000000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setTransitionRange(500.000000f, 500.000000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setScudEnable(false);
	pEnvCloudLayer2D_myEnvCloudLayer->setTextureFile("");
	pEnvCloudLayer2D_myEnvCloudLayer->setTextureBlendColor(1.000000f, 1.000000f, 1.000000f, 1.000000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setTextureBlendMode(vpEnvCloudLayer2D::TEXTURE_BLEND_MODE_MODULATE);
	pEnvCloudLayer2D_myEnvCloudLayer->setTextureTiling(2.000000f, 2.000000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setMinVisibilityScale(0.000000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setHorizonColorScale(1.000000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setShadowsEnable(false);
	pEnvCloudLayer2D_myEnvCloudLayer->setShadowsColorPunchThrough(0.300000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setShadowIntensity(0.600000f);
	pEnvCloudLayer2D_myEnvCloudLayer->setShadowsContribution(0.100000f, 0.900000f);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pEnvCloudLayer2D_myEnvCloudLayer);

	vpEnvStars* pEnvStars_myEnvStars = new vpEnvStars();
	pEnvStars_myEnvStars->setName("myEnvStars");
	pEnvStars_myEnvStars->setEnable(true);
	pEnvStars_myEnvStars->setIntensityThreshold(0.350000f);
	pEnvStars_myEnvStars->setBrightnessThreshold(0.400000f, 0.250000f);
	pEnvStars_myEnvStars->setVisibilityRangeRatio(0.100000f);
	pEnvStars_myEnvStars->setPointSize(2.300000f);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pEnvStars_myEnvStars);

	vpEnvWind* pEnvWind_myEnvWind = new vpEnvWind();
	pEnvWind_myEnvWind->setName("myEnvWind");
	pEnvWind_myEnvWind->setEnable(true);
	pEnvWind_myEnvWind->setSpeed(100.000000f);
	pEnvWind_myEnvWind->setDirection(0.000000f, 1.000000f, 0.000000f);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pEnvWind_myEnvWind);

	vpMotionDrive* pMotionDrive_myMotion = new vpMotionDrive();
	pMotionDrive_myMotion->setName("myMotion");
	pMotionDrive_myMotion->setSpeed(0);
	pMotionDrive_myMotion->setSpeedLimits(-200, 10);
	pMotionDrive_myMotion->setSpeedDelta(1, 1);
	pMotionDrive_myMotion->setHeadingDelta(1);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pMotionDrive_myMotion);

	vpFxDebris* pFxDebris_Debris = new vpFxDebris();
	pFxDebris_Debris->setName("Debris");
	pFxDebris_Debris->setCullMask(0x0FFFFFFFF);
	pFxDebris_Debris->setRenderMask(0x0FFFFFFFF);
	pFxDebris_Debris->setIsectMask(0x0FFFFFFFF);
	pFxDebris_Debris->setStrategyEnable(true);
	pFxDebris_Debris->setTranslate(0, 0, 0);
	pFxDebris_Debris->setRotate(0, 0, 0);
	pFxDebris_Debris->setScale(20, 20, 20);
	pFxDebris_Debris->setStaticEnable(false);
	pFxDebris_Debris->setRepeatEnable(false);
	pFxDebris_Debris->setOverallColor(1.000000f, 1.000000f, 1.000000f, 1.000000f);
	pFxDebris_Debris->setTextureBlendColor(1.000000f, 1.000000f, 1.000000f, 1.000000f);
	pFxDebris_Debris->setTextureMode(vpFx::TEXTURE_MODE_MODULATE);
	pFxDebris_Debris->setTextureFile("debris.inta");
	pFxDebris_Debris->setOverallDuration(4.000000f);
	pFxDebris_Debris->setFadeDuration(0.000000f, 0.000000f);
	pFxDebris_Debris->setTransparencyDepthOffset(0.000000f);
	pFxDebris_Debris->setTransparencyDepthRadiusScaler(0.000000f);
	pFxDebris_Debris->setDepthWriteEnable(false);
	pFxDebris_Debris->setWindSource(vpFxParticleSystem::WIND_SOURCE_TABLE);

	PublicMember::CTS_s_pInstancesToUnref->push_back(pFxDebris_Debris);

	// Satisfy all references
	//




	pPipeline_myPipeline->addWindow(pWindow_myWindow);

	pWindow_myWindow->addChannel(pChannel_myChannel);


	pObserver_myObserver->setStrategy(pMotionDrive_myMotion);
	pObserver_myObserver->addChannel(pChannel_myChannel);
	pObserver_myObserver->addAttachment(pEnv_myEnv);
	pObserver_myObserver->setScene(pScene_myScene);
	pObserver_myObserver->setLookFrom(pTransform_hummerTransform);

	pScene_myScene->addChild(pObject_terrain);
	pScene_myScene->addChild(pObject_farmhouse);
	pScene_myScene->addChild(pObject_hummer);
	pScene_myScene->addChild(pObject_grainstorage);



	pObject_farmhouse->addChild(pFxDebris_Debris);

	pObject_hummer->addChild(pTransform_hummerTransform);
	pObject_hummer->setStrategy(pMotionDrive_myMotion);


	pIsectorBump_bumpIsector->setTarget(pObject_farmhouse);
	pIsectorBump_bumpIsector->setPositionReference(pObject_hummer);

	pIsectorTripod_tripodIsector->setTarget(pObject_terrain);

	pIsectorServiceInline_myIsectorService->addIsector(pIsectorBump_bumpIsector);

	pGroundClamp_myGroundClamp->setIsector(pIsectorTripod_tripodIsector);



	pEnv_myEnv->addEnvFx(pEnvSun_myEnvSun);
	pEnv_myEnv->addEnvFx(pEnvMoon_myEnvMoon);
	pEnv_myEnv->addEnvFx(pEnvSkyDome_myEnvSkyDome);
	pEnv_myEnv->addEnvFx(pEnvCloudLayer2D_myEnvCloudLayer);
	pEnv_myEnv->addEnvFx(pEnvWind_myEnvWind);
	pEnv_myEnv->addEnvFx(pEnvStars_myEnvStars);







	pMotionDrive_myMotion->setNextStrategy(pGroundClamp_myGroundClamp);

	pFxDebris_Debris->setTriggerIsector(pIsectorBump_bumpIsector);


}//5错误点

UINT PublicMember::CTS_RunBasicThread(LPVOID)
{

	vp::initialize(__argc,__argv);      //初始化(int _argc, _argv);

	PublicMember::CTS_Define();    // 定义场景

	vpKernel::instance()->configure();   //配置场景
	

	vpWindow *vpWin = *vpWindow::begin();  //设置窗体
	vpWin->setParent(PublicMember::CTS_RunningWindow);
	vpWin->setBorderEnable(false);
	vpWin->setFullScreenEnable(true);
	vpWin->open();
	::SetFocus(vpWin->getWindow());
	//帧循环

	while (vpKernel::instance()->beginFrame()!= 0)
	{
		vpKernel::instance()->endFrame();
		if (!PublicMember::CTS_continueRunVP)
		{
			vpKernel::instance()->unconfigure();
			vp::shutdown();
			return 0;

		}
	}
	return 0;
}


