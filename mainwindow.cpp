#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame->resize(50, this->height());
    ui->penButton->setChecked(true);
    this->setWindowTitle("MyPaint");

    paintWdg = new PaintWidget;
    initPaintWidget();

    paintWdg->setPenWidth(ui->penWidthSpinBox->value());

    ui->openPaletteButton->setStyleSheet("border-image:url(:/Icons/palette.png);");

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->clearButton, SIGNAL(clicked()), paintWdg, SLOT(clearImage()));
    connect(ui->openPaletteButton, SIGNAL(clicked()), this, SLOT(showPallete()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->penButton, SIGNAL(pressed()), this, SLOT(drawByPen()));
    connect(ui->lineButton, SIGNAL(pressed()), this, SLOT(drawLine()));
    connect(ui->rectButton, SIGNAL(pressed()), this, SLOT(drawRect()));
    connect(ui->ellipseButton, SIGNAL(pressed()), this, SLOT(drawEllipse()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->penWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changePenWidth()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initPaintWidget()
{

    //Set paint widget size and position
    paintWdg->setParent(this);

    QRect paintWdgSize = QRect(ToolBarWidth, ui->menuBar->height(),
                               this->width() - ToolBarWidth, this->height() - ui->menuBar->height());
    paintWdg->setGeometry(paintWdgSize);

    // set black background
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    paintWdg->setAutoFillBackground(true);
    paintWdg->setPalette(Pal);
    paintWdg->show();
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    paintWdg->resize(this->width() - ToolBarWidth, this->height() - ui->menuBar->height());
}

void MainWindow::showPallete()
{
    QColor newColor = QColorDialog::getColor(Qt::black);
    if (newColor.isValid())
        paintWdg->setPenColor(newColor);
}

void MainWindow::save()
{
    saveFile("png");
}

void MainWindow::open()
{
    if (isSaved())
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            paintWdg->openImage(fileName);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About MyPaint"),
            tr("<b>MyPaint</b> is made for drawing simple objects.\n"
               "Created by Dmitry Chebotarsky\n"
               "email: inen1995@gmail.com"));
}

bool MainWindow::isSaved()
{
    if (paintWdg->isModified())
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::warning(this, tr("MyPaint"),
                                   tr("The image has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (button == QMessageBox::Save)
        {
            return saveFile("png");
        } else if (button == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString path = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), path, tr("Images (*.png *.xpm *.jpg)"));
    if (fileName.isEmpty())
    {
        return false;
    } else
    {
        return paintWdg->saveImage(fileName, fileFormat);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isSaved())
    {
        event->accept();
    } else
    {
        event->ignore();
    }
}

void MainWindow::drawByPen()
{
    paintWdg->setDrawingTypeFlag(PaintWidget::byPen);
}

void MainWindow::drawLine()
{
    paintWdg->setDrawingTypeFlag(PaintWidget::line);
}

void MainWindow::drawRect()
{
    paintWdg->setDrawingTypeFlag(PaintWidget::rect);
}

void MainWindow::drawEllipse()
{
    paintWdg->setDrawingTypeFlag(PaintWidget::ellipse);
}

void MainWindow::newFile()
{
    if (isSaved())
        paintWdg->clearImage();
}

void MainWindow::changePenWidth()
{
    paintWdg->setPenWidth(ui->penWidthSpinBox->value());
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPen pen(paintWdg->getPenColor(), ui->penWidthSpinBox->value(), Qt::SolidLine, Qt::RoundCap);
    p.setPen(pen);
    p.drawLine(10, ui->openPaletteButton->y() - 32, 40, ui->openPaletteButton->y() - 2);
}
