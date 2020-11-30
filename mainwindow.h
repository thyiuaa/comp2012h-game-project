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
    friend class GameField;
    Ui::MainWindow *ui;

    GameEngine game_engine;
    GameField game_field;
    QTimer* screen_refersher;
    const int screen_refresh_interval{10}; // millisecond
    void refresh_screen();

    bool up_pressed{false}, down_pressed{false}, left_pressed{false}, right_pressed{false}, space_pressed{false};
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
