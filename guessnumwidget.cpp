#include "guessnumwidget.h"
#include "ui_guessnumwidget.h"

GuessNumWidget::GuessNumWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuessNumWidget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(QPixmap(":/image/logo.jpg")));
    setWindowTitle(tr("猜数字游戏"));
    ui->stackedWidget->setCurrentIndex(0);
    initData();
    ui->lcdNumberShowNum->display(m_strNum);
    m_timer = new QTimer(this);
    qsrand(QTime::currentTime().msec());

    connect(ui->pushButton_0,&QPushButton::clicked,this,[=](){
        if(m_strNum.length() < ui->lcdNumberShowNum->digitCount())
        {
            m_strNum.append(ui->pushButton_0->text());
            ui->lcdNumberShowNum->display(m_strNum);
        }
    });
    connect(ui->pushButton_01,&QPushButton::clicked,this,[=](){
        if(m_strNum.length() < ui->lcdNumberShowNum->digitCount())
        {
            m_strNum.append(ui->pushButton_01->text());
            ui->lcdNumberShowNum->display(m_strNum);
        }
    });
    connect(ui->pushButton_02,&QPushButton::clicked,this,[=](){
        if(m_strNum.length() < ui->lcdNumberShowNum->digitCount())
        {
            m_strNum.append(ui->pushButton_02->text());
            ui->lcdNumberShowNum->display(m_strNum);
        }
    });
    connect(ui->pushButton_03,&QPushButton::clicked,this,[=](){
        if(m_strNum.length() < ui->lcdNumberShowNum->digitCount())
        {
            m_strNum.append(ui->pushButton_03->text());
            ui->lcdNumberShowNum->display(m_strNum);
        }
    });
    connect(ui->pushButton_04,&QPushButton::clicked,this,[=](){
        if(m_strNum.length() < ui->lcdNumberShowNum->digitCount())
        {
            m_strNum.append(ui->pushButton_04->text());
            ui->lcdNumberShowNum->display(m_strNum);
        }
    });
    connect(ui->pushButton_05,&QPushButton::clicked,this,[=](){
        if(m_strNum.length() < ui->lcdNumberShowNum->digitCount())
        {
            m_strNum.append(ui->pushButton_05->text());
            ui->lcdNumberShowNum->display(m_strNum);
        }
    });
    connect(ui->pushButton_06,&QPushButton::clicked,this,[=](){
        if(m_strNum.length() < ui->lcdNumberShowNum->digitCount())
        {
            m_strNum.append(ui->pushButton_06->text());
            ui->lcdNumberShowNum->display(m_strNum);
        }
    });
    connect(ui->pushButton_07,&QPushButton::clicked,this,[=](){
        if(m_strNum.length() < ui->lcdNumberShowNum->digitCount())
        {
            m_strNum.append(ui->pushButton_07->text());
            ui->lcdNumberShowNum->display(m_strNum);
        }
    });
    connect(ui->pushButton_08,&QPushButton::clicked,this,[=](){
        if(m_strNum.length() < ui->lcdNumberShowNum->digitCount())
        {
            m_strNum.append(ui->pushButton_08->text());
            ui->lcdNumberShowNum->display(m_strNum);
        }
    });
    connect(ui->pushButton_09,&QPushButton::clicked,this,[=](){
        if(m_strNum.length() < ui->lcdNumberShowNum->digitCount())
        {
            m_strNum.append(ui->pushButton_09->text());
            ui->lcdNumberShowNum->display(m_strNum);
        }
    });
}

GuessNumWidget::~GuessNumWidget()
{
    delete ui;
}

void GuessNumWidget::initData()
{
    m_timeInterval = 1000;
    m_recorderTime = 0;
    m_second = 0;
    m_minute = 0;
    m_hour = 0;
    isPause = false;
    unclick = true;
    m_strNum = "";
    m_minNum = ui->lineEditMinNum->text().toInt();
    m_maxNum = ui->lineEditMaxNum->text().toInt();
}

void GuessNumWidget::numLength()
{
    QString maxNum = ui->lineEditMaxNum->text();
    ui->lcdNumberShowNum->setDigitCount(maxNum.length());
}


void GuessNumWidget::on_pushButtonGameOk_clicked()
{
    initData();
    if(ui->lineEditGameTime->text().isEmpty() || ui->lineEditMinNum->text().isEmpty() || ui->lineEditMaxNum->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("请输入游戏时间、数字下限和上限！"));
        return;
    }
    canClickButton();
    ui->pushButtonStart->setDisabled(false);

    ui->stackedWidget->setCurrentIndex(1);
    QString hour = QString::number(m_hour);
    if(hour.length() == 1)
    {
        hour = "0" + hour;
    }
    QString minute = QString::number(m_minute);
    if(minute.length() == 1)
    {
        minute = "0" + minute;
    }
    QString second = QString::number(m_second);
    if(second.length() == 1)
    {
        second = "0" + second;
    }
    QString str = hour + ":" + minute + ":" + second;

    ui->lcdNumberShowTime->display(str);

    ui->pushButtonStart->setDisabled(false);
    numLength();
    m_randNum = createRandNum(m_minNum, m_maxNum);
}

void GuessNumWidget::on_pushButtonQuit_clicked()
{
    this->close();
}

void GuessNumWidget::on_pushButtonStart_clicked()
{
    if(m_timer->isActive())
    {
        return;
    }
    else
    {
        if(isPause == false)
        {
            m_timer->start(m_timeInterval);
        }
        connect(m_timer,&QTimer::timeout,this,&GuessNumWidget::onTimeOut);
        unclick = false;
        canClickButton();
    }
}

void GuessNumWidget::onTimeOut()
{
    m_second++;
    if(m_second == 60)
    {
        m_second = 0;
        m_minute++;
        if(m_minute == 60)
        {
            m_minute = 0;
            m_hour++;
        }
    }

    QString hour = QString::number(m_hour);
    if(hour.length() == 1)
    {
        hour = "0" + hour;
    }
    QString minute = QString::number(m_minute);
    if(minute.length() == 1)
    {
        minute = "0" + minute;
    }
    QString second = QString::number(m_second);
    if(second.length() == 1)
    {
        second = "0" + second;
    }
    QString m_lcdShowtime = hour + ":" + minute + ":" + second;
    ui->lcdNumberShowTime->display(m_lcdShowtime);
    m_recorderTime++;
    isTimeout(ui->lineEditGameTime->text().toInt());
}

void GuessNumWidget::on_pushButtonPause_clicked()
{
    if(ui->pushButtonPause->text() == "暂停" )
    {
        m_timer->stop();
        isPause = true;
        ui->pushButtonPause->setText("继续");
        unclick = true;
        canClickButton();
        ui->pushButtonPause->setDisabled(false);
    }
    else
    {
        isPause = false;
        m_timer->start(m_timeInterval);
        ui->pushButtonPause->setText("暂停");
        unclick = false;
        canClickButton();
    }
}

void GuessNumWidget::on_pushButtonReset_clicked()
{
    m_timer->stop();
    disconnect(m_timer,&QTimer::timeout,this,&GuessNumWidget::onTimeOut);
    on_pushButtonGameOk_clicked();
}

void GuessNumWidget::on_pushButtonClear_clicked()
{
    m_strNum = "";
    ui->lcdNumberShowNum->display(m_strNum);
}

void GuessNumWidget::on_pushButtonGuessOk_clicked()
{
    if(ui->lcdNumberShowNum->intValue() < m_randNum)
    {
        QMessageBox::information(this,tr("提示"),tr("猜错了，有点小了！"));
        m_strNum = "";
        ui->lcdNumberShowNum->display(m_strNum);
    }
    else if(ui->lcdNumberShowNum->intValue() > m_randNum)
    {
        QMessageBox::information(this,tr("提示"),tr("猜错了，有点大了！"));
        m_strNum = "";
        ui->lcdNumberShowNum->display(m_strNum);
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("恭喜你答对了"));
        m_timer->stop();
        disconnect(m_timer,&QTimer::timeout,this,&GuessNumWidget::onTimeOut);
        ui->stackedWidget->setCurrentIndex(0);
    }
}

int GuessNumWidget::createRandNum(int minNum, int maxNum)
{
    return qrand()%(maxNum-minNum) + minNum+1;
}

void GuessNumWidget::isTimeout(int getTime)
{
    if(getTime == m_recorderTime)
    {
        m_timer->stop();
        disconnect(m_timer,&QTimer::timeout,this,&GuessNumWidget::onTimeOut);
        QMessageBox::information(this,tr("提示"),tr("很遗憾，时间到了，请重新来一次。"));
        ui->stackedWidget->setCurrentIndex(0);
        canClickButton();
    }
}

void GuessNumWidget::canClickButton()
{
    if(unclick == true)
    {
        ui->pushButton_0->setDisabled(true);
        ui->pushButton_01->setDisabled(true);
        ui->pushButton_02->setDisabled(true);
        ui->pushButton_03->setDisabled(true);
        ui->pushButton_04->setDisabled(true);
        ui->pushButton_05->setDisabled(true);
        ui->pushButton_06->setDisabled(true);
        ui->pushButton_07->setDisabled(true);
        ui->pushButton_08->setDisabled(true);
        ui->pushButton_09->setDisabled(true);
        ui->pushButtonGuessOk->setDisabled(true);
        ui->pushButtonClear->setDisabled(true);
        ui->pushButtonStart->setDisabled(true);
        ui->pushButtonPause->setDisabled(true);
        ui->pushButtonReset->setDisabled(true);
    }
    else
    {
        ui->pushButton_0->setDisabled(false);
        ui->pushButton_01->setDisabled(false);
        ui->pushButton_02->setDisabled(false);
        ui->pushButton_03->setDisabled(false);
        ui->pushButton_04->setDisabled(false);
        ui->pushButton_05->setDisabled(false);
        ui->pushButton_06->setDisabled(false);
        ui->pushButton_07->setDisabled(false);
        ui->pushButton_08->setDisabled(false);
        ui->pushButton_09->setDisabled(false);
        ui->pushButtonGuessOk->setDisabled(false);
        ui->pushButtonClear->setDisabled(false);
        ui->pushButtonStart->setDisabled(false);
        ui->pushButtonPause->setDisabled(false);
        ui->pushButtonReset->setDisabled(false);
    }
}
