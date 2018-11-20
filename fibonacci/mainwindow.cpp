#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"

double getFibonacci(int n);

static QString myIdentV;
static QString TMP;

QString cv(double v)
{
    char s[1200] = "";
    sprintf(s, "%.f",v);
    return s;
}

QString cv2(double v)
{
    char s[1200] = "";
    sprintf(s, "%.3f",v);
    return s;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myIdentV = ui->lbIdenTmp->text();
    TMP = ui->lbNextFib->text();
    on_pushButton_2_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    double a=1;
    double b=1;
    double c;
    int max= ui->lineEdit->text().toInt();
    QString result;
    for (int i=0;i<max;i++)
    {
        result+= QString::number(i+1)+"  : "+ cv(b) +"\n";
        c=a+b;
        a=b;
        b=c;
    }
    ui->textEdit->setText(result);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    int a=arg1+1;
    double v = (pow(1.618033988749894848204586834365, a)-pow(0.618033988749894848204586834365, a))/sqrt(5);
    QString s = cv(v) +" round "+cv(round(v));
    ui->lbGrValue->setText(s);
    v = getFibonacci(arg1-1);
    ui->lbReadValue->setText(cv(v));
}

double getFibonacci(int n)
{
    double a=1;
    double b=1;
    double c=0;
    for (int i=0;i<n;i++)
    {
        c=a+b;
        a=b;
        b=c;
    }
    return b;
}

QString fibonacciStr(double v)
{
    return cv(getFibonacci(static_cast<long>(v)));
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    double v = getFibonacci(arg1-1);
    double n = round(v*1.618033988749894848204586834365);
    double r = getFibonacci(arg1);
    QString s(TMP);
    s = s.replace("$v", cv(v));
    s = s.replace("$r", cv(r));
    s = s.replace("$n", cv(n));

    ui->lbNextFib->setText(s);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->lbFinoIden->setText(fibonacciStr(value));
    on_pushButton_2_clicked();
}

void MainWindow::on_pushButton_2_clicked()
{
    double v = ui->lbFinoIden->text().toDouble();
    double v1 = v*v*5+4;
    double v2 = v*v*5-4;
    double r1 = sqrt(v1);
    double r2 = sqrt(v2);
    long r = static_cast<long>(r1-round(r1));
    if (r!=0)
        r = static_cast<long>(r2-round(r2));
    QString rv = (r==0)?tr("IS A FIBONACCI NUMBER"):tr("NOT IS FIBONACCI NUMBER");

    QString s(myIdentV);
    s = s.replace("%v1", cv2(v1));
    s = s.replace("%v2", cv2(v2));
    s = s.replace("%r1", cv2(r1));
    s = s.replace("%r2", cv2(r2));
    s = s.replace("%r", rv);

    ui->lbIdenTmp->setText(s);
}

