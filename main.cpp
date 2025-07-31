#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QVulkanInstance>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickWindow::setGraphicsApi(QSGRendererInterface::Vulkan);
    // Create a Vulkan instance
    QVulkanInstance vulkanInstance;
#ifdef QT_DEBUG
    vulkanInstance.setLayers({ "VK_LAYER_KHRONOS_validation", "VK_KHR_dynamic_renderinge" });
#endif
    vulkanInstance.setApiVersion(QVersionNumber(1, 3, 0));

    if (!vulkanInstance.create()) {
        qFatal("Failed to create Vulkan instance");
    }

    QQuickView view;
    view.setVulkanInstance(&vulkanInstance);
    view.setSource(QUrl("qrc:/main.qml"));
    view.resize(1920, 1080);
    view.show();

    return app.exec();
}
