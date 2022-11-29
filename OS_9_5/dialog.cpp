#include "dialog.h"
#include "./ui_dialog.h"

STARTUPINFOA si[20];
PROCESS_INFORMATION pi[20];

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->l_message->hide();
}

Dialog::~Dialog()
{
    delete ui;    
}

void Dialog::setError(QString error) {
    ui->l_message->show();
    ui->l_message->setText(error);
    QTimer::singleShot(1500, ui->l_message, &QLabel::hide);
}

void Dialog::on_b_start_clicked()
{
    int prAmmount = ui->sB_prAmmount->value();
    if(prAmmount == 0) {
        setError("ammount can not be zero");
        return;
    }
    int typeMethod = 1;
    for(int i = 0; i < prAmmount; i++) {
        ZeroMemory(&si[i], sizeof(si[i]));
        ZeroMemory(&pi[i], sizeof(pi[i]));
        si[i].cb = sizeof(si[i]);
        char path[100] = "OS_9_5.exe";
        bool bCreateProcess = NULL;
        char tmp[10];

        sprintf_s(tmp, " %d",typeMethod);
        strcat_s(path, tmp);
        bCreateProcess = CreateProcessA(NULL, LPSTR(path), NULL, NULL, FALSE, 0, NULL, NULL, &si[i], &pi[i]);
        if(!bCreateProcess) {
            setError("cannot create a process");
            return;
        }
    }


}


void Dialog::on_pushButton_clicked()
{
    STARTUPINFOA siPipes;
    PROCESS_INFORMATION piPipes;

    char path[500] = "D:\\Workspace\\cpp\\InterProcessCommunication\\Project56\\x64\\Debug\\Project56.exe";
    ZeroMemory(&siPipes, sizeof(siPipes));
    ZeroMemory(&piPipes, sizeof(piPipes));
    siPipes.cb = sizeof(siPipes);
    bool bCreateProcess = CreateProcessA(NULL, LPSTR(path), NULL, NULL, FALSE, 0, NULL, NULL, &siPipes, &piPipes);
    if(!bCreateProcess) {
         setError("cannot create a process");
         return;
    }

}


void Dialog::on_pushButton_2_clicked()
{
    STARTUPINFOA siPipes;
    PROCESS_INFORMATION piPipes;

    char path[500] = "D:\\Workspace\\cpp\\InterProcessCommunication\\Project57\\x64\\Debug\\Project57.exe";
    ZeroMemory(&siPipes, sizeof(siPipes));
    ZeroMemory(&piPipes, sizeof(piPipes));
    siPipes.cb = sizeof(siPipes);
    bool bCreateProcess = CreateProcessA(NULL, LPSTR(path), NULL, NULL, FALSE, 0, NULL, NULL, &siPipes, &piPipes);
    if(!bCreateProcess) {
         setError("cannot create a process");
         return;
    }
}

