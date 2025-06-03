#include <QApplication>
#include "Repository.h"
#include "CSVWatchList.h"
#include "Service.h"
#include "GUI.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Repository repo{ "movies.txt" };
    CSVWatchList watchlist{ "watchlist.csv" };
    Service service{ repo, watchlist };

    GUI gui{ service };
    gui.setWindowTitle("Movie Management");
    gui.resize(800, 600);
    gui.show();

    return app.exec();
}
