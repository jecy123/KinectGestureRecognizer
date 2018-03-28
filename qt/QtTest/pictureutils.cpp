#include "pictureutils.h"
#include <QDirIterator>

PictureUtils::PictureUtils()
{
}

PictureUtils::PictureUtils(QString picDir)
{
    qDebug() << picDir;
    if(picDir.endsWith('\\') || picDir.endsWith('/'))
    {
        this->parentDir = picDir.left(picDir.length() - 1);
    }else
    {
        this->parentDir = picDir;
    }
    QDirIterator it(picDir,QDir::Files);
    while(it.hasNext())
    {
        QString name = it.next();
        QFileInfo info(name);
        if(info.suffix() == "jpg" ||info.suffix() == "bmp" ||info.suffix() == "png")
        {
            this->filePaths.append(name);
        }
    }
}

PictureUtils::~PictureUtils()
{
}

QList<QPixmap> & PictureUtils::loadPictures()
{
    foreach (QString name, this->filePaths)
    {
        qDebug()<<name;
        QPixmap px;
        px.load(name);
        this->pixmaps.append(px);
    }
    return pixmaps;
}

QList<QImage> & PictureUtils::loadImages()
{
    foreach (QString name, this->filePaths)
    {
        QImage image;
        image.load(name);
        this->images.append(image);
    }
    return images;

}

QList<QString> & PictureUtils::getFilePaths()
{
    return this->filePaths;
}

QString PictureUtils::toString()
{
    return "";
}
