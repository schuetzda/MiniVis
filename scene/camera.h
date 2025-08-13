#ifndef CAMERA_H
#define CAMERA_H
#include <qmatrix4x4.h>
#include <QtMath>

class QuaternionCamera {
public:
    QuaternionCamera(float aspectRatio = 0.6, float fovY = qDegreesToRadians(45.f), float zNear = 0.1f, float zFar = 500.f) {
        view.setToIdentity();
        const float f = 1.f / qTan(fovY/ 2.f);
        projection = QMatrix4x4(
            f/ aspectRatio, 0.f, 0.f, 0.f,
            0.f, f, 0.f, 0.f,
            0.f, 0.f, -(zFar + zNear) / (zFar - zNear), -2 * zFar * zNear / (zFar - zNear),
            0.f, 0.f, -1.f, 0.f);
    }
    QMatrix4x4* getViewPtr()
    {
        return &view;
    }
    QMatrix4x4 getProjection()
    {
        QMatrix4x4 identity;
        identity.setToIdentity();
        return identity;
    }
    QMatrix4x4 getViewProjection()
    {
        QMatrix4x4 identity;
        identity.setToIdentity();
        return identity;
    }

private:
    QMatrix4x4 view;
    QMatrix4x4 projection;
};

#endif // CAMERA_H
