#include <QDebug>
#include <QKeyEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&game_field);
    ui->graphicsView->show();

    ui->scoreBar->setVisible(false);

    screen_refersher = new QTimer(this);
    screen_refersher->setInterval(screen_refresh_interval);
    connect(screen_refersher, &QTimer::timeout, this, &MainWindow::refresh_screen);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_startButton_clicked() {
    // show in game ui
    ui->startButton->setVisible(false);
    ui->leaveButton->setVisible(false);
    ui->scoreBar->setVisible(true);

    // create player and enemys
    game_engine.spawn_player(game_field);
    game_engine.show_hp_bar(game_field);

    // start the screen refresher
    screen_refersher->start(10);
}

void MainWindow::on_leaveButton_clicked() {
    close();
}

void MainWindow::refresh_screen() {
    if (!game_engine.game_over()) {
        static int timer = 0;
        timer += 1;
        if (timer % 250 == 1){          //every 2.5 second
        game_engine.spawn_enemy(game_field);
        }
        game_engine.refresh_all_units_cooldown();
        game_engine.refresh_all_pos(up_pressed, down_pressed, left_pressed, right_pressed);
        game_engine.collision_detection(game_field);
        game_engine.refresh_hp(game_field);
        game_engine.refresh_score(ui->scoreBar);
        game_engine.refresh_units_bullet_view(game_field);
        if (space_pressed) game_engine.player_shoot(game_field);
    } else {
        //screen_refersher->stop();
    }
        game_engine.enemy_shoot(game_field);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;

    if (!event->isAutoRepeat()) {
        switch (event->key()) {
            case Qt::Key_Up:
                up_pressed = true;
                break;

            case Qt::Key_Down:
                down_pressed = true;
                break;

            case Qt::Key_Left:
                left_pressed = true;
                break;

            case Qt::Key_Right:
                right_pressed = true;
                break;

            case Qt::Key_Space:
                space_pressed = true;
                break;

            default:
                break;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;

    switch (event->key()) {
        case Qt::Key_Up:
            up_pressed = false;
            break;

        case Qt::Key_Down:
            down_pressed = false;
            break;

        case Qt::Key_Left:
            left_pressed = false;
            break;

        case Qt::Key_Right:
            right_pressed = false;
            break;

        case Qt::Key_Space:
            space_pressed = false;
            break;

        default:
            break;
    }
}
