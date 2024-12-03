#include "rotatewidget.h"
#include "ui_rotatewidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QTransform> // Qt界面转换类

struct RotateWidgetPrivate
{
    QPixmap mp;
    int r; // 半径
    QPoint center; // 圆心
    int degree; // 旋转角度
    QTimer timer;
};

RotateWidget::RotateWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RotateWidget)
    , p(new RotateWidgetPrivate)
{
    ui->setupUi(this);
    connect(&p->timer,&QTimer::timeout,[this]()
    {
        p->degree = (p->degree + 1) % 360;
        update();
    });
}

RotateWidget::~RotateWidget()
{
    delete ui;
    delete p;
}

void RotateWidget::SetPixmap(const QPixmap &mp)
{
    p->mp = mp;
    p->r = std::min(this->height(), this->width()) / 2; // 矩形内切圆半径
    p->center = QPoint(this->width() / 2, this->height() / 2); // 矩形内切圆圆心
    p->degree = 0;
    p->timer.setInterval(20);
//    p->timer.start(20);
}

void RotateWidget::stop()
{
    p->timer.stop();
}

void RotateWidget::start()
{
    p->timer.start();
}

void RotateWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿:增加cpu渲染压力，降低性能

    QPainterPath painterPath;// 绘制的形状路径
    painterPath.addEllipse(p->center,p->r,p->r);// 设置裁剪原图成为一个圆

    // 旋转
    QTransform transform;
    transform.translate(p->center.x(),p->center.y()); // 按照圆心旋转
    transform.rotate(p->degree); // 旋转角度

    painter.setClipPath(painterPath); // 把裁剪路径给到画家
    painter.setTransform(transform); // 绘制旋转变换
    painter.drawPixmap(-p->r,-p->r,this->width(),this->height(),p->mp);
    // painter.drawPixmap(0,0,this->width(),this->height(),p->mp);
}
