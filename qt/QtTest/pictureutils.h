#ifndef PICTUREUTILS_H
#define PICTUREUTILS_H

#include <QString>
#include <QList>
#include <QPixmap>
#include <QDebug>
#include <QImage>

class PictureUtils
{
public:
    PictureUtils();
    PictureUtils(QString picDir);
    ~PictureUtils();

    QList<QPixmap> & loadPictures();
    QList<QImage> & loadImages();
    QList<QString> & getFilePaths();
    QString toString();
private:
    QList<QImage> images;
    QList<QString> filePaths;
    QList<QPixmap> pixmaps;
    QString parentDir;
};

#endif // PICTUREUTILS_H
