#include "Controller.h"

bool processInput(SDL_Event& e, float& deltaTime, glm::vec3& cameraPos,
	glm::vec3& cameraFront, glm::vec3& cameraUp)
{
	if( e.type == SDL_QUIT ) return true;

	//float cameraSpeed{ static_cast<float>( 2.5 * deltaTime ) };

	//switch( e.key.keysym.sym )
	//{
	//case SDLK_ESCAPE:
	//	e.type = SDL_QUIT;
	//	return true;

	//case SDLK_w:
	//	cameraPos += cameraSpeed * cameraFront;
	//	break;
	//	//return false;
	//case SDLK_s:
	//	cameraPos -= cameraSpeed * cameraFront;
	//	break;
	//	//return false;

	//case SDLK_a:
	//	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//	break;
	//	//return false;

	//case SDLK_d:
	//	break;
	//	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//	//return false;

	//}

	else if( e.type == SDL_KEYDOWN )
	{
		//Adjust the velocity
		if( e.key.keysym.sym == SDLK_ESCAPE ) {
			e.type = SDL_QUIT;
			return true;
		}
		float cameraSpeed = static_cast<float>( 2.5 * deltaTime );
		if( e.key.keysym.sym == SDLK_w )
			cameraPos += cameraSpeed * cameraFront;
		if( e.key.keysym.sym == SDLK_s )			
			cameraPos -= cameraSpeed * cameraFront;
		if( e.key.keysym.sym == SDLK_a )
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if( e.key.keysym.sym == SDLK_d )
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		return false;
	}
	return false;
}
