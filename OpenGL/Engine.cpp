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
	float currentTimeToUpdateFPS = 0;
	float TimeToUpdateFPS = 0.3f;
	uint32_t counter = 0;
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
	uint32_t shadowVertex = basicToScene.rm->getShader("ShadowMapVertexShader.vert");
	uint32_t shadowPixel = basicToScene.rm->getShader("ShadowMapPixelShader.frag");
	basicToScene.shadowMap->addShaderProgram(basicToScene.rm->createShaderProgram("ShadowMapProgram", shadowVertex, shadowPixel));

	uint32_t tessellationVertex = basicToScene.rm->getShader("Tesselation.vert");
	uint32_t tessellationControl = basicToScene.rm->getShader("TessellationControlShader.tesc");
	uint32_t tessellationEvaluation = basicToScene.rm->getShader("TessellationEvaluationShader.tese");

	basicToScene.rm->createShaderProgram("DefTessellation", tessellationVertex, tessellationControl, tessellationEvaluation, basicToScene.rm->getShader("BasicPixelShader.frag"));

	uint32_t SkeletalAnimationVertex = basicToScene.rm->getShader("SkeletalAnimationVertexShader.vert");
	basicToScene.rm->createShaderProgram("DefSkeletalAnimation", SkeletalAnimationVertex, basicToScene.rm->getShader("BasicPixelShader.frag"));
}
