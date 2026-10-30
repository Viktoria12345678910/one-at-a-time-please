#ifndef CHANGETHEMEDIALOG_H
#define CHANGETHEMEDIALOG_H

#include <QDialog>
#include "imports.h"


namespace Ui {
class ChangeThemeDialog;
}

class ChangeThemeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeThemeDialog(QWidget *parent = nullptr);
    ~ChangeThemeDialog();

private:
    Ui::ChangeThemeDialog *ui;
    void loadThemes();
signals:
    void themeSelected(const QString &theme);
private slots:
    void on_saveBtn_clicked();

};

#endif // CHANGETHEMEDIALOG_H
