#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>

#include "model.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(1024, 768);
    createMenu();
    buildCentralWidget();

    connect(&Model::instance(), SIGNAL(signalLoaded()), this, SLOT(updateValues()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::load()
{
    QString qsFile = QFileDialog::getOpenFileName(this, tr("Select file"), ".");
    if (qsFile.isEmpty() == false) {
        Model::instance().parse(qsFile);
    }
}

void MainWindow::createMenu()
{
    QMenu* pMenu = new QMenu(tr("File"));
    pMenu->addAction(tr("Load"), this, SLOT(load()));

    menuBar()->addMenu(pMenu);
}

void MainWindow::buildCentralWidget()
{
    QWidget* pW = new QWidget;
    QHBoxLayout* pLayout = new QHBoxLayout(pW);
    m_pTE = new QTextEdit(pW);
    m_pLE = new QLineEdit(pW);

    pLayout->addWidget(m_pTE);
    pLayout->addWidget(m_pLE, Qt::AlignLeft | Qt::AlignTop);
    pLayout->setStretch(0, 3);
    pLayout->setStretch(1, 1);

    setCentralWidget(pW);
}

void MainWindow::updateValues()
{
    m_pTE->clear();
    Model& rM = Model::instance();
    QString qsText;
    int iBegin = -1;
    int iEnd = -1;

    int iN = rM.count();
    for (int i = 0; i < iN; ++i) {
        if ((iN % 2) == 0) {
            if (i == iN/2 - 1) {
                iBegin = qsText.length();
            }
        }   else {
            if (i == iN/2) {
                iBegin = qsText.length();
            }
        }
        qsText += QString::number(rM.value(i), 'f') + "\n";
        if (i == iN/2) {
            iEnd = qsText.length();
        }
    }

    m_pTE->setText(qsText);
    bool bOK;
    double dMedian = rM.median(bOK);
    if (bOK == true) {
        m_pLE->setText(QString::number(dMedian, 'f'));
    }   else {
        m_pLE->clear();
    }

    qDebug() << "BE" << iBegin << iEnd;

    if ((iBegin >= 0) && (iEnd >= 0)) {
        QTextCharFormat fmt;
        fmt.setBackground(Qt::green);

        QTextCursor cursor(m_pTE->document());
        cursor.setPosition(iBegin, QTextCursor::MoveAnchor);
        cursor.setPosition(iEnd, QTextCursor::KeepAnchor);
        cursor.setCharFormat(fmt);
    }
}

