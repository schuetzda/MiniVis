#include <QGuiApplication>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QVulkanInstance>
#include <QQmlContext>
#include <QDir>
#include <QDebug>
#include <ecs/Registry.h>
#include "scene/scenetreemodel.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQuickWindow::setGraphicsApi(QSGRendererInterface::Vulkan);
    // Create a Vulkan instance
    QVulkanInstance vulkanInstance;

#ifdef QT_DEBUG
    //vulkanInstance.setLayers({ "VK_LAYER_KHRONOS_validation" });
#endif

    vulkanInstance.setApiVersion(QVersionNumber(1, 4, 0));
    if (!vulkanInstance.create()) {
        qFatal("Failed to create Vulkan instance");
    }

    mini::Registry registry;
    mini::SceneTreeModel model(registry);

    QQuickView view;
    view.setVulkanInstance(&vulkanInstance);
    view.rootContext()->setContextProperty("sceneTreeModel", &model);
    view.rootContext()->setContextProperty("ecsRegistry", &registry);
    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.resize(1920, 1080);
    view.show();

    return app.exec();
}
