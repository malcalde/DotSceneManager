/*
    Copyright (C) 2012  CodeMokey_1131 <miguel.wasabi@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <OgreResourceManager.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreRenderTarget.h>
#include <OgreRenderTexture.h>
#include <OgreMaterialManager.h>
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreRenderWindow.h>
#include <OgreSubEntity.h>
#include <OgreBillboard.h>
#include <OgreShadowCameraSetupFocused.h>
#include <OgreShadowCameraSetupLiSPSM.h>
#include <OgreShadowCameraSetupPlaneOptimal.h>
#include <OgreShadowCameraSetupPSSM.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <tinyxml.h>

#include "DotSceneManager.h"

#define CREATE_SCENE_MODE_AUTO          "auto"
#define CREATE_SCENE_MODE_MANUAL        "manual"

#ifdef __GNUC__
    #define _FUNC_              String(__PRETTY_FUNCTION__)
    #define TRACE_FUNC()        log(_FUNC_)
    #define P4H_TRACE_LOG(msg)  log(_FUNC_ + " " + msg)   
#else
    #define _FUNC_              String(__FILE__) + " " + String("__LINE__")
    #define TRACE_FUNC()        log(_FUNC_)
    #define P4H_TRACE_LOG(msg)  log(_FUNC_ + " " + msg)    
#endif

#define NEAR_CLIP_DISTANCE              5
#define FAR_CLIP_DISTANCE               5

#define ANIMATION_PKG_MAYA              0
#define ANIMATION_PKG_OTHER             1

using namespace Ogre;

/*****************************************************************************/
/** helper functions          (declaration)                                  */                   
/*****************************************************************************/
static void log(const String& formatString, ...);
//----------------------------------------------------------------------------
static String generateUUID(const String& prefix=StringUtil::BLANK, const String& suffix=StringUtil::BLANK);
//----------------------------------------------------------------------------
static bool isPowerOfTwo(int value);
//----------------------------------------------------------------------------
static unsigned int nextSmallestPowerOfTwo(unsigned int value);
//----------------------------------------------------------------------------
static unsigned int nextLargestPowerOfTwo(unsigned int value);
//----------------------------------------------------------------------------
inline String stringify(double x);
//----------------------------------------------------------------------------
inline String stringify(int x);
//----------------------------------------------------------------------------
inline String stringify(long int x);
//----------------------------------------------------------------------------
inline String stringify(float x);
//----------------------------------------------------------------------------
inline String stringify(bool x); 
//----------------------------------------------------------------------------
inline const String& stringify(const String& x) ;

/*****************************************************************************/
/** DotScenePersistenceHelper (declaration)                                  */                   
/*****************************************************************************/
/** Helper class to create .scene from a SceneManager and loaded DotScene */
class _DotSceneManagerExport DotScenePersistenceHelper
{
public:
    /** Constructor */
    DotScenePersistenceHelper(DotScene* scene);
    /** Destructor */
    ~DotScenePersistenceHelper();
    
    /** persists scene */
    bool persist(const String& filename=StringUtil::BLANK);
private:
//     /** dotscene loader method: process 'scene' node*/
//     void persistScene(TiXmlElement* XMLRoot);
//     /** dotscene loader method: process 'nodes' node*/
//     void persistNodes(TiXmlElement* node);
//     /** dotscene loader method: process 'externals' node*/
//     void persistExternals(TiXmlElement* node);
//     /** dotscene loader method: process 'enviroment' node*/
//     void persistEnvironment(TiXmlElement* node);
//     /** dotscene loader method: process 'terrain' node*/
//     void persistTerrain(TiXmlElement* node);
//     /** dotscene loader method: process 'octree' node*/
//     void persistOctree(TiXmlElement* node);
//     /** dotscene loader method: process 'octNode' node*/
//     void persistOctNode(TiXmlElement* node);
//     /** dotscene loader method: process 'octMesh' node*/
//     void persistOctMesh(TiXmlElement* node);
//     /** dotscene loader method: process 'light' node*/
//     void persistLight(TiXmlElement* node, SceneNode* parent);
//     /** dotscene loader method: process 'camera' node*/
//     void persistCamera(TiXmlElement* node, SceneNode* parent);
//     /** dotscene loader method: process 'node' node*/
//     void persistNode(TiXmlElement* node, SceneNode* parent);
//     /** dotscene loader method: process 'look-target' node*/
//     void persistLookTarget(TiXmlElement* node, SceneNode* parent);
//     /** dotscene loader method: process 'track-target' node*/
//     void persistTrackTarget(TiXmlElement* node, SceneNode* parent);
//     /** dotscene loader method: process 'entity' node*/
//     void persistEntity(TiXmlElement* node, SceneNode* parent);
//     /** dotscene loader method: process 'particle-system' node*/
//     void persistParticleSystem(TiXmlElement* node, SceneNode* parent);
//     /** dotscene loader method: process 'billboard' node*/
//     void persistBillboardSet(TiXmlElement* node, SceneNode* parent);
//     /** dotscene loader method: process 'plane' node*/
//     void persistPlane(TiXmlElement* node, SceneNode* parent);
//     /** dotscene loader method: process 'fog' node*/
//     void persistFog(TiXmlElement* node);
//     /** dotscene loader method: process 'skybox' node*/
//     void persistSkyBox(TiXmlElement* node);
//     /** dotscene loader method: process 'skydome' node*/
//     void persistSkyDome(TiXmlElement* node);
//     /** dotscene loader method: process 'plane' node*/
//     void persistSkyPlane(TiXmlElement* node);
//     /** dotscene loader method: process 'clipping' node*/
//     void persistClipping(TiXmlElement* node, ClippingPlanesType* clippingPlanes);
//     /** dotscene loader method: process 'light' node*/
//     void persistLightRange(TiXmlElement* node, Light* light);
//     /** dotscene loader method: process 'scene' node*/
//     void persistLightAttenuation(TiXmlElement* node, Light* light);
//     /** process vertex buffer */
//     void persistVertexBuffer(TiXmlElement* node);
//     /** process index buffer */
//     void persistIndexBuffer(TiXmlElement* node);
//     /** process subentity */
//     void persistSubEntity(TiXmlElement* node, Entity* entity);
//     
//     /** dotscene helper method: tinyxml set attribute*/
//     void setAttrib(TiXmlElement* node, const String& parameter, const String& value);
//     /** dotscene helper method: tinyxml set attribute Integer*/
//     void setAttribInt(TiXmlElement* node, const String& parameter, Integer value);
//     /** dotscene helper method: tinyxml set attribute Real*/
//     void setAttribReal(TiXmlElement* node, const String& parameter, Real value);
//     /** dotscene helper method: tinyxml set attribute boolean*/
//     //void setAttribBool(TiXmlElement *node, const String& parameter, bool value);
//     
//     /** dotscene helper method: persit Quaternion*/
//     void persistVector3(TiXmlElement* node, Vector3& vec3);
//     /** dotscene helper method: persit Quaternion*/
//     void parseQuaternion(TiXmlElement* node, Quaternion& Quaternion);
//     /** dotscene helper method: persit ColourValue*/
//     void parseColour(TiXmlElement* node, ColourValue colorValue);

private:
    /** Reference DotScene*/
    DotScene* mScene;
}; //DotScenePersistenceHelper

/*****************************************************************************/
/** DotScene                                                                 */                   
/*****************************************************************************/
DotScene::DotScene(ResourceManager* creator, 
                   const String& name, 
                   ResourceHandle handle, 
                   const String& group,
                   const NameValuePairList* params,
                   bool isManual, 
                   ManualResourceLoader* loader)
         :Resource(creator, name, handle, group, isManual, loader),
          mSceneMgr(0), 
          mSceneRoot(0),
          mFile(StringUtil::BLANK), 
          mPrefix(StringUtil::BLANK),
          mCreateSceneMode(true), 
          mVersion(StringUtil::BLANK),
          mAmbientLight(ColourValue::White),
          mBackgroundColor(ColourValue::Black)
{
    TRACE_FUNC(); 
    
    assert(params);
    assert(params->end() != params->find("file"));
    assert(params->end() != params->find("prefix"));
    assert(params->end() != params->find("sceneManager"));
    assert(params->end() != params->find("createSceneMode"));
 
    for(NameValuePairList::const_iterator it=params->begin(); it!=params->end();it++)
    {
        if ("file" == it->first)
            mFile = it->second;
        if ("prefix" == it->first)
            mPrefix = it->second;
        if ("sceneManager" == it->first)
            mSceneMgr = Root::getSingletonPtr()->getSceneManager(it->second);
        if ("createSceneMode" == it->first)
            mCreateSceneMode = (it->second == CREATE_SCENE_MODE_AUTO)? true: false;
    }
    
     for(int i=0; i<DOTSCENE_MAX_VIEWPORTS; i++)
    {
        mBackupViewport[i] = 0;
    }
}
//----------------------------------------------------------------------------
DotScene::~DotScene()
{
    TRACE_FUNC();
    unload();
    
    if (helper) 
        delete helper;
    helper = 0;
}
//----------------------------------------------------------------------------
SceneManager* DotScene::getSceneManager()
{
    return mSceneMgr;
}
//----------------------------------------------------------------------------
SceneNode* DotScene::getRootSceneNode()
{
    assert(mSceneRoot);
    return mSceneRoot;
}
//----------------------------------------------------------------------------
void DotScene::loadImpl()
{
    TRACE_FUNC();
    //Clean internal structures
    mClipPlanes.mNear = NEAR_CLIP_DISTANCE;
    mClipPlanes.mFar = FAR_CLIP_DISTANCE;
    
    mDefaultCameras.clear();
    mSceneNodes.clear();
    mDynamicEntities.clear();
    mStaticEntities.clear();
    mLights.clear();
    mCameras.clear();
    mBillboardSets.clear();
    mParticleSystem.clear();
    mExternals.clear();
    mMeshes.clear();
    mUserReferences.clear();
    mProperties.clear();
    mRenderTextures.clear();
    
    mAmbientLight = ColourValue::White;
    mAnimationPackage = ANIMATION_PKG_OTHER;
    mBackgroundColor = ColourValue::Black;
    
    for(int i=0; i<DOTSCENE_MAX_VIEWPORTS; i++)
    {
        assert(! mBackupViewport[i]);
    }
    
    mUpAxis = UP_AXIS_Z;
    mQueryFlags = 0;
    mVisibilityFlags = 0;
 
    
    //Load & parse scene file
    TiXmlDocument* doc = 0;
    TiXmlElement* rootNode = 0;
    try
    {
        // Strip the path
        ResourceGroupManager* resman = ResourceGroupManager::getSingletonPtr();
        DataStreamPtr pStream = resman->openResource(mFile,mGroup);
        
        String data = pStream->getAsString();
        
        // Open the .scene File
        doc = new TiXmlDocument();
        doc->Parse( data.c_str() );
        pStream->close();
        pStream.setNull();

        //Has parse error */
        if (doc->Error())
        {
            log("Error parsing .dotscene resource" + mFile);
            delete doc;
            
            assert(false);
            return;
        }
    }
    catch(...)
    {
        log("Error creating TiXmlDocument for file " + mFile);
        delete doc;
        
        assert(false);
        return;
    }

    //Clean & init internal & scene resources
    //cleanResources();
    
    // Validate the File
    rootNode = doc->RootElement(); 
    if ("scene" != String(rootNode->Value())) 
    {
        log("Error: Invalid .scene File. Missing <scene> node");
        delete doc;    
        
        assert(false);
        return;
    }

    //backup current viewport configuracion
    backupViewportConfiguration();

    // Process the scene - always work in radian units
    Math::AngleUnit angleUnit = Math::getAngleUnit();
    Math::setAngleUnit(Math::AU_RADIAN);
    processScene(rootNode);
    Math::setAngleUnit(angleUnit);
    
    //set lighting by default
    setDefaultLighting();
    
    //Exist viewport? 
    Root* root = Root::getSingletonPtr();
    RenderWindow* window = root->getAutoCreatedWindow();
    
    //Crear viewport  -  set camera por defecto
    if (! mDefaultCameras.size())    //if (! window->getNumViewports())
    {
        //Usar camera desde el fichero dotscene
        if (mCameras.size())
        {
             setDefaultCamera(mCameras[0]);
        }
        else  
        {
            //Usar la camara creadas en sceneManager
            SceneManager::CameraIterator it = mSceneMgr->getCameraIterator();
            if (it.hasMoreElements())
            {
                Camera* camera = it.getNext();
                
                mCameras.push_back(camera->getName());
                setDefaultCamera(camera->getName());   
            }
            else
            {
                //TODO evaluar esta necesidad - crear una camara por defecto
                Camera* camera = mSceneMgr->createCamera(mName+"Camera");
                mCameras.push_back(camera->getName());
                camera->setPosition(mUnitConversionFactor * Vector3(0,10,-10));
                camera->lookAt(Vector3(0,0,50));
                camera->setNearClipDistance(6);
                
                mCameras.push_back(camera->getName());
                setDefaultCamera(camera->getName());
            }
        }
    }
    
    for(int i=0; i<window->getNumViewports(); i++)
    {
        log("Default camera for viewport " + stringify(i) + " is " + window->getViewport(i)->getCamera()->getName());
    }
        
        
    //if Auto create scene flag is set attach sceneNode to RootSceneNode
    if (mCreateSceneMode)
        setVisible(true);
    
    // Close the XML File
    delete doc;
}
//----------------------------------------------------------------------------
void DotScene::unloadImpl()
{
    TRACE_FUNC();
    
    cleanResources();
    
    //recuperamos la configuracion de cameras y viewport
    restoreViewportConfiguration();
}
//----------------------------------------------------------------------------
size_t DotScene::calculateSize() const
{
    TRACE_FUNC();
    
    int sz = 0;
    sz += mSceneNodes.size();
    sz += mSceneNodes.size();
    sz += mDynamicEntities.size();
    sz += mStaticEntities.size();
    sz += mLights.size();
    sz += mCameras.size();
    sz += mBillboardSets.size();
    sz += mParticleSystem.size();
    sz += mExternals.size();
    sz += mMeshes.size();
    sz += mUserReferences.size();

    return sz;
}
//----------------------------------------------------------------------------
void DotScene::cleanResources()
{
    for(StringVector::iterator it= mLights.begin(); it!=mLights.end(); it++)
        mSceneMgr->destroyLight(*it);
    for(StringVector::iterator it= mBillboardSets.begin(); it!=mBillboardSets.end(); it++)
        mSceneMgr->destroyBillboardSet(*it);
    for(StringVector::iterator it= mMeshes.begin(); it!=mMeshes.end(); it++)
        mSceneMgr->destroyManualObject(*it);
    for(StringVector::iterator it= mParticleSystem.begin(); it!=mParticleSystem.end(); it++)
        mSceneMgr->destroyParticleSystem(*it);
    
    for(StringVector::iterator it= mCameras.begin(); it!=mCameras.end(); it++)
            mSceneMgr->destroyCamera(*it);
    
    //Destroy scene nodes
    for(StringVector::iterator it= mStaticEntities.begin(); it!=mStaticEntities.end(); it++)
        mSceneMgr->destroyEntity(*it);
    for(StringVector::iterator it= mDynamicEntities.begin(); it!=mDynamicEntities.end(); it++)
        mSceneMgr->destroyEntity(*it);
    for(StringVector::iterator it= mSceneNodes.begin(); it!=mSceneNodes.end(); it++)
        mSceneMgr->destroySceneNode(*it);        
            
    //Clean scene
    mSceneRoot->setVisible(false);    
    setVisible(false);
    mSceneMgr->destroySceneNode(mSceneRoot);
    mSceneRoot = 0;
        
    //Clean local structures
    mSceneNodes.clear();
    mDynamicEntities.clear();
    mStaticEntities.clear();
    mLights.clear();
    mCameras.clear();
    mBillboardSets.clear();
    mParticleSystem.clear();
    mExternals.clear();
    mMeshes.clear();
    mUserReferences.clear();
    mProperties.clear();
    mDefaultCameras.clear();
    mProperties.clear();
    mRenderTextures.clear(); 
}
//----------------------------------------------------------------------------
Quaternion DotScene::getUpAxisOrientation()
{
   if (UP_AXIS_Y == mUpAxis )
       return Quaternion::IDENTITY;
   else if (UP_AXIS_Z == mUpAxis )
       return Quaternion((Real)0.707107f, (Real)0.707107f, 0.0f, 0.0f);
   else
       assert(true);
   
   return Quaternion::IDENTITY;
}
//----------------------------------------------------------------------------
Vector3 DotScene::getUpVector() 
{ 
    if (UP_AXIS_Y == mUpAxis )
       return Vector3::UNIT_Y;
   else if (UP_AXIS_Z == mUpAxis )
       return Vector3::UNIT_Z;
   else
       assert(true);
   
    return Vector3::ZERO;
}
//----------------------------------------------------------------------------
void DotScene::setDefaultLighting()
{
    TRACE_FUNC();
    assert(true);
}
//----------------------------------------------------------------------------
void DotScene::backupViewportConfiguration()
{
    RenderWindow* window =  Root::getSingletonPtr()->getAutoCreatedWindow();
    if (window->getNumViewports() > 0)
    {
        for(int i=0; i<window->getNumViewports(); i++)
        {
            Viewport* viewport = window->getViewport(i);
            
            ViewportConfigurationType* backup = new ViewportConfigurationType();
            backup->mTop = viewport->getTop();
            backup->mLeft = viewport->getLeft();
            backup->mHeight = viewport->getHeight();
            backup->mWidth = viewport->getWidth();
            backup->mBackgroundColor = viewport->getBackgroundColour();
            backup->mClearEveryFrame = viewport->getClearEveryFrame();
            backup->mMaterialSchema = viewport->getMaterialScheme();
            backup->mRenderQueueInvocationSequenceName = viewport->getRenderQueueInvocationSequenceName();
            backup->mOverlaysEnabled = viewport->getOverlaysEnabled();
            backup->mShadowsEnabled = viewport->getShadowsEnabled();
            backup->mSkiesEnabled = viewport->getSkiesEnabled();
            backup->mVisibilityMask = viewport->getVisibilityMask();
            backup->mZOrder = viewport->getZOrder(); 
            
            if(viewport->getCamera())
            {
                Camera* camera = viewport->getCamera();
                backup->mCamera.mName = camera->getName();
                backup->mCamera.mPosition = camera->getPosition();
                backup->mCamera.mDirection = camera->getDirection();
                backup->mCamera.mOrientation = camera->getOrientation();
                backup->mCamera.mPolygonMode = camera->getPolygonMode();
                backup->mCamera.mNearPlane = camera->getNearClipDistance(); 
                backup->mCamera.mFarPlane = camera->getFarClipDistance();
                backup->mCamera.mProjectionType = camera->getProjectionType();
                backup->mCamera.mFOVy = camera->getFOVy();
                backup->mCamera.mAspectRatio = camera->getAspectRatio();
                backup->mCamera.mCastShadows = camera->getCastShadows();
                backup->mCamera.mUpAxis = camera->getUp();
                backup->mCamera.mFocalLenght = camera->getFocalLength();
                backup->mCamera.mVisibilityFlags = camera->getVisibilityFlags(); 
                backup->mCamera.mQueryFlags = camera->getQueryFlags(); 
                backup->mCamera.mLightMask = camera->getLightMask();
            }
            
            log("[Viewport-Backup] Getting camera " + backup->mCamera.mName +  " from viewport " 
                    + stringify(i));
            
            mBackupViewport[i] = backup;
        }   
    } 
}
//----------------------------------------------------------------------------
void DotScene::restoreViewportConfiguration()
{
    Root* root = Root::getSingletonPtr();
    RenderWindow* window = root->getAutoCreatedWindow();
    
    for(int i=0; i<DOTSCENE_MAX_VIEWPORTS; i++)
    {
        ViewportConfigurationType* backup = mBackupViewport[i];
        
        if (! backup) continue;
        
        log("[Viewport-Restore] Setting camera " + backup->mCamera.mName +  " to viewport " + 
                 stringify(i));
        
        if (window->getNumViewports() > i)
        {
            Viewport* viewport = window->getViewport(i);
            Camera* camera = mSceneMgr->getCamera(backup->mCamera.mName);
            if (! camera)
                mSceneMgr->createCamera(backup->mCamera.mName);
            viewport->setCamera(camera);
            
            setDefaultCamera(camera->getName(), i, backup->mZOrder);
            
            //restore camera settings
            camera->setPosition(backup->mCamera.mPosition);
            camera->setDirection(backup->mCamera.mDirection);
            camera->setOrientation(backup->mCamera.mOrientation);
            camera->setPolygonMode(backup->mCamera.mPolygonMode);
            camera->setNearClipDistance(backup->mCamera.mNearPlane); 
            camera->setFarClipDistance(backup->mCamera.mFarPlane);
            camera->setProjectionType(backup->mCamera.mProjectionType);
            camera->setFOVy(backup->mCamera.mFOVy);
            camera->setAspectRatio(backup->mCamera.mAspectRatio);
            camera->setCastShadows(backup->mCamera.mCastShadows);
            camera->setFocalLength(backup->mCamera.mFocalLenght);
            camera->setVisibilityFlags(backup->mCamera.mVisibilityFlags); 
            camera->setQueryFlags(backup->mCamera.mQueryFlags); 
            camera->setLightMask(backup->mCamera.mLightMask);
            
            //restore viewport settings
            viewport->setDimensions(backup->mTop,backup->mLeft,
                                    backup->mWidth,backup->mHeight);
            viewport->setBackgroundColour(backup->mBackgroundColor);
            viewport->setClearEveryFrame(backup->mClearEveryFrame);
            viewport->setMaterialScheme(backup->mMaterialSchema);
            viewport->setRenderQueueInvocationSequenceName(backup->mRenderQueueInvocationSequenceName);
            viewport->setOverlaysEnabled(backup->mOverlaysEnabled);
            viewport->setShadowsEnabled(backup->mShadowsEnabled);
            viewport->setSkiesEnabled(backup->mSkiesEnabled);
            viewport->setVisibilityMask(backup->mVisibilityMask);
        }
        else 
        {
           Camera* camera = mSceneMgr->getCamera(backup->mCamera.mName);
            if (! camera)
                mSceneMgr->createCamera(backup->mCamera.mName); 
            
            camera->setPosition(backup->mCamera.mPosition);
            camera->setDirection(backup->mCamera.mDirection);
            camera->setOrientation(backup->mCamera.mOrientation);
            camera->setPolygonMode(backup->mCamera.mPolygonMode);
            camera->setNearClipDistance(backup->mCamera.mNearPlane); 
            camera->setFarClipDistance(backup->mCamera.mFarPlane);
            camera->setProjectionType(backup->mCamera.mProjectionType);
            camera->setFOVy(backup->mCamera.mFOVy);
            camera->setAspectRatio(backup->mCamera.mAspectRatio);
            camera->setCastShadows(backup->mCamera.mCastShadows);
            camera->setFocalLength(backup->mCamera.mFocalLenght);
            camera->setVisibilityFlags(backup->mCamera.mVisibilityFlags); 
            camera->setQueryFlags(backup->mCamera.mQueryFlags); 
            camera->setLightMask(backup->mCamera.mLightMask);
            
            window->addViewport(camera, backup->mZOrder, backup->mTop, backup->mLeft, backup->mWidth, backup->mHeight);
        }
        
        delete backup; backup = 0; mBackupViewport[i] = 0;
    }
}
//----------------------------------------------------------------------------
const String& DotScene::getName()
{
    return mName;
}
//----------------------------------------------------------------------------
void DotScene::setVisible(bool visible)
{
    //Check if my scene root node and scene manager root mode is the same
    
    if (mSceneMgr->getRootSceneNode()->getName() == mSceneRoot->getName())
    {
        mSceneRoot->setVisible(true);
    }
    else
    {
        //If not attach to scene node and must be - add to RootScenenode
        if ((visible) && (! mSceneRoot->isInSceneGraph()))
            mSceneMgr->getRootSceneNode()->addChild(mSceneRoot);
        
        //If attach to scene node and not must be - remove to RootScenenode
        if ((! visible) && ( mSceneRoot->isInSceneGraph()))
            mSceneMgr->getRootSceneNode()->removeChild(mSceneRoot);
    }
}
//----------------------------------------------------------------------------
bool DotScene::getVisible(void)
{
    return mSceneRoot->isInSceneGraph();
}
//----------------------------------------------------------------------------
void DotScene::processScene(TiXmlElement* root)
{
    TRACE_FUNC();
    
    // Process the scene parameters
    String str = getAttrib(root, "formatVersion", "unknown");
    mProperties.push_back(new SceneNodeProperty<DotScene>(this,"formatVersion",str,SCENE));
    str = getAttrib(root, "id", "unknown");
    mProperties.push_back(new SceneNodeProperty<DotScene>(this,"id",str,SCENE));
    str = getAttrib(root, "minOgreVersion", OGRE_VERSION_NAME);
    mProperties.push_back(new SceneNodeProperty<DotScene>(this,"minOgreVersion",str,SCENE));
    str = getAttrib(root, "author", "iBIT");
    mProperties.push_back(new SceneNodeProperty<DotScene>(this,"author",str,SCENE));
    str = getAttrib(root, "sceneManager", mSceneMgr->getName().c_str());
    mProperties.push_back(new SceneNodeProperty<DotScene>(this,"sceneManager",str,SCENE));
    str = getAttrib(root, "upAxis", "y");
    mProperties.push_back(new SceneNodeProperty<DotScene>(this,"upAxis",str,SCENE));
    str = getAttrib(root, "unitsPerMeter", "100");
    mProperties.push_back(new SceneNodeProperty<DotScene>(this,"unitsPerMeter",str,SCENE));
    str = getAttrib(root, "unitType", "centimeters");
    mProperties.push_back(new SceneNodeProperty<DotScene>(this,"unitType",str,SCENE));
    str = getAttrib(root, "ogreMaxVersion", "unknown");
    mProperties.push_back(new SceneNodeProperty<DotScene>(this,"ogreMaxVersion",str,SCENE));
    str = getAttrib(root, "application", "unknown");
    {
        mProperties.push_back(new SceneNodeProperty<DotScene>(this,"application",str,SCENE));
        StringUtil::toLowerCase(str);
        
        mAnimationPackage = ANIMATION_PKG_OTHER;
        if ("maya" == str) mAnimationPackage = ANIMATION_PKG_MAYA;
    }
    //Calculamos factor de conversion de unidades de escena
    mUnitConversionFactor = /*getAttribReal(root, "unitsPerMeter", 100.0f)*/ 1.0f;
    
    TiXmlElement* elem = 0;

    //Comprobamos que no se llame dos veces a esta funcion
    assert(! mSceneRoot);
    
    //Set default ambient light
    mSceneMgr->setAmbientLight(mAmbientLight);
    
    assert(! mSceneMgr->hasSceneNode(mPrefix + this->getName() + "RootNode")); //Nunca deberia pasar
    
    mSceneRoot = mSceneMgr->createSceneNode(mPrefix + this->getName() + "RootNode");
    //mSceneNodes.push_back(mSceneRoot->getName());
    
    // Process nodes (?)
    elem = root->FirstChildElement("nodes");
    if (elem)
        processNodes(elem);

    // Process externals (?)
    elem = root->FirstChildElement("externals");
    if (elem)
        processExternals(elem);

    // Process environment (?)
    elem = root->FirstChildElement("environment");
    if (elem)
        processEnvironment(elem);

    // Process terrain (?)
    elem = root->FirstChildElement("terrain");
    if (elem)
        processTerrain(elem);

    // Process octree (?)
    elem = root->FirstChildElement("octree");
    if (elem)
        processOctree(elem);

    // Process light (?)
    elem = root->FirstChildElement("light");
    if (elem)
        processLight(elem,0);

    // Process camera (?)
    elem = root->FirstChildElement("camera");
    if (elem)
        processCamera(elem,0);
    
    // Process rendertextures (?)
    elem = root->FirstChildElement("renderTextures");
    if (elem)
        processRenderTextures(elem);
    
    // Process queryFlags (?)
    elem = root->FirstChildElement("queryFlags");
    if (elem)
        mQueryFlags = parseQueryFlags(elem);
    
    // Process visibilityFlags (?)
    elem = root->FirstChildElement("visibilityFlags");
    if (elem)
        mVisibilityFlags = parseVisibilityFlags(elem);
    
    // Process instancedGeometries (?)
    elem = root->FirstChildElement("instancedGeometries");
    if (elem)
        processInstancedGeometries(elem);
    
    // Process staticGeometries (?)
    elem = root->FirstChildElement("staticGeometries");
    if (elem)
        processStaticGeometries(elem);
    
    // Process portalConnectedZones (?)
    elem = root->FirstChildElement("portalConnectedZones");
    if (elem)
        processPortalConnectedZones(elem);
    
    // Process userdata (*)
    elem = root->FirstChildElement("userData");
    while(elem)
    {
        processUserData<DotScene>(elem, this, SCENE);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = root->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<DotScene>(elem, this, SCENE);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processNodes(TiXmlElement* node)
{
    TRACE_FUNC();
    assert(mSceneRoot);
    
    TiXmlElement* elem = 0;

    SceneNode* sceneNode = mSceneRoot->createChildSceneNode(mPrefix + "Nodes" + generateUUID());
    mSceneNodes.push_back(sceneNode->getName());
    
    // Process position (?)
    elem = node->FirstChildElement("position");
    if (elem)
        sceneNode->setPosition(mUnitConversionFactor * parseVector3(elem));

    // Process rotation (?)
    elem = node->FirstChildElement("rotation");
    if (elem)
        sceneNode->setOrientation(parseQuaternion(elem));
    
    // Process rotation alternative(?)
    elem = node->FirstChildElement("quaternion");
    if (elem)
        sceneNode->setOrientation(parseQuaternion(elem));
    
    // Process scale (?)
    elem = node->FirstChildElement("scale");
    if (elem)
        sceneNode->setScale(parseVector3(elem));
    
    //set initial state
    sceneNode->setInitialState();
    
    // Process node (*)
    elem = node->FirstChildElement("node");
    while(elem)
    {
        processNode(elem,sceneNode);
        elem = elem->NextSiblingElement("node");
    }
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<SceneNode>(elem, sceneNode, SCENE_NODE);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<SceneNode>(elem, sceneNode, SCENE_NODE);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processNode(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    assert(parent);
    
    // Construct the node's name
    String name = mPrefix + getAttrib(node, "name");

    // Create the scene node
    SceneNode* sceneNode;
    if(name.empty())
        sceneNode = parent->createChildSceneNode();
    else
        sceneNode = parent->createChildSceneNode(name);
    mSceneNodes.push_back(sceneNode->getName());
    
    // Process other attributes
    String id = getAttrib(node, "id");
    id = (StringUtil::BLANK == id)? name: id;
    
    bool visible = getAttribBool(node, "visible", true);
    sceneNode->setVisible(visible);
    
    // set target property
    bool isTarget = getAttribBool(node, "isTarget");
    //TODO decidir donde guardar las propiedades del objeto
    //TODO OPCION 1: Como Any de los nodos
    sceneNode->getUserObjectBindings().setUserAny("isTarget",Any(isTarget));
    //TODO OPCION 2: Como propiedades
    addProperty<SceneNode>(sceneNode,"isTarget",stringify(isTarget),SCENE_NODE);
    
    TiXmlElement* elem = 0;

    // Process position (?)
    elem = node->FirstChildElement("position");
    if (elem)
        sceneNode->setPosition(mUnitConversionFactor * parseVector3(elem));

    // Process rotation (?)
    elem = node->FirstChildElement("rotation");
    if (elem)
        sceneNode->setOrientation(parseQuaternion(elem));
    
    // Process rotation alternative (?)
    elem = node->FirstChildElement("quaternion");
    if (elem)
        sceneNode->setOrientation(parseQuaternion(elem));
    
    // Process scale (?)
    elem = node->FirstChildElement("scale");
    if (elem)
        sceneNode->setScale(parseVector3(elem));

    //set initial state
    sceneNode->setInitialState();
    
    // Process lookTarget (?)
    elem = node->FirstChildElement("lookTarget");
    if (elem)
        processLookTarget(elem, sceneNode);

    // Process trackTarget (?)
    elem = node->FirstChildElement("trackTarget");
    if (elem)
        processTrackTarget(elem, sceneNode);

    // Process node (*)
    elem = node->FirstChildElement("node");
    while(elem)
    {
        processNode(elem, sceneNode);
        elem = elem->NextSiblingElement("node");
    }

    // Process entity (*)
    elem = node->FirstChildElement("entity");
    while(elem)
    {
        processEntity(elem, sceneNode);
        elem = elem->NextSiblingElement("entity");
    }

    // Process light (*)
    elem = node->FirstChildElement("light");
    while(elem)
    {
        processLight(elem, sceneNode);
        elem = elem->NextSiblingElement("light");
    }

    // Process camera (*)
    elem = node->FirstChildElement("camera");
    while(elem)
    {
        processCamera(elem, sceneNode);
        elem = elem->NextSiblingElement("camera");
    }

    // Process particleSystem (*)
    elem = node->FirstChildElement("particleSystem");
    while(elem)
    {
        processParticleSystem(elem, sceneNode);
        elem = elem->NextSiblingElement("particleSystem");
    }

    // Process billboardSet (*)
    elem = node->FirstChildElement("billboardSet");
    while(elem)
    {
        processBillboardSet(elem, sceneNode);
        elem = elem->NextSiblingElement("billboardSet");
    }
    
    // Process plane (*)
    elem = node->FirstChildElement("plane");
    while(elem)
    {
        processPlane(elem, sceneNode);
        elem = elem->NextSiblingElement("plane");
    }

    // Process plane (*)
    elem = node->FirstChildElement("animations");
    if(elem)
    {
        TiXmlElement* child = node->FirstChildElement("animation");
        while(child)
        {
            processAnimation(elem, sceneNode);
            elem = elem->NextSiblingElement();
        }
    }

    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<SceneNode>(elem, sceneNode, SCENE_NODE);
        elem = elem->NextSiblingElement("userData");
    } 
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while(elem)
    {
        processUserDataReference<SceneNode>(elem, sceneNode, SCENE_NODE); 
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processExternals(TiXmlElement* node)
{
    TRACE_FUNC();
    TiXmlElement* elem = 0;

    // Process items
    Resource* resource = 0;
    
    elem = node->FirstChildElement("item");
    while (elem)
    {
        String type = getAttrib(elem, "type", StringUtil::BLANK);
        TiXmlElement* asset = elem->FirstChildElement("file");
        
        if (elem)
        {
            //process external file: material
            if ( "material" == type )
            {
                const String material = getAttrib(asset, "name", StringUtil::BLANK);
                ResourcePtr ptr =  MaterialManager::getSingletonPtr()->load(material, mGroup);
                if (ptr.isNull())
                {
                    log("Failed to load material" + material);
                }
                else
                {
                    mExternals.insert(std::make_pair<String,String>(material,type));
                }
            }
            
            //process external file: particles system
            if ( "particle" == type )
            {
                assert(false);
            }
            
            //process external file: overlays
            if ( "overlay" == type )
            {
                assert(false);
            }
        }
    }
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<Resource>(elem, resource, EXTERNAL);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<Resource>(elem, resource, EXTERNAL);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processEnvironment(TiXmlElement* node)
{
    TRACE_FUNC();
    
    TiXmlElement* elem = 0;

    // Process fog (?)
    elem = node->FirstChildElement("fog");
    if (elem)
        processFog(elem);

    // Process skyBox (?)
    elem = node->FirstChildElement("skyBox");
    if (elem)
        processSkyBox(elem);

    // Process skyDome (?)
    elem = node->FirstChildElement("skyDome");
    if (elem)
        processSkyDome(elem);

    // Process skyPlane (?)
    elem = node->FirstChildElement("skyPlane");
    if (elem)
        processSkyPlane(elem);

    // Process clipping (?)
    elem = node->FirstChildElement("clipping");
    if (elem)
        processClipping(elem, &mClipPlanes);

    // Process colourAmbient (?)
    elem = node->FirstChildElement("colourAmbient");
    if (elem)
    {
        mAmbientLight = parseColour(elem);
        mSceneMgr->setAmbientLight(mAmbientLight);
    }

    // Process colourBackground (?)
    elem = node->FirstChildElement("colourBackground");
    {
        //Lo guardamos para posterior uso en caso de no tener viewport definido
        mBackgroundColor = parseColour(elem);
        
        //if exists viewport apply it this background color
        RenderWindow* window =  Root::getSingletonPtr()->getAutoCreatedWindow();
        if (window->getNumViewports() > 0)
        {
            for(int i=0; i<window->getNumViewports(); i++)
            {
                window->getViewport(i)->setBackgroundColour(mBackgroundColor);
            }   
        }   
    }

    // Process shadows ( Maya specific feature?)
    elem = node->FirstChildElement("shadows");
    if (elem)
        processShadow(elem);
    // Process shadows ( Maya specific feature alternative?)
    elem = node->FirstChildElement("shadow");
    if (elem)
        processShadow(elem);
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<DotScene>(elem, this, ENVIROMENT);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<DotScene>(elem, this, ENVIROMENT);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processTerrain(TiXmlElement* node)
{
    TRACE_FUNC();
    assert(false);
    
    String terrain = getAttrib(node,"dataFile");
    String queue = getAttrib(node,"renderQueue");

    assert(StringUtil::BLANK != terrain);
    
    mSceneMgr->setWorldGeometry(terrain);
    
    if (StringUtil::BLANK != queue)
        mSceneMgr->setWorldGeometryRenderQueue(parseRenderQueue(queue));
    
    TiXmlElement* elem = 0;
    
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<DotScene>(elem, this, TERRAIN);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<DotScene>(elem, this, TERRAIN);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processOctree(TiXmlElement* node)
{
    assert(false);
    TRACE_FUNC();

    log("TODO implement DotScene::processOctree"); 
    
    String file = getAttrib(node, "binFile");
    
    TiXmlElement* elem = 0;
    
    // Process octNode (*)
    elem = node->FirstChildElement("octNode");
    while(elem)
    {
        processOctNode(elem);
        elem = elem->NextSiblingElement();
    }
    
    // Process octMesh (*)
    elem = node->FirstChildElement("octMesh");
    while(elem)
    {
        processOctMesh(elem);
        elem = elem->NextSiblingElement();
    }
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<SceneManager>(elem, mSceneMgr, OCTREE);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<SceneManager>(elem, mSceneMgr, OCTREE);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processOctNode(TiXmlElement* node)
{
    assert(false);
    TRACE_FUNC();
    
    String px = getAttrib(node, "px");
    String py = getAttrib(node, "py");
    String pz = getAttrib(node, "pz");
    String width = getAttrib(node, "width");
    String height = getAttrib(node, "height");
    String depth = getAttrib(node, "depth");
    
    TiXmlElement* elem = 0;
    
    //process children octNode (*)
    elem = node->FirstChildElement("octNode");
    while (elem)
    {
        processOctNode(elem);
        elem = elem->NextSiblingElement();
    }
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<SceneManager>(elem, mSceneMgr, OCTREE_NODE);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<SceneManager>(elem, mSceneMgr, OCTREE_NODE);
        elem = elem->NextSiblingElement("userDataReference");
    } 
}
//----------------------------------------------------------------------------
void DotScene::processOctMesh(TiXmlElement* node)
{
    assert(false);
    TRACE_FUNC();
    
    TiXmlElement* elem = 0;
    
    //process children octNode (*)
    elem = node->FirstChildElement("octGeometry");
    if (elem)
    {
        String binaryDataOffset = getAttrib(node, "binaryDataOffset");
        String vertTotal = getAttrib(node, "vertTotal");
        String triTotal = getAttrib(node, "triTotal");
        String normalTotal = getAttrib(node, "normalTotal");
        String colorTotal = getAttrib(node, "colorTotal");
        String texSets = getAttrib(node, "texSets");
        String texTotal = getAttrib(node, "texTotal");
    }
    
    //process children octNode (*)
    elem = node->FirstChildElement("octMaterial");
    if (elem)
    {
        String name = getAttrib(node, "name");
        String texture = getAttrib(node, "texture");
    }
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<SceneManager>(elem, mSceneMgr, OCTREE_MESH);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<SceneManager>(elem, mSceneMgr, OCTREE_MESH);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processLight(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    
    // Process attributes
    String id = getAttrib(node, "id");
    String name = mPrefix + getAttrib(node, "name");
    id = (StringUtil::BLANK == id)? name: id;
    
    String type = getAttrib(node, "type");
    bool visible = getAttribBool(node, "visible", true);
    bool castShadows = getAttribBool(node, "castShadows", true);
    Real power = getAttribReal(node, "power", 1.0f);
    
    int queryFlags =  getAttribInt(node, "queryFlags", 0);
    int visibilityFlags = getAttribInt(node, "visibilityFlags", 0);
    
    bool ambientOnly = getAttribBool(node, "ambientOnly", false); 
    bool affectDiffuse = getAttribBool(node, "affectDiffuse", true); 
    bool affectSpecular = getAttribBool(node, "affectSpecular", true);
    
    //TODO averiguar uso de estos atributos
    assert(! ambientOnly);
    
    // Create the light and attach to scenenode (if required)
    Light* light = (mSceneMgr->hasLight(name))? 
                          mSceneMgr->getLight(name): 
                          mSceneMgr->createLight(name);
    mLights.push_back(light->getName());
    
    //attach to scenenode (if needed)
    if(parent)
        parent->attachObject(light);

    if (type == "point")
        light->setType(Light::LT_POINT);
    else if (type == "directional")
        light->setType(Light::LT_DIRECTIONAL);
    else if (type == "spot")
        light->setType(Light::LT_SPOTLIGHT);
    else if (type == "radPoint")
        light->setType(Light::LT_POINT);

    //set light parameters
    light->setVisible(visible);
    light->setCastShadows(castShadows);
    light->setPowerScale(power);
    
    // 
    if (visibilityFlags) 
        light->setVisibilityFlags(visibilityFlags);
    if (queryFlags) 
        light->setVisibilityFlags(queryFlags);
    //
    
    TiXmlElement* elem = 0;

    // Process position (?)
    elem = node->FirstChildElement("position");
    if ((elem) && ( light->getType() != Light::LT_DIRECTIONAL))
        light->setPosition(mUnitConversionFactor * parseVector3(elem));

    // Process direction (?)
    elem = node->FirstChildElement("normal");
    if ((elem) && ( light->getType() != Light::LT_POINT))
        light->setDirection(parseVector3(elem));
    
    // Process direction alternative (?)
    elem = node->FirstChildElement("rotation");
    if ((elem) && ( light->getType() != Light::LT_POINT))
    {
        Quaternion orientation = parseQuaternion(elem);
        Vector3 direction;
        orientation.ToAxes(&direction);
        light->setDirection(direction);
        
        //Fix some speficic animation package issues 
        //   exporter is not considering coordinate system (Y-UP for maya Z-UP fro Ogre) 
        if (ANIMATION_PKG_MAYA == mAnimationPackage)
        {
            direction = orientation * Vector3::UNIT_Z;
            light->setDirection(direction);
        }
    }
    // Process direction alternative alternative(?)
    elem = node->FirstChildElement("quaternion");
    if ((elem) && ( light->getType() != Light::LT_POINT))
    {
        Quaternion orientation = parseQuaternion(elem);
        Vector3 direction;
        orientation.ToAxes(&direction);
        light->setDirection(direction);
        
        //Fix some speficic animation package issues 
        //   exporter is not considering coordinate system (Y-UP for maya Z-UP fro Ogre) 
        if (ANIMATION_PKG_MAYA == mAnimationPackage)
        {
            direction = orientation * Vector3::UNIT_Z;
            light->setDirection(direction);
        }
    }
    
    // Process colourDiffuse (?)
    elem = node->FirstChildElement("colourDiffuse");
    if ( (elem) && (affectDiffuse))
        light->setDiffuseColour(parseColour(elem));

    // Process colourSpecular (?)
    elem = node->FirstChildElement("colourSpecular");
    if ((elem) && (affectSpecular))
        light->setSpecularColour(parseColour(elem));

    // Process lightRange (?)
    elem = node->FirstChildElement("lightRange");
    if ((elem) && ( light->getType() == Light::LT_SPOTLIGHT))
        processLightRange(elem, light);

    // Process lightAttenuation (?)
    elem = node->FirstChildElement("lightAttenuation");
    if ((elem) && ( light->getType() != Light::LT_DIRECTIONAL))
        processLightAttenuation(elem, light);

    // Process noteTracks (?)
//     elem = node->FirstChildElement("noteTracks");
//     if (elem)
//         processNoteTrack(elem);
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<Light>(elem, light, LIGHT);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<Light>(elem, light, LIGHT);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processCamera(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    
    // Process attributes
    String id = getAttrib(node, "id");
    String name = mPrefix + getAttrib(node, "name");
    id = (StringUtil::BLANK == id)? name: id;
    
    String projectionType = getAttrib(node, "projectionType", "perspective");
    Real fov = getAttribReal(node, "fov", Math::PI/2);
    Real aspectRatio = getAttribReal(node, "aspectRatio", 4.0f/3.0f);
    Real width = getAttribReal(node, "orthoWidth", 50.0f);
    Real height = getAttribReal(node, "orthoHeight", 50.0f);
    
    int queryFlags =  getAttribInt(node, "queryFlags", 0);
    int visibilityFlags = getAttribInt(node, "visibilityFlags", 0);
    bool visible = getAttribBool(node, "visible", true);
    
    ClippingPlanesType clipPlanes;
    clipPlanes.mNear = NEAR_CLIP_DISTANCE;
    clipPlanes.mFar = FAR_CLIP_DISTANCE;
    
    // Create the camera
    Camera* camera = (mSceneMgr->hasCamera(name))? 
                            mSceneMgr->getCamera(name):
                            mSceneMgr->createCamera(name);
    mCameras.push_back(camera->getName());
    
    //Set camera settings
    camera->setVisible(visible);
    
    if (visibilityFlags) 
        camera->setVisibilityFlags(visibilityFlags);
    if (queryFlags) 
        camera->setVisibilityFlags(queryFlags);
    
    //Attach to node (if required)
    if(parent)
        parent->attachObject(camera);

    // Set the projection type
    if(projectionType == "perspective")
    {
        camera->setProjectionType(PT_PERSPECTIVE);
        //KLUDGE <malcalde@ibit.org> camera FOVy in radians
        camera->setFOVy(parseAngleUnit(fov));
        camera->setAspectRatio(aspectRatio);
    }
    else if(projectionType == "orthographic")
    {
        assert(false);
        camera->setProjectionType(PT_ORTHOGRAPHIC);
        camera->setOrthoWindowWidth(width);
        camera->setOrthoWindowHeight(height);
    }

    TiXmlElement* elem = 0;

    // Process clipping (?)
    elem = node->FirstChildElement("clipping");
    if (elem)
        processClipping(elem, &clipPlanes);
    
    camera->setNearClipDistance(clipPlanes.mNear);
    camera->setFarClipDistance(clipPlanes.mFar);
    
    // Process position (?)
    elem = node->FirstChildElement("position");
    if (elem)
        camera->setPosition(mUnitConversionFactor * parseVector3(elem));

    // Process rotation (?)
    elem = node->FirstChildElement("rotation");
    if (elem)
        camera->setOrientation(parseQuaternion(elem));
    // Process quaternion (?)
    elem = node->FirstChildElement("quaternion");
    if (elem)
        camera->setOrientation(parseQuaternion(elem));

    // Process normal (?)
    elem = node->FirstChildElement("normal");
    if (elem)
       camera->setDirection(parseVector3(elem)); 

    // Process lookTarget (?)
    elem = node->FirstChildElement("lookTarget");
    if (elem)
        processLookTarget(elem, parent);

    // Process trackTarget (?)
    elem = node->FirstChildElement("trackTarget");
    if (elem)
        processTrackTarget(elem, parent);
    
    // Process trackTarget (?)
//     elem = node->FirstChildElement("noteTracks");
//     if (elem)
//         processNoteTrack(elem);
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<Camera>(elem, camera, CAMERA);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<Camera>(elem, camera, CAMERA);
        elem = elem->NextSiblingElement("userDataReference");
    }
    
    //Si es camara por defecto
    bool isdefault = boost::algorithm::ends_with(name, "default");
    isdefault |= getPropertyBool(name,"default");
    
     if (isdefault)
        setDefaultCamera(name);
}
//----------------------------------------------------------------------------
void DotScene::processLookTarget(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    assert(false);
    
    // Process attributes
    String nodeName = getAttrib(node, "nodeName");

    Node::TransformSpace relativeTo = Node::TS_PARENT;
    String value = getAttrib(node, "relativeTo");
    if(value == "local")
        relativeTo = Node::TS_LOCAL;
    else if(value == "parent")
        relativeTo = Node::TS_PARENT;
    else if(value == "world")
        relativeTo = Node::TS_WORLD;

    TiXmlElement* elem = 0;

    // Process position (?)
    Vector3 position;
    elem = node->FirstChildElement("position");
    if (elem)
        position = parseVector3(elem);

    // Process localDirection (?)
    Vector3 localDirection = Vector3::NEGATIVE_UNIT_Z;
    elem = node->FirstChildElement("localDirection");
    if (elem)
        localDirection = parseVector3(elem);

    SceneNode* lookTargetNode = 0;
    // Setup the look target
    try
    {
        if (StringUtil::BLANK != nodeName)
        {
            lookTargetNode = mSceneMgr->getSceneNode(nodeName);
            position = lookTargetNode->_getDerivedPosition();
        }

        parent->lookAt(position, relativeTo, localDirection);
    }
    catch(Exception &e)
    {
        log("[DotScene] Error processing a look target! -> " + e.getFullDescription());
        assert(false);
    }
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<SceneNode>(elem, parent, LOOK_TARGET);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<SceneNode>(elem, parent, LOOK_TARGET);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processTrackTarget(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    assert(false);
    
    // Process attributes
    String nodeName = getAttrib(node, "nodeName");

    TiXmlElement* elem = 0;

    // Process localDirection (?)
    Vector3 localDirection = Vector3::NEGATIVE_UNIT_Z;
    elem = node->FirstChildElement("localDirection");
    if (elem)
        localDirection = parseVector3(elem);

    // Process offset (?)
    Vector3 offset = Vector3::ZERO;
    elem = node->FirstChildElement("offset");
    if (elem)
        offset = parseVector3(elem);

    // Setup the track target
    SceneNode* trackTargetNode = 0;    
    try
    {
        trackTargetNode = mSceneMgr->getSceneNode(nodeName);
        parent->setAutoTracking(true, trackTargetNode, localDirection, offset);
    }
    catch(Exception &e)
    {
        log("[DotScene] Error processing a track target! -> " + e.getFullDescription());
        assert(false);
    }
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<SceneNode>(elem, parent, TRACK_TARGET);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<SceneNode>(elem, parent, TRACK_TARGET);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processEntity(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    assert(parent);
    
    // Process attributes
    String id = getAttrib(node, "id");
    String name = mPrefix + getAttrib(node, "name");
    id = (StringUtil::BLANK == id)? name: id;
    
    String mesh = getAttrib(node, "meshFile");
    
    String material = getAttrib(node, "materialFile");
    if (StringUtil::BLANK == material)
        material = getAttrib(node, "material");
    
    bool isStatic = getAttribBool(node, "static", false);
    bool castShadows = getAttribBool(node, "castShadows", true);
    bool receiveShadows = getAttribBool(node, "receiveShadows", true);

    SkeletonAnimationBlendMode skelAnimMode = ANIMBLEND_AVERAGE;
    String _skelAnimMode = getAttrib(node, "skeletonAnimationBlendMode");
    StringUtil::toLowerCase(_skelAnimMode);
    if (_skelAnimMode == "average")
          skelAnimMode = ANIMBLEND_AVERAGE;
    else if (_skelAnimMode == "cumulative")
        skelAnimMode = ANIMBLEND_CUMULATIVE;

    int queryFlags =  getAttribInt(node, "queryFlags", mQueryFlags);
    int visibilityFlags = getAttribInt(node, "visibilityFlags", mVisibilityFlags);
    bool visible = getAttribBool(node, "visible", true);
    
    String renderQueue = getAttrib(node, "renderQueue");
    float renderingDistance = getAttribReal(node, "renderingDistance");
    
    assert(StringUtil::BLANK != mesh);

    TiXmlElement* elem = 0;

    // Create the entity
    Entity *entity = 0;
    try
    {
        unsigned short src, dest;
        
        MeshPtr meshPtr = MeshManager::getSingleton().load(mesh, mGroup);
//         if (!meshPtr->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
//         {
//             meshPtr->buildTangentVectors(VES_TANGENT, src, dest);
//         }

        entity = (mSceneMgr->hasEntity(name))? 
                  mSceneMgr->getEntity(name):
                  mSceneMgr->createEntity(name, mesh);                  
        // Maintain a list of static and dynamic objects
        if(isStatic)
            mStaticEntities.push_back(name);
        else
            mDynamicEntities.push_back(name);
        
        entity->setCastShadows(castShadows);
        
        // 
        entity->setVisible(visible);
        if (visibilityFlags) 
            entity->setVisibilityFlags(visibilityFlags);
        if (queryFlags) 
            entity->setVisibilityFlags(queryFlags);
        if (renderingDistance > 0)
            entity->setRenderingDistance(renderingDistance);
        if (StringUtil::BLANK != renderQueue)
            entity->setRenderQueueGroup(parseRenderQueue(renderQueue));
        //
        
        SkeletonInstance* skeleton = entity->getSkeleton();
        if (skeleton)
            skeleton->setBlendMode(skelAnimMode);

        // Process vertexBuffer (?)
        elem = node->FirstChildElement("vertexBuffer");
        if (elem)
        {
            HardwareVertexBuffer::Usage usage = HardwareVertexBuffer::HBU_STATIC;
            bool useShadowBuffer = false;
            
            processVertexBuffer(elem, &usage, &useShadowBuffer);
            entity->getMesh().getPointer()->setVertexBufferPolicy(usage, useShadowBuffer);
        }

        // Process indexBuffer (?)
        elem = node->FirstChildElement("indexBuffer");
        if (elem)
        {
            HardwareIndexBuffer::Usage usage = HardwareIndexBuffer::HBU_STATIC;
            bool useShadowBuffer = false;
            
            processIndexBuffer(elem, &usage, &useShadowBuffer);
            entity->getMesh().getPointer()->setIndexBufferPolicy(usage, useShadowBuffer);
        }
        
        // Process subentities (?)
        elem = node->FirstChildElement("subentities");
        if (elem)
        {
            elem = elem->FirstChildElement("subentity");
            while (elem)
            {
                processSubEntity(elem, entity);
                elem = elem->NextSiblingElement();
            }
        }
       
       // Process noteTracks (?)
//        elem = node->FirstChildElement("noteTracks");
//         if (elem)
//         {
//             elem = elem->FirstChildElement("noteTrack");
//             while (elem)
//             {
//                 processNoteTrack(elem, entity);
//                 elem = elem->NextSiblingElement();
//             }
//         }
//         
        elem = node->FirstChildElement("customParameters");
        if (elem)
        {
            elem = elem->FirstChildElement("customParameter");
            while (elem)
            {
                processCustomParameter(elem, entity);
                elem = elem->NextSiblingElement();
            }
        }
        
        elem = node->FirstChildElement("boneAttachments");
        if (elem)
        {
            elem = elem->FirstChildElement("boneAttachment");
            while (elem)
            {
                processBoneAttachment(elem, entity);
                elem = elem->NextSiblingElement();
            }
        }
        
        if (StringUtil::BLANK != material)
        {
            MaterialPtr materialPtr =  MaterialManager::getSingletonPtr()->getByName(material);
            assert(! materialPtr.isNull());
            materialPtr.getPointer()->setReceiveShadows(receiveShadows);
            entity->setMaterial(materialPtr); 
        }
        
        log("Attaching entity " + entity->getName() + " on node " + parent->getName());  
        parent->attachObject(entity);
    }
    catch(Exception &e)
    {
        log("[DotScene] Error loading an entity! -> " + e.getFullDescription());
        assert(false);        
    }

    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<Entity>(elem, entity, ENTITY);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<Entity>(elem, entity, ENTITY);
        elem = elem->NextSiblingElement("userDataReference");
    }     
}
//----------------------------------------------------------------------------
void DotScene::processEntity(TiXmlElement* node, InstancedGeometry* geometry)
{
    TRACE_FUNC();
    assert(geometry);
    
    // Process attributes
    String id = getAttrib(node, "id");
    String name = mPrefix + getAttrib(node, "name");
    id = (StringUtil::BLANK == id)? name: id;
    
    String mesh = getAttrib(node, "meshFile");
    String material = getAttrib(node, "materialFile");
    if (StringUtil::BLANK == material)
        material = getAttrib(node, "material");
    
    bool isStatic = getAttribBool(node, "static", false);
    bool castShadows = getAttribBool(node, "castShadows", true);
    bool receiveShadows = getAttribBool(node, "receiveShadows", true);

    int queryFlags =  getAttribInt(node, "queryFlags", 0);
    int visibilityFlags = getAttribInt(node, "visibilityFlags", 0);
    bool visible = getAttribBool(node, "visible", true);
    
    String renderQueue = getAttrib(node, "renderQueue");
    float renderingDistance = getAttribReal(node, "renderingDistance"); 
    
    Vector3 position = Vector3::ZERO;
    Quaternion orientation = Quaternion::IDENTITY;
    Vector3 scale = Vector3::UNIT_SCALE;
    
    assert(StringUtil::BLANK != mesh);

    TiXmlElement* elem = 0;

    // Process position (?)
    elem = node->FirstChildElement("position");
    if (elem)
        position = parseVector3(elem);

    // Process rotation (?)
    elem = node->FirstChildElement("rotation");
    if (elem)
        orientation = parseQuaternion(elem);
    
    // Process rotation alternative (?)
    elem = node->FirstChildElement("quaternion");
    if (elem)
        orientation = parseQuaternion(elem);

    // Process scale (?)
    elem = node->FirstChildElement("scale");
    if (elem)
        scale = parseVector3(elem);
    
    // Create the entity
    Entity *entity = 0;
    try
    {
        unsigned short src, dest;
        
        MeshPtr meshPtr = MeshManager::getSingleton().load(mesh, mGroup);
        if (!meshPtr->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
        {
            meshPtr->buildTangentVectors(VES_TANGENT, src, dest);
        }

        entity = (mSceneMgr->hasEntity(name))? 
                  mSceneMgr->getEntity(name):
                  mSceneMgr->createEntity(name, mesh);                  
        // Maintain a list of static and dynamic objects
        if(isStatic)
            mStaticEntities.push_back(name);
        else
            mDynamicEntities.push_back(name);
        
        entity->setCastShadows(castShadows);
        
        // 
        entity->setVisible(visible);
        if (visibilityFlags) 
            entity->setVisibilityFlags(visibilityFlags);
        if (queryFlags) 
            entity->setVisibilityFlags(queryFlags);
        if (renderingDistance > 0)
            entity->setRenderingDistance(renderingDistance);
        if (StringUtil::BLANK != renderQueue)
            entity->setRenderQueueGroup(parseRenderQueue(renderQueue));
        //
        
        if (StringUtil::BLANK != renderQueue)
            entity->setRenderQueueGroup(parseRenderQueue(renderQueue));
        
        if  (castShadows && meshPtr->isEdgeListBuilt())
            meshPtr->buildEdgeList();

        // Process vertexBuffer (?)
        elem = node->FirstChildElement("vertexBuffer");
        if (elem)
        {
            HardwareVertexBuffer::Usage usage = HardwareVertexBuffer::HBU_STATIC;
            bool useShadowBuffer = false;

            processVertexBuffer(elem, &usage, &useShadowBuffer);
            entity->getMesh().getPointer()->setVertexBufferPolicy(usage, useShadowBuffer);
        }

        // Process indexBuffer (?)
        elem = node->FirstChildElement("indexBuffer");
        if (elem)
        {
            HardwareIndexBuffer::Usage usage = HardwareIndexBuffer::HBU_STATIC;
            bool useShadowBuffer = false;

            processIndexBuffer(elem, &usage, &useShadowBuffer);
            entity->getMesh().getPointer()->setIndexBufferPolicy(usage, useShadowBuffer);
        }
        
        elem = node->FirstChildElement("subentities");
        if (elem)
        {
            elem = elem->FirstChildElement("subentity");
            while (elem)
            {
                processSubEntity(elem, entity);
                elem = elem->NextSiblingElement();
            }
        }
        
        if (StringUtil::BLANK != material)
        {
            MaterialPtr materialPtr =  MaterialManager::getSingletonPtr()->getByName(material);
            assert(! materialPtr.isNull());
            materialPtr.getPointer()->setReceiveShadows(receiveShadows);
            entity->setMaterial(materialPtr); 
        }
        
        log("Attaching entity " + entity->getName() + " on geometry " + geometry->getName());  
        geometry->addEntity(entity, position, orientation, scale);
    }
    catch(Exception &e)
    {
        log("[DotScene] Error loading an entity! -> " + e.getFullDescription());
        assert(false);        
    }

    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<Entity>(elem, entity, ENTITY);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<Entity>(elem, entity, ENTITY);
        elem = elem->NextSiblingElement("userDataReference");
    }  
}
//----------------------------------------------------------------------------
void DotScene::processEntity(TiXmlElement* node, StaticGeometry* geometry)
{
    TRACE_FUNC();
    assert(geometry);
    
    // Process attributes
    String id = getAttrib(node, "id");
    String name = mPrefix + getAttrib(node, "name");
    id = (StringUtil::BLANK == id)? name: id;
    
    String mesh = getAttrib(node, "meshFile");
    String material = getAttrib(node, "materialFile");
    if (StringUtil::BLANK == material)
        material = getAttrib(node, "material");
    
    bool isStatic = getAttribBool(node, "static", false);
    bool castShadows = getAttribBool(node, "castShadows", true);
    bool receiveShadows = getAttribBool(node, "receiveShadows", true);

    int queryFlags =  getAttribInt(node, "queryFlags", 0);
    int visibilityFlags = getAttribInt(node, "visibilityFlags", 0);
    bool visible = getAttribBool(node, "visible", true);
    
    String renderQueue = getAttrib(node, "renderQueue");
    float renderingDistance = getAttribReal(node, "renderingDistance"); 
    
    Vector3 position = Vector3::ZERO;
    Quaternion orientation = Quaternion::IDENTITY;
    Vector3 scale = Vector3::UNIT_SCALE;
    
    assert(StringUtil::BLANK != mesh);

    TiXmlElement* elem = 0;

    // Process position (?)
    elem = node->FirstChildElement("position");
    if (elem)
        position = parseVector3(elem);

    // Process rotation (?)
    elem = node->FirstChildElement("rotation");
    if (elem)
        orientation = parseQuaternion(elem);
    
    // Process rotation alternative (?)
    elem = node->FirstChildElement("quaternion");
    if (elem)
        orientation = parseQuaternion(elem);

    // Process scale (?)
    elem = node->FirstChildElement("scale");
    if (elem)
        scale = parseVector3(elem);
    
    // Create the entity
    Entity *entity = 0;
    try
    {
        unsigned short src, dest;
        
        MeshPtr meshPtr = MeshManager::getSingleton().load(mesh, mGroup);
        if (!meshPtr->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
        {
            meshPtr->buildTangentVectors(VES_TANGENT, src, dest);
        }

        entity = (mSceneMgr->hasEntity(name))? 
                  mSceneMgr->getEntity(name):
                  mSceneMgr->createEntity(name, mesh);                  
        // Maintain a list of static and dynamic objects
        if(isStatic)
            mStaticEntities.push_back(name);
        else
            mDynamicEntities.push_back(name);
        
        entity->setCastShadows(castShadows);
        
        // 
        entity->setVisible(visible);
        if (visibilityFlags) 
            entity->setVisibilityFlags(visibilityFlags);
        if (queryFlags) 
            entity->setVisibilityFlags(queryFlags);
        if (renderingDistance > 0)
            entity->setRenderingDistance(renderingDistance);
        if (StringUtil::BLANK != renderQueue)
            entity->setRenderQueueGroup(parseRenderQueue(renderQueue));
        //
        
        if (StringUtil::BLANK != renderQueue)
            entity->setRenderQueueGroup(parseRenderQueue(renderQueue));
        
        if  (castShadows && meshPtr->isEdgeListBuilt())
            meshPtr->buildEdgeList();

        // Process vertexBuffer (?)
        elem = node->FirstChildElement("vertexBuffer");
        if (elem)
        {
            HardwareVertexBuffer::Usage usage = HardwareVertexBuffer::HBU_STATIC;
            bool useShadowBuffer = false;

            processVertexBuffer(elem, &usage, &useShadowBuffer);
            entity->getMesh().getPointer()->setVertexBufferPolicy(usage, useShadowBuffer);
        }

        // Process indexBuffer (?)
        elem = node->FirstChildElement("indexBuffer");
        if (elem)
        {
            HardwareIndexBuffer::Usage usage = HardwareIndexBuffer::HBU_STATIC;
            bool useShadowBuffer = false;

            processIndexBuffer(elem, &usage, &useShadowBuffer);
            entity->getMesh().getPointer()->setIndexBufferPolicy(usage, useShadowBuffer);
        }        
        
        // Process subentities (?)
        elem = node->FirstChildElement("subentities");
        if (elem)
        {
            elem = elem->FirstChildElement("subentity");
            while (elem)
            {
                processSubEntity(elem, entity);
                elem = elem->NextSiblingElement();
            }
        }
        
        if (StringUtil::BLANK != material)
        {
            MaterialPtr materialPtr =  MaterialManager::getSingletonPtr()->getByName(material);
            assert(! materialPtr.isNull());
            materialPtr.getPointer()->setReceiveShadows(receiveShadows);
            entity->setMaterial(materialPtr); 
        }
        
        log("Attaching entity " + entity->getName() + " on geometry " + geometry->getName());  
        geometry->addEntity(entity, position, orientation, scale);
    }
    catch(Exception &e)
    {
        log("[DotScene] Error loading an entity! -> " + e.getFullDescription());
        assert(false);        
    }

    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<Entity>(elem, entity, ENTITY);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<Entity>(elem, entity, ENTITY);
        elem = elem->NextSiblingElement("userDataReference");
    }  
}
//----------------------------------------------------------------------------
void DotScene::processSubEntity(TiXmlElement* node, Entity* entity)
{
    assert(entity);
    TRACE_FUNC();
    
    int idx = StringConverter::parseInt(getAttrib(node, "index","0"));
    String material = getAttrib(node, "materialName");
    if (StringUtil::BLANK == material)
        material = getAttrib(node, "materialFile");
    if (StringUtil::BLANK == material)
        material = getAttrib(node, "material");
    
    MaterialPtr materialPtr =  MaterialManager::getSingletonPtr()->getByName(material);
    assert(! materialPtr.isNull());
    entity->getSubEntity(idx)->setMaterial(materialPtr);
}
//----------------------------------------------------------------------------
void DotScene::processParticleSystem(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    
    // Process attributes
    String id = getAttrib(node, "id");
    String name = mPrefix + getAttrib(node, "name");
    id = (StringUtil::BLANK == id)? name: id;
    
    bool receiveShadows = getAttribBool(node,"receiveShadows",true);
    
    String file = getAttrib(node, "file");

    int queryFlags =  getAttribInt(node, "queryFlags", 0);
    int visibilityFlags = getAttribInt(node, "visibilityFlags", 0);
    bool visible = getAttribBool(node, "visible", true);
    
    String renderQueue = getAttrib(node, "renderQueue");
    Real renderingDistance = getAttribReal(node, "renderingDistance", 0.0f);
    
    // Create the particle system
    ParticleSystem* particlessystem = 0;
    try
    {
        ParticleSystem* particlessystem = (mSceneMgr->hasParticleSystem(name))? 
                                                 mSceneMgr->getParticleSystem(name) 
                                                :mSceneMgr->createParticleSystem(name, file);
        mParticleSystem.push_back(name);
        
        //Set particlessystem settings
        particlessystem->setVisible(visible);
        
        if (visibilityFlags) 
            particlessystem->setVisibilityFlags(visibilityFlags);
        if (queryFlags) 
            particlessystem->setQueryFlags(queryFlags);
        
        String materialName = particlessystem->getMaterialName();
        MaterialPtr materialPtr =  MaterialManager::getSingletonPtr()->getByName(materialName);
        materialPtr.getPointer()->setReceiveShadows(receiveShadows);
        
        parent->attachObject(particlessystem);
    }
    catch(Exception &e)
    {
        log("[DotScene] Error creating a particle system! -> " + e.getFullDescription());
        assert(false);
    }
    
    TiXmlElement* elem = 0;
    
    // Process noteTracks (?)
//     elem = node->FirstChildElement("noteTracks");
//     if (elem)
//         processNoteTrack(elem);
    
     // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<ParticleSystem>(elem, particlessystem, PARTICLE_SYSTEM);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<ParticleSystem>(elem, particlessystem, PARTICLE_SYSTEM);
        elem = elem->NextSiblingElement("userDataReference");
    }  
}
//----------------------------------------------------------------------------
void DotScene::processBillboardSet(TiXmlElement* node, SceneNode* parent)
{
    assert(false);
    TRACE_FUNC();
    
    String id = getAttrib(node, "id");
    String name = mPrefix + getAttrib(node, "name");
    id = (StringUtil::BLANK == id)? name: id;
    
    BillboardType billboardtype = BBT_POINT; 
    String type = getAttrib(node, "type");
    if ("a" == type)
        billboardtype = BBT_POINT;
    else if ("b" == type)
        billboardtype = BBT_ORIENTED_COMMON;
    else if ("c" == type)
        billboardtype = BBT_ORIENTED_SELF;
    else if ("d" == type)
        billboardtype = BBT_PERPENDICULAR_COMMON;
    else if ("e" == type)
        billboardtype = BBT_PERPENDICULAR_SELF;
    
    BillboardOrigin billboardOrigin = BBO_CENTER;
    String origin = getAttrib(node, "origin");
    if ("a" == type)
        billboardOrigin = BBO_TOP_LEFT;
    else if ("b" == type)
        billboardOrigin = BBO_TOP_CENTER;
    else if ("c" == type)
        billboardOrigin = BBO_TOP_RIGHT;
    else if ("d" == type)
        billboardOrigin = BBO_CENTER_LEFT;
    else if ("w" == type)
        billboardOrigin = BBO_CENTER;
    else if ("f" == type)
        billboardOrigin = BBO_CENTER_RIGHT;
    else if ("g" == type)
        billboardOrigin = BBO_BOTTOM_LEFT;
    else if ("h" == type)
        billboardOrigin = BBO_BOTTOM_CENTER;
    else if ("i" == type)
        billboardOrigin = BBO_BOTTOM_RIGHT;
    
    String material = getAttrib(node, "material");
    
    Real width = getAttribReal(node, "width", 10);
    Real height = getAttribReal(node, "height", 10);
    
    assert(StringUtil::BLANK!=material);
    assert(0.01 < width);
    assert(0.01 < height);
    
    int queryFlags =  getAttribInt(node, "queryFlags", 0);
    int visibilityFlags = getAttribInt(node, "visibilityFlags", 0);
    bool visible = getAttribBool(node, "visible", true);
    
    String renderQueue = getAttrib(node, "renderQueue");
    Real renderingDistance = getAttribReal(node, "renderingDistance", 0.0f);
    
    BillboardRotationType rotationType = BBR_VERTEX;
    String _rotationType= getAttrib(node, "rotationType", "vertex");
    StringUtil::toLowerCase(_rotationType);
    if (_rotationType == "vertex")
        rotationType = BBR_VERTEX;
    else if (_rotationType == "texcoord")
        rotationType = BBR_TEXCOORD;

    int poolSize = getAttribInt(node, "poolSize", 20);
    bool autoExtendPool = getAttribBool(node, "autoExtendPool", false);
    bool cullIndividual = getAttribBool(node, "cullIndividual", false);
    bool sort = getAttribBool(node, "sort", false);
    bool accurateFacing = getAttribBool(node, "accurateFacing", false);
    
    bool receiveShadows = getAttribBool(node, "receiveShadows", false);
    
    //register
    BillboardSet* billboardSet = (mSceneMgr->hasBillboardSet(name))? 
                                        mSceneMgr->getBillboardSet(name) :
                                        mSceneMgr->createBillboardSet(name);
    mBillboardSets.push_back(name);
    
    //set billboardset settings
    billboardSet->setBillboardType(billboardtype);
    billboardSet->setBillboardOrigin(billboardOrigin);
    billboardSet->setBillboardRotationType(rotationType);
    billboardSet->setMaterialName(material);
    billboardSet->setDefaultHeight(height);
    billboardSet->setDefaultWidth(width);
    billboardSet->setVisible(visible);
    billboardSet->setDefaultWidth(width);
    billboardSet->setDefaultHeight(height);
    billboardSet->setAutoextend(autoExtendPool);
    billboardSet->setCullIndividually(cullIndividual);
    billboardSet->setSortingEnabled(sort);
    billboardSet->setUseAccurateFacing(accurateFacing);
    
    if (StringUtil::BLANK != material)
    {
        billboardSet->setMaterialName(material);
    }
    
    if (poolSize > 0)
        billboardSet->setPoolSize(poolSize);
    
    // 
    if (visibilityFlags) 
        billboardSet->setVisibilityFlags(visibilityFlags);
    if (queryFlags) 
        billboardSet->setVisibilityFlags(queryFlags);
    if (renderingDistance > 0)
        billboardSet->setRenderingDistance(renderingDistance);
    if (StringUtil::BLANK != renderQueue)
        billboardSet->setRenderQueueGroup(parseRenderQueue(renderQueue));
    //
    
    TiXmlElement* elem = 0;
    
    elem = node->FirstChildElement("billboard");
    while(elem)
    {
        assert(false);
        
        Real width = getAttribReal(elem, "width", 0.0f);
        Real height = getAttribReal(elem, "height", 0.0f);
        
        //TODO revisar si precisamos de autodetect units.
        Radian rotationAngle = Radian(getAttribReal(node, "rotation", 0.0f));
        
        Vector3 position = Vector3::ZERO;
        Quaternion rotation = Quaternion::IDENTITY;
        ColourValue colorDiffuse = ColourValue::White;
        FloatRect floatRect;
        
        TiXmlElement* child = 0;
        
        child = node->FirstChildElement("position");
        if (child)
            position = parseVector3(child);
        
        child = node->FirstChildElement("rotation");
        if (child)
            rotation = parseQuaternion(child);
        
        child = node->FirstChildElement("colourDiffuse");
        if (child)
            colorDiffuse = parseColour(child);
        
        child = node->FirstChildElement("texCoordRectangle");
        if (child)
            floatRect = parseFloatRectangle(child);
        
        elem = elem->NextSiblingElement("node");
    }
    
    // Process noteTracks (?)
//     elem = node->FirstChildElement("noteTracks");
//     if (elem)
//         processNoteTrack(elem);
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<BillboardSet>(elem, billboardSet, BILLBOARD_SET);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<BillboardSet>(elem, billboardSet, BILLBOARD_SET);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processPlane(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    
    String name = getAttrib(node, "name");
    String id = getAttrib(node, "name");
    id = (StringUtil::BLANK == id)? name: id;
    
    Real distance = getAttribReal(node, "distance", 500);
    Real width = getAttribReal(node, "width", 1500);
    Real height = getAttribReal(node, "height", 1500);
    Integer xSegments = getAttribInt(node, "xSegments", 1);
    Integer ySegments = getAttribInt(node, "ySegments", 1);
    Integer numTexCoordSets = getAttribInt(node, "numTexCoordSets", 1);
    Integer uTile = getAttribInt(node, "uTile", 1);
    Integer vTile = getAttribInt(node, "vTile", 1);
    String material = getAttrib(node, "material"); 
    
    bool buildNormals = getAttribBool(node, "normals", true);
    bool castShadows = getAttribBool(node,"castShadows",true);
    bool receiveShadows = getAttribBool(node, "receiveShadows", false);
    bool createMovablePlane = getAttribBool(node, "movablePlane", false);
    
    int queryFlags =  getAttribInt(node, "queryFlags", 0);
    int visibilityFlags = getAttribInt(node, "visibilityFlags", 0);
    bool visible = getAttribBool(node, "visible", true);
    
    String renderQueue = getAttrib(node, "renderQueue");
    Real renderingDistance = getAttribReal(node, "renderingDistance", 0.0f);

    TiXmlElement* elem = 0;
    
    Vector3 up = Vector3::UNIT_Z;
    elem = node->FirstChildElement("upVector");
    if (elem)
        up = parseVector3(elem);
    
    // Process direction (?)
    Vector3 normal = Vector3::UNIT_Y;
    elem = node->FirstChildElement("normal");
    if (elem)
        normal = parseVector3(elem);
    
    MeshPtr planePtr = MeshManager::getSingletonPtr()->getByName(name);
    if (planePtr.isNull())
    {
        MeshPtr planePtr = MeshManager::getSingletonPtr()->createPlane(
            name, mGroup,
            Plane(normal, -1), width, height, 
            xSegments, ySegments, buildNormals, 
            numTexCoordSets, uTile, vTile, up);
        mMeshes.push_back(name);
        
        // Process vertexBuffer (?)
        elem = node->FirstChildElement("vertexBuffer");
        if (elem)
        {
            HardwareVertexBuffer::Usage usage = HardwareVertexBuffer::HBU_STATIC;
            bool useShadowBuffer = false;

            processVertexBuffer(elem, &usage, &useShadowBuffer);
            planePtr.getPointer()->setVertexBufferPolicy(usage, useShadowBuffer);
        }

        // Process indexBuffer (?)
        elem = node->FirstChildElement("indexBuffer");
        if (elem)
        {
            HardwareIndexBuffer::Usage usage = HardwareIndexBuffer::HBU_STATIC;
            bool useShadowBuffer = false;

            processIndexBuffer(elem, &usage, &useShadowBuffer);;
            planePtr.getPointer()->setIndexBufferPolicy(usage, useShadowBuffer);
        }
        
        // Add a floor to our scene using the GPCupidGymGroundMesh mesh we created
        Entity* entity = mSceneMgr->createEntity(name + "Entity", name);
        mStaticEntities.push_back(entity->getName());
        entity->setCastShadows(false);
        entity->setVisible(visible);
        
        if (visibilityFlags) 
            entity->setVisibilityFlags(visibilityFlags);
        if (queryFlags) 
            entity->setVisibilityFlags(queryFlags);
        if (renderingDistance > 0)
            entity->setRenderingDistance(renderingDistance);
        if (StringUtil::BLANK != renderQueue)
            entity->setRenderQueueGroup(parseRenderQueue(renderQueue));
        
        if (StringUtil::BLANK != material)
        {
            MaterialPtr materialPtr =  MaterialManager::getSingletonPtr()->getByName(material);
            assert(! materialPtr.isNull());
            materialPtr.getPointer()->setReceiveShadows(receiveShadows);
            entity->setMaterial(materialPtr); 
        }
        
        SceneNode* planeNode = mSceneMgr->createSceneNode(name + "Node");
        mSceneNodes.push_back(planeNode->getName());
        
        planeNode->attachObject(entity);
        parent->addChild(planeNode);
        
        if (createMovablePlane)
        {
            MovablePlane* movablePlane = new MovablePlane(name + "MovablePlane");
            movablePlane->normal = normal;
            movablePlane->d = distance;
            parent->attachObject(movablePlane);
        }
    } 
    else
    {
        Entity* planeEntity = mSceneMgr->getEntity(name + "Entity");
        if (StringUtil::BLANK != material)
        {
            MaterialPtr materialPtr =  MaterialManager::getSingletonPtr()->getByName(material);
            assert(! materialPtr.isNull());
            materialPtr.getPointer()->setReceiveShadows(receiveShadows);
            planeEntity->setMaterial(materialPtr); 
        }
    }
    
    // Process noteTracks (?)
//     elem = node->FirstChildElement("noteTracks");
//     if (elem)
//         processNoteTrack(elem);
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<Mesh>(elem, planePtr.getPointer(), MESH);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<Mesh>(elem, planePtr.getPointer(), MESH);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processFog(TiXmlElement* node)
{
    assert(false);
    TRACE_FUNC();
   
    // Process attributes
    Real density = getAttribReal(node, "expDensity", 0.001);
    Real start = getAttribReal(node, "linearStart", 0.0);
    Real end = getAttribReal(node, "linearEnd", 1.0);

    ColourValue colour = ColourValue::White;
    FogMode mode = FOG_NONE;
    
    String type = getAttrib(node, "mode");
    if  (type == "none")
        mode = FOG_NONE;
    else if(type == "exp")
        mode = FOG_EXP;
    else if(type == "exp2")
        mode = FOG_EXP2;
    else if(type == "linear")
        mode = FOG_LINEAR;

    TiXmlElement* elem = 0;

    // Process colourDiffuse (?)
    elem = node->FirstChildElement("colourDiffuse");  
    if (elem)
        colour = parseColour(elem);

    // Setup the fog
    mSceneMgr->setFog(mode, colour, density, start, end);
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<DotScene>(elem, this, SCENE);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<DotScene>(elem, this, SCENE);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processSkyBox(TiXmlElement* node)
{
    TRACE_FUNC();
   
    // Process attributes
    String material = getAttrib(node, "material");
    Real distance = getAttribReal(node, "distance", 5000);
    bool drawFirst = getAttribBool(node, "drawFirst", true);
    bool enabled = getAttribBool(node, "enable", true);
    
    TiXmlElement* elem = 0;

    
    Quaternion rotation = Quaternion::IDENTITY;
    
    // Process rotation (?)
    elem = node->FirstChildElement("rotation");
    if (elem)
        rotation = parseQuaternion(elem);
    // Process rotation alternative(?)
    elem = node->FirstChildElement("quaternion");
    if (elem)
        rotation = parseQuaternion(elem);
    
    elem = node->FirstChildElement("animations");
    // Process animations (?)
    if (elem)
        assert(false); //TODO

    // Setup the sky box
    mSceneMgr->setSkyBox(enabled, material, distance, drawFirst, rotation, mGroup);
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<DotScene>(elem, this, SKY_BOX);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<DotScene>(elem, this, SKY_BOX);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processSkyDome(TiXmlElement* node)
{
    TRACE_FUNC();
    
    // Process attributes
    String material = node->Attribute("material");
    Real curvature = getAttribReal(node, "curvature", 10);
    Real tiling = getAttribReal(node, "tiling", 8);
    Real distance = getAttribReal(node, "distance", 4000);
    Integer xSegments = getAttribInt(node, "xSegments", 16);
    Integer ySegments = getAttribInt(node, "ySegments", 16);
    bool drawFirst = getAttribBool(node, "drawFirst", true);
    bool enabled = getAttribBool(node, "enable", true);

    TiXmlElement* elem = 0;
    
    Quaternion rotation = Quaternion::IDENTITY;
    
    elem = node->FirstChildElement("rotation");
    // Process rotation (?)
    if (elem)
        rotation = parseQuaternion(elem);
    // Process rotation alternative(?)
    elem = node->FirstChildElement("quaternion");
    // Process rotation (?)
    if (elem)
        rotation = parseQuaternion(elem);

    elem = node->FirstChildElement("animations");
    // Process animations (?)
    if (elem)
        assert(false); //TODO
        
    // Setup the sky dome
    mSceneMgr->setSkyDome(enabled, material, curvature, tiling, distance, drawFirst, rotation, xSegments, ySegments, -1, mGroup);
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<DotScene>(elem, this, SKY_DOME);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<DotScene>(elem, this, SKY_DOME);
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//----------------------------------------------------------------------------
void DotScene::processSkyPlane(TiXmlElement* node)
{
    TRACE_FUNC();

    // Process attributes
    String material = getAttrib(node, "material");
    Real planeX = getAttribReal(node, "planeX", 0);
    Real planeY = getAttribReal(node, "planeY", -1);
    Real planeZ = getAttribReal(node, "planeX", 0);
    Real planeD = getAttribReal(node, "planeD", 5000);
    Real scale = getAttribReal(node, "scale", 1000);
    Real bow = getAttribReal(node, "bow", 0);
    Real tiling = getAttribReal(node, "tiling", 10);
    Integer xSegments = getAttribInt(node, "xSegments", 1);
    Integer ySegments = getAttribInt(node, "ySegments", 1);
    bool drawFirst = getAttribBool(node, "drawFirst", true);
    bool enabled = getAttribBool(node, "enable", true);

    TiXmlElement* elem = 0;
    elem = node->FirstChildElement("animations");
    // Process animations (?)
    if (elem)
        assert(false); //TODO
        
    // Setup the sky plane
    Plane plane;
    plane.normal = Vector3(planeX, planeY, planeZ);
    plane.d = planeD;
    mSceneMgr->setSkyPlane(enabled, plane, material, scale, tiling, drawFirst, bow, xSegments, ySegments, mGroup);
   
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<DotScene>(elem, this, SKY_PLANE);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<DotScene>(elem, this, SKY_PLANE);
        elem = elem->NextSiblingElement("userDataReference");
    }

}
//----------------------------------------------------------------------------
void DotScene::processClipping(TiXmlElement* node, ClippingPlanesType* clippingPlanes)
{
    assert(clippingPlanes);
    TRACE_FUNC();
    
    RenderSystem* rendersystem = Root::getSingletonPtr()->getRenderSystem();
    Real defaultFarDistance = (rendersystem->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))? 
                                     0: FAR_CLIP_DISTANCE;
     
    clippingPlanes->mNear = getAttribReal(node, "near", NEAR_CLIP_DISTANCE);
    clippingPlanes->mFar = getAttribReal(node, "far", defaultFarDistance);
    
    if ((! rendersystem->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE)) &&
        (clippingPlanes->mFar <= clippingPlanes->mNear))
        assert(false);
        
}
//----------------------------------------------------------------------------
void DotScene::processLightRange(TiXmlElement* node, Light *pLight)
{
    TRACE_FUNC();
    
    // Process attributes
    Real inner = getAttribReal(node, "inner");
    Real outer = getAttribReal(node, "outer");
    Real falloff = getAttribReal(node, "falloff", 1.0);

    // Setup the light range
    pLight->setSpotlightRange(Angle(inner), Angle(outer), falloff);
}
//----------------------------------------------------------------------------
void DotScene::processLightAttenuation(TiXmlElement* node, Light *pLight)
{
    TRACE_FUNC();
    
    // Process attributes
    Real range = getAttribReal(node, "range");
    Real constant = getAttribReal(node, "constant");
    Real linear = getAttribReal(node, "linear");
    Real quadratic = getAttribReal(node, "quadratic");

    // Setup the light attenuation
    pLight->setAttenuation(range, constant, linear, quadratic);
}
//---------------------------------------------------------------------------
void DotScene::processShadow(TiXmlElement* node)
{
    TRACE_FUNC();
        
    String technique = getAttrib(node, "technique", "textureModulative");
    bool self = getAttribBool(node, "selfShadow", false);
    int distance = getAttribInt(node, "farDistance", 0);
    
    if (technique == "detailAdditive")
        mSceneMgr->setShadowTechnique(SHADOWDETAILTYPE_ADDITIVE);
    else if (technique == "detailModulative")
        mSceneMgr->setShadowTechnique(SHADOWDETAILTYPE_MODULATIVE);
    else if (technique == "detailIntegrated")
        mSceneMgr->setShadowTechnique(SHADOWDETAILTYPE_INTEGRATED);
    else if (technique == "detailStencil")
        mSceneMgr->setShadowTechnique(SHADOWDETAILTYPE_STENCIL);
    else if (technique == "detailTexture")
        mSceneMgr->setShadowTechnique(SHADOWDETAILTYPE_TEXTURE);
    else if (technique == "stencilModulative")
        mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
    else if (technique == "stencilModulative")
        mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
    else if (technique == "textureModulative")
        mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);
    else if (technique == "textureAdditive")
        mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE);
    else if (technique == "textureAdditiveIntegrated")
        mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);
    else if (technique == "textureModulativeIntegrated")
        mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);
    else 
    {
        mSceneMgr->setShadowTechnique(SHADOWTYPE_NONE);
        log("No shadow technique selected");
        return;
    }
    
    mSceneMgr->setShadowTextureSelfShadow(self);
    mSceneMgr->setShadowColour(ColourValue::Black);
    
    if (distance) 
        mSceneMgr->setShadowFarDistance(distance);
    
    TiXmlElement* elem = 0;
    
    // get shadow color
    elem = node->FirstChildElement("colourShadow");
    if (elem)
    {
        ColourValue color = parseColour(elem);
        mSceneMgr->setShadowColour(color);
    }
    
    // get shadow projection settings
    elem = node->FirstChildElement("shadowCameraSetup");
    if (elem)
    {
        processShadowCameraSetup(elem);
    }
        
    // get parameters in mode shadow textures
    elem = node->FirstChildElement("shadowTextures");
    if (elem) 
    {
        bool depth = getAttribBool(elem, "useDepthTexture", false); 
        int size = getAttribInt(elem,"size",512); 
        int count =getAttribInt(elem,"count",1);
        float offset = getAttribReal(elem,"offset", 0.6f);
        float start = getAttribReal(elem,"fadeStart", 0.7f);
        float end = getAttribReal(elem,"fadeEnd", 0.9f);
        String casterMaterial = getAttrib(elem,"shadowCasterMaterial");
        String receiverMaterial = getAttrib(elem,"shadowReceiverMaterial");
       
        if (mSceneMgr->isShadowTechniqueTextureBased())
        {
            //Render support to render to texture by hardware?
            RenderSystem* render = Root::getSingletonPtr()->getRenderSystem();
            const RenderSystemCapabilities* capabilities =  render->getCapabilities();
            
            if (! capabilities->hasCapability(RSC_HWRENDER_TO_TEXTURE))
            {
                //Render works with non-power of two textures?
                if (! capabilities->hasCapability(RSC_NON_POWER_OF_2_TEXTURES))
                {
                    if (! isPowerOfTwo(size))
                        size = nextSmallestPowerOfTwo(size);    
                }
            }
            
            //Set shadow texture settings
            mSceneMgr->setShadowTexturePixelFormat(PF_FLOAT16_R);
            mSceneMgr->setShadowTextureSize(size);
            mSceneMgr->setShadowTextureCount(count);
            mSceneMgr->setShadowDirLightTextureOffset(offset);
            mSceneMgr->setShadowTextureFadeStart(start);
            mSceneMgr->setShadowTextureFadeEnd(end);
            
            if (StringUtil::BLANK != casterMaterial) 
                mSceneMgr->setShadowTextureCasterMaterial(casterMaterial);
            if (StringUtil::BLANK != receiverMaterial) 
                mSceneMgr->setShadowTextureReceiverMaterial(receiverMaterial);
            
        }
    }
}
//----------------------------------------------------------------------------
void DotScene::processShadowCameraSetup(TiXmlElement* node)
{
    TRACE_FUNC();
    //assert(false);
    
    ShadowCameraSetupPtr ptr;
    ShadowCameraSetup* setup = 0;
    
    String _setup = getAttrib(node, "type", "lispsm");
    
    if (_setup == "uniform")
    {
        setup = new DefaultShadowCameraSetup();
    }
    else if (_setup == "uniformfocused")
    {
        FocusedShadowCameraSetup* setup = new FocusedShadowCameraSetup();
        setup->setUseAggressiveFocusRegion(getAttribBool(node, "useAggressiveFocusRegion", true));
    }
    else if (_setup == "lispsm")
    {
        LiSPSMShadowCameraSetup* setup = new LiSPSMShadowCameraSetup;
        setup->setUseAggressiveFocusRegion(getAttribBool(node, "useAggressiveFocusRegion", true));
        setup->setUseSimpleOptimalAdjust(getAttribBool(node, "useSimpleOptimalAdjust", true));
        
        float optimalAdjustFactor = 0;
        if (! setup->getUseSimpleOptimalAdjust())
            optimalAdjustFactor = getAttribReal(node, "optimalAdjustFactor", 0.1f);
        setup->setOptimalAdjustFactor(optimalAdjustFactor);
        
        setup->setCameraLightDirectionThreshold(Radian(getAttribReal(node, "lightDirectionThreshold",0.45102624)));
    }
    else if (_setup == "pssm")
    {
        PSSMShadowCameraSetup* setup = new PSSMShadowCameraSetup;
        setup->setUseAggressiveFocusRegion(getAttribBool(node, "useAggressiveFocusRegion", true));
        setup->calculateSplitPoints(
            getAttribInt(node, "splitCount", 3),
            getAttribReal(node, "splitNearDistance", 100.0f),
            getAttribReal(node, "splitFarDistance", 100000.0f),
            getAttribReal(node, "splitReduction", 0.95f));
        
        setup->setSplitPadding(getAttribReal(node, "splitPadding", 1.0));
    }
    else if (_setup == "planeoptimal")
    {
        //The plane optimal setup requires a plane.
        MovablePlane* plane = new MovablePlane("_shadowOptimalPlane");

        Vector3  up = getUpVector();
        plane->normal.x = getAttribReal(node, "planeX", up.x);
        plane->normal.y = getAttribReal(node, "planeY", up.y);
        plane->normal.z = getAttribReal(node, "planeZ", up.z);
        plane->d = getAttribReal(node, "planeD");
        
        setup = new PlaneOptimalShadowCameraSetup(plane);
    }
    else
    {
        log("Error: Invalid shadow camera setup");
        assert(false);
    }
    
    ptr = ShadowCameraSetupPtr(setup);
    mSceneMgr->setShadowCameraSetup(ptr);
}
//---------------------------------------------------------------------------
void DotScene::processRenderTextures(TiXmlElement* node)
{
    TRACE_FUNC();
    assert(false);
    
    Root* root = Root::getSingletonPtr();
    
    //Get default pixel format
    unsigned int colorDepth = root->getAutoCreatedWindow()->getColourDepth();
    PixelFormat pixelFormat = (colorDepth == 16) ? PF_A4R4G4B4 : PF_A8R8G8B8;

    //Read all the render textures
    TiXmlElement* elem = 0;
    
    elem = node->FirstChildElement("renderTexture");
    while(elem)
    {
        String name = getAttrib(elem, "name");
        int width = getAttribInt(elem, "width", 512);
        int height = getAttribInt(elem, "height", 512);
        
        String _pixelFormat = getAttrib(elem, "pixelFormat");
        if (StringUtil::BLANK != _pixelFormat)
            pixelFormat = parsePixelFormat(_pixelFormat);
        
        String _textureType = getAttrib(elem,"textureType");
        TextureType textureType = parseTextureType(_textureType);
        
        String camera = getAttrib(elem, "camera");
        String scheme = getAttrib(elem, "scheme");
        bool clearOnEveryFrame = getAttribBool(elem, "clearEveryFrame");
        bool autoUpdate = getAttribBool(elem, "autoUpdate");
        bool hideRenderObject = getAttribBool(elem, "hideRenderObject");
        String renderObject = getAttrib(elem, "renderObjectName");
        
        //
        TiXmlElement* child = 0;
        
        child = elem->FirstChildElement("materials");
        if (child)
        {
            TiXmlElement* childOfChild = elem->FirstChildElement("material");
            while(childOfChild)
            {
                childOfChild = childOfChild->NextSiblingElement();
            }
        }
        
        child = elem->FirstChildElement("hiddenObjects");
        if (child)
        {
            TiXmlElement* childOfChild = elem->FirstChildElement("hiddenObject");
            while(childOfChild)
            {
                childOfChild = childOfChild->NextSiblingElement();
            }
        }
        
        child = elem->FirstChildElement("exclusiveObjects");
        if (child)
        {
            TiXmlElement* childOfChild = elem->FirstChildElement("exclusiveObject");
            while(childOfChild)
            {
                childOfChild = childOfChild->NextSiblingElement();
            }
        }
        
        Plane plane;
        child = elem->FirstChildElement("renderPlane");
        if (child)
        {
            plane = parsePlane(child);
        }
        
        //
        ResourceGroupManager* resman = ResourceGroupManager::getSingletonPtr();
        
        TexturePtr ptr = TextureManager::getSingletonPtr()->createManual(
            name, mGroup, textureType, width, height, 0, pixelFormat, TU_RENDERTARGET);
        mRenderTextures.push_back(name);
        
        for(int i =0; i<ptr.getPointer()->getNumFaces(); i++)
        {
            HardwarePixelBufferSharedPtr buffer = ptr.getPointer()->getBuffer(i);
            RenderTexture* rt = buffer.getPointer()->getRenderTarget();
            rt->setAutoUpdated(autoUpdate);
        }
        //
        elem = elem->NextSiblingElement();
    }
}
//---------------------------------------------------------------------------
void DotScene::processInstancedGeometries(TiXmlElement* node)
{
    TRACE_FUNC();
    assert(false);
    
    //Ensure instancing is supported
    Root* root = Root::getSingletonPtr();
    bool supported = root->getRenderSystem()->getCapabilities()->hasCapability(RSC_VERTEX_PROGRAM);
    assert(supported);

    //Read all the instanced geometries
    TiXmlElement* elem = 0;
    elem = node->FirstChildElement("instancedGeometry");
    while(elem)
    {
        
        String name = getAttrib(elem, "name");
        bool castShadows = getAttribBool(elem, "castShadows", true);
        bool visible = getAttribBool(elem, "visible");
        unsigned int batchCount = getAttribInt(elem, "batchCount", 0);
        
        String queue = getAttrib(elem, "renderQueue");
        Real distance = getAttribReal(elem, "renderingDistance", 0);
    
        
        TiXmlElement* child = 0; 
        
        Vector3 origin = Vector3::ZERO;
        child = elem->FirstChildElement("origin");
        if (child)
            origin = parseVector3(child);
        
        
        Vector3 dimension = Vector3(1000000, 1000000, 1000000);
        child = elem->FirstChildElement("dimensions");
        if (child)
            dimension = parseVector3(child);
        
        InstancedGeometry* geometry = mSceneMgr->createInstancedGeometry(name);
        geometry->setCastShadows(castShadows);
        geometry->setVisible(visible);
        geometry->setOrigin(origin);
        geometry->setBatchInstanceDimensions(dimension);
        
        if (StringUtil::BLANK != queue)
            geometry->setRenderQueueGroup(parseRenderQueue(queue));
        geometry->setRenderingDistance(distance);

        //Add the entities
        child = elem->FirstChildElement("entities");
        if (child)
        {
            child = child->FirstChildElement("entity");    
            while (child)
            {
                processEntity(child, geometry);
                child =  child->NextSiblingElement();
            }
        }
        
        //Build the instanced geometry
        geometry->build();
    }
}
//---------------------------------------------------------------------------
void DotScene::processStaticGeometries(TiXmlElement* node)
{
    TRACE_FUNC();
    assert(false);
    
    TiXmlElement* elem = 0;
    
    elem = node->FirstChildElement("staticGeometry");
    while (elem)
    {
        String name = getAttrib(node, "name");
        bool castShadows = getAttribBool(node, "castShadows", true);
        bool visible = getAttribBool(node, "visible", true);
        String queue = getAttrib(node, "renderQueue");
        Real distance = getAttribReal(node, "renderingDistance");
        
        TiXmlElement* child = 0;

        Vector3 origin = Vector3::ZERO;
        child = elem->FirstChildElement("origin");
        if (child)
            origin = parseVector3(child);
        
        Vector3 dimension(1000000, 1000000, 1000000);
        child = elem->FirstChildElement("dimensions");
        if (child)
            dimension = parseVector3(child);
        
        //Create the instanced geometry
        StaticGeometry* geometry = mSceneMgr->createStaticGeometry(name);
        geometry->setCastShadows(castShadows);
        geometry->setVisible(visible);
        geometry->setOrigin(origin);
        geometry->setRegionDimensions(dimension);
        geometry->setRenderingDistance(distance);
        if (StringUtil::BLANK != queue)
            geometry->setRenderQueueGroup(parseRenderQueue(queue));

        child = elem->FirstChildElement("entities");
        if (child)
        {
            child = child->FirstChildElement("entity");    
            while (child)
            {
                processEntity(child, geometry);
                child =  child->NextSiblingElement();
            }
        }
        
        elem = elem->NextSiblingElement();
    }
}
//---------------------------------------------------------------------------
void DotScene::processPortalConnectedZones(TiXmlElement* node)
{
    TRACE_FUNC();
    assert(false);
}
//---------------------------------------------------------------------------
void DotScene::processNoteTrack(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    assert(false);
    assert(node);
    assert(parent);
    
    //<noteTrack name="string"><note time="Real">Text</note></noteTrack>
}
//---------------------------------------------------------------------------
void DotScene::processNoteTrack(TiXmlElement* node, Entity* entity)
{
    TRACE_FUNC();
    assert(false);
    assert(node);
    assert(entity);
    
    //<noteTrack name="string"><note time="Real">Text</note></noteTrack>
}
//---------------------------------------------------------------------------
void DotScene::processCustomParameter(TiXmlElement* node, Entity* entity)
{
    TRACE_FUNC();
    assert(false);
    
    //<customParameter id="name" x="Real", y="Real", z="Real", w="Real"/>
}
//---------------------------------------------------------------------------
void DotScene::processBoneAttachment(TiXmlElement* node, Entity* entity)
{
    TRACE_FUNC();
    assert(false);
    assert(node);
    assert(entity);
    
    String name = getAttrib(node, "name");
    String _bone = getAttrib(node, "bone");
    
    SkeletonInstance* skel = entity->getSkeleton();
    assert(skel);
    
    Bone* bone = skel->getBone(_bone);
    assert(bone);
    
    Vector3 position = Vector3::ZERO;
    Vector3 scale = Vector3(1,1,1);
    Quaternion orientation = Quaternion::IDENTITY;
    
    TiXmlElement* elem = 0;
    
    // Process position (?)
    elem = node->FirstChildElement("position");
    if (elem)
        position = mUnitConversionFactor * parseVector3(elem);

    // Process rotation (?)
    elem = node->FirstChildElement("rotation");
    if (elem)
        orientation = parseQuaternion(elem);
    
    // Process rotation alternative (?)
    elem = node->FirstChildElement("quaternion");
    if (elem)
        orientation = parseQuaternion(elem);
    
    // Process scale (?)
    elem = node->FirstChildElement("scale");
    if (elem)
        scale = parseVector3(elem);
    
    
    //Create scenenode for attached object
    SceneNode* sceneNode = mSceneMgr->createSceneNode(bone->getName() + "_" + name);
    mSceneNodes.push_back(sceneNode->getName());
        
    // Process entity (?)
    elem = node->FirstChildElement("entity");
    while (elem)
    {
        processEntity(elem, sceneNode);
        elem = elem->NextSiblingElement("entity");
    }
    
    // Process light (?)
    elem = node->FirstChildElement("light");
    while (elem)
    {
        processLight(elem, sceneNode);
        elem = elem->NextSiblingElement("light");
    }
    
    // Process camera (?)
    elem = node->FirstChildElement("camera");
    while (elem)
    {
        processCamera(elem, sceneNode);
        elem = elem->NextSiblingElement("camera");
    }
    
    // Process particle (?)
    elem = node->FirstChildElement("particleSystem");
    while (elem)
    {
        processParticleSystem(elem, sceneNode);
        elem = elem->NextSiblingElement("particleSystem");
    }
    
    // Process billboardSet (?)
    elem = node->FirstChildElement("billboardSet");
    while (elem)
    {
        processBillboardSet(elem, sceneNode);
        elem = elem->NextSiblingElement("billboardSet");
    }
    
    // Process plane (?)
    elem = node->FirstChildElement("plane");
    while (elem)
    {
        processPlane(elem, sceneNode);
        elem = elem->NextSiblingElement("plane");
    }
    
    // Process userdata (*)
    elem = node->FirstChildElement("userData");
    while(elem)
    {
        processUserData<Bone>(elem, bone, BONE);
        elem = elem->NextSiblingElement("userData");
    }
    // Process userDataReference (?)
    elem = node->FirstChildElement("userDataReference");
    while (elem)
    {
        processUserDataReference<Bone>(elem, bone, BONE);      
        elem = elem->NextSiblingElement("userDataReference");
    }
}
//---------------------------------------------------------------------------
void DotScene::processVertexBuffer(TiXmlElement* node, HardwareVertexBuffer::Usage* usage, bool* useShadowBuffer)
{
    TRACE_FUNC();
    assert(usage);
    assert(useShadowBuffer);
    
    *useShadowBuffer =  getAttribBool(node,"useShadow");
    
    String _usage = getAttrib(node, "usage");
    if (_usage == "static")
        *usage = HardwareBuffer::HBU_STATIC;
    else if (_usage == "dynamic")
        *usage = HardwareBuffer::HBU_DYNAMIC;
    else if (_usage == "writeonly")
        *usage = HardwareBuffer::HBU_WRITE_ONLY;
    else if (_usage == "staticwriteonly")
        *usage = HardwareBuffer::HBU_STATIC_WRITE_ONLY;
    else if (_usage == "dynamicwriteonly")
        *usage = HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY;
    else
        *usage = HardwareBuffer::HBU_STATIC;
}
//----------------------------------------------------------------------------
void DotScene::processIndexBuffer(TiXmlElement* node, HardwareIndexBuffer::Usage* usage, bool* useShadowBuffer)
{
    TRACE_FUNC();
    assert(usage);
    assert(useShadowBuffer);
    
    *useShadowBuffer =  getAttribBool(node,"useShadow");
    
    String _usage = getAttrib(node, "usage");
    if (_usage == "static")
        *usage = HardwareBuffer::HBU_STATIC;
    else if (_usage == "dynamic")
        *usage = HardwareBuffer::HBU_DYNAMIC;
    else if (_usage == "writeonly")
        *usage = HardwareBuffer::HBU_WRITE_ONLY;
    else if (_usage == "staticwriteonly")
        *usage = HardwareBuffer::HBU_STATIC_WRITE_ONLY;
    else if (_usage == "dynamicwriteonly")
        *usage = HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY;
    else
        *usage = HardwareBuffer::HBU_STATIC;
}
//----------------------------------------------------------------------------
void DotScene::processAnimation(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    assert(false);
    
    String name = getAttrib(node, "name");
    Real length = getAttribReal(node, "length");
    
    String _interpolationMode = getAttrib(node, "interpolationMode");
    Animation::InterpolationMode interpolationMode = Animation::IM_LINEAR;
    if (_interpolationMode == "spline")
        interpolationMode = Animation::IM_SPLINE;
    else if (_interpolationMode == "linear")
        interpolationMode = Animation::IM_LINEAR;
    
    //Rotation interpolation mode
    String _rotationInterpolationMode = getAttrib(node, "rotationInterpolationMode");
    Animation::RotationInterpolationMode rotationInterpolationMode = Animation::RIM_LINEAR;
    if (_interpolationMode == "linear")
        rotationInterpolationMode = Animation::RIM_LINEAR;
    else if (_interpolationMode == "spherical")
        rotationInterpolationMode = Animation::RIM_SPHERICAL;

    bool enable = getAttribBool(node, "enable", true);
    bool looping = getAttribBool(node, "loop", true);

    //Load animation keyframes
    TiXmlElement* elem = 0;
    elem = node->FirstChildElement("keyframe");
    while (elem)
    {
        processAnimationKeyFrame(elem, parent);
        elem = elem->NextSiblingElement();
    }
}
//----------------------------------------------------------------------------
void DotScene::processAnimationKeyFrame(TiXmlElement* node, SceneNode* parent)
{
    TRACE_FUNC();
    assert(false);
    
    //Key time
    Real time = getAttribReal(node, "time");

    Vector3 translation = Vector3::ZERO; 
    Quaternion rotation = Quaternion::IDENTITY;
    Vector3 scale = Vector3::UNIT_SCALE; 
    
    TiXmlElement* child =0, *elem = 0;
    elem = node->FirstChildElement("keyframe");
    while (elem)
    {
        translation = Vector3::ZERO; 
        rotation = Quaternion::IDENTITY;
        scale = Vector3::UNIT_SCALE; 
        
        child = elem->FirstChildElement("translation");  
        if (child)
            translation = parseVector3(child);
        
        child = elem->FirstChildElement("rotation");  
        if (child)
            rotation = parseQuaternion(child);
        
        child = elem->FirstChildElement("scale");  
        if (child)
            scale = parseVector3(child);
        
        elem = elem->FirstChildElement();
    }
}
//----------------------------------------------------------------------------
template <typename T>
void DotScene::processUserData(TiXmlElement* node, T* reference, NodePropertyType type)
{
    TRACE_FUNC();
    assert(node);
    assert(reference);
    
    String name = StringUtil::BLANK;
    String value = StringUtil::BLANK;
    
    TiXmlElement* elem = 0;
    elem = node->FirstChildElement("property");
    
    //Option A: UserData is a property list
    if(elem)
    {
        while(elem)
        {
            name = getAttrib(elem, "name");
            value = getAttrib(elem, "data");
            
            if(StringUtil::BLANK == value) 
                value = name;
            
            addProperty<T>(reference, name, value, type);
            
            elem = elem->NextSiblingElement("property");
        }
    }
    else
    {
        //Option B: UserData == UserDataReference
        name = getAttrib(node, "id", "id");
        value = getAttrib(node, "value");
        
        if(StringUtil::BLANK == value) 
            value = name;

        addProperty<T>(reference, name, value, type);
    }
}
//----------------------------------------------------------------------------
template <typename T>
void DotScene::processUserDataReference(TiXmlElement* node, T* reference, NodePropertyType type)
{
    TRACE_FUNC();
    
    String name = getAttrib(node, "id", "id");
    String value = getAttrib(node, "value");
    if(StringUtil::BLANK == value) 
        value = name;
    
    addProperty<T>(reference, name, value, type);
}
//----------------------------------------------------------------------------
template<typename T>
void DotScene::addProperty(T* reference, const  String& name, const String& value, NodePropertyType type)
{
    printf("Property (%s, %s, %s, %i)\n", reference->getName().c_str(), name.c_str(), value.c_str(), type);
    
    SceneNodeProperty<T>* property = 0;
    
    //special case boolean properties 'isxxx', 'isnotxxx'
    String str = name;
    boost::to_lower(str);
    
    //special case boolean properties 'isxxx', 'isnotxxx'
    if (boost::algorithm::starts_with(str, "isnot"))
    {
        boost::algorithm::replace_first(str, "isnot", StringUtil::BLANK);
        boost::algorithm::to_lower(str);
        property = new SceneNodeProperty<T>(reference, str, "false", type);
        mProperties.push_back(property);
    }
    else if (boost::algorithm::starts_with(str, "is"))
    {
        boost::algorithm::replace_first(str, "is", StringUtil::BLANK);
        boost::algorithm::to_lower(str);
        property = new SceneNodeProperty<T>(reference, str, "true", type);
        mProperties.push_back(property);
    }
    else
    {
        property = new SceneNodeProperty<T>(reference, name, value, type);
        mProperties.push_back(property);
    }
}
//----------------------------------------------------------------------------
template<typename T>
const PropertyList& DotScene::findObjectByProperty(NodePropertyType type, const String& name, const String& value/*=BLANK*/)
{
    static PropertyList lst; 
    
    lst.clear();
    for(PropertyListIterator it=mProperties.begin(); it!=mProperties.end(); it++)
    {
        SceneNodeProperty<T> *prop = *it;
        if ((prop->mType == type) && (prop->mName == name))
        {
            if ((value == StringUtil::BLANK) || (prop->mValue == value))
                lst.push_back(prop); 
        }
    }
        
    return lst;
}
//----------------------------------------------------------------------------
template<typename T>
const PropertyList& DotScene::getObjectProperties(T* reference)
{
    static PropertyList lst; 
    
    assert(reference);
    
    lst.clear();
    for(PropertyListIterator it=mProperties.begin(); it!=mProperties.end(); it++)
    {
        SceneNodeProperty<T> *prop = *it;
        if (prop->mNode == reference)
            lst.push_back(prop); 
    }
        
    return lst;
}
//----------------------------------------------------------------------------
template<typename T>
const PropertyList& DotScene::getObjectProperties(const String& name)
{
    static PropertyList lst; 
    
    lst.clear();
    for(PropertyListIterator it=mProperties.begin(); it!=mProperties.end(); it++)
    {
        SceneNodeProperty<T> *prop = *it;
        if (prop->mName == name)
            lst.push_back(prop); 
    }
        
    return lst;
}
//----------------------------------------------------------------------------
String DotScene::getAttrib(TiXmlElement* node, const String& parameter, const String& defaultValue)
{
    if(node->Attribute(parameter.c_str()))
        return String(node->Attribute(parameter.c_str()));
    
    String _parameter = parameter;
    boost::to_lower(_parameter);
    if(node->Attribute(parameter.c_str()))
       return String(node->Attribute(parameter.c_str()));   
   
   return defaultValue;
}
//----------------------------------------------------------------------------
Real DotScene::getAttribReal(TiXmlElement* node, const String& parameter, Real defaultValue)
{
    if(node->Attribute(parameter.c_str()))
        return StringConverter::parseReal(node->Attribute(parameter.c_str()));
    
    String _parameter = parameter;
    boost::to_lower(_parameter);
    if(node->Attribute(parameter.c_str()))
        return StringConverter::parseReal(node->Attribute(parameter.c_str()));
    
    return defaultValue;  
}
//----------------------------------------------------------------------------
Integer DotScene::getAttribInt(TiXmlElement* node, const String& parameter, Integer defaultValue)
{
    if(node->Attribute(parameter.c_str()))
        return StringConverter::parseInt(node->Attribute(parameter.c_str()));
    
    String _parameter = parameter;
    boost::to_lower(_parameter);
    if(node->Attribute(parameter.c_str()))
        return StringConverter::parseInt(node->Attribute(parameter.c_str()));
    
    return defaultValue;  
}
//----------------------------------------------------------------------------
bool DotScene::getAttribBool(TiXmlElement* node, const String& parameter, bool defaultValue)
{
    if (node->Attribute(parameter.c_str()))
    {
        if(String(node->Attribute(parameter.c_str())) == "true")
            return true;
        if(String(node->Attribute(parameter.c_str())) == "false")
            return false;
    }
    
    String _parameter = parameter;
    boost::to_lower(_parameter);
    if (node->Attribute(_parameter.c_str()))
    {
        if(String(node->Attribute(_parameter.c_str())) == "true")
            return true;
        if(String(node->Attribute(_parameter.c_str())) == "false")
            return false;
    }
    
    return defaultValue;
}
//----------------------------------------------------------------------------
Plane DotScene::parsePlane(TiXmlElement* node)
{
    Plane plane;
    plane.normal.x = getAttribReal(node, "x", 0);
    plane.normal.y = getAttribReal(node, "y", 0);
    plane.normal.z = getAttribReal(node, "z", 0);
    plane.d = getAttribReal(node, "d", 0);
    return plane;
}
//----------------------------------------------------------------------------
Vector3 DotScene::parseVector3(TiXmlElement* node)
{
    Vector3 vec3(
        StringConverter::parseReal(node->Attribute("x")),
        StringConverter::parseReal(node->Attribute("y")),
        StringConverter::parseReal(node->Attribute("z"))
    );
    
    printf("Position Vector3(%f,%f,%f)\n", vec3.x, vec3.y, vec3.z);
    return vec3;
}
//----------------------------------------------------------------------------
Quaternion DotScene::parseQuaternion(TiXmlElement* node)
{
    Quaternion quaternion = Quaternion::IDENTITY;

    if(node->Attribute("qw"))
    {
        quaternion.w = StringConverter::parseReal(node->Attribute("qw"));
        quaternion.x = StringConverter::parseReal(node->Attribute("qx"));
        quaternion.y = StringConverter::parseReal(node->Attribute("qy"));
        quaternion.z = StringConverter::parseReal(node->Attribute("qz"));
    }
    else if(node->Attribute("axisX"))
    {
        Vector3 axis;
        axis.x = StringConverter::parseReal(node->Attribute("axisX"));
        axis.y = StringConverter::parseReal(node->Attribute("axisY"));
        axis.z = StringConverter::parseReal(node->Attribute("axisZ"));
        Real angle = StringConverter::parseReal(node->Attribute("angle"));
        assert(false); //detectoproblem with  angle units
        quaternion.FromAngleAxis(Angle(angle), axis);
    }
    else if(node->Attribute("angleX"))
    {
        Vector3 euler;
        euler.x = StringConverter::parseReal(node->Attribute("angleX"));
        euler.y = StringConverter::parseReal(node->Attribute("angleY"));
        euler.z = StringConverter::parseReal(node->Attribute("angleZ"));
        String order = getAttrib(node, "order", "x");

        //Convert Euler angles to a matrix
        Matrix3 rotationMatrix;
        
        if (order.length() < 2)
        {
            rotationMatrix.FromEulerAnglesXYZ(Radian(euler.x), Radian(euler.y), Radian(euler.z));
        }
        else
        {
            if (order[0] == 'x')
            {
                if (order[1] == 'y')
                    rotationMatrix.FromEulerAnglesXYZ(Radian(euler.x), Radian(euler.y), Radian(euler.z));
                else
                    rotationMatrix.FromEulerAnglesXZY(Radian(euler.x), Radian(euler.y), Radian(euler.z));
            }
            else if (order[0] == 'y')
            {
                if (order[1] == 'x')
                    rotationMatrix.FromEulerAnglesYXZ(Radian(euler.x), Radian(euler.y), Radian(euler.z));
                else
                    rotationMatrix.FromEulerAnglesYZX(Radian(euler.x), Radian(euler.y), Radian(euler.z));
            }
            else
            {
                if (order[1] == 'x')
                    rotationMatrix.FromEulerAnglesZXY(Radian(euler.x), Radian(euler.y), Radian(euler.z));
                else
                    rotationMatrix.FromEulerAnglesZYX(Radian(euler.x), Radian(euler.y), Radian(euler.z));
            }
        }

        //Convert the matrix into the rotation quaternion
        quaternion.FromRotationMatrix(rotationMatrix);
    }
    else if(node->Attribute("x"))
    {
        quaternion.x = StringConverter::parseReal(node->Attribute("x"));
        quaternion.y = StringConverter::parseReal(node->Attribute("y"));
        quaternion.z = StringConverter::parseReal(node->Attribute("z"));
        quaternion.w = StringConverter::parseReal(node->Attribute("w"));
    }
    else if(node->Attribute("w"))
    {
        quaternion.w = StringConverter::parseReal(node->Attribute("w"));
        quaternion.x = StringConverter::parseReal(node->Attribute("x"));
        quaternion.y = StringConverter::parseReal(node->Attribute("y"));
        quaternion.z = StringConverter::parseReal(node->Attribute("z"));
    }
 
    printf("Orientacion Quaternion(%f,%f,%f,%f)\n", quaternion.w, quaternion.x, quaternion.y, quaternion.z);
    return quaternion;  
}
//----------------------------------------------------------------------------
ColourValue DotScene::parseColour(TiXmlElement* node)
{
    ColourValue colorValue(
        StringConverter::parseReal(node->Attribute("r")),
        StringConverter::parseReal(node->Attribute("g")),
        StringConverter::parseReal(node->Attribute("b")),
        node->Attribute("a") != NULL ? StringConverter::parseReal(node->Attribute("a")) : 1
    );
   
   printf("Color ColorValue(%f,%f,%f,%f)\n", colorValue.r, colorValue.g, colorValue.b, colorValue.a);
   return colorValue;
}
//----------------------------------------------------------------------------
FloatRect DotScene::parseFloatRectangle(TiXmlElement* node)
{
    FloatRect rect;
    
    rect.left = getAttribReal(node, "left", 0.0f);
    rect.top = getAttribReal(node, "top", 0.0f);
    rect.right = getAttribReal(node, "right", 0.0f);
    rect.bottom = getAttribReal(node, "bottom", 0.0f);
    
    return rect;
}
//----------------------------------------------------------------------------
int DotScene::parseRenderQueue(String& queue)
{
    int rst = RENDER_QUEUE_MAIN;
    
    StringUtil::toLowerCase(queue);
        
    if ("background" == queue) rst = RENDER_QUEUE_BACKGROUND;
    if ("skiesearly"== queue) rst =  RENDER_QUEUE_SKIES_EARLY;
    if ("queue1"== queue) rst = RENDER_QUEUE_1;
    if ("queue2"== queue) rst = RENDER_QUEUE_2;
    if ("worldgeometry1"== queue) rst = RENDER_QUEUE_WORLD_GEOMETRY_1;
    if ("queue3"== queue) rst = RENDER_QUEUE_3;
    if ("queue4"== queue) rst = RENDER_QUEUE_4;
    if ("main"== queue) rst = RENDER_QUEUE_MAIN;
    if ("queue6"== queue) rst = RENDER_QUEUE_6;
    if ("queue7"== queue) rst = RENDER_QUEUE_7;
    if ("worldgeometry2"== queue) rst = RENDER_QUEUE_WORLD_GEOMETRY_2;
    if ("queue8"== queue) rst = RENDER_QUEUE_8;
    if ("queue9"== queue) rst = RENDER_QUEUE_9;
    if ("skieslate"== queue) rst = RENDER_QUEUE_SKIES_LATE;
    if ("overlay"== queue) rst = RENDER_QUEUE_OVERLAY;
    if ("max"== queue) rst = RENDER_QUEUE_MAX;
    
    return rst;
}
//---------------------------------------------------------------------------
int DotScene::parseQueryFlags(TiXmlElement* node)
{
    TRACE_FUNC();
    assert(false);
   
    int flags = 0;
    
    TiXmlElement* elem = 0;
    
    elem = node->FirstChildElement("queryFlag");
    while(elem)
    {
        String name = getAttrib(elem, "name");
        int flag = getAttribInt(elem, "bit");
        flags |= flag;
        elem = elem->NextSiblingElement();
    }
    
    return flags;
}
//---------------------------------------------------------------------------
int DotScene::parseVisibilityFlags(TiXmlElement* node)
{
    TRACE_FUNC();
    assert(false);
   
    int flags = 0;
    
    TiXmlElement* elem = 0;
    
    elem = node->FirstChildElement("visibilityFlag");
    while(elem)
    {
        String name = getAttrib(elem, "name");
        int flag = getAttribInt(elem, "bit");
        flags |= flag;
        elem = elem->NextSiblingElement();
    }
    
    return flags;
}
//---------------------------------------------------------------------------
PixelFormat DotScene::parsePixelFormat(String& format)
{
    PixelFormat pf = PF_FLOAT16_R;
    
    StringUtil::toLowerCase(format);
        
    if (format == "L8") pf = PF_L8;
    else if (format == "L16") pf = PF_L16;
    else if (format == "A8") pf = PF_A8;
    else if (format == "A4L4") pf = PF_A4L4;
    else if (format == "BYTE_LA") pf = PF_BYTE_LA;
    else if (format == "R5G6B5") pf = PF_R5G6B5;
    else if (format == "B5G6R5") pf = PF_B5G6R5;
    else if (format == "R3G3B2") pf = PF_R3G3B2;
    else if (format == "A4R4G4B4") pf = PF_A4R4G4B4;
    else if (format == "A1R5G5B5") pf = PF_A1R5G5B5;
    else if (format == "R8G8B8") pf = PF_R8G8B8;
    else if (format == "B8G8R8") pf = PF_B8G8R8;
    else if (format == "A8R8G8B8") pf = PF_A8R8G8B8;
    else if (format == "A8B8G8R8") pf = PF_A8B8G8R8;
    else if (format == "B8G8R8A8") pf = PF_B8G8R8A8;
    else if (format == "R8G8B8A8") pf = PF_R8G8B8A8;
    else if (format == "X8R8G8B8") pf = PF_X8R8G8B8;
    else if (format == "X8B8G8R8") pf = PF_X8B8G8R8;
    else if (format == "A2R10G10B10") pf = PF_A2R10G10B10;
    else if (format == "A2B10G10R10") pf = PF_A2B10G10R10;
    else if (format == "FLOAT16_R") pf = PF_FLOAT16_R;
    else if (format == "FLOAT16_RGB") pf = PF_FLOAT16_RGB;
    else if (format == "FLOAT16_RGBA") pf = PF_FLOAT16_RGBA;
    else if (format == "FLOAT32_R") pf = PF_FLOAT32_R;
    else if (format == "FLOAT32_RGB") pf = PF_FLOAT32_RGB;
    else if (format == "FLOAT32_RGBA") pf = PF_FLOAT32_RGBA;
    else if (format == "FLOAT16_GR") pf = PF_FLOAT16_GR;
    else if (format == "FLOAT32_GR") pf = PF_FLOAT32_GR;
    else if (format == "DEPTH") pf = PF_DEPTH;
    else if (format == "SHORT_RGBA") pf = PF_SHORT_RGBA;
    else if (format == "SHORT_GR") pf = PF_SHORT_GR;
    else if (format == "SHORT_RGB") pf = PF_SHORT_RGB;

    return pf;
}
//----------------------------------------------------------------------------
TextureType DotScene::parseTextureType(String& type)
{
    StringUtil::toLowerCase(type);
    
    if (type == "1d")
        return TEX_TYPE_1D;
    else if (type == "2d")
        return TEX_TYPE_2D;
    else if (type == "3d")
        return TEX_TYPE_3D;
    else if (type == "cubic")
        return TEX_TYPE_CUBE_MAP;
    else
        return TEX_TYPE_2D;
}
//----------------------------------------------------------------------------
Radian DotScene::parseAngleUnit(Real value)
{
    Radian radian(value);
    
    //is degrees??
    if (value > Math::PI)
        radian = Degree(value);
    
    return radian;
}
//----------------------------------------------------------------------------
SceneNode* DotScene::getSceneNode(const String& sceneNode)
{
    for(StringVector::iterator it=mSceneNodes.begin(); it!=mSceneNodes.end(); it++)
    {
        if (sceneNode == *it) 
            return mSceneMgr->getSceneNode(sceneNode);
    }
    
    return 0;
}
//----------------------------------------------------------------------------
Entity* DotScene::getEntity(const String& entity)
{
    for(StringVector::iterator it=mDynamicEntities.begin(); it!=mDynamicEntities.end(); it++)
    {
        if (entity == *it) 
            return mSceneMgr->getEntity(entity);
    }
    
    for(StringVector::iterator it=mStaticEntities.begin(); it!=mStaticEntities.end(); it++)
    {
        if (entity == *it) 
            return mSceneMgr->getEntity(entity);
    }
    
    return 0;
}
//----------------------------------------------------------------------------
Light* DotScene::getLight(const String& light)
{
    for(StringVector::iterator it=mLights.begin(); it!=mLights.end(); it++)
    {
        if (light == *it) 
            return mSceneMgr->getLight(light);
    }
    
    return 0;
}
//----------------------------------------------------------------------------
Camera* DotScene::getCamera(const String& camera)
{
    for(StringVector::iterator it=mCameras.begin(); it!=mCameras.end(); it++)
    {
        if (camera == *it) 
            return mSceneMgr->getCamera(camera);
    }
    
    return 0;
}
//----------------------------------------------------------------------------
BillboardSet* DotScene::getBillboardSet(const String& billboardSet)
{
    for(StringVector::iterator it=mBillboardSets.begin(); it!=mBillboardSets.end(); it++)
    {
        if (billboardSet == *it) 
            return mSceneMgr->getBillboardSet(billboardSet);
    }
    
    return 0;
}
//----------------------------------------------------------------------------
ParticleSystem* DotScene::getParticleSystem(const String& particleSystem)
{
    for(StringVector::iterator it=mParticleSystem.begin(); it!=mParticleSystem.end(); it++)
    {
        if (particleSystem == *it) 
            return mSceneMgr->getParticleSystem(particleSystem);
    }
    
    return 0;
}
//----------------------------------------------------------------------------
Mesh* DotScene::getMesh(const String& mesh)
{
    for(StringVector::iterator it=mMeshes.begin(); it!=mMeshes.end(); it++)
    {
        if (mesh == *it) 
        {
            MeshPtr ptr = MeshManager::getSingletonPtr()->getByName(mesh);
            assert(! ptr.isNull());
            return ptr.getPointer();
        }
    }
    
    return 0;
}
//----------------------------------------------------------------------------
const PropertyList DotScene::getProperties(const String& node)
{
    PropertyList proplst;
    for(PropertyListIterator it=mProperties.begin(); it!=mProperties.end(); it++)
    {
        NodeProperty* prop = *it;
        assert(prop);
        
        if (node == prop->mReference)
            proplst.push_back(prop);
    }
    
    return proplst;
}
//----------------------------------------------------------------------------
const String DotScene::getProperty(const String& node, const String& name)
{
    for(PropertyListIterator it=mProperties.begin(); it!=mProperties.end(); it++)
    {
        NodeProperty* prop = *it;
        assert(prop);
        
        log("Propiedad " + prop->mName + " del objeto " + prop->mReference + " con valor " + prop->mValue);
        if ((node == prop->mReference) && (name == prop->mName))
            return ((StringUtil::BLANK == prop->mValue)? prop->mName :prop->mValue);
    }
    
    return StringUtil::BLANK;
}
//----------------------------------------------------------------------------
int DotScene::getPropertyInt(const String& node, const String& name)
{
    const String& value = getProperty(node, name);
    assert(StringUtil::BLANK != value);
    
    return StringConverter::parseInt(value.c_str());
}
//----------------------------------------------------------------------------
Real DotScene::getPropertyReal(const String& node, const String& name)
{
    const String& value = getProperty(node, name);
    assert(StringUtil::BLANK != value);
    
    return StringConverter::parseReal(value.c_str());
}
//----------------------------------------------------------------------------
bool DotScene::getPropertyBool(const String& node, const String& name)
{
    String value = getProperty(node, name);
    
    boost::to_lower(value);
    if(value == "true")
        return true;
    if(value == "false")
        return false;
    
    return false;
}
//----------------------------------------------------------------------------
Camera* DotScene::getDefaultCamera(int idx_viewport/*=0*/)
{
    std::map<int,String>::iterator it = mDefaultCameras.find(idx_viewport);
    if (mDefaultCameras.end() != it)
    {
        String camera = it->second;
        
        if (mSceneMgr->hasCamera(camera))
            return mSceneMgr->getCamera(camera);
    }
    
    return 0;
}
//----------------------------------------------------------------------------
Camera* DotScene::setDefaultCamera(const String& camera, int idx_viewport/*=0*/, int zorder/*=0*/)
{
    assert(StringUtil::BLANK != camera);
    assert(mSceneMgr->getCamera(camera));
    //assert(mCameras.size());
   
//     StringVector::iterator it_camera = mCameras.begin();
//     for(StringVector::iterator it_camera=mCameras.begin(); it_camera!=mCameras.end(); it_camera++)
//     {
//         if (camera == *it_camera) break;
//     }
//     assert(it_camera != mCameras.end());
   
    log("Setting default camera " + camera + " to viewport "  + stringify(idx_viewport));
    
    std::map<int,String>::iterator it_default = mDefaultCameras.find(idx_viewport);
    if (it_default != mDefaultCameras.end())
        mDefaultCameras.erase(it_default);
    
    mDefaultCameras.insert(std::make_pair<int,String>(idx_viewport,camera));
    
    Root* root = Root::getSingletonPtr();
    RenderWindow* window = root->getAutoCreatedWindow();
    
    if (window->getNumViewports())
    {
        Viewport* viewport = window->getViewport(idx_viewport);
        viewport->setCamera(mSceneMgr->getCamera(camera));
    }
    else
    {
        Viewport* viewport = window->addViewport(mSceneMgr->getCamera(camera), zorder);
        viewport->setBackgroundColour(mBackgroundColor);
    }
}
//----------------------------------------------------------------------------
void DotScene::viewSceneFromCamera(const String& camera, bool fitToWholeScene/*=false*/)
{
    assert(false);
}
//----------------------------------------------------------------------------
void DotScene::update(Real delta)
{
    assert(false);
}
//----------------------------------------------------------------------------
void DotScene::showBoundingBoxes()
{
    for(StringVector::iterator it=mSceneNodes.begin(); it!=mSceneNodes.end(); it++)
    {
        SceneNode* node = mSceneMgr->getSceneNode(*it);
        node->showBoundingBox(true);
    }
}
//----------------------------------------------------------------------------
void DotScene::hideBoundingBoxes()
{
    for(StringVector::iterator it=mSceneNodes.begin(); it!=mSceneNodes.end(); it++)
    {
        SceneNode* node = mSceneMgr->getSceneNode(*it);
        node->showBoundingBox(false);
    }
}

//----------------------------------------------------------------------------
void DotScene::showSkeletons()
{
    for(StringVector::iterator it=mDynamicEntities.begin(); it!=mDynamicEntities.end(); it++)
    {
        Entity* entity = mSceneMgr->getEntity(*it);
        if (entity->hasSkeleton()) entity->setDisplaySkeleton(true);
    }
}
//----------------------------------------------------------------------------
void DotScene::hideSkeletons()
{
    for(StringVector::iterator it=mDynamicEntities.begin(); it!=mDynamicEntities.end(); it++)
    {
        Entity* entity = mSceneMgr->getEntity(*it);
        if (entity->hasSkeleton()) entity->setDisplaySkeleton(true);
    }
}
//----------------------------------------------------------------------------
bool DotScene::exportToFile(const String& filename/*=StringUtil::BLANK*/)
{
    TRACE_FUNC();
    
    if (! helper) 
        helper = new DotScenePersistenceHelper(this);
    
    helper->persist();
    
    return true;
}

/*****************************************************************************/
/** DotScenePtr                                                              */                   
/*****************************************************************************/
DotScenePtr::DotScenePtr() : SharedPtr<DotScene>() 
{}
//----------------------------------------------------------------------------
DotScenePtr::DotScenePtr(DotScene* scene) : SharedPtr<DotScene>(scene) 
{}
//----------------------------------------------------------------------------
DotScenePtr::DotScenePtr(const DotScenePtr& scenePtr) : SharedPtr<DotScene>(scenePtr) 
{}
//----------------------------------------------------------------------------
DotScenePtr::DotScenePtr(const ResourcePtr& r) 
            : SharedPtr<DotScene>()
{
    if (r.isNull()) return;
    
    // lock & copy other mutex pointer
    OGRE_LOCK_MUTEX(*resourcePtr.OGRE_AUTO_MUTEX_NAME)
    OGRE_COPY_AUTO_SHARED_MUTEX(resourcePtr.OGRE_AUTO_MUTEX_NAME)
    
    pRep = static_cast<DotScene*>(r.getPointer());
    pUseCount = r.useCountPointer();
    useFreeMethod = r.freeMethod();
    
    if (pUseCount) ++(*pUseCount);
}
//----------------------------------------------------------------------------
DotScenePtr& DotScenePtr::operator=(const ResourcePtr& r)
{
    if(pRep == static_cast<DotScene*>(r.getPointer()))
             return *this;
    
    release();
    
    if (r.isNull())
        return *this; 
    
    // lock & copy other mutex pointer
    OGRE_LOCK_MUTEX(*resourcePtr.OGRE_AUTO_MUTEX_NAME)
    OGRE_COPY_AUTO_SHARED_MUTEX(resourcePtr.OGRE_AUTO_MUTEX_NAME)
    
    pRep = static_cast<DotScene*>(r.getPointer());
    pUseCount = r.useCountPointer();
    useFreeMethod = r.freeMethod();
    
    if (pUseCount) ++(*pUseCount);
    
    return *this;
}

/*****************************************************************************/
/** DotSceneManager                                                          */                   
/*****************************************************************************/
const String DotSceneManager::msName = "DotSceneManager";

template<> DotSceneManager* Singleton<DotSceneManager>::ms_Singleton = 0;
//----------------------------------------------------------------------------
DotSceneManager* DotSceneManager::getSingletonPtr ( void )
{
        return ms_Singleton;
}
//----------------------------------------------------------------------------
DotSceneManager& DotSceneManager::getSingleton ( void )
{
        assert ( ms_Singleton );
        return ( *ms_Singleton );
}
//----------------------------------------------------------------------------
DotSceneManager::DotSceneManager()
{
    TRACE_FUNC();
    mResourceType = "DotScene";
    mLoadOrder = 30.0f;
    ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);
}
//----------------------------------------------------------------------------        
DotSceneManager::~DotSceneManager()
{
    TRACE_FUNC();
    ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}
//----------------------------------------------------------------------------
const String& DotSceneManager::getEmitterName() const
{
    return msName;
}
//----------------------------------------------------------------------------
DotScenePtr DotSceneManager::createScene(const String& name, 
                                         const String& sceneFile/*=P4H::StringUtil::BLANK*/, 
                                         const String& namePrefix/*=P4H::StringUtil::BLANK*/,
                                         const String& groupName/*=AUTODETECT_RESOURCE_GROUP_NAME*/,
                                         const SceneManager* sceneManager/*=0*/,
                                         bool visible/*=true*/
                                        )
{
    assert(StringUtil::BLANK != name);
    
    //Recover from registered resources
    DotScenePtr scenePtr = getByName(name);
    
    //If not found, create it (internally call to DotSceneManager::createImpl)
    if (scenePtr.isNull())
    {
        NameValuePairList values;
        
        String file = sceneFile;
        if (StringUtil::BLANK == file)
            file = name + ".scene";
        values["file"] =  file;

        values["prefix"] = StringUtil::BLANK;
        if (StringUtil::BLANK != namePrefix)
            values["prefix"] = namePrefix;
        
        SceneManager* _sceneManager = const_cast<SceneManager*>(sceneManager);
        if (! _sceneManager)
        {
            SceneManagerEnumerator::SceneManagerIterator it = Root
                ::getSingletonPtr()->getSceneManagerIterator();
            assert(it.begin() != it.end());
            _sceneManager = it.getNext();
        }
        values["sceneManager"] = _sceneManager->getName();
    
        values["createSceneMode"] = CREATE_SCENE_MODE_MANUAL;
        if (visible)
            values["createSceneMode"] = CREATE_SCENE_MODE_AUTO;
    

        //Determine ResourceGrpup that contains Resource
        String group = groupName;
        if (ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME == groupName)
        {
            ResourceGroupManager* resman = ResourceGroupManager::getSingletonPtr();
            group = resman->findGroupContainingResource(file);
        }

        scenePtr = create(name, group, false, 0, &values);
    }
         
    //Internally call to DotScene::loadImpl
    scenePtr->load();
    
    //Register scene 
    mScenes.push_back(name);
    mCurrentScene = name;
    
    return scenePtr;
}
//----------------------------------------------------------------------------        
void DotSceneManager::destroyScene(const String& name)
{
    TRACE_FUNC();
    
    DotScenePtr scenePtr = getByName(name);
    assert(! scenePtr.isNull());
    destroyScene(scenePtr);
}
//----------------------------------------------------------------------------        
void DotSceneManager::destroyScene(const DotScenePtr& scenePtr)
{
    TRACE_FUNC();
    assert(! scenePtr.isNull());
    
    scenePtr.getPointer()->unload();
    
    //Remove from list of loaded scenes
    String name = scenePtr.getPointer()->getName();    
    
    StringVector::iterator it;
    for(it=mScenes.begin(); it!=mScenes.end();it++)
    {
        if (name == scenePtr.getPointer()->getName()) break;
    }
    
    //Remove of the list of loaded scenes
    if (mScenes.end() != it)
        mScenes.erase(it);
    //Set current scene to next of list
    mCurrentScene = (mScenes.size())? mScenes.back(): StringUtil::BLANK;    
}
//----------------------------------------------------------------------------        
void DotSceneManager::destroyAllScenes()
{
    StringVector::iterator it;
    for(it=mScenes.begin(); it!=mScenes.end();it++)
    {
        destroyScene(*it);
    }
}
//----------------------------------------------------------------------------        
const DotScenePtr DotSceneManager::getScene(const String& name/*=StringUtil::BLANK*/)
{
    TRACE_FUNC();
    
    DotScenePtr scenePtr = getByName(name);
    assert(! scenePtr.isNull());
    
    return scenePtr;
}
//----------------------------------------------------------------------------    
Resource* DotSceneManager::createImpl(const String &name, 
                                            ResourceHandle handle, 
                                            const String &group, 
                                            bool isManual, 
                                            ManualResourceLoader *loader, 
                                            const NameValuePairList *params)
{
    TRACE_FUNC();
    return new DotScene(this, name, handle, group, params, isManual, loader);
}

/*****************************************************************************/
/** DotScenePersistenceHelper (implementation)                               */                   
/*****************************************************************************/
static void log(const String& formatString, ...)
{
    static char msg[1024]; // Buffer for error messages - hopefully long enough...
    const char* fmMsg = formatString.c_str();
    va_list ap;
    va_start(ap, 0);
    vsnprintf(msg, sizeof(msg), fmMsg, ap);
    va_end(ap);
    LogManager::getSingleton().logMessage(String(msg));
}
//----------------------------------------------------------------------------
static String generateUUID(const String& prefix/*=BLANK*/, const String& suffix/*=BLANK*/)
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::stringstream ss;
    ss << uuid;

    String suuid = ss.str();
    if (prefix.size()) suuid.insert(0,prefix);
    if (suffix.size()) suuid.append(prefix);

    return suuid;
}
//--------------------------------------------------------------------- 
static bool isPowerOfTwo(int value)
{
    return (value & (value - 1)) == 0;
}
//--------------------------------------------------------------------- 
static unsigned int nextSmallestPowerOfTwo(unsigned int value)
{
    if (!isPowerOfTwo(value))
    {
        //Not a power of 2. Round value up to the next power of 2
        value = nextLargestPowerOfTwo(value);
    }

    //The value is a power of 2. Shift downward to get the next smallest power of 2
    return value >> 1;
}
//--------------------------------------------------------------------- 
static unsigned int nextLargestPowerOfTwo(unsigned int value)
{
    value |= (value >> 1);
    value |= (value >> 2);
    value |= (value >> 4);
    value |= (value >> 8);
    value |= (value >> 16);
    return value + 1;
}
//----------------------------------------------------------------------------
inline String stringify(double x)
{
    std::ostringstream o("");
    if (!(o << x))
        throw std::runtime_error("stringify(double)");
    return o.str();
}
//----------------------------------------------------------------------------
inline String stringify(int x)
{
    std::ostringstream o("");
    if (!(o << x))
        throw std::runtime_error("stringify(int)");
    return o.str();
}
//----------------------------------------------------------------------------
inline String stringify(long int x)
{
    std::ostringstream o("");
    if (!(o << x))
        throw std::runtime_error("stringify(int)");
    return o.str();
}
//----------------------------------------------------------------------------
inline String stringify(float x)
{
    std::ostringstream o("");
    if (!(o << x))
        throw std::runtime_error("stringify(float)");
    return o.str();
}
//----------------------------------------------------------------------------
inline String stringify(bool x)
{
    std::ostringstream o("");
    if (!(o << std::boolalpha << x))
        throw std::runtime_error("stringify(bool)");
    return o.str();
}
//----------------------------------------------------------------------------
inline const String& stringify(const String& x) 
{
    return x;
}
