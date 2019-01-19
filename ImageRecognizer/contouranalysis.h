#ifndef CONTOURANALYSIS_H
#define CONTOURANALYSIS_H

#include <QString>
#include <QLabel>
#include <opencv/cv.h>

class ContourAnalysis
{
public:
    explicit ContourAnalysis(const QString& fn);
    ContourAnalysis() = default;

    ~ContourAnalysis();

public:
    void run(const double minArea, const double maxArea, const bool limitAreas);
    void clear();
    void setFileName(const QString& fileName);
    void setCellsFoundLabel(QLabel* cellsFoundLabel);

    bool IsRunningAsService(const unsigned int pId);
private:
    QString fileName;
    QLabel* cellsFoundLabel = nullptr;
    IplImage* sourceImage = nullptr;
    IplImage* grayImage = nullptr;
    IplImage* binImage = nullptr;
};


#endif // CONTOURANALYSIS_H
