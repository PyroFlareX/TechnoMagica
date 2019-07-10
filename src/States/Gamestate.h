#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Basestate.h"
#include "../World/World.h"
#include "../Player.h"
#include "../Application.h"

#include "../Util/Input.h"

class GameState : public Basestate
{
public:
    GameState();

    bool input(Application& app) override;
    void update(sf::RenderWindow* window, float dt) override;
	void lateUpdate(Camera* cam) override;
	void render(Renderer* renderer) override;

	void tryPause();

    ~GameState() override;
protected:


private:
	bool isColliding(sf::Vector2f playerPos);

	bool isPaused;
	bool TryPause;
	
	Input::Inputs vInput;
	glm::vec3 momentum = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
};

#endif // GAMESTATE_H
