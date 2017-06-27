#ifndef WINDOW_H
#define WINDOW_H

#include "Core/Singleton/Singleton.h"

#include <SDL2/SDL.h>
#include <string>

#include "Core/Math/glm/vec2.hpp"

class Window
{
private:
	static std::size_t _width;
	static std::size_t _height;
	static std::string _title;
	static bool _fullscreen;

	static SDL_Window* _window;
	static SDL_GLContext _glContext;

public:
	static bool Init (std::size_t width, std::size_t height, 
		bool fullscreen, std::string name);

	static void SwapBuffers ();
	static void Resize (const glm::ivec2&);
	static void SetFullscreen (bool fullscreen);

	static std::size_t GetWidth ();
	static std::size_t GetHeight ();
	static bool IsFullscreen ();
	static std::string GetTitle ();

	static void Clear ();
	static void Close ();
private:
	static unsigned int GetWindowFlags ();

	static void UpdateCamera ();
};

#endif