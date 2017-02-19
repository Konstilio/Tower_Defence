#include "gamestatewidget.h"
#include "ui_gamestatewidget.h"

GameStateWidget::GameStateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameStateWidget)
{
    ui->setupUi(this);
    
    connect(ui->m_StartButton, &QPushButton::clicked, this, &GameStateWidget::onStartClicked);
    connect(ui->m_PauseButton, &QPushButton::clicked, this, &GameStateWidget::onPauseClicked);
    ui->m_PauseButton->setDisabled(true);
}

GameStateWidget::~GameStateWidget()
{
    delete ui;
}

void GameStateWidget::onStartClicked()
{
    ui->m_StartButton->setText("Restart");
    ui->m_PauseButton->setEnabled(true);
    emit StartRequested();
}

void GameStateWidget::onPauseClicked()
{
    if (mp_Paused)
    {
        mp_Paused = false;
        ui->m_PauseButton->setText("Pause");
        emit ResumeRequested();
    }
    else
    {
        mp_Paused = true;
        ui->m_PauseButton->setText("Resume");
        emit PauseRequested();
    }
}

void GameStateWidget::onGameEnded()
{
    mp_Paused = false;
    ui->m_PauseButton->setText("Pause");
    ui->m_PauseButton->setDisabled(true);
    ui->m_StartButton->setText("Start");
}

