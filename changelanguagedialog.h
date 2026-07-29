#ifndef CHANGELANGUAGEDIALOG_H
#define CHANGELANGUAGEDIALOG_H

#include <QDialog>
#include "database.h"
#include <QDir>
#include "imports.h"

namespace Ui {
class ChangeLanguageDialog;
}

class ChangeLanguageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeLanguageDialog(QWidget *parent = nullptr);
    ~ChangeLanguageDialog();
signals:
    void languageSelected(const QString &lang);

private slots:
    void on_saveBtn_clicked();


private:
    Ui::ChangeLanguageDialog *ui;
    void loadLanguages();
    enum lang
    {
        ua,
        eng,
        pl
    };


};

#endif // CHANGELANGUAGEDIALOG_H
