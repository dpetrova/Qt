#include "mandelbrotwidget.h"

#include <QResizeEvent>
#include <QImage>
#include <QPainter>
#include <QtMath>

const int ITERATION_MAX = 4000;
const double DEFAULT_SCALE = 0.005;
const double DEFAULT_OFFSET_X = -0.74364390249094747;
const double DEFAULT_OFFSET_Y = 0.13182589977450967;

MandelbrotWidget::MandelbrotWidget(QWidget *parent) :
    QWidget(parent),
    mMandelbrotCalculator(),
    mThreadCalculator(this),
    mScaleFactor(DEFAULT_SCALE),
    mLastMouseMovePosition(),
    mMoveOffset(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y),
    mAreaSize(),
    mIterationMax(ITERATION_MAX)
{
    //change the thread affinity of the mMandelbrotCalculator class; in this way, processing performed by the calculator (creating and starting jobs, aggregating job results, and clearing jobs) does not disturb the UI thread
    mMandelbrotCalculator.moveToThread(&mThreadCalculator);

    connect(this, &MandelbrotWidget::requestPicture, &mMandelbrotCalculator, &MandelbrotCalculator::generatePicture);

    connect(&mMandelbrotCalculator, &MandelbrotCalculator::pictureLinesGenerated, this, &MandelbrotWidget::processJobResults);

    mThreadCalculator.start(); //start the thread
}

MandelbrotWidget::~MandelbrotWidget()
{
    mThreadCalculator.quit(); //request the calculator thread to quit
    mThreadCalculator.wait(1000); //wait 1,000 ms for the thread to end
    if (!mThreadCalculator.isFinished()) {
        mThreadCalculator.terminate();
    }
}

void MandelbrotWidget::processJobResults(QList<JobResult> jobResults)
{
    int yMin = height();
    int yMax = 0;

    for(JobResult& jobResult : jobResults) {

        //check if the concerned area size is still valid
        if (mImage->size() != jobResult.areaSize) {
            continue;
        }

        int y = jobResult.pixelPositionY;
        // scanLine() function returns a pointer on the pixel data
        QRgb* scanLine = reinterpret_cast<QRgb*>(mImage->scanLine(y));

        //update the pixel colors of mImage
        for (int x = 0; x < mAreaSize.width(); ++x) {
            scanLine[x] = generateColorFromIteration(jobResult.values[x]); //returns a RGB value depending on the iteration value
        }

        if (y < yMin) {
            yMin = y;
        }

        if (y > yMax) {
            yMax = y;
        }
    }

    repaint(0, yMin,
            width(), yMax);
}

void MandelbrotWidget::resizeEvent(QResizeEvent* event)
{
    //update mAreaSize with the new widget size
    mAreaSize = event->size();

    //a new black QImage is created with the correct dimensions
    mImage = std::make_unique<QImage>(mAreaSize, QImage::Format_RGB32);
    mImage->fill(Qt::black);

    //request a picture computation to MandelbrotCalculator
    emit requestPicture(mAreaSize, mMoveOffset, mScaleFactor, mIterationMax);
}

//zoom
void MandelbrotWidget::wheelEvent(QWheelEvent* event)
{
    int delta = event->delta(); //retreive mouse wheel value
    mScaleFactor *= qPow(0.75, delta / 120.0); //use a power function to apply a coherent value on mScaleFactor
    emit requestPicture(mAreaSize, mMoveOffset, mScaleFactor, mIterationMax); //request an updated picture
}

//pan
void MandelbrotWidget::mousePressEvent(QMouseEvent* event)
{
    //stores the mouse position where the user begins the move gesture
    if (event->buttons() & Qt::LeftButton) {
        mLastMouseMovePosition = event->pos();
    }
}

void MandelbrotWidget::mouseMoveEvent(QMouseEvent* event)
{
    //create a pan offset
    if (event->buttons() & Qt::LeftButton) {
        QPointF offset = mLastMouseMovePosition - event->pos(); //difference between the new and the old mouse position gives us the pan offset
        mLastMouseMovePosition = event->pos();
        offset.setY(-offset.y());
        mMoveOffset += offset * mScaleFactor;
        emit requestPicture(mAreaSize, mMoveOffset, mScaleFactor, mIterationMax);
    }
}

void MandelbrotWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.save();

    QRect imageRect = event->region().boundingRect();
    painter.drawImage(imageRect, *mImage, imageRect); //draw the updated region of the image

    painter.setPen(Qt::white);

    //draw some information texts of the current input data in white
    painter.drawText(10, 20, QString("Size: %1 x %2")
        .arg(mImage->width())
        .arg(mImage->height()));

    painter.drawText(10, 35, QString("Offset: %1 x %2")
        .arg(mMoveOffset.x())
        .arg(mMoveOffset.y()));

    painter.drawText(10, 50, QString("Scale: %1")
        .arg(mScaleFactor));

    painter.drawText(10, 65, QString("Max iteration: %1")
        .arg(ITERATION_MAX));

    painter.restore();
}

QRgb MandelbrotWidget::generateColorFromIteration(int iteration)
{
    if (iteration == mIterationMax) {
        return qRgb(50, 50, 255);
    }

    return qRgb(0, 0, (255.0 * iteration / mIterationMax)); //simple linear interpolation on the blue channel
}
