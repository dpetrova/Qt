#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QRunnable>
#include <QPointF>
#include <QSize>
#include <QAtomicInteger>

#include "jobresult.h"

/**
A Job class producesa JobResult function containing result values.
In our project, a Job class generates values for one line of the complete picture.
For example, an image resolution of 800 x 600 requires 600 jobs, each one generating 800 values
*/

class Job :	public QObject, public QRunnable
{
    Q_OBJECT

public:
    Job(QObject *parent = 0);
    void run() override;

    void setPixelPositionY(int value);
    void setMoveOffset(const QPointF& value);
    void setScaleFactor(double value);
    void setAreaSize(const QSize& value);
    void setIterationMax(int value);

signals:
    void jobCompleted(JobResult jobResult); //emitted when the algorithm is over

public slots:
    void abort(); //allow us to stop the job updating the mIsAbort flag value

private:
    int mPixelPositionY; //picture height index
    QPointF mMoveOffset; //Mandelbrot origin offset (user can pan the picture, so the origin will not always be (0, 0))
    double mScaleFactor; //Mandelbrot scale value (user can zoom into the picture)
    QSize mAreaSize; //final picture size in a pixel
    int mIterationMax; //ount of iterations allowed to determine the Mandelbrot result for one pixel
    QAtomicInteger<bool> mAbort; //using an atomic variable is a fast way to safely update and access a variable from different threads
};

#endif // JOB_H
