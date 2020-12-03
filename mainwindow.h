#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "GameField.h"
#include "GameEngine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// handle from user, i.e. keyboard control, menuclicking
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_leaveButton_clicked();

private:
    Ui::MainWindow *ui;

    GameEngine game_engine; // interact with game element through the engine
    GameField game_field; // the display area of the game

    const int SCREEN_REFRESH_INTERVAL {10}; // millisecond
    QTimer* screen_refresher; // this will refresh the screen for every SCREEN_REFRESH_INTERVAL millisecond
    void refresh_screen(); // action performed by the refresher
    int enemy_spawn_timer {0}; // number of frames passed since the game start
    const int ENEMY_SPAWN_INTERVAL {150}; // number of frames between each enemy spawn

    bool up_pressed {false}, down_pressed {false}, left_pressed {false}, right_pressed {false}, space_pressed {false}; // indicate keypresses
    void keyPressEvent(QKeyEvent *event); // set the above corresponding keypress to true
    void keyReleaseEvent(QKeyEvent *event); // set the above corresponding keypress to false
};
#endif // MAINWINDOW_H
