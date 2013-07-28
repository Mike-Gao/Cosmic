//
// CLOUDS Interactive Documentary
//
// VISUAL SYSTEMS
//
// Welcome to the EMPTY CloudsVisualSystem
//
//
//

#pragma once

#include "CloudsVisualSystem.h"
#include "ofxColorPalettes.h"
#include "ofxAutoReloadedShader.h"

//TODO: rename this to your own visual system
class CloudsVisualSystemCosmic : public CloudsVisualSystem {
  public:
    
	//TODO: Change this to the name of your visual system
	//This determines your data path so name it at first!
	//ie getVisualSystemDataPath() uses this
    string getSystemName(){
		return "Cosmic";
	}
    
	//Use system gui for global or logical settings, for exmpl
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
	//use render gui for display settings, like changing colors
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);

	// selfSetup is called when the visual system is first instantiated
	// This will be called during a "loading" screen, so any big images or
	// geometry should be loaded here
    void selfSetup();

	// selfBegin is called when the system is ready to be shown
	// this is a good time to prepare for transitions
	// but try to keep it light weight as to not cause stuttering
    void selfBegin();

	// selfPresetLoaded is called whenever a new preset is triggered
	// it'll be called right before selfBegin() and you may wish to
	// refresh anything that a preset may offset, such as stored colors or particles
	void selfPresetLoaded(string presetPath);
    
	//do things like ofRotate/ofTranslate here
	//any type of transformation that doesn't have to do with the camera
    void selfSceneTransformation();
	
	//normal update call
	void selfUpdate();

	// selfDraw draws in 3D using the default ofEasyCamera
	// you can change the camera by returning getCameraRef()
    void selfDraw();
	
	// use this to draw the point cloud
	void selfDrawRGBD();
	
    // draw any debug stuff here
	void selfDrawDebug();

	//draws through RGBD camera;
//	void selfDrawRGBD();
	
	// or you can use selfDrawBackground to do 2D drawings that don't use the 3D camera
	void selfDrawBackground();

	// this is called when your system is no longer drawing.
	// Right after this selfUpdate() and selfDraw() won't be called any more
	void selfEnd();

	// this is called when you should clear all the memory and delet anything you made in setup
    void selfExit();

    // if you use a custom camera to fly through the scene
	// you must implement this method for the transitions to work properly
//	ofCamera& getCameraRef(){
//		return myCustomCamera;
//	}

	//
//	ofCamera& getCameraRef(){
//		return cloudsCamera;
//	}
    
    ofCamera& getCameraRef(){
		return cam;
	}


    int ID(int x, int y); 
    void setupFboViewerGui(string name, ofFbo *fbo);
    void addSphereShaderGui(string name);
    void addHomeShaderGui(string name);
    void addElectroShaderGui(string name);    
    void addAttractorShaderGui(string name);
    void addCurlNoiseShaderGui(string name); 
    
    void setupFloorVbo(); 
    void clearFbo(ofFbo &fbo);
    
    void updateRadiusShader();
    void applyHomeShader();
    void applyElectroShader();
    void applyAttractorShader();
    void applySphereShader();
    void applyCurlNoiseShader(); 
    
    void updateAcceleration();
    void updateVelocity();
    void updatePosition();

    void drawParticles();
    void drawFloor();
    
    void drawSphereDebug();
    void drawAttractorDebug();    
    
    void addGui(ofxUISuperCanvas *g);
    void selfSetupGuis();
    
    void drawTexturedQuad(float x, float y, float w, float h, float texWidth, float texHeight); 
    
protected:
    ofShader pointcloudShader;
	ofVboMesh simplePointcloud;
    
    ofxColorPalettes *colorPalettes;
    
    float colorIndex;
    int numTris;
    int numIndi;
    int rows;
    int cols;
    int size;
    
    float *pos;
    float *vel;
    ofVec3f * verts;
	ofFloatColor * colors;
    ofVec3f * normals;
    ofVec2f * texCoords;
    ofIndexType * indices;
    
    ofVbo vbo;
    ofVbo vboFloor;
    
    ofTexture glow;
    float spriteSize;
    
    ofFbo homeFbo;
    ofFbo radiFbo;
    
    ofFbo posFboSrc;
    ofFbo posFboDst;
    
    ofFbo velFboSrc;
    ofFbo velFboDst;
    
    ofFbo accFboSrc;
    ofFbo accFboDst;  
    
    ofxAutoReloadedShader accShader;
    ofxAutoReloadedShader velShader;
    ofxAutoReloadedShader posShader;
    ofxAutoReloadedShader rdrShader;
    ofxAutoReloadedShader radShader;
    
    bool bUpdateRadius;
    bool bUpdateAcceleration;
    bool bUpdateVelocity;
    bool bUpdatePosition;
    
    float timeStep;
    float accLimit;
    float velLimit;
    float damping;
    float time;
    
    float radiusMultiplier;
    
    //Sphere Shader
    ofxAutoReloadedShader sphereShader;
    vector<bool *> sphereActive;
    vector<float *> sphereRadius;
    vector<float *> sphereAccLimit;
    vector<ofVec3f *> spherePosition;
    
    //Home Shader
    ofxAutoReloadedShader homeShader;
    bool bHomingActive;
    float homeForceLimit;
    
    //Electro Shader
    ofxAutoReloadedShader electroShader;
    bool bElectroActive;
    float electroForceLimit;
    
    //Attractor Shader
    ofxAutoReloadedShader attractorShader;
    vector<bool *> attractorActive;
    vector<float *> attractorPower;
    vector<float *> attractorExpPower;
    vector<float *> attractorAccLimit;
    vector<ofVec3f *> attractorPosition;
    
    //Floor Shader
    ofxAutoReloadedShader floorShader;
    int floorIndexSize;
    float shadowScale;
    float shadowOpacity;

    //Curl Noise Shader
    ofxAutoReloadedShader noiseShader;
    bool bNoiseActive;
    float noiseForceLimit;
    float noiseScale;
};
