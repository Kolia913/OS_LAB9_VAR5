#ifndef PROCESS_H
#define PROCESS_H

#include <QDialog>
#include <QTimer>
#include "ibaseswop.h"
#include "csharememoryswop.h"
#include "windows.h"

namespace Ui {
class process;
}

class process : public QDialog
{
    Q_OBJECT

public:
    explicit process(QWidget *parent, char *);
    ~process();

private slots:
    void on_b_send_clicked();

private:
    Ui::process *ui;
    iBaseSwop * ptrMethod = NULL;
    void checkTimer(void);
    int messDisplayed = 0;

};

#endif // PROCESS_H
