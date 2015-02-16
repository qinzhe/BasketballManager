#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(2);
    readTeams();

    for(auto &teamName: teamNames)
    {
        ui->teamOneBox->addItem(QString::fromStdString(teamName));
        ui->teamTwoBox->addItem(QString::fromStdString(teamName));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run()
{


}

void MainWindow::startGame()
{
    match->sim();
}

void MainWindow::readTeams()
{
    int posCount = 1;
    //open the document
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../teams.xml");

    //loop through the tree structure created of the xml
    for (pugi::xml_node team: doc.child("teams"))
    {
       teamNames.push_back(team.first_attribute().value());
    }
}

void MainWindow::on_playMatch_clicked()
{
    Team *teamOne = new Team(ui->teamOneBox->currentText().toStdString(), true);
    Team *teamTwo = new Team(ui->teamTwoBox->currentText().toStdString());
    receiver = new MatchReceiver(teamOne, ui->MatchWidget);
    match = new Match(teamOne, teamTwo, ui->MatchWidget);
    connect(ui->MatchWidget, SIGNAL(startGame()), this, SLOT(startGame()));
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_runSims_clicked()
{
    int simCount = ui->numSims->value();
    ui->simProgress->setMaximum(simCount);

    for(int i = 0; i < simCount; i++)
    {
        ui->simProgress->setValue(i);
        Team teamOne(ui->teamOneBox->currentText().toStdString());
        Team teamTwo(ui->teamTwoBox->currentText().toStdString());
        Match match(&teamOne, &teamTwo);
        match.setSimSpeed(0);
        match.sim();
        string filename = string("../stats/Game") + string(to_string(i)) + string(".csv");
        match.writeMatchStats(filename);
    }
    ui->simProgress->setValue(simCount);

}
