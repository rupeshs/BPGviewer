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
#ifndef QBETTERPORTABLEGRAPHICS_H
#define QBETTERPORTABLEGRAPHICS_H

#include <QObject>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <getopt.h>
#include <inttypes.h>
#include <QImage>
#include <QByteArray>
#include <QImageReader>
#include <QDebug>
#include <QDesktopServices>
#include <QTimeLine>
#include <QMap>
extern "C" {
#include "libbpg/libbpg.h"
#include "libpng/include/png.h"
}

#define PNG_VERSION_INFO_ONLY
class QBetterPortableGraphics : public QObject
{
    Q_OBJECT
public:
    explicit QBetterPortableGraphics(QObject *parent = 0);
     bool openFile(QString filePath);
     inline int getWidth(){return _width;}
     inline int getHeight(){return _height;}
     inline QMap<QString, QString> GetBpgInfo(){return _mapInfo;}
     inline bool  isBPG(){return _isBPG;}
     void decodeBpg();

signals:
     void imageready(QString);
public slots:

private:
       const char* _fileName;
       QString _qfileName;
       int _width;
       int _height;
       BPGImageInfo *_bpgInfo;
       bool _isBPG;
       QMap<QString, QString> _mapInfo;
       bool ReadHeader();
};

#endif // QBETTERPORTABLEGRAPHICS_H
