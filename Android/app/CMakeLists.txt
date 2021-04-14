# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Declares and names the project.
project("learnopengl")

# build native_app_glue as a static lib (Android includes it as source code only, must built into a .so lib)
add_library(app-glue STATIC
            ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
			
add_library(cpufeatures STATIC
            ${ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c)
			
# Build dependency lib to overwrite definitions for subsequent libs/cpp----------------------------//
add_library( # Sets the name of the library.
             dependency-lib

             # Sets the library as a shared library.
             STATIC
			
			 libs/Android_dep/Android_Dependencies.h
			 libs/Android_dep/Android_Dependencies.cpp
			 )
			 
target_include_directories(dependency-lib PRIVATE
							${ANDROID_NDK}/sources/android/cpufeatures
                           ${ANDROID_NDK}/sources/android/native_app_glue)
						   
target_link_libraries( # Specifies the target library.
                       dependency-lib			 
						app-glue
						cpufeatures
						android)
			
#add RUNTIME dependency files here for subsequent libs/cpp
SET(CMAKE_CXX_FLAGS "-include ../../../../libs/Android_dep/Android_Dependencies.h")
SET(CMAKE_C_FLAGS "-include ../../../../libs/Android_dep/Android_Dependencies.h")
			
# build the ndk-helper library--------------------------------------------------------------------//
set(ndk_helper_dir libs/ndk_helper)	#start location is location of CMakeLists.txt
add_subdirectory(${ndk_helper_dir} ndk_helper)

# build the native library--------------------------------------------------------------------//			 
ADD_DEFINITIONS (-DANDROID_VERSION)
ADD_DEFINITIONS (-DPLATFORM_ANDROID=1)
# output for diff. mobile CPUs
ADD_DEFINITIONS (-DANDROID_ABI=arm64-v8a)
# ADD_DEFINITIONS (-DANDROID_ABI=x86_64)
# ADD_DEFINITIONS (-DANDROID_ABI=armeabi-v7a)
# ADD_DEFINITIONS (-DANDROID_ABI=x86)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
			 # shared by all platforms (with defines to differentiate btw platforms)
			 ../../shared/Source/Utility.cpp
			 ../../shared/Source/Utility.h
			 
			 # platform agnostic (utility headers)
			 libs/STB/stb_image.h
			 
			 # platform agnostic
			 ../../shared/Source/camera/Camera.cpp
			 ../../shared/Source/camera/Camera.h
			 ../../shared/Source/engine/Engine.cpp
			 ../../shared/Source/engine/Engine.h
			 ../../shared/Source/material/Material.cpp
			 ../../shared/Source/material/Material.h
			 ../../shared/Source/material/MaterialBuilder.cpp
			 ../../shared/Source/material/MaterialBuilder.h
			 ../../shared/Source/material/MaterialColor.cpp
			 ../../shared/Source/material/MaterialColor.h
			 ../../shared/Source/material/MaterialLightMap.cpp
			 ../../shared/Source/material/MaterialLightMap.h
			 ../../shared/Source/mesh/Mesh.cpp
			 ../../shared/Source/mesh/Mesh.h
			 ../../shared/Source/mesh/MeshBuilder.cpp
			 ../../shared/Source/mesh/MeshBuilder.h
			 ../../shared/Source/object/GameObject.cpp
			 ../../shared/Source/object/GameObject.h
			 ../../shared/Source/scenes/Scene.cpp
			 ../../shared/Source/scenes/Scene.h
			 ../../shared/Source/scenes/SceneLightMap.cpp
			 ../../shared/Source/scenes/SceneLightMap.h
			 ../../shared/Source/shader/Shader.cpp
			 ../../shared/Source/shader/Shader.h
			 ../../shared/Source/shader/ShaderManager.cpp
			 ../../shared/Source/shader/ShaderManager.h
			 ../../shared/Source/texture/TextureBuilder.cpp
			 ../../shared/Source/texture/TextureBuilder.h
			 
			 # Android dependent files
			 src/main/cpp/AndroidUtils.cpp
			 src/main/cpp/AndroidUtils.h
			 src/main/cpp/OSEngine.cpp
			 src/main/cpp/OSEngine.h
			 src/main/cpp/stb_image.cpp
			 src/main/cpp/Main.cpp
			)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )
			  
# we are building everything into .so libs, so just like in VS we need to target the include directories
# of said libs' header files
target_include_directories(native-lib PRIVATE
                           ${ANDROID_NDK}/sources/android/cpufeatures
                           ${ANDROID_NDK}/sources/android/native_app_glue
						   ../../shared/Source
						   ../../shared/Includes
						   ../../shared/Includes/glm
						   libs
						   ${ndk_helper_dir}
						   )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
					   android
                       cpufeatures
                       app-glue
					   atomic
                       EGL
                       GLESv3
					   ndk-helper
					   dependency-lib
                       ${log-lib} )	# log-lib is special, others no need ${}