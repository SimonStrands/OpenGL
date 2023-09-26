#include "ImGuiManager.h"

ImGuiManager::ImGuiManager()
{
	Image = 0;
}

void ImGuiManager::init()
{

}

void ImGuiManager::render()
{
	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
	
	renderGameObject();
	renderTexture();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::addGameObject(GameObject* gameObject, std::string name)
{
	if(name == ""){
		name = std::to_string(gameObjects.size());
	}
	gameObjects.push_back(std::pair<GameObject*, std::string>(gameObject, name));
}

void ImGuiManager::setTexture(unsigned int buffer, glm::vec2 size)
{
	Image = buffer;
	textureWidthHeight = size;
}

void ImGuiManager::renderGameObject()
{
	static const char* current_item = NULL;
	static int sItem = -1;
	
	if(ImGui::BeginCombo("GameObjects", current_item)){
		for(int i = 0; i < gameObjects.size(); i++){
			bool is_selcted = (current_item == gameObjects[i].second.c_str());
			if(ImGui::Selectable(gameObjects[i].second.c_str(), is_selcted)){
				current_item = gameObjects[i].second.c_str();
				sItem = i;
			}
			if(is_selcted){
				sItem = i;
			}
		}
	ImGui::EndCombo();
	}
	if(sItem > -1){
		Transform* transform = (Transform*)gameObjects[sItem].first->getComponent("Transform");
		ImGui::Text("Position");
		ImGui::SliderFloat("x##Position", &transform->position.x, -100, 100);
		ImGui::SliderFloat("y##Position", &transform->position.y, -100, 100);
		ImGui::SliderFloat("z##Position", &transform->position.z, -100, 100);
		ImGui::Text("Rotation");
		ImGui::SliderFloat("x##Rotation", &transform->rotation.x, -10, 10);
		ImGui::SliderFloat("y##Rotation", &transform->rotation.y, -10, 10);
		ImGui::SliderFloat("z##Rotation", &transform->rotation.z, -10, 10);
		ImGui::Text("Scale");
		ImGui::SliderFloat("x##Scale", &transform->scale.x, 0, 20);
		ImGui::SliderFloat("y##Scale", &transform->scale.y, 0, 20);
		ImGui::SliderFloat("z##Scale", &transform->scale.z, 0, 20);
	}
}

void ImGuiManager::renderTexture()
{
	if(Image != 0){
		ImGui::Begin("OpenGL Texture Text");
		ImGui::Text("pointer = %p", Image);
		ImGui::Text("size = %d x %d", textureWidthHeight.x, textureWidthHeight.y);
		ImGui::Image((void*)(intptr_t)Image, ImVec2(textureWidthHeight.x, textureWidthHeight.y));
		ImGui::End();
	}
}
