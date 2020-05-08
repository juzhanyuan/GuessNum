#ifndef GUESSNUMWIDGET_H
#define GUESSNUMWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class GuessNumWidget; }
QT_END_NAMESPACE

class GuessNumWidget : public QWidget
{
    Q_OBJECT

public:
    GuessNumWidget(QWidget *parent = nullptr);
    ~GuessNumWidget();


    void initData();

    void numLength();

    int createRandNum(int minNum, int maxNum);

    void isTimeout(int getTime);

    void canClickButton();


private slots:
    void on_pushButtonGameOk_clicked();

    void on_pushButtonQuit_clicked();

    void on_pushButtonStart_clicked();

    void onTimeOut();

    void on_pushButtonPause_clicked();

    void on_pushButtonReset_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonGuessOk_clicked();

private:
    Ui::GuessNumWidget *ui;
    bool isPause;
    bool unclick;

    int m_timeInterval;
    int m_recorderTime;
    int m_second;
    int m_minute;
    int m_hour;
    int m_minNum;
    int m_maxNum;
    QTimer *m_timer;
    QString m_strNum;
    int m_numLength;
    int  m_randNum;
};
#endif // GUESSNUMWIDGET_H
