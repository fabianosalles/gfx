# CMakeList.txt: projeto de CMake para doom-fire, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.
add_executable (doom-fire "main.cpp" "fx.h" "fx.cpp")
target_link_libraries(doom-fire PRIVATE raylib)
target_include_directories(doom-fire PRIVATE "${raygui_SOURCE_DIR}/src")

set_property(TARGET doom-fire PROPERTY CXX_STANDARD 23)
set_property(TARGET doom-fire PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET doom-fire PROPERTY CXX_EXTENSIONS OFF)

# TODO: Adicione testes e instale destinos, se necessário.

set(ASSETS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSETS_BINARY_DIR "$<TARGET_FILE_DIR:doom-fire>/assets")

add_custom_command(TARGET doom-fire POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:doom-fire>/assets"
)

