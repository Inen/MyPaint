#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintwidget.h"
#include "drawmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initPaintWidget();
    void initPaletteButtons();
    bool isSaved();
    bool saveFile(const QByteArray &fileFormat);

    Ui::MainWindow *ui;    
    int ToolBarWidth = 50; //Set toolbar width
    PaintWidget *paintWdg;
    bool paletteStatus = false;

protected:
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *);

public slots:
    void showPallete();
    void newFile();
    void open();
    void save();
    void about();
    void drawByPen();
    void drawLine();
    void drawRect();
    void drawEllipse();
    void changePenWidth();
};

#endif // MAINWINDOW_H
