# reference : http://blog.hwrd.me/2014/05/07/beginning-opengl-development-on-os-x/

# GLFW is a windowing manager for OpenGL. Makes things easier when working with windows, as well as input via keyboard or mouse.
# GLFW is in homebrew/versions so we'll have to tap that to be able to install.
brew tap homebrew/versions
brew install glfw3
 
# GLEW offers bindings for your OS so that you don't have to call some OS specific OpenGL calls.
brew install glew
