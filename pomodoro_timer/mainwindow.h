#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startTimer(int minutes, int seconds);
    void showTimer(int minutes, int seconds);

  private slots:
    void on_startButton_clicked();

  private:
    Ui::MainWindow *ui;
    bool stopTimer;
};
#endif // MAINWINDOW_H
