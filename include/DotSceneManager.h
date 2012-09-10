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

#ifndef __DOTSCENEMANAGER_H__
#define __DOTSCENEMANAGER_H__

/****************************************************************************/
#include <Ogre.h>

// Enable GCC symbol visibility
#   ifdef __GNUC__ 
#       define _DotSceneManagerExport  __attribute__ ((visibility("default")))
#       define _DotSceneManagerPrivate __attribute__ ((visibility("hidden")))
#   else
#       define _DotSceneManagerExport
#       define _DotSceneManagerPrivate
#   endif

/****************************************************************************/

// Forward declarations
class TiXmlElement;
// Forward declarations
class DotScenePersistenceHelper;

namespace Ogre {

    /** datatype signed integer */
    typedef int Integer;
    /** datatype string maps */
    typedef std::map<String,String> StringMap;

    /** datatype .dotscenenode type */
    typedef enum 
    {
        BILLBOARD_SET,
        BONE,
        CAMERA,
        ENTITY,
        ENVIROMENT,
        EXTERNAL,
        FOG,
        LIGHT,
        LOOK_TARGET,
        MESH,
        OCTREE,
        OCTREE_NODE,
        OCTREE_MESH,
        PARTICLE_SYSTEM,
        PLANE,
        SCENE,
        SCENE_NODE,
        SKY_BOX,
        SKY_DOME,
        SKY_PLANE,
        TERRAIN,
        TRACK_TARGET,
        UNKNOWN=99
    } NodePropertyType;         
    
    /** Base node property */
    struct _DotSceneManagerExport NodeProperty        
    {
        String mReference;
        String mName;
        String mValue;
        NodePropertyType mType;
        
        NodeProperty(const String &reference,
                     const String &name, 
                     const String &value, 
                     NodePropertyType type=UNKNOWN)
                     :mReference(reference), mName(name), mValue(value), mType(type) {}
    };//struct nodeProperty
    
    template<typename T>
    struct SceneNodeProperty : NodeProperty
    {
        SceneNodeProperty(T* node,
                          const String &name, 
                          const String &value, 
                          NodePropertyType type=UNKNOWN)
                         :NodeProperty(node->getName(),name,value,type), mNode(node){}
        T* mNode;
    }; //SceneNodeProperty
    
    /** Datatype property list */
    typedef std::vector<NodeProperty*> PropertyList;
    /** Datatype property list iterator */
    typedef std::vector<NodeProperty*>::iterator PropertyListIterator;
    
    /** Datatype clip planes */
    typedef struct 
    { 
        /** Clip plane near */
        Real mNear;
        /** Clip plane far */
        Real mFar;
    } ClippingPlanesType; //ClippingPlanesType
    
    /****************************************************************************/
    /** Clase recurso escena tipo .dotscene */
    class _DotSceneManagerExport DotScene : public Resource
    {
    public:
        typedef enum 
        { 
            UP_AXIS_Y,
            UP_AXIS_Z,
            UP_AXIS_X
        } UpAxisType;
        
    public:
        /** Constructor */
        DotScene(ResourceManager* creator, 
                 const String& name, 
                 ResourceHandle handle, 
                 const String& group,
                 const NameValuePairList* params=0,
                 bool isManual=false, 
                 ManualResourceLoader* loader=0);
 
        virtual ~DotScene();
    
        /** @return scene name */
        const String& getName();
        
        /** @return scene manager */
        SceneManager* getSceneManager();
        /** @return scene root node */
        SceneNode* getRootSceneNode();
     
        /** Change scene visibility status  - attach to RootSceneNode*/
        void setVisible(bool visible);
        /** Get scene visibility status */
        bool getVisible(void);
        
        /** return SceneNode in scene or null */
        SceneNode* getSceneNode(const String& sceneNode);
        /** return Entity in scene or null */
        Entity* getEntity(const String& entity);
        /** return Light in scene or null */
        Light* getLight(const String& light);
        /** return Camera in scene or null */
        Camera* getCamera(const String& camera);
        /** return BillboardSet in scene or null */
        BillboardSet* getBillboardSet(const String& billboardSet);
        /** return ParticleSystem in scene or null */
        ParticleSystem* getParticleSystem(const String& particleSystem);
        /** return Mesh in scene or null */
        Mesh* getMesh(const String& mesh);
        /** return la lista  de propiedades de un nodo de la escena */
        const PropertyList getProperties(const String& node);
        /** return la lista  de propiedades de un nodo de la escena */
        const String getProperty(const String& node, const String& name);
        /** return la lista  de propiedades de un nodo de la escena */
        int getPropertyInt(const String& node, const String& name);
        /** return la lista  de propiedades de un nodo de la escena */
        Real getPropertyReal(const String& node, const String& name);
        /** return la lista  de propiedades de un nodo de la escena */
        bool getPropertyBool(const String& node, const String& name);
        
        /** return default camera or null*/
        Camera* getDefaultCamera(int viewport=0);
        /** return default camera or null*/
        Camera* setDefaultCamera(const String& camera, int viewport=0);
        
        /** change camera in viewport */
        void viewSceneFromCamera(const String& camera, bool fitToWholeScene=false);
        
        /** update scene node behaviours: lookTarget, TrackTarget, camera best-fits */
        void update(Real delta);
        
        /** debug facilities: show AABB for all entities*/
        void showBoundingBoxes();
        /** debug facilities: hide AABB for all entities*/
        void hideBoundingBoxes();
        /** debug facilities: show skeleton for all entities*/
        void showSkeletons();
        /** debug facilities: hide skeleton for all entities*/
        void hideSkeletons();
        
        /** 
         * export current scene to a .scene file 
         * @param String filename
         */
        bool exportToFile(const String& filename=StringUtil::BLANK);
        
    protected:
        /** Parse and load dot scene file */
        void loadImpl();
        /** Release internal resources */
        void unloadImpl();
        /** return resource size (in nodes) */
        size_t calculateSize() const;
    private:
        /** dotscene loader method: process 'scene' node*/
        void processScene(TiXmlElement* XMLRoot);
        /** dotscene loader method: process 'nodes' node*/
        void processNodes(TiXmlElement* node);
        /** dotscene loader method: process 'externals' node*/
        void processExternals(TiXmlElement* node);
        /** dotscene loader method: process 'enviroment' node*/
        void processEnvironment(TiXmlElement* node);
        /** dotscene loader method: process 'terrain' node*/
        void processTerrain(TiXmlElement* node);
        /** dotscene loader method: process 'octree' node*/
        void processOctree(TiXmlElement* node);
        /** dotscene loader method: process 'octNode' node*/
        void processOctNode(TiXmlElement* node);
        /** dotscene loader method: process 'octMesh' node*/
        void processOctMesh(TiXmlElement* node);
        /** dotscene loader method: process 'light' node*/
        void processLight(TiXmlElement* node, SceneNode* parent);
        /** dotscene loader method: process 'camera' node*/
        void processCamera(TiXmlElement* node, SceneNode* parent);
        /** dotscene loader method: process 'node' node*/
        void processNode(TiXmlElement* node, SceneNode* parent);
        /** dotscene loader method: process 'look-target' node*/
        void processLookTarget(TiXmlElement* node, SceneNode* parent);
        /** dotscene loader method: process 'track-target' node*/
        void processTrackTarget(TiXmlElement* node, SceneNode* parent);
        /** dotscene loader method: process 'entity' node*/
        void processEntity(TiXmlElement* node, SceneNode* parent);
        /** dotscene loader method: process 'entity' node*/
        void processEntity(TiXmlElement* node, InstancedGeometry* geometry);
        /** dotscene loader method: process 'entity' node*/
        void processEntity(TiXmlElement* node, StaticGeometry* geometry);
        /** dotscene loader method: process 'particle-system' node*/
        void processParticleSystem(TiXmlElement* node, SceneNode* parent);
        /** dotscene loader method: process 'billboard' node*/
        void processBillboardSet(TiXmlElement* node, SceneNode* parent);
        /** dotscene loader method: process 'plane' node*/
        void processPlane(TiXmlElement* node, SceneNode* parent);
        /** dotscene loader method: process 'fog' node*/
        void processFog(TiXmlElement* node);
        /** dotscene loader method: process 'skybox' node*/
        void processSkyBox(TiXmlElement* node);
        /** dotscene loader method: process 'skydome' node*/
        void processSkyDome(TiXmlElement* node);
        /** dotscene loader method: process 'plane' node*/
        void processSkyPlane(TiXmlElement* node);
        /** dotscene loader method: process 'clipping' node*/
        void processClipping(TiXmlElement* node, ClippingPlanesType* clippingPlanes);
        /** dotscene loader method: process 'light' node*/
        void processLightRange(TiXmlElement* node, Light* light);
        /** dotscene loader method: process 'scene' node*/
        void processLightAttenuation(TiXmlElement* node, Light* light);
        /** process vertex buffer */
        void processVertexBuffer(TiXmlElement* node, HardwareVertexBuffer::Usage* usage, bool* useShadowBuffer);
        /** process index buffer */
        void processIndexBuffer(TiXmlElement* node, HardwareIndexBuffer::Usage* usage, bool* useShadowBuffer);
        /** process animation */
        void processAnimation(TiXmlElement* node, SceneNode* parent);
        /** process animation keyframe */
        void processAnimationKeyFrame(TiXmlElement* node, SceneNode* parent);
        /** process shadows */
        void processShadow(TiXmlElement* node);
        /** process subentity */
        void processSubEntity(TiXmlElement* node, Entity* entity);
        /** process shadowcamerasetup */
        void processShadowCameraSetup(TiXmlElement* node);
        /** process renderTextures */
        void processRenderTextures(TiXmlElement* node);
        /** process InstancedGeometries */
        void processInstancedGeometries(TiXmlElement* node);
        /** process StaticGeometries */
        void processStaticGeometries(TiXmlElement* node);
        /** process PortalConnectedZones */
        void processPortalConnectedZones(TiXmlElement* node);
        /** process NoteTrack */
        void processNoteTrack(TiXmlElement* node, SceneNode* parent);
        /** process NoteTrack */
        void processNoteTrack(TiXmlElement* node, Entity* entity);
        /** process CustomParameter */
        void processCustomParameter(TiXmlElement* node, Entity* entity);
        /** process BoneAttachment */
        void processBoneAttachment(TiXmlElement* node, Entity* entity);
        
        /** dotscene helper method: tinyxml get attribute*/
        String getAttrib(TiXmlElement* node, const String& parameter, const String& defaultValue=StringUtil::BLANK);
        /** dotscene helper method: tinyxml get attribute Integer*/
        Integer getAttribInt(TiXmlElement* node, const String& parameter, Integer defaultValue=0);
        /** dotscene helper method: tinyxml get attribute Real*/
        Real getAttribReal(TiXmlElement* node, const String& parameter, Real defaultValue=0);
        /** dotscene helper method: tinyxml get attribute boolean*/
        bool getAttribBool(TiXmlElement *node, const String& parameter, bool defaultValue=false);
        
        /** dotscene helper method: parse value to Vector3*/
        Vector3 parseVector3(TiXmlElement* node);
        /** dotscene helper method: parse value to Quaternion*/
        Quaternion parseQuaternion(TiXmlElement* node);
        /** dotscene helper method: parse value to ColourValue*/
        ColourValue parseColour(TiXmlElement* node);
        /** dotscene helper method: parse value to Plane*/
        Plane parsePlane(TiXmlElement* node);
        /** dotscene helper method: parse value to FloatRect*/
        FloatRect parseFloatRectangle(TiXmlElement* node);
        
        /** dotscene helper method: parse value to RenderQueue*/
        int parseRenderQueue(String& queue);
        /** dotscene helper method: parse value to query flags*/
        int parseQueryFlags(TiXmlElement* node);
        /** dotscene helper method: parse value to visibility flags*/
        int parseVisibilityFlags(TiXmlElement* node);
        /** dotscene helper method: parse value to PixelFormat*/
        PixelFormat parsePixelFormat(String& format);
        /** dotscene helper method: parse value to TextureType*/
        TextureType parseTextureType(String& type);
        /** dotscene helper method: parse value to autodetect angle units*/
        Radian parseAngleUnit(Real value);
        
        /** dotscene loader method: process 'userdata' node*/
        template <typename T>
        void processUserData(TiXmlElement* node, T* reference, NodePropertyType type);
        
        /** dotscene loader method: process 'userdatareference' node*/
        template <typename T>
        void processUserDataReference(TiXmlElement* node, T* reference, NodePropertyType type);
        
        /** dotscene helper method: add runtime property to scene node */
        template<typename T>
        void addProperty(T* reference, const  String& name, const String& value, NodePropertyType type);
        
        /** clean resources dotscene */
        void cleanResources();
        
        /** return Quaternion for upAxis configuration */
        Quaternion getUpAxisOrientation();
        /** return vector for upAxis configuration */
        Vector3 getUpVector();
        
        /** set default lighting schema */
        void setDefaultLighting();
    private:
        /** Friend DotScenePersistenceHelper */
        friend class DotScenePersistenceHelper;
        /** Export helper class */
        DotScenePersistenceHelper* helper;
        
        /** Scene Manager used to create node */
        SceneManager* mSceneMgr;
        /** Root scene node */
        SceneNode* mSceneRoot;
        /** Default camera */
        std::map<int,String> mDefaultCameras;
        
        /** Resource .dotscene filename */
        String mFile;
        /** SceneNode prefix */
        String mPrefix;
        /** Flag auto create scene */
        bool mCreateSceneMode;
        /** Version of .dotscene file */
        String mVersion;
        /** Units conversion factor */
        int mUnitConversionFactor;
        /** Background color */
        ColourValue mBackgroundColor;
        /** Color ambient light*/
        ColourValue mAmbientLight;
        /** General clipping planes*/
        ClippingPlanesType mClipPlanes;
        /** Up axis configuration */
        UpAxisType mUpAxis;
        /** Scene Query flag */
        int mQueryFlags;
        /** Scene Visibility flag */
        int mVisibilityFlags;
        /** Animation package */
        int mAnimationPackage;
        
        /** Node properties: UserData */
        PropertyList mProperties;
        
        /** Objects in scene:  scenenodes*/
        StringVector mSceneNodes;
        /** Objects in scene: dynamic entities */
        StringVector mDynamicEntities;
        /** Objects in scene: static entities */
        StringVector mStaticEntities;
        /** Objects in scene: lights */
        StringVector mLights;
        /** Objects in scene: cameras */
        StringVector mCameras;
        /** Objects in scene: billboards set */
        StringVector mBillboardSets;
        /** Objects in scene: particles system */
        StringVector mParticleSystem;
        /** Objects in scene: External resources */ 
        StringMap mExternals;
        /** Objects in scene: Mesh & manual objects  */ 
        StringVector mMeshes;
        
        /** Objects in scene: RenderTextures */
        StringVector mRenderTextures;
        
        /** Objects in scene: TODO */
        std::vector<String> mUserReferences;
    }; //Class DotScene
    
    /****************************************************************************/
    class _DotSceneManagerExport DotScenePtr : public SharedPtr<DotScene>
    {
    public :
        /** Constructor */
        DotScenePtr();
        /** Constructor */
        explicit DotScenePtr(DotScene* scene);
        /** Constructor */
        DotScenePtr(const DotScenePtr& scenePtr);
        /** Constructor */
        DotScenePtr(const ResourcePtr& resourcePtr);
        /** Constructor */
        DotScenePtr& operator=(const ResourcePtr& resourcePtr);
    };//Class DotScenePtr
    
    /****************************************************************************/
    /** Clase manager de recursos escena tipo .dotscene */
    class _DotSceneManagerExport DotSceneManager : public ResourceManager, public Singleton<DotSceneManager>
    {
    public:
        /** Constructor */
        DotSceneManager();
        /** Destructor */
        virtual ~DotSceneManager();
        
        /** @return name as Event Emitter */
        virtual const String& getEmitterName() const;
        
        /** Load request for a .dotscene file */
        DotScenePtr createScene(const String& name, 
                                const String& sceneFile=StringUtil::BLANK, 
                                const String& namePrefix=StringUtil::BLANK,
                                const String& groupName=ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
                                const SceneManager* sceneManager=0,
                                bool visible=true
                               );
        /** Create scene from file */
        void destroyScene(const String& name);
        /** Create scene from file */
        void destroyScene(const DotScenePtr& scenePtr);
        /** Destroy all scenes */
        void destroyAllScenes();
        
        /** Return DotScene by name */
        const DotScenePtr getScene(const String& name=StringUtil::BLANK);
        
        /** Singleton pattern */
        static DotSceneManager& getSingleton();
        /** Singleton pattern */
        static DotSceneManager* getSingletonPtr();
    protected:
        Resource *createImpl(const String &name, 
                                   ResourceHandle handle, 
                                   const String &group, 
                                   bool isManual, 
                                   ManualResourceLoader *loader, 
                                   const NameValuePairList *createParams);
    private:
        /** event emitter name */
        static const String msName;
        /** current scene active */
        StringVector mScenes;
        /** create scene */
        String mCurrentScene;
    }; //Class DotSceneManager
}//namespace P4H

#endif //__DOTSCENEMANAGER_H__
