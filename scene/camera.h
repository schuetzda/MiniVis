#ifndef CAMERA_H
#define CAMERA_H

#include <qmatrix4x4.h>


class QuaternionCamera
{
public:
    QuaternionCamera() = default;
    QMatrix4x4 getView() {
        QMatrix4x4 identity;
        identity.setToIdentity();
        return identity;
    }
    QMatrix4x4 getProjection() {
        QMatrix4x4 identity;
        identity.setToIdentity();
        return identity;
    }
    QMatrix4x4 getViewProjection() {
        QMatrix4x4 identity;
        identity.setToIdentity();
        return identity;
    }
};

#endif // CAMERA_H
