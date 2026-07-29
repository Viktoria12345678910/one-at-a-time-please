#include "viewttdialog.h"
#include "ui_viewttdialog.h"

ViewTTDialog::ViewTTDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewTTDialog)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    auto threads = Database::instance().getAllThreads();

    for (const Thread &thread : threads)
    {
        auto *threadItem = new QStandardItem(thread.name);
        threadItem->setData(ThreadItem, TypeRole);
        threadItem->setData(thread.threadId, IdRole);

        model->appendRow(threadItem);

        for (const Task &task : Database::instance().getTasksByThread(thread.threadId))
        {
            auto *taskItem = new QStandardItem(task.name);
            taskItem->setData(TaskItem, TypeRole);
            taskItem->setData(task.taskId, IdRole);

            threadItem->appendRow(taskItem);
        }
    }

    ui->treeView->setModel(model);
}

ViewTTDialog::~ViewTTDialog()
{
    delete ui;
}

void ViewTTDialog::on_deleteBtn_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid())
    {
        return;
    }
    QStandardItem *item = model->itemFromIndex(index);
    ItemType type = static_cast<ItemType>(item->data(TypeRole).toInt());
    int id = item->data(IdRole).toInt();
    QString name = item->text();
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("попередження"), QString(tr("Чи справді ви хочете видалити %1 з назвою %2")).arg(QString(type ? tr("гілку") : tr("завдання")),name), QMessageBox::Yes | QMessageBox::No);
    if(reply != QMessageBox::Yes) return;
    switch (type)
    {
    case ThreadItem:
        Database::instance().deleteThread(id);
        break;

    case TaskItem:
        Database::instance().deleteTask(id);
        break;
    }
    model->removeRow(item->row(), item->parent() ? item->parent()->index() : QModelIndex());

}


void ViewTTDialog::on_collapseBtn_clicked()
{
    ui->treeView->collapseAll();
}


void ViewTTDialog::on_expandBtn_clicked()
{
    ui->treeView->expandAll();
}

void ViewTTDialog::DBWipe()
{
    Database::instance().wipe();
}


void ViewTTDialog::on_wipedbtn_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("попередження"), tr("Ця дія цілком очистить базу даних. Чи впевнені ви що хочете прожовжити?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) DBWipe();
}

