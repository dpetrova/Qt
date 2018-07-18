#define CAMERA_CONTROLS
//#define VIDEO_ACCELARATION

#include "videorecorder.h"
#include "ui_videorecorder.h"

#include <QDebug>
#include <QCamera>
#include <QCameraViewfinder>
#include <QVideoProbe>
#include <QProcess>
#include <QPushButton>
#include <QInputDialog>

VideoRecorder::VideoRecorder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoRecorder),
    filename("test.ogv")
{
    ui->setupUi(this);

    mQCamera = new QCamera(this);
    mQCameraViewFinder = new QCameraViewfinder(this);
    mQVideoProbe = new QVideoProbe(this);
    mQCamera->setViewfinder(mQCameraViewFinder);

#ifdef CAMERA_CONTROLS

    startRecordBtn = new QPushButton("Rec", this);
    stopRecordBtn = new QPushButton("Stop", this);
    stopRecordBtn->move(330, 0);
    connect(startRecordBtn, SIGNAL(clicked()), this, SLOT(start()));
    connect(stopRecordBtn, SIGNAL(clicked()), this, SLOT(stop()));

#endif

    ffmpegRecordingProcess = new QProcess(this);
    connect(ffmpegRecordingProcess, SIGNAL(started()), this, SLOT(processStarted()));    
    connect(ffmpegRecordingProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));
    connect(ffmpegRecordingProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));

    mQCamera->start();
}

void VideoRecorder::start()
{
#ifdef CAMERA_CONTROLS

    QString filename = QString::fromStdString("C:\\Users\\Dani\\Videos\\test.ogv");
    this->setFilename(filename);

#endif

    if (mQVideoProbe->setSource(mQCamera)) {
        connect(mQVideoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(processFrame(QVideoFrame)));
    }

    QString program = "C:/ffmpeg/bin/ffmpeg";
    QString strArguments = "-y -f rawvideo -video_size 640x360 -pix_fmt bgra -i - -c:v libx264 -preset ultrafast -vf vflip -vcodec libtheora";

#ifdef VIDEO_ACCELARATION

        strArguments = "-y -f rawvideo -video_size 640x360 -pix_fmt bgra -i - -c:v vp9_cuvid -preset ultrafast -vf vflip -vcodec libtheora";

#endif

    QStringList arguments = strArguments.split(' ');
    arguments << this->filename;

    ffmpegRecordingProcess->setProcessChannelMode(QProcess::ForwardedChannels);
    ffmpegRecordingProcess->start(program, arguments);
}

void VideoRecorder::stop()
{
    ffmpegRecordingProcess->waitForBytesWritten(-1);
    ffmpegRecordingProcess->closeWriteChannel();
    ffmpegRecordingProcess->waitForFinished(-1);
}

void VideoRecorder::processFrame(const QVideoFrame &frame)
{
    QVideoFrame frame2(frame);
    frame2.map(QAbstractVideoBuffer::ReadOnly);
    ffmpegRecordingProcess->write((char*)frame2.bits(), frame2.mappedBytes());
    frame2.unmap();
}

void VideoRecorder::processStarted()
{
    qDebug() << "processStarted()";
}

void VideoRecorder::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Finished: exitCode: " << exitCode << ", exitStatus: " << exitStatus;
    if(exitCode != 0) {
        ffmpegRecordingProcess->closeWriteChannel();
        ffmpegRecordingProcess->kill();
    }
}

void VideoRecorder::processError(QProcess::ProcessError error)
{
    qDebug() << "Error: " << error;
}

void VideoRecorder::setFilename(QString filename)
{
    this->filename = filename;
}

VideoRecorder::~VideoRecorder()
{
    delete ui;
}
