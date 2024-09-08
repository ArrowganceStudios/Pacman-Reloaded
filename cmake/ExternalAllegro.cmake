# Define the download URL and the output file paths
set(ALLEGRO_URL "https://www.nuget.org/api/v2/package/Allegro/5.2.9")
set(ALLEGRO_DEPS_URL "https://www.nuget.org/api/v2/package/AllegroDeps/1.15.0-nightly.20240817")
set(ALLEGRO_ZIP "${CMAKE_BINARY_DIR}/allegro.zip")
set(ALLEGRO_DEPS_ZIP "${CMAKE_BINARY_DIR}/allegro_deps.zip")
set(ALLEGRO_DIR "${CMAKE_BINARY_DIR}/allegro")

# Step 1: Download the Allegro5 zip file
if(NOT EXISTS ${ALLEGRO_ZIP})
  message(STATUS "Downloading Allegro5 binaries...")
  file(DOWNLOAD ${ALLEGRO_URL} ${ALLEGRO_ZIP} SHOW_PROGRESS)
endif()

# Step 1.5: Download the Allegro5 deps zip file
if(NOT EXISTS ${ALLEGRO_DEPS_ZIP})
  message(STATUS "Downloading Allegro5-deps binaries...")
  file(DOWNLOAD ${ALLEGRO_DEPS_URL} ${ALLEGRO_DEPS_ZIP} SHOW_PROGRESS)
endif()

# Step 2: Extract the ZIP file
if(NOT EXISTS ${ALLEGRO_DIR})
    message(STATUS "Extracting Allegro5 and deps binaries...")

    # Create the directory to extract files
    file(MAKE_DIRECTORY ${ALLEGRO_DIR})

    # Use execute_process to unzip allegro
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar x ${ALLEGRO_ZIP}
        RESULT_VARIABLE res WORKING_DIRECTORY ${ALLEGRO_DIR}
    )

    if(NOT res EQUAL "0")
        message(FATAL_ERROR "Failed to extract Allegro5 binaries!")
        file(REMOVE RECURSE ${ALLEGRO_DIR})
    endif()

    # Use execute_process to unzip allegro deps
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar x ${ALLEGRO_DEPS_ZIP}
        RESULT_VARIABLE res WORKING_DIRECTORY ${ALLEGRO_DIR}
    )

    if(NOT res EQUAL "0")
        message(FATAL_ERROR "Failed to extract Allegro5 binaries!")
        file(REMOVE RECURSE ${ALLEGRO_DIR})
    endif()
else()
    message(STATUS "Allegro5 binaries already extracted.")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH "x64")
else()
    set(ARCH "win32")
endif()

# Step 3: Set the CMake variables used by src/CMakeLists.txt
set(ALLEGRO_INCLUDES ${ALLEGRO_DIR}/build/native/include)
set(ALLEGRO_LIB_DIR ${ALLEGRO_DIR}/build/native/v${MSVC_TOOLSET_VERSION}/${ARCH}/deps/lib;
                    ${ALLEGRO_DIR}/build/native/v${MSVC_TOOLSET_VERSION}/${ARCH}/lib)

list(APPEND ALLEGRO_LIBS allegro)
list(APPEND ALLEGRO_LIBS allegro_primitives)
list(APPEND ALLEGRO_LIBS allegro_image)
list(APPEND ALLEGRO_LIBS allegro_font)
list(APPEND ALLEGRO_LIBS allegro_ttf)
list(APPEND ALLEGRO_LIBS allegro_audio)
list(APPEND ALLEGRO_LIBS allegro_acodec)

# Copy .dlls to the bin/ directory
file(INSTALL ${ALLEGRO_DIR}/build/native/v${MSVC_TOOLSET_VERSION}/${ARCH}/bin/ DESTINATION ${OUTPUT_BINARY_DIR})