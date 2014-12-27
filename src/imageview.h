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
#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDropEvent>
class ImageView:public QGraphicsView
{
    Q_OBJECT
public:
     explicit  ImageView(QWidget *parent = 0);

signals:
     void sgdropEvent(QDropEvent*);
public slots:
    void dropEvent(QDropEvent* event);
    
};

#endif // IMAGEVIEW_H
