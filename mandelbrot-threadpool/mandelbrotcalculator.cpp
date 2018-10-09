#include "mandelbrotcalculator.h"

#include <QDebug>
#include <QThreadPool>

#include "job.h"

const int JOB_RESULT_THRESHOLD = 10;

MandelbrotCalculator::MandelbrotCalculator(QObject *parent)
    : QObject(parent),
      mMoveOffset(0.0, 0.0),
      mScaleFactor(0.005),
      mAreaSize(0, 0),
      mIterationMax(10),
      mReceivedJobResults(0),
      mJobResults(),
      mTimer()
{
}

void MandelbrotCalculator::generatePicture(QSize areaSize, QPointF moveOffset, double scaleFactor, int iterationMax)
{
    if (areaSize.isEmpty()) { //If the areaSize dimension is 0x0, we have nothing to do
        return;
    }

    mTimer.start(); //start mTimer to track the whole generation duration
    clearJobs(); //first cancel existing jobs

    //set our member variables
    mAreaSize = areaSize;
    mMoveOffset = moveOffset;
    mScaleFactor = scaleFactor;
    mIterationMax = iterationMax;

    //create a new Job class for each vertical picture line
    for(int pixelPositionY = 0; pixelPositionY < mAreaSize.height(); pixelPositionY++) {
        //QThreadPool::globalInstance() is a static function that gives us the optimal global thread pool depending on the core count of our CPU
        //Even if we call start() for all the Job classes, only the firsts starts immediately. Others are added to the pool queue waiting for an available thread
        QThreadPool::globalInstance()->start(createJob(pixelPositionY)); //thread pool takes ownership of the job (it will be deleted by the thread pool when Job::run() ends)
    }
}

void MandelbrotCalculator::process(JobResult jobResult)
{
    //check is that the current JobResult is still valid with the current input data
    if (jobResult.areaSize != mAreaSize || jobResult.moveOffset != mMoveOffset || jobResult.scaleFactor != mScaleFactor) {
        return;
    }

    mReceivedJobResults++; //increment the mReceivedJobResults counter
    mJobResults.append(jobResult); //append this JobResult to our member queue

    //calculator waits to get JOB_RESULT_THRESHOLD (that is, 10) results before dispatching them by emitting the pictureLinesGenerated() signal
    if (mJobResults.size() >= JOB_RESULT_THRESHOLD || mReceivedJobResults == mAreaSize.height()) {
        emit pictureLinesGenerated(mJobResults);
        mJobResults.clear();
    }

    if (mReceivedJobResults == mAreaSize.height()) {
        qDebug() << "Generated in " << mTimer.elapsed() << " ms";
    }
}

Job* MandelbrotCalculator::createJob(int pixelPositionY)
{
    Job* job = new Job(); //jobs are allocated on the heap

    job->setPixelPositionY(pixelPositionY);
    job->setMoveOffset(mMoveOffset);
    job->setScaleFactor(mScaleFactor);
    job->setAreaSize(mAreaSize);
    job->setIterationMax(mIterationMax);

    connect(this, &MandelbrotCalculator::abortAllJobs, job, &Job::abort);

    connect(job, &Job::jobCompleted, this, &MandelbrotCalculator::process);

    return job; //return Job pointer
}

void MandelbrotCalculator::clearJobs()
{
    mReceivedJobResults = 0; //reset counter
    emit abortAllJobs(); //emit signal to abort all active jobs
    QThreadPool::globalInstance()->clear(); //remove queued jobs waiting for an available thread in the thread pool
}
