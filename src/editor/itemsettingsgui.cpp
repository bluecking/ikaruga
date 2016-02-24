#include "itemsettingsgui.h"
#include "ui_itemsettingsgui.h"

ItemSettingsGui::ItemSettingsGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemSettingsGui)
{
    ui->setupUi(this);
}

ItemSettingsGui::~ItemSettingsGui()
{
    delete ui;
}
