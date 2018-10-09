#ifndef MANDELBROTWIDGET_H
#define MANDELBROTWIDGET_H

#include <memory>

#include <QWidget>
#include <QPoint>
#include <QThread>
#include <QList>

#include "mandelbrotcalculator.h"

class QResizeEvent;

class MandelbrotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MandelbrotWidget(QWidget *parent = 0);
    ~MandelbrotWidget();

public slots:
    void processJobResults(QList<JobResult> jobResults); //handle the JobResult list dispatched by MandelbrotCalculator

signals:
    void requestPicture(QSize areaSize, QPointF moveOffset, double scaleFactor, int iterationMax); //signal is emitted each time the user changes the input data (offset, scale, or area size)

protected:
    void paintEvent(QPaintEvent* event) override; //draws the widget with the current mImage
    void resizeEvent(QResizeEvent* event) override; //resizes the Mandelbrot area size when the user resizes the window
    void wheelEvent(QWheelEvent* event) override; //handles the user mouse wheel event to apply a scale factor
    void mousePressEvent(QMouseEvent* event) override; //retrieve user mouse events to move the Mandelbrot picture
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QRgb generateColorFromIteration(int iteration); //helper function to colorize the Mandelbrot picture

private:
    MandelbrotCalculator mMandelbrotCalculator; //our multi-threaded Job manager; The widget will do requests to it and wait for results
    QThread mThreadCalculator; //allows the Mandelbrot calculator to run in its own thread
    QPoint mLastMouseMovePosition; //used by the widget to handle user events for the pan feature
    double mScaleFactor;
    QPointF mMoveOffset;
    QSize mAreaSize;
    int mIterationMax;
    std::unique_ptr<QImage> mImage; //current picture displayed by the widget
};

#endif // MANDELBROTWIDGET_H
