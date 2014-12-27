#ifndef IMAGESCENE_H
#define IMAGESCENE_H

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
#include <QWidget>
#include <QGraphicsScene>
#include <QDropEvent>
#include <QtGui>
class ImageScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ImageScene();

    
    bool event(QEvent* event)
      {
        return QObject::event(event);
      }

public slots:
    
};

#endif // IMAGESCENE_H
