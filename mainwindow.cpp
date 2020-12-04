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
    game_field.addPixmap(QPixmap("://images/bg.jpg"))->setZValue(-1);
    connect(&exit_confirm_window, SIGNAL(close_mainwindow_signal()), this, SLOT(close())); // close the game if the player sure to leave
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (exit_confirm_window.get_leave_game() == false) {
        event->ignore();
        exit_confirm_window.show();
    } else {
        event->accept();
    }
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

void MainWindow::on_startButton_clicked() {
    // set up screen refresher
    screen_refresher = new QTimer(this);
    screen_refresher->setInterval(SCREEN_REFRESH_INTERVAL);
    connect(screen_refresher, SIGNAL(timeout()), this, SLOT(refresh_screen()));
    connect(&exit_confirm_window, SIGNAL(show_signal()), screen_refresher, SLOT(stop())); // pause the game when the exit confirm shows
    connect(&exit_confirm_window, SIGNAL(close_signal()), screen_refresher, SLOT(start())); // resume the game when the exit confirm closes

    // show in game ui
    ui->startButton->setVisible(false);
    ui->leaveButton->setVisible(false);
    ui->scoreBar->setVisible(true);

    // create player
    game_engine.reset_total_score(ui->scoreBar);
    game_engine.spawn_player(game_field);
    game_engine.show_hp_bar(game_field);

    // start the screen refresher
    screen_refresher->start(10);
}

void MainWindow::on_leaveButton_clicked() {
    close();
}

void MainWindow::refresh_screen() {
    if (!game_engine.game_over()) {
        game_engine.spawn_enemy(game_field);
        game_engine.refresh_all_units_cooldown();
        game_engine.refresh_all_pos(up_pressed, down_pressed, left_pressed, right_pressed);
        if (space_pressed) game_engine.player_shoot(game_field);
        game_engine.enemy_shoot(game_field);
        game_engine.collision_detection(game_field);
        game_engine.refresh_units_bullet_view(game_field);
        game_engine.refresh_hp(game_field);
        game_engine.refresh_score(ui->scoreBar);
    } else {
        // destroy the refresher
        screen_refresher->stop();
        delete screen_refresher;

        // destroy player, enemy, and bullets

        // show buttons
        ui->startButton->setText("Play again!");
        ui->startButton->setVisible(true);
        if(game_engine.show_game_over_screen(game_field)){
            ui->leaveButton->setText("haha! You Win!\nLeave Game");
        } else {
            ui->leaveButton->setText("You Lose >_<\nLeave Game");
        }
        ui->leaveButton->setVisible(true);
    }
}
