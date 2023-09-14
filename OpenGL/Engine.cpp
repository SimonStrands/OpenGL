#include "Engine.h"
#include "ErrorHelper.h"

Engine::Engine():
	m_sceneHandler(new TestScene()),
	m_gameOver(false)
{
	dt.restartClock();
	rm = new ResourceManager;
	mouse = new Mouse(gfx.getCurrentActiveWindow());
	keyboard = new Keyboard(gfx.getCurrentActiveWindow());
	m_sceneHandler.setResourceManager(rm);
	m_sceneHandler.setMouseandKeyboard(mouse, keyboard);
	m_sceneHandler.sceneInit();
	glUseProgram(rm->getShaderProgram("defShaderProgram"));
	//Graphics Creates Window on it's own first
}

Engine::~Engine()
{
	delete rm;
	delete mouse;
	delete keyboard;
}

void Engine::Run()
{
	while(!m_gameOver){
	
		dt.restartClock();
        #ifdef TurnOfWithWindow
		if(gfx.GetNrOfWindows() <= 0){
			m_gameOver = true;
			return;
		}
        #else
		    
        #endif // TurnOfWithWindow
		
			if(keyboard->getKeyDown(GLFW_KEY_ESCAPE)){
				m_gameOver = true;
			}
			glClearColor(0,0,0,255);
			glClear(GL_COLOR_BUFFER_BIT);
	
			mouse->Update();
			m_sceneHandler.Update(dt.dt());
			m_sceneHandler.Render();
	
			glfwSwapBuffers(gfx.getCurrentActiveWindow());
	
			glfwPollEvents();
			gfx.UpdateWindows();
	}
}