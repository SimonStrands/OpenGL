#pragma once
#include "Keyboard.h"

class Mouse{
public:
	enum MouseButton{
		LEFT,
		MIDDLE,
		RIGHT
	};
	Mouse(GLFWwindow* wnd);
	void Update();
	double getScrollDelta();
	glm::vec2 getMouseDelta() const;
	void hideMouseCursor(bool hide);
	void stickMouse();
private:
	static Mouse& instance();
	void scroll_callBack(double xoffset, double yoffset);
	GLFWwindow* wnd;
	glm::vec2 mouseDelta;
	double scrollDelta;
	double lastScroll;
	bool mouseStuck;
};