#ifndef ITEMSETTINGSGUI_H
#define ITEMSETTINGSGUI_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include "bot.h"
#include "item.h"
#include "player.h"

namespace Ui {
class ItemSettingsGui;
}

class ItemSettingsGui : public QDialog
{
    Q_OBJECT

public:
    ItemSettingsGui(QWidget *parent = 0);
    explicit ItemSettingsGui(Player *player,QWidget *parent = 0);
    explicit ItemSettingsGui(Bot *bot,QWidget *parent = 0);
    explicit ItemSettingsGui(Item *item,QWidget *parent = 0);
    ~ItemSettingsGui();
private slots:
    void on_ButtonOption_accepted();
    void on_ButtonOption_rejected();

private:
    Ui::ItemSettingsGui *ui;
    Player* player;
    Bot* bot;
    Item* item;
};

#endif // ITEMSETTINGSGUI_H
