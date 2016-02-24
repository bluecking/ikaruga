#ifndef ITEMSETTINGSGUI_H
#define ITEMSETTINGSGUI_H

#include <QDialog>

namespace Ui {
class ItemSettingsGui;
}

class ItemSettingsGui : public QDialog
{
    Q_OBJECT

public:
    explicit ItemSettingsGui(QWidget *parent = 0);
    ~ItemSettingsGui();

private:
    Ui::ItemSettingsGui *ui;
};

#endif // ITEMSETTINGSGUI_H
