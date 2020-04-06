#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

#include "model.h"

bool Model::parse(QString qsFile)
{
    QFile f(qsFile);
    if (f.open(QFile::ReadOnly) == false) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();
    qDebug() << "doc" << doc.isNull() << f.readAll();
    if (doc.isNull() == true) {
        return false;
    }

    m_vValues.clear();
    QJsonArray arr = doc.array();
    //qDebug() << "Elements" << arr.count();
    for (int i = 0; i < arr.count(); ++i) {
        m_vValues << arr[i].toDouble();
    }
    qSort(m_vValues);
    //qDebug() << "Values" << m_vValues;

    emit signalLoaded();
}

double Model::median(bool& rbOK) const
{
    if (count() == 0) {
        rbOK = false;
        return 0.0;
    }

    rbOK = true;
    if (count() % 2 == 1) {
        return m_vValues[count() / 2];
    }   else {
        return (m_vValues[count() / 2] + m_vValues[count()/2 - 1])/2;
    }
}

