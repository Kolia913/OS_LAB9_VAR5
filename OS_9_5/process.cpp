#include "process.h"
#include "ui_process.h"


process::process(QWidget *parent, char *method) :
    QDialog(parent),
    ui(new Ui::process)
{
    ui->setupUi(this);
    QString temp(method);
    if(temp == "1") {
       ptrMethod = new cShareMemorySwop();
    }
    ptrMethod->ClientInit();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &process::checkTimer);
    timer->start(1000);
}

void process::checkTimer(void){
    QString output = "";
    for(int i = 0; i < ptrMethod->GetCount(); i++) {
        QString line(ptrMethod->Get(i));
        output += line + '\n';
    }
    ui->textBrowser->setText(output);
}

process::~process()
{
    delete ui;
}

void process::on_b_send_clicked()
{
    QByteArray ba = ui->l_input->text().toLatin1();
    char *caMessage = ba.data();
    ptrMethod->Send(caMessage);
    ui->l_input->setText("");
}

