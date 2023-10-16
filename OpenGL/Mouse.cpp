#include "Mouse.h"
#include <iostream>

Mouse::Mouse(GLFWwindow* wnd):
mouseDelta(0,0),
scrollDelta(0),
lastScroll(0)
{
    mouseStuck = true;
    this->wnd = wnd;
    glfwSetCursorPos(this->wnd, (double)(1024/2), (double)(768/2));
    //glfwSetScrollCallback(this->wnd, [](GLFWwindow* window, double xoffset, double yoffset) {
    //        // Call the member function to handle the scroll event
    //        instance().scroll_callBack(xoffset, yoffset);
    //    });
}

void Mouse::Update()
{
    if(mouseStuck){
        double xpos, ypos;
        glfwGetCursorPos(this->wnd, &xpos, &ypos);
        mouseDelta.x = (float)xpos - (1024.f/2.f);
        mouseDelta.y = (float)ypos - (768.f/2.f);
        glfwSetCursorPos(this->wnd, (double)(1024/2), (double)(768/2));
    }
    else{
        mouseDelta = glm::vec2(0,0);
    }
    lastScroll = scrollDelta;
}

double Mouse::getScrollDelta()
{
    return scrollDelta - lastScroll;
}

glm::vec2 Mouse::getMouseDelta() const
{
    return mouseDelta;
}

void Mouse::hideMouseCursor(bool hide)
{
}

void Mouse::stickMouse()
{
    glfwSetCursorPos(this->wnd, (double)(1024/2), (double)(768/2));
    mouseStuck = !mouseStuck;
}

Mouse& Mouse::instance(){
		static Mouse mouse(nullptr);
		return mouse;
	}

void Mouse::scroll_callBack(double xoffset, double yoffset)
{
    scrollDelta += yoffset;
}
