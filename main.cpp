#include <QApplication>
#include "SortingVisualizer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SortingVisualizer visualizer;
    visualizer.setWindowTitle("Sorting Algorithm Visualizer");
    visualizer.resize(800,600);
    visualizer.show();

    return app.exec();
}
