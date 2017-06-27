#include "Window.h"

#include "Core/Console/Console.h"

#include "Wrappers/OpenGL/GL.h"

#include "Systems/Camera/Camera.h"

#include "Debug/Profiler/Profiler.h"

std::size_t Window::_width (0);
std::size_t Window::_height (0);
std::string Window::_title ("");
bool Window::_fullscreen (true);

SDL_Window* Window::_window (nullptr);
SDL_GLContext Window::_glContext;

bool Window::Init (std::size_t width, std::size_t height, bool fullscreen, std::string title)
{
	_width = width; 
	_height = height; 
	_fullscreen = fullscreen;
	_title = title;

	/*
	 * Create Window with SDL so MUST include SDL_WINDOW_OPENGL to use OpenGL
	*/

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	unsigned int windowFlags = GetWindowFlags ();

	_window = SDL_CreateWindow (_title.c_str (), 0, 0, _width, _height, windowFlags);

	if (_window == nullptr) {
		Console::LogError ("Window \"" + title + "\" could not be initialized");

		return false;
	}

	/*
	 * Create an OpenGL context associated with the window.
	*/

	_glContext = SDL_GL_CreateContext(_window);

	GL::Viewport (0, 0, _width, _height);

	Window::UpdateCamera ();

	return true;
}

void Window::SwapBuffers ()
{
	PROFILER_LOGGER("Swap buffers")

	SDL_GL_SwapWindow(_window);
}

void Window::Resize (const glm::ivec2& dimensions)
{
	_width = (std::size_t)dimensions.x;
	_height = (std::size_t)dimensions.y;

	SDL_SetWindowSize (_window, _width, _height);

	GL::Viewport (0, 0, _width, _height);

	Window::UpdateCamera ();
}

void Window::Clear ()
{

}

void Window::Close ()
{
	/* 
	 * Once finished with OpenGL functions, the SDL_GLContext can be deleted.
	*/

	SDL_GL_DeleteContext(_glContext);

	SDL_DestroyWindow (_window);
}

/*
 * TODO: Rethink this
*/

void Window::UpdateCamera ()
{
	Camera::Main ()->SetAspect (1.0f * _width / _height);
}

std::size_t Window::GetWidth ()
{
	return _width;
}

std::size_t Window::GetHeight ()
{
	return _height;
}

std::string Window::GetTitle ()
{
	return _title;
}

unsigned int Window::GetWindowFlags ()
{
	unsigned int windowFlags = _fullscreen ? 
		SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE:
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
		
	return windowFlags;
}