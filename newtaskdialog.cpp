#include "newtaskdialog.h"
#include "ui_newtaskdialog.h"

NewTaskDialog::NewTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTaskDialog)
{
    ui->setupUi(this);
    loadThreads();
}

NewTaskDialog::~NewTaskDialog()
{
    delete ui;
}

void NewTaskDialog::loadThreads(){
    ui->threadCb->clear();
    ui->threadCb->addItem(" ", -1);

    QList<Thread> threads = Database::instance().getAllThreads();
    for (auto &thread : threads){
        QString arch;
        if(thread.archived){
            arch = tr("гілку заархівовано");
        } else {
                arch = tr("гілку не заархівовано");
        }
        ui->threadCb->addItem(
            QString("%1 (%2)").arg(thread.name, thread.archived), thread.threadId);
        qDebug()<<"added: "<<thread.name;

    }
}
void NewTaskDialog::on_saveBtn_clicked()
{
    qDebug() <<"save btn clicked";
    //if(ui->threadCb->currentText() == " " || "") {qDebug()<<"current text is '' or ' '";return;}
    QString name = ui->nameLe->text();
    QString desc = ui->descTe->toPlainText();
    int threadId = ui->threadCb->currentData().toInt();

    if(Database::instance().createTask(name, desc, threadId)){
        QMessageBox::information(this, tr("Успіх"), tr("завдання успішно створено"));
    } else {
        QMessageBox::critical(this, "error", "create task returned false");
    }
    this->close();
}

