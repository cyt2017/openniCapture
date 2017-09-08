#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <OpenNI.h>
#include <QTimer>
#include <QImage>

using namespace std;
using namespace cv;
using namespace openni;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Mat depthChannel2Color(Mat in);
    void showOutLabel(Mat inSrc);



protected slots:
    void onTimeOut();
    void onCaptureBtn();

private slots:
    void on_openCaptureBtn_clicked();

private:
    Ui::MainWindow *ui;
    openni::Device device;
    VideoStream depthStream,rgbStream,irStream;
    VideoFrameRef depthFrame,rgbFrame,irFrame;
    Mat depthMat,rgbMat,irMat;

    QTimer *timer;
    int countRgb , countIr;
};

#endif // MAINWINDOW_H
