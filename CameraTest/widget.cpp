#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVideoProbe>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QProcess>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mQCamera = new QCamera(this);
    mQCameraViewFinder = new QCameraViewfinder(this);
    mQCameraImageCapture = new QCameraImageCapture(mQCamera, this);
    mQCameraVBoxLayout = new QVBoxLayout;

    mOptionsMenu = new QMenu("Options", this);
    mOnAction = new QAction("On", this);
    mOffAction = new QAction("Off", this);
    mCaptureAction = new QAction("Capture", this);

    mQVideoProbe = new QVideoProbe(this);

    mOptionsMenu->addActions({mOnAction, mOffAction, mCaptureAction});
    ui->optionsPushButton->setMenu(mOptionsMenu);
    mQCamera->setViewfinder(mQCameraViewFinder);    
    mQCameraVBoxLayout->addWidget(mQCameraViewFinder);
    mQCameraVBoxLayout->setMargin(0);
    ui->scrollArea->setLayout(mQCameraVBoxLayout);

    ffmpegRecordingProcess = new QProcess(this);
    connect(ffmpegRecordingProcess, SIGNAL(started()), this, SLOT(processStarted()));
    connect(ffmpegRecordingProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()));
    connect(ffmpegRecordingProcess, SIGNAL(finished(int)), this, SLOT(recordFinished()));

    connect(mOnAction, &QAction::triggered, [&](){
        if (mQVideoProbe->setSource(mQCamera)) { // Returns true, hopefully
            // Probing succeeded
            connect(mQVideoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(processFrame(QVideoFrame)));

            QString program = "C:/ffmpeg/bin/ffmpeg";
            //QString strArguments = "-y -f rawvideo -video_size 640x360 -pix_fmt bgra -i - -c:v vp9_cuvid -preset ultrafast -vf vflip out.mp4"; //videocard accellaration
            QString strArguments = "-y -f rawvideo -video_size 640x360 -pix_fmt bgra -i - -c:v libx264 -preset ultrafast -vf vflip out.mp4";
            QStringList arguments = strArguments.split(' ');

            ffmpegRecordingProcess->setProcessChannelMode(QProcess::ForwardedChannels);
            ffmpegRecordingProcess->start(program, arguments);
        }

        mQCamera->start();
    });

    connect(mOffAction, &QAction::triggered, [&](){
        ffmpegRecordingProcess->waitForBytesWritten(-1);
        ffmpegRecordingProcess->closeWriteChannel();
        ffmpegRecordingProcess->waitForFinished(-1);
        mQCamera->stop();
    });

    connect(mCaptureAction, &QAction::triggered, [&](){
        auto filename = QFileDialog::getSaveFileName(this, "Capture", "/", "Image (*.jpg;*.jpeg)");
        if(filename.isEmpty()){
            return;
        }

        mQCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
        QImageEncoderSettings imageEncoderSettings;
        imageEncoderSettings.setCodec("image/jpeg");
        imageEncoderSettings.setResolution(1600, 1200);
        mQCameraImageCapture->setEncodingSettings(imageEncoderSettings);
        mQCamera->setCaptureMode(QCamera::CaptureStillImage);
        mQCamera->start();
        mQCamera->searchAndLock();
        mQCameraImageCapture->capture(filename);
        mQCamera->unlock();
    });
}

void Widget::processFrame(const QVideoFrame &frame)
{
    QVideoFrame frame2(frame);
    frame2.map(QAbstractVideoBuffer::ReadOnly);
    ffmpegRecordingProcess->write((char*)frame2.bits(), frame2.mappedBytes());
    frame2.unmap();
}

void Widget::processStarted()
{
    qDebug() << "processStarted()";
}

void Widget::readyReadStandardOutput()
{
   qDebug() << "readyReadStandardOutput()";
   ffmpegRecordingProcess->readAllStandardOutput();
}

void Widget::recordFinished()
{
    qDebug() << "recordFinished()";
}

Widget::~Widget()
{
    delete ui;
}
