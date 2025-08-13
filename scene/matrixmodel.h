#ifndef MATRIXMODEL_H
#define MATRIXMODEL_H

#include <QMatrix4x4>
#include <QObject>

class MatrixModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QMatrix4x4 matrix READ matrix WRITE setMatrix NOTIFY matrixChanged)

public:
    explicit MatrixModel(QMatrix4x4* matrix, QObject* parent = nullptr)
        : QObject(parent)
        , m_matrix(matrix)
    {
    }

    QMatrix4x4 matrix() const
    {
        return m_matrix ? *m_matrix: QMatrix4x4();
    }

    void setMatrix(const QMatrix4x4& matrix) {
        if (matrix != *m_matrix) {
            *m_matrix = matrix;
            emit matrixChanged();
        }
    }

    Q_INVOKABLE float element(int row, int column) const {
        if (!m_matrix || row < 0 || row >= 4 || column < 0 || column >= 4)
            return 0.0f;
        return (*m_matrix)(row, column);
    }

    Q_INVOKABLE void setElement(int row, int column, float value) {
        if (!m_matrix || row < 0 || row >= 4 || column < 0 || column >= 4)
            return;
        (*m_matrix)(row, column) = value;
        emit matrixChanged();
    }

signals:
    void matrixChanged();
private:
    QMatrix4x4* m_matrix;
};

#endif // MATRIXMODEL_H
