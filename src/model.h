#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QObject>

class Model : public QObject
{
    Q_OBJECT

private:
    Model() = default;

public:
    static Model& instance()
    {
        static Model s_m;
        return s_m;
    }

    bool parse(QString qsFile);

    int count() const
    {   return m_vValues.count(); }

    double value(int i) const
    {   return m_vValues[i]; }

    double median(bool& rbOK) const;

signals:
    void signalLoaded();

private:
    QVector<double> m_vValues;
};

#endif // MODEL_H
