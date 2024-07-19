#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <thread>
#include <sstream>
#include <iostream>
#include <chrono>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTimer(int minutes, int seconds)
{

}

void MainWindow::on_startButton_clicked()
{

}

