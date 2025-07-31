cmake_minimum_required(VERSION 3.16)

project(MiniVis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Vulkan REQUIRED)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appMiniVis
    main.cpp
    vulkantextureitem.cpp
    vulkantextureitem.h
)

target_link_libraries(appMiniVis PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

# Add the unified resource file with QML and shaders
qt_add_qml_module(appMiniVis
    URI MiniVis
    QML_FILES
        main.qml
    RESOURCES
        squircle.frag.spv
        squircle.vert.spv
    NO_RESOURCE_TARGET_PATH
    SOURCES
)
set_target_properties(appMiniVis PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMiniVis
    PRIVATE
    Qt6::Quick
    Vulkan::Vulkan
)

include(GNUInstallDirs)
install(TARGETS appMiniVis
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
