# Computer graphics cross-platform project
Attempt at developing a proof-of-concept rendering engine that runs on Windows, Android and web.

Core logic (physics, gameplay etc) is platform agnostic. Platform specific runner code and utilities (windows setup, main loop, file handling, I/O etc) calls and executes core logic.

Framework will be used for upcoming CG projects (thinking of a voxel engine).
## Windows
GLFW3 and GLAD with OpenGL 4.6.
## Android
Android NDK to bound and run native code. JNI and OpenGL ES 3.0.
## Web
Emscripten to complile native code to WebAssembly compatible with web major browsers. GLFW3 and WebGL 2.0.
