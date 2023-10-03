#include "Engine.h"
#include "ErrorHelper.h"

Engine::Engine():
	m_sceneHandler(new TestScene()),
	m_gameOver(false)
{
	dt.restartClock();
	basicToScene.rm = new ResourceManager();
	basicToScene.mouse = new Mouse(gfx.getCurrentActiveWindow());
	basicToScene.keyboard = new Keyboard(gfx.getCurrentActiveWindow());
	basicToScene.camera = new Camera();
	basicToScene.shadowMap = new ShadowMap();
	basicToScene.gfx = &this->gfx;

	basicToScene.imGuiManager = &this->imGuiManager;
	imGuiManager.init();
	
	setUpDefaultShaders();
	
	m_sceneHandler.setBasicDefaultVariables(basicToScene);
	basicToScene.camera->init();
	m_sceneHandler.sceneInit();
	
	//Graphics Creates Window on it's own first
}

Engine::~Engine()
{
	delete basicToScene.camera;
	delete basicToScene.keyboard;
	delete basicToScene.mouse;
	delete basicToScene.rm;
	delete basicToScene.shadowMap;
}

void Engine::Run()
{
	std::vector<Light*> l;
	l.push_back(new SpotLight(glm::vec3(0,5,0), glm::vec3(0,0,0), glm::vec2(2000, 2000), glm::vec3(1,1,1), 90));
	basicToScene.shadowMap->setLights(l);

	float currentTimeToUpdateFPS = 0;
	float TimeToUpdateFPS = 0.3f;
	unsigned int counter = 0;
	while(!m_gameOver){

		#ifdef TurnOfWithWindow
		if(gfx.GetNrOfWindows() <= 0){
			m_gameOver = true;
			return;
		}
        #else
		    
        #endif // TurnOfWithWindow

		dt.restartClock();

		currentTimeToUpdateFPS += (float)dt.dt();
		counter++;
		if(currentTimeToUpdateFPS >= TimeToUpdateFPS){
			float fps = 1/(currentTimeToUpdateFPS / (float)counter);
			glfwSetWindowTitle(gfx.getWindowByIndex(0), std::to_string((int)fps).c_str());


			currentTimeToUpdateFPS -= TimeToUpdateFPS;
			counter = 0;
		}


		
			if(basicToScene.keyboard->getKeyDown(GLFW_KEY_ESCAPE)){
				m_gameOver = true;
			}
			glClearColor(0.1f,0.1f,0.1f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_DEPTH_BUFFER_BIT);

			//update
			basicToScene.mouse->Update();
			m_sceneHandler.Update((float)dt.dt());

			//render
			//shadows
			basicToScene.shadowMap->renderShadow();
			gfx.setDefaultViewPort();

			if(basicToScene.keyboard->getKeyDown('O')){
				l[0]->position = basicToScene.camera->getPosition();
				((SpotLight*)l[0])->rotation = basicToScene.camera->getRotation();
			}


			//real object
			glUseProgram(basicToScene.rm->getShaderProgram("defShaderProgram"));
			basicToScene.shadowMap->updateLightMatrices();
			m_sceneHandler.Render();

			imGuiManager.render();

			if(basicToScene.keyboard->getKeyReleased(GLFW_KEY_TAB)){
				basicToScene.mouse->stickMouse();
			}

			glfwSwapBuffers(gfx.getCurrentActiveWindow());
			basicToScene.keyboard->update();
			glfwPollEvents();
			gfx.UpdateWindows();
	}
}

void Engine::setUpDefaultShaders()
{
	unsigned int shadowVertex = basicToScene.rm->getShader("ShadowMapVertexShader.vert");
	unsigned int shadowPixel = basicToScene.rm->getShader("ShadowMapPixelShader.frag");
	basicToScene.shadowMap->addShaderProgram(basicToScene.rm->createShaderProgram("ShadowMapProgram", shadowVertex, shadowPixel));

	unsigned int tessellationVertex = basicToScene.rm->getShader("Tesselation.vert");
	unsigned int tessellationControl = basicToScene.rm->getShader("TessellationControlShader.tesc");
	unsigned int tessellationEvaluation = basicToScene.rm->getShader("TessellationEvaluationShader.tese");

	basicToScene.rm->createShaderProgram("DefTessellation", tessellationVertex, tessellationControl, tessellationEvaluation, basicToScene.rm->getShader("BasicPixelShader.frag"));

	unsigned int SkeletalAnimationVertex = basicToScene.rm->getShader("SkeletalAnimationVertexShader.vert");
	basicToScene.rm->createShaderProgram("DefSkeletalAnimation", SkeletalAnimationVertex, basicToScene.rm->getShader("BasicPixelShader.frag"));
}
