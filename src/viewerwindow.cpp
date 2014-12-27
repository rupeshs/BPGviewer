#include "viewerwindow.h"
#include "ui_viewerwindow.h"

ViewerWindow::ViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewerWindow)
{
    _isCmd=false;
    QCoreApplication::addLibraryPath(qApp->applicationDirPath()+"/imageformats");
    ui->setupUi(this);

    ui->mainToolBar->addAction(ui->actionZoom_In);
    ui->mainToolBar->addAction(ui->actionZoom_Out);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionClockwise);
    ui->mainToolBar->addAction(ui->actionCounter_clockwise);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionFile_Info);

    bpgFile=new QBetterPortableGraphics();
    QObject::connect(bpgFile,SIGNAL(imageready(QString)),this,SLOT(LoadImage(QString)));

    scene = new ImageScene();

    ui->graphicsView->setScene(scene);
    QObject::connect(ui->graphicsView,SIGNAL(sgdropEvent(QDropEvent*)),this,SLOT(dropEvent(QDropEvent*)));
    imgItem=scene->addPixmap(QPixmap(":/images/bpgviewer.png"));
    _numScheduledScalings=0;
    _scaleFactor = 1.1;
    _isFirst=true;

    if(qApp->arguments().count()>1)
    {  _isCmd=true;
        ShowImage(qApp->arguments().at(1));
    }
}

ViewerWindow::~ViewerWindow()
{
    delete ui;
}
void  ViewerWindow::wheelEvent ( QWheelEvent * event )
{

    ui->graphicsView->transformationAnchor();

    if (event->delta()>0){

        ui->graphicsView->scale(_scaleFactor, _scaleFactor);
    }
    else{
        ui->graphicsView->scale(1/_scaleFactor, 1/_scaleFactor);

    }

}
void ViewerWindow::scalingTime(qreal x)
{
    qreal factor = 1.0 + qreal(_numScheduledScalings) / 300.0;
    ui->graphicsView->scale(factor, factor);
}
void ViewerWindow::animFinished()
{
    if (_numScheduledScalings > 0)
        _numScheduledScalings--;
    else
        _numScheduledScalings++;
    sender()->~QObject();
}

void ViewerWindow::on_actionZoom_In_triggered()
{
    ui->graphicsView->scale(_scaleFactor, _scaleFactor);

}

void ViewerWindow::on_actionZoom_Out_triggered()
{
    ui->graphicsView->scale(1/_scaleFactor, 1/_scaleFactor);
}

void ViewerWindow::on_actionClockwise_triggered()
{
    ui->graphicsView->rotate(90);
}

void ViewerWindow::on_actionCounter_clockwise_triggered()
{
    ui->graphicsView->rotate(-90);
}

void ViewerWindow::on_actionAbout_triggered()
{
    abtDlg=new AboutDialog(this);
    abtDlg->show();
}
void ViewerWindow::dropEvent(QDropEvent *event)
{

    QList<QUrl> urlList;
    if (event->mimeData()->hasUrls())
        urlList = event->mimeData()->urls();

    for (int i = 0; i < urlList.count(); i++) {
        QString url = urlList.at(i).toLocalFile();
        if (urlList[i].isValid())
        {
            QFileInfo fi(url);
            if(fi.isFile())
            {
                //Check dropped file is a bpg or not
                if ( fi.suffix().toLower().contains("bpg"))
                {
                    ShowImage(url);
                }
            }
        }
    }

    event->acceptProposedAction();
}
void ViewerWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void ViewerWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();

}
void ViewerWindow::ShowImage(QString imgFile)
{

    ui->graphicsView->resetTransform();
    //view transformation to the identity matrix.
    bpgFile->openFile(imgFile);
    bpgFile->decodeBpg();

}
void ViewerWindow::LoadImage(QString path)
{
    scene->removeItem(imgItem);
    delete imgItem;

    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
    qDebug()<<QString::number(mainScreenSize.width());
    qDebug()<<QString::number(mainScreenSize.height());

    _isFirst=false;
    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
    dropShadowEffect->setBlurRadius(30);
    dropShadowEffect->setOffset(10);
    QImage ldImage(path );
    qDebug()<<QString::number(ldImage.width());
    if(mainScreenSize.width()<ldImage.width())
    {
        imgItem=scene->addPixmap(QPixmap::fromImage(ldImage));

        if (!_isCmd)
            ui->graphicsView->fitInView( imgItem->boundingRect(), Qt::KeepAspectRatio );
        else
            _isCmd=false;

    }
    else
    {
        if (_isCmd)
            _isCmd=false;
        imgItem=scene->addPixmap(QPixmap::fromImage(ldImage));
    }

    imgItem->setGraphicsEffect(dropShadowEffect);
    scene->setSceneRect(scene->itemsBoundingRect());
    QString infoStr;
    QMap<QString, QString> mapInfo=bpgFile->GetBpgInfo();
    if( bpgFile->GetBpgInfo().count()>0)
    {   infoStr=mapInfo["Width"]+" x "+
                mapInfo["Height"]+" | "+
                mapInfo["Color space"]+" | "+
                mapInfo["Bit depth"];
        ui->labelInfo->setText(infoStr);
    }
    else{
        ui->labelInfo->setText("");
    }
}

void ViewerWindow::on_actionOpen_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "", tr("Image Files (*.bpg)"));

    if(!fileName.isEmpty())
    {
        ShowImage(fileName);
    }

}

void ViewerWindow::on_actionFile_Info_triggered()
{
    QString bpgInfoStr;
    if (bpgFile->GetBpgInfo().count()>0)
    {
        QMessageBox msgInfoBox;
        msgInfoBox.setWindowTitle("BPG File Info...");

        QMapIterator<QString, QString> i(bpgFile->GetBpgInfo());
        while (i.hasNext()) {
            i.next();
            bpgInfoStr.append(i.key()).append(": ").append(i.value()).append("\t\n");

        }
        msgInfoBox.setText(bpgInfoStr);
        msgInfoBox.exec();
    }
}
void ViewerWindow::getMessage(QString msg)
{

    this->ShowImage(msg);
    this->setFocus(Qt::ActiveWindowFocusReason);
    this->activateWindow();
    this->raise();

}
