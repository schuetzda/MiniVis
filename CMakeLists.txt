cmake_minimum_required(VERSION 3.16)

project(MiniVis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Svg)
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
    RESOURCES scene/icons/camera.png scene/icons/light.png scene/icons/model.png
    NO_RESOURCE_TARGET_PATH
    SOURCES renderer/vulkanrenderer.h renderer/vulkanrenderer.cpp
    SOURCES renderer/framegraph/framegraph.h renderer/framegraph/framegraphbuilder.h
    SOURCES util/stringviewhash.h
    SOURCES ecs/componenttable.h ecs/componentview.h ecs/registry.h ecs/sparseset.h ecs/typeidgenerator.h
    SOURCES renderer/types/rendererfactory.h renderer/types/rendercycle.h
    SOURCES renderer/types/simpleforward/simpleforwardrenderer.h
    SOURCES renderer/wrapper/pipeline.h
    SOURCES renderer/framegraph/rendervalues.h
    SOURCES scene/scenegraph.h
    SOURCES scene/camera.h
    QML_FILES scene/SceneView.qml
    SOURCES scene/scenetreemodel.h scene/scenetreemodel.cpp
    QML_FILES scene/Vector3InputForm.qml
    QML_FILES scene/DoubleSpinBox.qml
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
target_link_libraries(appMiniVis PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appMiniVis
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
