#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;
class QVideoProbe;
class QVideoFrame;
class QProcess;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void processFrame(const QVideoFrame &frame);   
    void readyReadStandardOutput();
    void processStarted();
    void recordFinished();

private:
    Ui::Widget *ui;
    QCamera *mQCamera;
    QCameraViewfinder *mQCameraViewFinder;
    QCameraImageCapture *mQCameraImageCapture;
    QVBoxLayout *mQCameraVBoxLayout;
    QMenu *mOptionsMenu;
    QAction *mOnAction;
    QAction *mOffAction;
    QAction *mCaptureAction;
    QVideoProbe *mQVideoProbe;
    QProcess *ffmpegRecordingProcess;
};

#endif // WIDGET_H
