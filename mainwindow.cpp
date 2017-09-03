#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    count = 0;

    connect(ui->captureBtn,SIGNAL(clicked(bool)),this,SLOT(onCaptureBtn()));
}

MainWindow::~MainWindow()
{
    printf("~MainWindow()\n");
    fflush(NULL);
    timer->stop();
    delete timer;
    if(ui->checkBox->isChecked()==false)
    {
        depthStream.stop();
        rgbStream.stop();
        depthStream.destroy();
        rgbStream.destroy();
    }
    else
    {
        irStream.stop();
        irStream.destroy();
    }
    device.close();
    OpenNI::shutdown();

    delete ui;
}

Mat MainWindow::depthChannel2Color(Mat in)
{
    Mat depth = in.clone();
    if(depth.empty())
    {
        printf("depth.empty()...\n");
        return in;
    }
    Mat dst = Mat(depth.size(),CV_8UC1);
    double maxVal,minVal;
    cv::minMaxLoc(depth,&minVal,&maxVal);
    depth.convertTo(dst,CV_8UC1,255/maxVal);

    Mat color = Mat(dst.size(),CV_8UC3);
    int tmp;
    for(int row=0;row<dst.rows;row++)
    {
        for(int col=0;col<dst.cols;col++)
        {
            tmp = dst.at<uchar>(row,col);
            if(tmp == 0)
            {
                color.at<Vec3b>(row,col)[0] = 0;
                color.at<Vec3b>(row,col)[1] = 0;
                color.at<Vec3b>(row,col)[2] = 0;
            }
            else
            {
                color.at<Vec3b>(row,col)[0] = abs(255-tmp);
                color.at<Vec3b>(row,col)[1] = abs(127-tmp);
                color.at<Vec3b>(row,col)[2] = abs(0-tmp);
            }
        }
    }
    return color;
}

void MainWindow::showOutLabel(Mat inSrc)
{
    Mat src = inSrc.clone();
    QImage img;
    if(src.type()==CV_8UC3)
    {
        img = QImage(src.data,src.cols,src.rows,src.cols*3,QImage::Format_RGB888);
        ui->label_rgb->setPixmap(QPixmap::fromImage(img));
    }
    else if(src.type()==CV_16UC1)
    {
        Mat depth = depthChannel2Color(src);
        img = QImage(depth.data,depth.cols,depth.rows,depth.cols*3,QImage::Format_RGB888);
        ui->label_depth->setPixmap(QPixmap::fromImage(img));
    }
    else if(src.type()==CV_8UC1)
    {
        img = QImage(src.data,src.cols,src.rows,src.cols,QImage::Format_Indexed8);
        ui->label_ir->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::onTimeOut()
{
    Status rc = STATUS_OK;
    if(ui->checkBox->isChecked()==false)
    {
        rc = rgbStream.readFrame(&rgbFrame);
        if(rc != STATUS_OK)
        {
            printf("rgbStream.readFrame() err..\n");
            return ;
        }
        Mat rgbSrc = Mat(rgbFrame.getHeight(),rgbFrame.getWidth(),CV_8UC3,(void*)rgbFrame.getData());
        if(rgbSrc.empty())
        {
            printf("rgbSrc.empty()...\n");
            return ;
        }
        rc = depthStream.readFrame(&depthFrame);
        if(rc != STATUS_OK)
        {
            printf("depthStream.readFrame() err..\n");
            return ;
        }
        Mat depthSrc = Mat(depthFrame.getHeight(),depthFrame.getWidth(),CV_16UC1,(void*)depthFrame.getData());
        if(depthSrc.empty())
        {
            printf("depthSrc.empty()...\n");
            return ;
        }
        rgbMat = rgbSrc.clone();
    //    imshow("rgbMat",rgbMat);
        showOutLabel(rgbMat);
        depthMat = depthSrc.clone();
        showOutLabel(depthMat);
    }
    else
    {
        rc = irStream.readFrame(&irFrame);
        if(rc != STATUS_OK)
        {
            printf("irStream.readFrame() err..\n");
            return ;
        }
        //    int aa = irFrame.getVideoMode().getPixelFormat();
        //    printf("getPixelFormat%d\n",aa);
        Mat irSrc = Mat(irFrame.getHeight(),irFrame.getWidth(),CV_16UC1,(void*)irFrame.getData());
        if(irSrc.empty())
        {
            printf("irSrc.empty()...\n");
            return ;
        }

        Mat dst = Mat(irSrc.size(),CV_8UC1);
        double maxVal,minVal;
        cv::minMaxLoc(irSrc,&minVal,&maxVal);
        irSrc.convertTo(dst,CV_8UC1,255/maxVal);

        showOutLabel(dst);
    }
}

void MainWindow::onCaptureBtn()
{
    QString str,strDepth;
    count++;
    Mat rgb,depth;
    flip(rgbMat,rgb,1);
    cvtColor(rgb,rgb,CV_BGR2RGB);
    flip(depthMat,depth,1);
    str = QString::number(count)+".jpg";
    imwrite(str.toStdString(),rgb);
    strDepth = "depth"+QString::number(count)+".png";
    imwrite(strDepth.toStdString(),depth);
    printf("88888\n");
}

void MainWindow::on_openCaptureBtn_clicked()
{
    Status rc = STATUS_OK;
    rc = OpenNI::initialize();
    if(rc != STATUS_OK)
    {
        printf("OpenNI::initialize() err...\n");
        return ;
    }
    rc = device.open(openni::ANY_DEVICE);
    if(rc != STATUS_OK)
    {
        printf("device.open() err...\n");
        return ;
    }

    if(ui->checkBox->isChecked())
    {
        if(device.getSensorInfo(openni::SENSOR_IR)!=NULL)
        {
            rc = irStream.create(device,openni::SENSOR_IR);
            if(rc != STATUS_OK)
            {
                printf("irStream.create() err...\n");
                return ;
            }
        }
        VideoMode model;
        model.setFps(30);
        model.setResolution(640,480);
        rc = irStream.setVideoMode(model);
        if(rc != STATUS_OK)
        {
            printf("irStream.setVideoMode() err...\n");
            return ;
        }
        rc = irStream.start();
        if(rc != STATUS_OK)
        {
            printf("irStream.start() err...\n");
            return ;
        }
    }
    else
    {
        if(device.getSensorInfo(openni::SENSOR_COLOR)!=NULL)
        {
            rc = rgbStream.create(device,openni::SENSOR_COLOR);
            if(rc != STATUS_OK)
            {
                printf("rgbStream.create() err...\n");
                return ;
            }
            VideoMode model;
            model.setFps(30);
            model.setPixelFormat(openni::PIXEL_FORMAT_RGB888);
            model.setResolution(640,480);
            rc = rgbStream.setVideoMode(model);
            if(rc != STATUS_OK)
            {
                printf("rgbStream.setVideoMode() err...\n");
                return ;
            }
        }
        if(device.getSensorInfo(openni::SENSOR_DEPTH)!=NULL)
        {
            rc = depthStream.create(device,openni::SENSOR_DEPTH);
            if(rc != STATUS_OK)
            {
                printf("depthStream.create() err...\n");
                return ;
            }
            VideoMode model;
            model.setFps(30);
            model.setPixelFormat(openni::PIXEL_FORMAT_DEPTH_1_MM);
            model.setResolution(640,480);
            rc = depthStream.setVideoMode(model);
            if(rc != STATUS_OK)
            {
                printf("depthStream.setVideoMode() err...\n");
                return ;
            }
        }

        rc = rgbStream.start();
        if(rc != STATUS_OK)
        {
            printf("rgbStream.start() err...\n");
            return ;
        }
        rc = depthStream.start();
        if(rc != STATUS_OK)
        {
            printf("depthStream.start() err...\n");
            return ;
        }
    }

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    timer->setInterval(30);
    timer->start(30);
    ui->checkBox->setEnabled(0);
}
