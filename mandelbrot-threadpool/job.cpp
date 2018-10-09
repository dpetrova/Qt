#include "Job.h"

Job::Job(QObject* parent) :
    QObject(parent),
    mAbort(false),
    mPixelPositionY(0),
    mMoveOffset(0.0, 0.0),
    mScaleFactor(0.0),
    mAreaSize(0, 0),
    mIterationMax(1)
{
}


void Job::run()
{
    //initialize a JobResult variable
    JobResult jobResult(mAreaSize.width());
    jobResult.areaSize = mAreaSize;
    jobResult.pixelPositionY = mPixelPositionY;
    jobResult.moveOffset = mMoveOffset;
    jobResult.scaleFactor = mScaleFactor;

    /* Mandelbrot algorithm */
    double imageHalfWidth = mAreaSize.width() / 2.0;
    double imageHalfHeight = mAreaSize.height() / 2.0;

    //iterates over all x positions of pixels over one line
    for (int imageX = 0; imageX < mAreaSize.width(); ++imageX) {
        int iteration = 0;
        //pixel position is converted into complex plane coordinates
        double x0 = (imageX - imageHalfWidth) * mScaleFactor + mMoveOffset.x();
        double y0 = (mPixelPositionY - imageHalfHeight) * mScaleFactor - mMoveOffset.y();
        double x = 0.0;
        double y = 0.0;

        do {
            if (mAbort.load()) { //atomic read (if the return value is true, the algorithm is aborted and nothing is emitted)
                return;
            }

            double nextX = (x * x) - (y * y) + x0;
            y = 2.0 * x * y + y0;
            x = nextX;
            iteration++;

        } while(iteration < mIterationMax && (x * x) + (y * y) < 4.0); //if the trial count exceeds the maximum authorized iteration, the algorithm ends

        //for each pixel, the iteration count is stored in values of JobResult
        jobResult.values[imageX] = iteration;
    }

    //signal is emitted with result values of this algorithm
    emit jobCompleted(jobResult);
}

void Job::setPixelPositionY(int value)
{
    mPixelPositionY = value;
}

void Job::setMoveOffset(const QPointF& value)
{
    mMoveOffset = value;
}

void Job::setScaleFactor(double value)
{
    mScaleFactor = value;
}

void Job::setAreaSize(const QSize& value)
{
    mAreaSize = value;
}

void Job::setIterationMax(int value)
{
    mIterationMax = value;
}

void Job::abort()
{
    //atomic write of the value
    //atomic mechanism ensures that we can call abort() from multiple threads without disrupting the mAbort read in the run() function
    mAbort.store(true);
}
