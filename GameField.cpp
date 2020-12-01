#include "GameField.h"

#include <QDebug>

GameField::GameField()
{

}

void GameField::initial_render_unit(Unit* unit) {
    QPixmap unit_icon_image = QPixmap(unit->get_icon_path());
    QGraphicsPixmapItem* _view = addPixmap(unit_icon_image);
    _view->setOffset(unit->get_pos_x(), unit->get_pos_y());
    _view->setZValue(10);

    unit->register_view(_view);
}

void GameField::render_unit_update(Unit* unit) {
    unit->get_view()->setOffset(unit->get_pos_x(), unit->get_pos_y());
}

void GameField::remove_dead_unit_view(QGraphicsPixmapItem* view) {
    removeItem(view);
}

void GameField::initial_render_bullet(Bullet* bullet, bool is_friendly) {
    QPixmap bullet_icon_image;
    if (is_friendly) {
        bullet_icon_image = QPixmap(bullet->get_frienly_fire_icon_path());
    } else {
        bullet_icon_image = QPixmap(bullet->get_enemy_fire_icon_path());
    }
    QGraphicsPixmapItem* _view = addPixmap(bullet_icon_image);
    _view->setOffset(bullet->get_pos_x(), bullet->get_pos_y());
    _view->setZValue(12);

    bullet->register_view(_view);
}

void GameField::render_bullet_update(QList<Bullet*>& bullet_list) {
    if (!bullet_list.isEmpty()) {
        for (QList<Bullet*>::iterator bullet = bullet_list.begin(); bullet != bullet_list.end(); ++bullet) {
            if ((*bullet)->get_pos_y() == -(*bullet)->get_height()) {
                removeItem((*bullet)->get_view());
                delete (*bullet)->get_view();
                bullet_list.removeOne((*bullet));
            } else {
                (*bullet)->get_view()->setOffset((*bullet)->get_pos_x(), (*bullet)->get_pos_y());
            }
        }
    }
}

void GameField::initial_render_player_hp(int MAX_HP) {
    if (MAX_HP == 0) return;

    QString hp_icon_path = "://images/heart%1.png";
    QPixmap hp_icon_image;
    QGraphicsPixmapItem* view;
    for (int i = 0; i < MAX_HP ; i++) {
        hp_icon_image = QPixmap(hp_icon_path.arg(i%2));
        view = addPixmap(hp_icon_image);
        view->setOffset(i*20+10, 100);
        view->setZValue(20);
        hp_bar << view;
    }
}

void GameField::render_player_hp_update() {
    removeItem(hp_bar.last());
    delete hp_bar.takeLast();
}
