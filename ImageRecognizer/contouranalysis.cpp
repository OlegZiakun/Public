#include "contouranalysis.h"
#include <opencv/highgui.h>

#include <QFileInfo>
#include <QDir>
#include <QPixmap>

ContourAnalysis::ContourAnalysis(const QString &fn)
    : fileName(fn)
{
}

ContourAnalysis::~ContourAnalysis()
{
    clear();
}

void ContourAnalysis::run(const double minArea, const double maxArea, const bool limitAreas)
{
    if(sourceImage)
        clear();

    sourceImage = cvLoadImage(fileName.toStdString().c_str(), 1);

    if(!sourceImage)
        return;

    const CvSize imageSize = cvGetSize(sourceImage);
    const int depth = IPL_DEPTH_8U;
    const int channels = 1;

    grayImage = cvCreateImage(imageSize, depth, channels);
    binImage = cvCreateImage(imageSize, depth, channels);

    cvCvtColor(sourceImage, grayImage, CV_RGB2GRAY);
    cvInRangeS(grayImage, cvScalar(40), cvScalar(150), binImage);

    CvMemStorage* storage = cvCreateMemStorage();
    CvSeq* contours;

    const int contoursCount = cvFindContours(binImage, storage, &contours);
    int numOfCellsFound = 0;

    for(CvSeq* contour = contours; contour; contour = contour->h_next)
    {
        const double area = fabs(cvContourArea(contour));

        if(limitAreas)
        {
            if(area >= minArea && area <= maxArea)
            {
                // qDebug() << "area" << area;
                ++numOfCellsFound;
            }
        }
        else
            ++numOfCellsFound;
    }


    if(cellsFoundLabel)
        cellsFoundLabel->setText(QString("Cells found: ") + QString::number(numOfCellsFound));

    const QFileInfo fileInfo(fileName);
    const QString binFileName = QDir::toNativeSeparators(fileInfo.path() + "/" + fileInfo.baseName()  + "-binary." + fileInfo.suffix());

    cvSaveImage(binFileName.toStdString().c_str(), binImage);
}

void ContourAnalysis::clear()
{
    cvReleaseImage(&sourceImage);
    cvReleaseImage(&grayImage);
    cvReleaseImage(&binImage);
}

void ContourAnalysis::setFileName(const QString &fileName)
{
    this->fileName = fileName;
}

void ContourAnalysis::setCellsFoundLabel(QLabel *cellsFoundLabel)
{
    this->cellsFoundLabel = cellsFoundLabel;
}
