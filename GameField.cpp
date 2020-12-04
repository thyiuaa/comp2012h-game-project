#include "GameField.h"

void GameField::initial_render_player_hp(int MAX_HP) {
    if (MAX_HP == 0) return;

    QString hp_icon_path = "://images/heart%1.png";
    QPixmap hp_icon_image;
    QGraphicsPixmapItem* view;
    for (int i = 0; i < MAX_HP ; i++) {
        hp_icon_image = QPixmap(hp_icon_path.arg(i%2));
        view = addPixmap(hp_icon_image);
        view->setOffset(i*16+10, 50);
        view->setZValue(20);
        hp_bar << view;
    }
}

void GameField::render_player_hp_update() {
    removeItem(hp_bar.last());
    delete hp_bar.takeLast();
}

void GameField::initial_render_unit(Unit* unit) {
    QPixmap unit_icon_image = QPixmap(unit->get_icon_path());
    QGraphicsPixmapItem* _view = addPixmap(unit_icon_image);
    _view->setOffset(unit->get_pos_x(), unit->get_pos_y());
    _view->setZValue(10);

    unit->register_view(_view);
}

void GameField::initial_render_bullet(Bullet* bullet, bool from_player) {
    QPixmap bullet_icon_image;
    if (from_player) {
        bullet_icon_image = QPixmap(bullet->get_frienly_fire_icon_path());
    } else {
        bullet_icon_image = QPixmap(bullet->get_enemy_fire_icon_path());
    }
    QGraphicsPixmapItem* _view = addPixmap(bullet_icon_image);
    _view->setOffset(bullet->get_pos_x(), bullet->get_pos_y());
    _view->setZValue(12);

    bullet->register_view(_view);
}

void GameField::render_player_pos_update(Player* player) {
    if(player == nullptr || player->get_view() == nullptr) return;
    player->get_view()->setOffset(player->get_pos_x(), player->get_pos_y());
}

void GameField::remove_and_delete_view(QGraphicsPixmapItem* view) {
    removeItem(view);
    delete view;
}
