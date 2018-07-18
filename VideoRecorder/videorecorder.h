#ifndef VIDEORECORDER_H
#define VIDEORECORDER_H

#include <QWidget>
#include <QProcess>

class QCamera;
class QCameraViewfinder;
class QVideoProbe;
class QVideoFrame;
class QProcess;
class QPushButton;

namespace Ui {
class VideoRecorder;
}

class VideoRecorder : public QWidget
{
    Q_OBJECT

public:
    explicit VideoRecorder(QWidget *parent = 0);
    ~VideoRecorder();
    void setFilename(QString filename);

public slots:
    void start();
    void stop();
    void processFrame(const QVideoFrame &frame);
    void processStarted();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError error);

private:
    Ui::VideoRecorder *ui;
    QCamera *mQCamera;
    QCameraViewfinder *mQCameraViewFinder;
    QVideoProbe *mQVideoProbe;
    QProcess *ffmpegRecordingProcess;
    QPushButton *startRecordBtn;
    QPushButton *stopRecordBtn;
    QString filename;
};

#endif // VIDEORECORDER_H
