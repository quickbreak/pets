#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    void sendToServer(QString str);
    quint16 nextBlockSize;
private slots:
    void slotReadyRead();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_lineEdit_returnPressed();
};
#endif // MAINWINDOW_H
