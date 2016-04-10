#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "consumer.h"
#include "producer.h"
#include <QSemaphore>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //QTimer *timer;

    void setName(const QString &name);
    QString name() const;


    void onBufferValueChanged(int);
    void onProducerValueChanged(int);
    void onConsumerValueChanged(int);
    void timerEvent( QTimerEvent * );

private:
    Ui::MainWindow *ui;
    int value;

    Producer *mProducer;
    //Consumer *mConsumer;

public slots:
    //void plotnewvector(int newvector);
    //void PlotData();

};

#endif // MAINWINDOW_H
