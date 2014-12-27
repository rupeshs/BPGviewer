/*
    BPGviewer, BPG image viewer

    Copyright (C) 2014 Rupesh Sreeraman

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H

#include <QMainWindow>
#include <qbetterportablegraphics.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QWheelEvent>
#include <QDesktopServices>
#include <QPropertyAnimation>
#include <aboutdialog.h>
#include <QUrl>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QPointer>
#include <imagescene.h>
#include <QDesktopWidget>
#include <QDebug>

namespace Ui {
class ViewerWindow;
}

class ViewerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ViewerWindow(QWidget *parent = 0);
    ~ViewerWindow();
    void  wheelEvent ( QWheelEvent * event );
    
private:
    Ui::ViewerWindow *ui;
    QBetterPortableGraphics *bpgFile;
    QGraphicsItem *imgItem;
    ImageScene *scene ;
    int _numScheduledScalings;
    double _scaleFactor;
    AboutDialog *abtDlg;
    bool _isFirst;
    bool _isCmd;


public slots:
    void animFinished();
    void scalingTime(qreal x);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void ShowImage(QString imgFile);
    void LoadImage(QString path);
    void getMessage(QString msg);



private slots:
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionClockwise_triggered();
    void on_actionCounter_clockwise_triggered();
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_actionFile_Info_triggered();
};

#endif // VIEWERWINDOW_H
